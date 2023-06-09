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

#ifndef _WEB_SOCKET_CLIENT_H_
#define _WEB_SOCKET_CLIENT_H_

#include "SipTcp.h"
#include "SipMutex.h"
#include "TlsFunction.h"

/**
 * @ingroup HttpStack
 * @brief WebSocket Client 콜백 인터페이스
 */
class IWebSocketClientCallBack
{
public:
	IWebSocketClientCallBack(){};
	virtual ~IWebSocketClientCallBack(){};

	virtual bool RecvWebSocket( const char * pszPacket, int iPacketLen ) = 0;
};

/**
 * @ingroup HttpStack
 * @brief WebSocket 패킷 타입
 */
enum EWebSocketType
{
	E_WST_TEXT = 0,
	E_WST_BINARY,
	E_WST_PING,
	E_WST_PONG
};

/**
 * @ingroup HttpStack
 * @brief WebSocket Client
 */
class CWebSocketClient
{
public:
	CWebSocketClient();
	~CWebSocketClient();

	bool Connect( const char * pszUrl, IWebSocketClientCallBack * pclsCallBack );
	void Close();

	bool Send( std::string & strData );
	bool Send( EWebSocketType eType, const char * pszData, int iDataLen );
	bool SendTcp( const char * pszPacket, int iPacketLen );

	bool IsClosed();

	int		m_iRecvTimeout;
	bool	m_bStop;
	bool	m_bThreadRun;
	Socket m_hSocket;
	SSL * m_psttSsl;
	CSipMutex	m_clsMutex;
	IWebSocketClientCallBack * m_pclsCallBack;
	std::string m_strServerIp;
	int					m_iServerPort;
};

#endif
