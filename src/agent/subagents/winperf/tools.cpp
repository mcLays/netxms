/*
** Windows Performance NetXMS subagent
** Copyright (C) 2004, 2005, 2006, 2007 Victor Kirhenshtein
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
** File: tools.cpp
**
**/

#include "winperf.h"


//
// Constants
//

#define MAX_ELEMENT_LENGTH		1024


//
// Static data
//

static COUNTER_INDEX *m_pCounterList = NULL;
static DWORD m_dwNumCounters = 0;


//
// Get error text for PDH functions
//

TCHAR *GetPdhErrorText(DWORD dwError, TCHAR *pszBuffer, int iBufferSize)
{
   TCHAR *pszMsg;

   if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | 
                     FORMAT_MESSAGE_FROM_HMODULE | 
                     FORMAT_MESSAGE_IGNORE_INSERTS,
                     GetModuleHandle(_T("PDH.DLL")), dwError,
                     MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
                     (LPTSTR)&pszMsg, 0, NULL)>0)
   {
      TranslateStr(pszMsg, _T("\r\n"), _T(""));
      nx_strncpy(pszBuffer, pszMsg, iBufferSize);
      LocalFree(pszMsg);
   }
   else
   {
      GetSystemErrorText(dwError, pszBuffer, iBufferSize);
   }
   return pszBuffer;
}


//
// Report PDH error to master agent's log
//

void ReportPdhError(TCHAR *pszFunction, TCHAR *pszPdhCall, PDH_STATUS dwError)
{
   TCHAR szBuffer[1024];

   AgentWriteLog(EVENTLOG_WARNING_TYPE, _T("%s: PDH Error %08X in call to %s (%s)"), 
                   pszFunction, dwError, pszPdhCall, GetPdhErrorText(dwError, szBuffer, 1024));
}


//
// Create index of counters
//

void CreateCounterIndex(TCHAR *pData)
{
	TCHAR *pCurr;

	for(pCurr = pData; *pCurr != 0; )
	{
		m_pCounterList = (COUNTER_INDEX *)realloc(m_pCounterList, sizeof(COUNTER_INDEX) * (m_dwNumCounters + 1));
		m_pCounterList[m_dwNumCounters].dwIndex = _tcstoul(pCurr, NULL, 10);
		pCurr += _tcslen(pCurr) + 1;
		m_pCounterList[m_dwNumCounters].pszName = _tcsdup(pCurr);
		pCurr += _tcslen(pCurr) + 1;
		m_dwNumCounters++;
	}
}


//
// Translate single counter name's element
//

static BOOL TranslateElement(TCHAR *pszText)
{
	DWORD i, dwSize;

	for(i = 0; i < m_dwNumCounters; i++)
	{
		if (!_tcsicmp(m_pCounterList[i].pszName, pszText))
		{
			dwSize = MAX_ELEMENT_LENGTH * sizeof(TCHAR);
			return PdhLookupPerfNameByIndex(NULL, m_pCounterList[i].dwIndex, pszText, &dwSize) == ERROR_SUCCESS;
		}
	}
	return FALSE;
}


//
// Translate counter name from English to localized
//

BOOL TranslateCounterName(const TCHAR *pszName, TCHAR *pszOut)
{
	const TCHAR *pCurr = pszName;
	const TCHAR *pSlash, *pBrace, *pNext;
	TCHAR szTemp[MAX_ELEMENT_LENGTH];
	BOOL bs1, bs2;
	int nLen;

	// Generic counter name looks like following:
	// \\machine\object(parent/instance#index)\counter
	// where machine, parent, instance, and index parts may be omited.
	// We should translate object and counter parts if possible.

	if (*pCurr != _T('\\'))
		return FALSE;	// Counter name should always start with "\"  or "\\"
	pCurr++;

	// Skip machine name
	if (*pCurr == _T('\\'))
	{
		pCurr++;
		pCurr = _tcschr(pCurr, _T('\\'));
		if (pCurr == NULL)
			return FALSE;	// Object name missing
		pCurr++;
	}
	memcpy(pszOut, pszName, (pCurr - pszName) * sizeof(TCHAR));
	pszOut[pCurr - pszName] = 0;

	// Object name ends by \ or (
	pSlash = _tcschr(pCurr, _T('\\'));
	pBrace = _tcschr(pCurr, _T('('));
	if (pSlash == NULL)
		return FALSE;
	if ((pSlash < pBrace) || (pBrace == NULL))
	{
		if (pSlash - pCurr >= MAX_ELEMENT_LENGTH)
			return FALSE;
		memcpy(szTemp, pCurr, (pSlash - pCurr) * sizeof(TCHAR));
		szTemp[pSlash - pCurr] = 0;
		pCurr = pSlash;
		pNext = pSlash + 1;
	}
	else
	{
		if (pBrace - pCurr >= MAX_ELEMENT_LENGTH)
			return FALSE;
		memcpy(szTemp, pCurr, pBrace - pCurr);
		szTemp[pBrace - pCurr] = 0;
		pCurr = pBrace;
		pNext = _tcschr(pCurr, _T(')'));
		if (pNext == NULL)
			return FALSE;
		pNext++;
		if (*pNext != _T('\\'))
			return FALSE;
		pNext++;
	}
	bs1 = TranslateElement(szTemp);
	_tcscat(pszOut, szTemp);
	nLen = (int)_tcslen(pszOut);
	memcpy(&pszOut[nLen], pCurr, (pNext - pCurr) * sizeof(TCHAR));
	pszOut[nLen + (pNext - pCurr)] = 0;
	pCurr = pNext;

	// Translate counter name
	nx_strncpy(szTemp, pCurr, MAX_ELEMENT_LENGTH);
	bs2 = TranslateElement(szTemp);
	_tcscat(pszOut, szTemp);

	return bs1 || bs2;
}
