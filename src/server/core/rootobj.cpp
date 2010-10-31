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
** $module: rootobj.cpp
**
**/

#include "nxcore.h"


//
// Service root class default constructor
//

ServiceRoot::ServiceRoot()
            :UniversalRoot()
{
   m_dwId = BUILTIN_OID_SERVICEROOT;
   strcpy(m_szName, "All Services");
}


//
// Service root class destructor
//

ServiceRoot::~ServiceRoot()
{
}


//
// Template root class default constructor
//

TemplateRoot::TemplateRoot()
             :UniversalRoot()
{
   m_dwId = BUILTIN_OID_TEMPLATEROOT;
   strcpy(m_szName, "Templates");
}


//
// Template root class destructor
//

TemplateRoot::~TemplateRoot()
{
}


//
// Redefined status calculation for template root
//

void TemplateRoot::CalculateCompoundStatus(BOOL bForcedRecalc)
{
   m_iStatus = STATUS_NORMAL;
}


//
// Policy root class default constructor
//

PolicyRoot::PolicyRoot()
           :UniversalRoot()
{
   m_dwId = BUILTIN_OID_POLICYROOT;
   strcpy(m_szName, "Policies");
}


//
// Policy root class destructor
//

PolicyRoot::~PolicyRoot()
{
}


//
// Redefined status calculation for policy root
//

void PolicyRoot::CalculateCompoundStatus(BOOL bForcedRecalc)
{
   m_iStatus = STATUS_NORMAL;
}


//
// Network maps root class default constructor
//

NetworkMapRoot::NetworkMapRoot()
               :UniversalRoot()
{
   m_dwId = BUILTIN_OID_NETWORKMAPROOT;
   strcpy(m_szName, "Network Maps");
}


//
// Network maps root class destructor
//

NetworkMapRoot::~NetworkMapRoot()
{
}


//
// Redefined status calculation for network maps root
//

void NetworkMapRoot::CalculateCompoundStatus(BOOL bForcedRecalc)
{
   m_iStatus = STATUS_NORMAL;
}
