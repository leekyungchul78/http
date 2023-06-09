/* 
 * Copyright (C) 2021 Yee Young Han <websearch@naver.com> (http://blog.naver.com/websearch)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA 
 */

#ifndef _PCAP_SAVE_H_
#define _PCAP_SAVE_H_

#include "SipPlatformDefine.h"
#include "PcapTcpMap.h"
#include <pcap.h>

/**
 * @brief SIP 메시지를 pcap 파일로 저장하는 클래스
 */
class CPcapSave
{
public:
	CPcapSave();
	~CPcapSave();

	bool Open( const char * pszFileName, int iSnapLen );
	bool Write( const struct pcap_pkthdr * psttHeader, const u_char * psttPacketData );
	bool WriteUdp( struct timeval * psttTime, const char * pszFromIp, uint16_t sFromPort, const char * pszToIp, uint16_t sToPort, const char * pszData, int iDataLen );
	bool WriteTcp( struct timeval * psttTime, const char * pszFromIp, uint16_t sFromPort, const char * pszToIp, uint16_t sToPort, const char * pszData, int iDataLen );
	void Close( );
	bool IsOpen();

private:
	pcap_t				* m_pPcap;
	pcap_dumper_t * m_pPcapDump;
	uint8_t				* m_pszPacket;
	int							m_iPacketSize;
	CPcapTcpMap			m_clsTcpMap;
};

#endif
