/* 
** NetXMS - Network Management System
** Utility Library
** Copyright (C) 2003 Victor Kirhenshtein
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
** $module: main.cpp
**
**/

#include "libnetxms.h"


//
// Swap byte order in 64-bit integer
//

#if defined(_WIN32) || !defined(HAVE___BSWAP_64)

QWORD LIBNETXMS_EXPORTABLE __bswap_64(QWORD qwVal)
{
   QWORD qwResult;
   BYTE *sptr = (BYTE *)&qwVal;
   BYTE *dptr = (BYTE *)&qwResult + 7;
   int i;

   for(i = 0; i < 8; i++, sptr++, dptr--)
      *dptr = *sptr;

   return qwResult;
}

#endif


//
// strupr() implementation for non-windows platforms
//

#ifndef _WIN32

void LIBNETXMS_EXPORTABLE strupr(char *in)
{
	char *p = in;

	if (in == NULL) 
   { 
		return;
	}
	
	for (; *p != 0; p++) 
   {
		// TODO: check/set locale
		*p = toupper(*p);
	}
}

#endif


//
// DLL entry point
//

#ifdef _WIN32

BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
   return TRUE;
}

#endif   /* _WIN32 */
