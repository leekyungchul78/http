/* 
 * Copyright (C) 2012 Yee Young Han <websearch@naver.com> (http://blog.naver.com/websearch)
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

#include "SipPlatformDefine.h"
#include "HttpSetCookie.h"
#include <stdlib.h>
#include "MemoryDebug.h"

bool TestHttpSetCookie( )
{
	CHttpSetCookie clsSetCookie;
	const char * pszSetCookie = "JSESSIONID=1C1A4301CA917C57A8D39A316D91081B; Path=/test; HttpOnly";

	if( clsSetCookie.Parse( pszSetCookie, (int)strlen(pszSetCookie) ) == -1 )
	{
		printf( "%s clsSetCookie.Parse() error", __FUNCTION__ );
		return false;
	}

	if( strcmp( clsSetCookie.m_strName.c_str(), "JSESSIONID" ) )
	{
		printf( "%s cookie name error", __FUNCTION__ );
		return false;
	}

	if( strcmp( clsSetCookie.m_strValue.c_str(), "1C1A4301CA917C57A8D39A316D91081B" ) )
	{
		printf( "%s cookie value error", __FUNCTION__ );
		return false;
	}

	if( strcmp( clsSetCookie.m_strPath.c_str(), "/test" ) )
	{
		printf( "%s cookie path error", __FUNCTION__ );
		return false;
	}

	return true;
}
