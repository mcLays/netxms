/* 
** NetXMS - Network Management System
** Copyright (C) 2003, 2004 Victor Kirhenshtein
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
** $module: acl.cpp
**
**/

#include "nms_core.h"


//
// Access list constructor
//

AccessList::AccessList()
{
   m_pElements = NULL;
   m_dwNumElements = 0;
   m_hMutex = MutexCreate();
}


//
// Destructor
//

AccessList::~AccessList()
{
   if (m_pElements != NULL)
      free(m_pElements);
   MutexDestroy(m_hMutex);
}


//
// Add element to list
//

void AccessList::AddElement(DWORD dwObjectId, DWORD dwAccessRights)
{
   DWORD i;

   Lock();
   for(i = 0; i < m_dwNumElements; i++)
      if (m_pElements[i].dwObjectId == dwObjectId)    // Object already exist in list
      {
         m_pElements[i].dwAccessRights = dwAccessRights;
         break;
      }

   if (i == m_dwNumElements)
   {
      m_pElements = (ACL_ELEMENT *)realloc(m_pElements, sizeof(ACL_ELEMENT) * (m_dwNumElements + 1));
      m_pElements[m_dwNumElements].dwObjectId = dwObjectId;
      m_pElements[m_dwNumElements].dwAccessRights = dwAccessRights;
      m_dwNumElements++;
   }
   Unlock();
}


//
// Delete element from list
//

void AccessList::DeleteElement(DWORD dwObjectId)
{
   DWORD i;

   Lock();
   for(i = 0; i < m_dwNumElements; i++)
      if (m_pElements[i].dwObjectId == dwObjectId)
      {
         m_dwNumElements--;
         memmove(&m_pElements[i], &m_pElements[i + 1], sizeof(ACL_ELEMENT) * (m_dwNumElements - i));
         break;
      }
   Unlock();
}


//
// Retrieve access rights for specific user object
// Return TRUE on success and stores access rights to specific location
// If user doesn't have explicit rights or via group, returns FALSE
//

BOOL AccessList::GetUserRights(DWORD dwUserId, DWORD *pdwAccessRights)
{
   DWORD i;
   BOOL bFound = FALSE;

   // Check for explicit rights
   for(i = 0; i < m_dwNumElements; i++)
      if (m_pElements[i].dwObjectId == dwUserId)
      {
         *pdwAccessRights = m_pElements[i].dwAccessRights;
         bFound = TRUE;
         break;
      }

   if (!bFound)
   {
      *pdwAccessRights = 0;   // Default: no access
      for(i = 0; i < m_dwNumElements; i++)
         if (m_pElements[i].dwObjectId & GROUP_FLAG)
         {
            if (CheckUserMembership(dwUserId, m_pElements[i].dwObjectId))
            {
               *pdwAccessRights |= m_pElements[i].dwAccessRights;
               bFound = TRUE;
            }
         }
   }

   return bFound;
}


//
// Enumerate all elements
//

void AccessList::EnumerateElements(void (* pHandler)(DWORD, DWORD, void *), void *pArg)
{
   DWORD i;

   Lock();
   for(i = 0; i < m_dwNumElements; i++)
      pHandler(m_pElements[i].dwObjectId, m_pElements[i].dwAccessRights, pArg);
   Unlock();
}
