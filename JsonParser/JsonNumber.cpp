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
#include "JsonNumber.h"
#include "MemoryDebug.h"

CJsonNumber::CJsonNumber()
{
	m_cType = JSON_TYPE_NUMBER;
}

CJsonNumber::~CJsonNumber()
{
}

/**
 * @ingroup JsonParser
 * @brief JSON 숫자 문자열 파싱하여서 자료구조에 저장한다.
 * @param pszText		JSON 숫자 문자열
 * @param iTextLen	JSON 숫자 문자열 길이
 * @returns JSON 숫자 문자열 파싱에 성공하면 파싱한 길이를 리턴하고 그렇지 않으면 -1 를 리턴한다.
 */
int CJsonNumber::Parse( const char * pszText, int iTextLen )
{
	m_strValue.clear();

	for( int i = 0; i < iTextLen; ++i )
	{
		if( i == 0 && pszText[i] == '-' )
		{
			// 첫번째 - 는 음수이므로 넘어간다.
		}
		else if( isspace( pszText[i] ) || pszText[i] == ',' || pszText[i] == '}' || pszText[i] == ']' )
		{
			m_strValue.append( pszText, i );
			return i;
		}
	}

	return -1;
}

/**
 * @ingroup JsonParser
 * @brief 자료구조를 JSON 숫자 문자열로 변환한다.
 * @param strText		JSON 문자열 저장 변수
 * @param eNewLine	의미없는 변수
 * @param iDepth		의미없는 변수
 * @returns JSON 숫자 문자열 길이를 리턴한다.
 */
int CJsonNumber::ToString( std::string & strText, EJsonNewLine eNewLine, int iDepth )
{
	strText.append( m_strValue );

	return (int)m_strValue.length();
}

/**
 * @ingroup JsonParser
 * @brief ToString 메소드로 생성될 문자열 길이를 리턴한다.
 * @returns ToString 메소드로 생성될 문자열 길이를 리턴한다.
 */
int CJsonNumber::GetStringLen( )
{
	return (int)m_strValue.length();
}

/**
 * @ingroup JsonParser
 * @brief 자신을 복제한 객체를 생성한다.
 * @returns 성공하면 자신을 복제한 객체를 리턴하고 그렇지 않으면 NULL 을 리턴한다.
 */
CJsonType * CJsonNumber::Copy( )
{
	CJsonNumber * pclsNum = new CJsonNumber();
	if( pclsNum == NULL ) return NULL;

	pclsNum->m_strValue = m_strValue;

	return pclsNum;
}

/**
 * @ingroup JsonParser
 * @brief double 인지 검사한다.
 * @returns double 이면 true 를 리턴하고 그렇지 않으면 false 를 리턴한다.
 */
bool CJsonNumber::IsDouble( )
{
	const char * pszValue = m_strValue.c_str();
	int iLen = (int)m_strValue.length();

	for( int i = 0; i < iLen; ++i )
	{
		if( pszValue[i] == 'e' ) return true;
	}

	return false;
}
