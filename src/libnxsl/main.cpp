/*
** NetXMS - Network Management System
** NetXMS Scripting Language Interpreter
** Copyright (C) 2003-2013 Victor Kirhenshtein
**
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU Lesser General Public License as published by
** the Free Software Foundation; either version 3 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU Lesser General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
**
** File: main.cpp
**
**/

#include "libnxsl.h"

/**
 * Interface to compiler
 */
NXSL_Program LIBNXSL_EXPORTABLE *NXSLCompile(const TCHAR *source, TCHAR *errorMessage, size_t errorMessageLen, int *errorLine)
{
   NXSL_Compiler compiler;
   NXSL_Program *pResult = compiler.compile(source);
   if (pResult == NULL)
   {
      if (errorMessage != NULL)
         _tcslcpy(errorMessage, compiler.getErrorText(), errorMessageLen);
      if (errorLine != NULL)
         *errorLine = compiler.getErrorLineNumber();
   }
   return pResult;
}

/**
 * Compile script and create VM
 */
NXSL_VM LIBNXSL_EXPORTABLE *NXSLCompileAndCreateVM(const TCHAR *source, TCHAR *errorMessage, size_t errorMessageLen, NXSL_Environment *env)
{
   NXSL_Program *p = NXSLCompile(source, errorMessage, errorMessageLen, NULL);
   if (p == NULL)
   {
      delete env;
      return NULL;
   }

   NXSL_VM *vm = new NXSL_VM(env);
   if (!vm->load(p))
   {
      if (errorMessage != NULL)
      {
         _tcslcpy(errorMessage, vm->getErrorText(), errorMessageLen);
      }
      delete vm;
      vm = NULL;
   }
   delete p;
   return vm;
}

/**
 * Load file into memory
 */
TCHAR LIBNXSL_EXPORTABLE *NXSLLoadFile(const TCHAR *pszFileName, UINT32 *pdwFileSize)
{
   int fd, iBufPos, iNumBytes, iBytesRead;
   char *pBuffer = NULL;
   struct stat fs;

   fd = _topen(pszFileName, O_RDONLY | O_BINARY);
   if (fd != -1)
   {
      if (fstat(fd, &fs) != -1)
      {
         pBuffer = (char *)malloc(fs.st_size + 1);
         if (pBuffer != NULL)
         {
            *pdwFileSize = fs.st_size;
            for(iBufPos = 0; iBufPos < fs.st_size; iBufPos += iBytesRead)
            {
               iNumBytes = std::min(16384, (int)fs.st_size - iBufPos);
               if ((iBytesRead = _read(fd, &pBuffer[iBufPos], iNumBytes)) < 0)
               {
                  free(pBuffer);
                  pBuffer = NULL;
                  break;
               }
            }
				if (pBuffer != NULL)
				{
					for(iBufPos = 0; iBufPos < fs.st_size; iBufPos++)
						if (pBuffer[iBufPos] == 0)
							pBuffer[iBufPos] = ' ';
					pBuffer[fs.st_size] = 0;
				}
         }
      }
      _close(fd);
   }

#ifdef UNICODE
	if (pBuffer == NULL)
		return NULL;

	WCHAR *ucBuffer = WideStringFromUTF8String(pBuffer);
	free(pBuffer);
	return ucBuffer;
#else
   return pBuffer;
#endif
}

#ifdef _WIN32

/**
 * DLL entry point
 */
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
   if (dwReason == DLL_PROCESS_ATTACH)
      DisableThreadLibraryCalls(hInstance);
   return TRUE;
}

#endif   /* _WIN32 */
