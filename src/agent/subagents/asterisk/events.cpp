/*
** NetXMS Asterisk subagent
** Copyright (C) 2004-2018 Victor Kirhenshtein
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
** File: events.cpp
**
**/

#include "asterisk.h"

/**
 * Process hangup event
 */
void AsteriskSystem::processHangup(AmiMessage *msg)
{
   TCHAR peer[128];
   PeerFromChannel(msg->getTag("Channel"), peer, 128);
   EventCounters *peerEventCounters = ((peer[0] != 0) ? m_peerEventCounters.get(peer) : NULL);
   if ((peer[0] != 0) && (peerEventCounters == NULL))
   {
      peerEventCounters = new EventCounters;
      memset(peerEventCounters, 0, sizeof(EventCounters));
      m_peerEventCounters.set(peer, peerEventCounters);
   }

   int cause = msg->getTagAsInt("Cause");
   switch(cause)
   {
      case 2:
      case 3:
         m_globalEventCounters.noRoute++;
         if (peerEventCounters != NULL)
            peerEventCounters->noRoute++;
         break;
      case 20:
         m_globalEventCounters.subscriberAbsent++;
         if (peerEventCounters != NULL)
            peerEventCounters->subscriberAbsent++;
         break;
      case 21:
         m_globalEventCounters.callRejected++;
         if (peerEventCounters != NULL)
            peerEventCounters->callRejected++;
         break;
      case 34:
      case 44:
         m_globalEventCounters.channelUnavailable++;
         if (peerEventCounters != NULL)
            peerEventCounters->channelUnavailable++;
         break;
      case 42:
         m_globalEventCounters.congestion++;
         if (peerEventCounters != NULL)
            peerEventCounters->congestion++;
         break;
      case 52:
      case 54:
         m_globalEventCounters.callBarred++;
         if (peerEventCounters != NULL)
            peerEventCounters->callBarred++;
         break;
   }
}

/**
 * Handler for Asterisk.Events.* parameter
 */
LONG H_EventCounters(const TCHAR *param, const TCHAR *arg, TCHAR *value, AbstractCommSession *session)
{
   GET_ASTERISK_SYSTEM;

   TCHAR peer[128];
   if (!AgentGetParameterArg(param, 2, peer, 128))
      return SYSINFO_RC_UNSUPPORTED;

   const EventCounters *cnt = ((peer[0] == 0) ? sys->getGlobalEventCounters() : sys->getPeerEventCounters(peer));
   switch(*arg)
   {
      case 'A':
         ret_uint64(value, (cnt != NULL) ? cnt->subscriberAbsent : 0);
         break;
      case 'B':
         ret_uint64(value, (cnt != NULL) ? cnt->callBarred : 0);
         break;
      case 'C':
         ret_uint64(value, (cnt != NULL) ? cnt->congestion : 0);
         break;
      case 'N':
         ret_uint64(value, (cnt != NULL) ? cnt->noRoute : 0);
         break;
      case 'R':
         ret_uint64(value, (cnt != NULL) ? cnt->callRejected : 0);
         break;
      case 'U':
         ret_uint64(value, (cnt != NULL) ? cnt->channelUnavailable : 0);
         break;
   }
   return SYSINFO_RC_SUCCESS;
}
