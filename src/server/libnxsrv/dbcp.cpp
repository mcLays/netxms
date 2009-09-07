/* 
** NetXMS - Network Management System
** Server Library
** Copyright (C) 2008 Alex Kirhenshtein
**
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
**
** File: dbcp.cpp
**
**/

#include "libnxsrv.h"

static int m_basePoolSize;
static int m_maxPoolSize;
static int m_currentPoolSize;
static int m_cooldownTime;

static MUTEX m_poolAccessMutex;

static DB_HANDLE *m_dbHandles;
static bool *m_dbHandlesInUseMarker;
static time_t *m_dbHandleLastAccessTime;

static void DBConnectionPoolPopulate()
{
	MutexLock(m_poolAccessMutex, INFINITE);

	for (int i = 0; i < m_basePoolSize; i++)
	{
		m_dbHandles[i] = DBConnect();
	}

	MutexUnlock(m_poolAccessMutex);
}

static void DBConnectionPoolShrink()
{
	MutexLock(m_poolAccessMutex, INFINITE);

	for (int i = 0; i < m_maxPoolSize; i++)
	{
		if (m_currentPoolSize <= m_basePoolSize)
		{
			break;
		}

		if (!m_dbHandlesInUseMarker[i] && m_dbHandles[i] != NULL)
		{
			if ((time(NULL) - m_dbHandleLastAccessTime[i]) > m_cooldownTime)
			{
				DBDisconnect(m_dbHandles[i]);
				m_dbHandles[i] = NULL;
				m_currentPoolSize--;
			}
		}
	}

	MutexUnlock(m_poolAccessMutex);
}

bool LIBNXSRV_EXPORTABLE DBConnectionPoolStartup(int basePoolSize, int maxPoolSize, int cooldownTime)
{
	m_basePoolSize = basePoolSize;
	m_currentPoolSize = basePoolSize;
	m_maxPoolSize = maxPoolSize;
	m_cooldownTime = cooldownTime;

	m_poolAccessMutex = MutexCreate();

	m_dbHandles = new DB_HANDLE[maxPoolSize];
	m_dbHandlesInUseMarker = new bool[maxPoolSize];
	m_dbHandleLastAccessTime = new time_t[maxPoolSize];

	for (int i = 0; i < m_maxPoolSize; i++)
	{
		m_dbHandles[i] = NULL;
		m_dbHandlesInUseMarker[i] = false;
		m_dbHandleLastAccessTime[i] = 0;
	}

	DBConnectionPoolPopulate();

	DbgPrintf(1, "Database Connection Pool initialized");

	return true;
}

void LIBNXSRV_EXPORTABLE DBConnectionPoolShutdown()
{
	MutexDestroy(m_poolAccessMutex);

	for (int i = 0; i < m_maxPoolSize; i++)
	{
		if (m_dbHandles[i] != NULL)
		{
			DBDisconnect(m_dbHandles[i]);
		}
	}

	delete m_dbHandles;
	delete m_dbHandlesInUseMarker;
	delete m_dbHandleLastAccessTime;
	
	DbgPrintf(1, "Database Connection Pool terminated");

}

DB_HANDLE LIBNXSRV_EXPORTABLE DBConnectionPoolAcquireConnection()
{
	MutexLock(m_poolAccessMutex, INFINITE);

	DB_HANDLE handle = NULL;
	for (int i = 0; i < m_maxPoolSize; i++)
	{
		if (m_dbHandles[i] != NULL && !m_dbHandlesInUseMarker[i])
		{
			handle = m_dbHandles[i];
			m_dbHandlesInUseMarker[i] = true;
			break;
		}
	}

	if (handle == NULL && m_currentPoolSize < m_maxPoolSize)
	{
		for (int i = 0; i < m_maxPoolSize; i++)
		{
			if (m_dbHandles[i] == NULL)
			{
				m_dbHandles[i] = DBConnect();
				m_currentPoolSize++;

				handle = m_dbHandles[i];
				m_dbHandlesInUseMarker[i] = true;
				break;
			}
		}
	}

	MutexUnlock(m_poolAccessMutex);

	DBConnectionPoolShrink();

	return handle;
}

void LIBNXSRV_EXPORTABLE DBConnectionPoolReleaseConnection(DB_HANDLE connection)
{
	MutexLock(m_poolAccessMutex, INFINITE);

	DB_HANDLE handle = NULL;
	for (int i = 0; i < m_maxPoolSize; i++)
	{
		if (m_dbHandles[i] == connection)
		{
			m_dbHandlesInUseMarker[i] = false;
			m_dbHandleLastAccessTime[i] = time(NULL);
			break;
		}
	}

	MutexUnlock(m_poolAccessMutex);

	DBConnectionPoolShrink();

}
