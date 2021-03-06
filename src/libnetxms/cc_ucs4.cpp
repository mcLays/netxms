/*
 ** NetXMS - Network Management System
 ** Copyright (C) 2003-2018 Raden Solutions
 **
 ** This program is free software; you can redistribute it and/or modify
 ** it under the terms of the GNU Lesser General Public License as published
 ** by the Free Software Foundation; either version 3 of the License, or
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
 ** File: cc_ucs4.cpp
 **
 **/

#include "libnetxms.h"
#include "unicode_cc.h"

/**
 * Convert UCS-4 to UCS-2
 */
int LIBNETXMS_EXPORTABLE ucs4_to_ucs2(const UCS4CHAR *src, int srcLen, UCS2CHAR *dst, int dstLen)
{
   int len = static_cast<int>((srcLen == -1) ? ucs4_strlen(src) : srcLen);
   int scount = 0, dcount = 0;
   const UCS4CHAR *s = src;
   UCS2CHAR *d = dst;
   while((scount < len) && (dcount < dstLen))
   {
      UCS4CHAR ch = *s++;
      scount++;
      if (ch <= 0xFFFF)
      {
         *d++ = static_cast<UCS2CHAR>(ch);
         dcount++;
      }
      else if (ch <= 0x10FFFF)
      {
         if (dcount > dstLen - 2)
            break;   // no enough space in destination buffer
         ch -= 0x10000;
         *d++ = static_cast<UCS2CHAR>((ch >> 10) | 0xD800);
         *d++ = static_cast<UCS2CHAR>((ch & 0x3FF) | 0xDC00);
         dcount += 2;
      }
   }

   if (srcLen != -1)
      return dcount;
   if (dcount == dstLen)
      dcount--;
   dst[dcount] = 0;
   return dcount;
}

/**
 * Calculate length in characters of given UCS-4 string in UCS-2 encoding (including terminating 0 byte)
 */
int LIBNETXMS_EXPORTABLE ucs4_ucs2len(const UCS4CHAR *src, int srcLen)
{
   int len = static_cast<int>((srcLen == -1) ? ucs4_strlen(src) : srcLen);
   int dcount = len + 1;
   const UCS4CHAR *s = src;
   while(len-- > 0)
   {
      UCS4CHAR ch = *s++;
      if (ch > 0xFFFF)
         dcount++;
   }
   return dcount;
}

/**
 * Convert UCS-4 to UTF-8
 */
int LIBNETXMS_EXPORTABLE ucs4_to_utf8(const UCS4CHAR *src, int srcLen, char *dst, int dstLen)
{
   int len = static_cast<int>((srcLen == -1) ? ucs4_strlen(src) : srcLen);
   int scount = 0, dcount = 0;
   const UCS4CHAR *s = src;
   char *d = dst;
   while((scount < len) && (dcount < dstLen))
   {
      UCS4CHAR ch = *s++;
      scount++;
      if (ch <= 0x7F)
      {
         *d++ = static_cast<char>(ch);
         dcount++;
      }
      else if (ch <= 0x7FF)
      {
         if (dcount > dstLen - 2)
            break;   // no enough space in destination buffer
         *d++ = static_cast<char>((ch >> 6) | 0xC0);
         *d++ = static_cast<char>((ch & 0x3F) | 0x80);
         dcount += 2;
      }
      else if (ch <= 0xFFFF)
      {
         if (dcount > dstLen - 3)
            break;   // no enough space in destination buffer
         *d++ = static_cast<char>((ch >> 12) | 0xE0);
         *d++ = static_cast<char>(((ch >> 6) & 0x3F) | 0x80);
         *d++ = static_cast<char>((ch & 0x3F) | 0x80);
         dcount += 3;
      }
      else if (ch <= 0x10FFFF)
      {
         if (dcount > dstLen - 4)
            break;   // no enough space in destination buffer
         *d++ = static_cast<char>((ch >> 18) | 0xF0);
         *d++ = static_cast<char>(((ch >> 12) & 0x3F) | 0x80);
         *d++ = static_cast<char>(((ch >> 6) & 0x3F) | 0x80);
         *d++ = static_cast<char>((ch & 0x3F) | 0x80);
         dcount += 4;
      }
   }

   if (srcLen != -1)
      return dcount;
   if (dcount == dstLen)
      dcount--;
   dst[dcount] = 0;
   return dcount;
}

/**
 * Calculate length in bytes of given UCS-4 string in UTF-8 encoding (including terminating 0 byte)
 */
int LIBNETXMS_EXPORTABLE ucs4_utf8len(const UCS4CHAR *src, int srcLen)
{
   int len = static_cast<int>((srcLen == -1) ? ucs4_strlen(src) : srcLen);
   int dcount = 1;
   const UCS4CHAR *s = src;
   while(len-- > 0)
   {
      UCS4CHAR ch = *s++;
      if (ch <= 0x7F)
      {
         dcount++;
      }
      else if (ch <= 0x7FF)
      {
         dcount += 2;
      }
      else if (ch <= 0xFFFF)
      {
         dcount += 3;
      }
      else if (ch <= 0x10FFFF)
      {
         dcount += 4;
      }
   }
   return dcount;
}

#if defined(_WIN32)

/**
 * Convert UCS-4 to multibyte
 */
int LIBNETXMS_EXPORTABLE ucs4_to_mb(const UCS4CHAR *src, int srcLen, char *dst, int dstLen)
{
   int len = (srcLen < 0) ? (int)ucs4_strlen(src) + 1 : srcLen;
   WCHAR *buffer = (len <= 32768) ? (WCHAR *)alloca(len * sizeof(WCHAR)) : (WCHAR *)malloc(len * sizeof(WCHAR));
   ucs4_to_ucs2(src, srcLen, buffer, len);
   int ret = WideCharToMultiByte(CP_ACP, WC_DEFAULTCHAR | WC_COMPOSITECHECK, buffer, srcLen, dst, dstLen, NULL, NULL);
   if (len > 32768)
      free(buffer);
   return ret;
}

#elif !defined(UNICODE_UCS4)

/**
 * Convert UCS-4 to multibyte using stub (no actual conversion for character codes above 0x007F)
 */
static int __internal_ucs4_to_mb(const UCS4CHAR *src, int srcLen, char *dst, int dstLen)
{
   const UCS4CHAR *psrc;
   char *pdst;
   int pos, size;

   size = (srcLen == -1) ? (int) ucs4_strlen(src) : srcLen;
   if (size >= dstLen)
      size = dstLen - 1;

   for(psrc = src, pos = 0, pdst = dst; pos < size; pos++, psrc++, pdst++)
      *pdst = (*psrc < 256) ? (char) (*psrc) : '?';
   *pdst = 0;

   return size;
}

/**
 * Convert UCS-4 to multibyte
 */
int LIBNETXMS_EXPORTABLE ucs4_to_mb(const UCS4CHAR *src, int srcLen, char *dst, int dstLen)
{
#if HAVE_ICONV && !defined(__DISABLE_ICONV)
   iconv_t cd;
   const char *inbuf;
   char *outbuf;
   size_t count, inbytes, outbytes;

   cd = IconvOpen(g_cpDefault, UCS4_CODEPAGE_NAME);
   if (cd == (iconv_t) (-1))
   {
      return __internal_ucs4_to_mb(src, srcLen, dst, dstLen);
   }

   inbuf = (const char *) src;
   inbytes = ((srcLen == -1) ? ucs4_strlen(src) + 1 : (size_t) srcLen) * sizeof(UCS4CHAR);
   outbuf = (char *) dst;
   outbytes = (size_t) dstLen;
   count = iconv(cd, (ICONV_CONST char **) &inbuf, &inbytes, &outbuf, &outbytes);
   IconvClose(cd);

   if (count == (size_t) - 1)
   {
      if (errno == EILSEQ)
      {
         count = (dstLen * sizeof(char) - outbytes) / sizeof(char);
      }
      else
      {
         count = 0;
      }
   }
   if ((srcLen == -1) && (outbytes >= sizeof(char)))
   {
      *((char *) outbuf) = 0;
   }

   return (int)count;
#else
   return __internal_ucs4_to_mb(src, srcLen, dst, dstLen);
#endif
}

#endif
