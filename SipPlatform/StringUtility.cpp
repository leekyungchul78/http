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

#include "StringUtility.h"
#include <string.h>
#include <stdlib.h>
#include "Log.h"
#include "MemoryDebug.h"

/**
 * @ingroup SipPlatform
 * @brief 문자열에 포함된 문자열을 수정한다.
 * @param strCallId	문자열
 * @param pszBefore 수정 대상 문자열
 * @param pszAfter	수정 대상 문자열을 수정할 문자열
 */
void ReplaceString( std::string & strCallId, const char * pszBefore, const char * pszAfter )
{
	size_t iPos = strCallId.find( pszBefore );
	size_t iBeforeLen = strlen( pszBefore );
	size_t iAfterLen = strlen( pszAfter );

	while( iPos < std::string::npos )
	{
		strCallId.replace( iPos, iBeforeLen, pszAfter );
		iPos = strCallId.find( pszBefore, iPos + iAfterLen );
	}
}

/**
 * @ingroup SipPlatform
 * @brief 문자열에 포함된 키의 값을 추출한다. 
 *				"app=36;msg=36;hotline=46;presence=36; broadcast=46" 문자열에서 
 *				app 의 값을 추출하고 싶으면 pszKey 에 "app=" 를 입력하고 cSep 에 ';' 를 입력하면 된다.
 * @param strText		문자열
 * @param pszKey		키
 * @param cSep			구분자
 * @param strValue	키의 값을 저장할 변수
 * @returns 성공하면 true 를 리턴하고 실패하면 false 를 리턴한다.
 */
bool SearchValue( std::string & strText, const char * pszKey, char cSep, std::string & strValue )
{
	strValue.clear();

	size_t iPos = strText.find( pszKey );
	if( iPos < std::string::npos )
	{
		size_t iKeyLen = strlen( pszKey );
		size_t iEndPos = strText.find( cSep, iPos + iKeyLen );

		if( iEndPos < std::string::npos )
		{
			strValue = strText.substr( iPos + iKeyLen, iEndPos - ( iPos + iKeyLen ) );
		}
		else
		{
			strValue = strText.substr( iPos + iKeyLen );
		}

		return true;
	}

	return false;
}

/**
 * @ingroup SipPlatform
 * @brief 문자열에 포함된 키의 값을 추출한다. 
 *				"app=36;msg=36;hotline=46;presence=36; broadcast=46" 문자열에서 
 *				app 의 값을 추출하고 싶으면 pszKey 에 "app=" 를 입력하고 cSep 에 ';' 를 입력하면 된다.
 * @param strText		문자열
 * @param pszKey		키
 * @param cSep			구분자
 * @param iValue		키의 값을 저장할 변수
 * @returns 성공하면 true 를 리턴하고 실패하면 false 를 리턴한다.
 */
bool SearchValue( std::string & strText, const char * pszKey, char cSep, int & iValue )
{
	std::string	strValue;

	if( SearchValue( strText, pszKey, cSep, strValue ) )
	{
		iValue = atoi( strValue.c_str() );

		return true;
	}

	return false;
}

/**
 * @ingroup SipPlatform
 * @brief 문자열의 왼쪽 공백을 제거한다.
 * @param strText 문자열
 */
void LeftTrimString( std::string & strText )
{
	int iIndex;
	int iLen = (int)strText.length();
	for( iIndex = 0; iIndex < iLen; ++iIndex )
	{
		char c = strText.at(iIndex);
		if( c == ' ' || c == '\t' ) continue;

		strText.erase( 0, iIndex );
		break;
	}

	if( iIndex == iLen )
	{
		strText.clear();
	}
}

/**
 * @ingroup SipPlatform
 * @brief 문자열의 오른쪽 공백을 제거한다.
 * @param strText 문자열
 */
void RightTrimString( std::string & strText )
{
	int iIndex;
	int iLen = (int)strText.length();
	for( iIndex = iLen - 1; iIndex >= 0; --iIndex )
	{
		char c = strText.at(iIndex);
		if( c == ' ' || c == '\t' ) continue;

		if( iIndex != ( iLen - 1 ) )
		{
			strText.erase( iIndex + 1 );
		}

		break;
	}

	if( iIndex == -1 )
	{
		strText.clear();
	}
}

/**
 * @ingroup SipPlatform
 * @brief 문자열의 왼쪽, 오른쪽 공백을 제거한다.
 * @param strText 문자열
 */
void TrimString( std::string & strText )
{
	LeftTrimString( strText );
	RightTrimString( strText );
}

/**
 * @ingroup SipPlatform
 * @brief 입력 문자열을 구분자로 분리하여서 문자열 리스트에 저장한다.
 * @param pszText 입력 문자열
 * @param clsList 문자열 리스트
 * @param cSep		구분자
 */
void SplitString( const char * pszText, STRING_LIST & clsList, char cSep )
{
	int iStartPos = -1, i;

	clsList.clear();

	for( i = 0; pszText[i]; ++i )
	{
		if( pszText[i] == cSep )
		{
			if( iStartPos >= 0 && iStartPos != i )
			{
				std::string strTemp;

				strTemp.append( pszText + iStartPos, i - iStartPos );
				clsList.push_back( strTemp );
			}

			iStartPos = i + 1;
		}
		else if( i == 0 )
		{
			iStartPos = 0;
		}
	}

	if( iStartPos >= 0 && iStartPos != i )
	{
		std::string strTemp;

		strTemp.append( pszText + iStartPos, i - iStartPos );
		clsList.push_back( strTemp );
	}
}

/**
 * @ingroup SipPlatform
 * @brief 입력 문자열을 구분자로 분리하여서 문자열 VECTOR 에 저장한다.
 * @param pszText 입력 문자열
 * @param clsList 문자열 VECTOR
 * @param cSep		구분자
 */
void SplitString( const char * pszText, STRING_VECTOR & clsList, char cSep )
{
	int iStartPos = -1, i;

	clsList.clear();

	for( i = 0; pszText[i]; ++i )
	{
		if( pszText[i] == cSep )
		{
			if( iStartPos >= 0 && iStartPos != i )
			{
				std::string strTemp;

				strTemp.append( pszText + iStartPos, i - iStartPos );
				clsList.push_back( strTemp );
			}

			iStartPos = i + 1;
		}
		else if( i == 0 )
		{
			iStartPos = 0;
		}
	}

	if( iStartPos >= 0 && iStartPos != i )
	{
		std::string strTemp;

		strTemp.append( pszText + iStartPos, i - iStartPos );
		clsList.push_back( strTemp );
	}
}

/**
 * @ingroup SipPlatform
 * @brief 문자열을 unsigned int 로 변환한다.
 * @param pszText 문자열
 * @returns unsigned int 를 리턴한다.
 */
uint32_t GetUInt32( const char * pszText )
{
	if( pszText == NULL ) return 0;

	return strtoul( pszText, NULL, 10 );
}

/**
 * @ingroup SipPlatform
 * @brief 문자열을 unsigned long long 으로 변환한다.
 * @param pszText 문자열
 * @returns unsigned long long 을 리턴한다.
 */
uint64_t GetUInt64( const char * pszText )
{
	if( pszText == NULL ) return 0;

#ifdef WIN32
	return _strtoui64( pszText, NULL, 10 );
#else
	return strtoull( pszText, NULL, 10 );
#endif
}

/**
 * @ingroup SipPlatform
 * @brief HEX 만 저장된 문자열을 숫자로 변환한 문자열을 생성한다.
 * @param pszInput	HEX 만 저장된 문자열
 * @param strOutput 숫자로 변환된 문자열 저장용 변수
 * @returns 성공하면 true 를 리턴하고 실패하면 false 를 리턴한다.
 */
bool HexToString( const char * pszInput, std::string & strOutput )
{
	int iLen = (int)strlen( pszInput );
	int iValue;

	strOutput.clear();

	if( iLen >= 2 )
	{
		if( pszInput[0] == '0' && pszInput[1] == 'x' )
		{
			pszInput += 2;
			iLen -= 2;
		}
	}

	if( iLen == 0 || iLen % 2 == 1 ) return false;

	for( int i = 0; i < iLen; i += 2 )
	{
		sscanf( pszInput + i, "%02x", &iValue );
		strOutput.push_back( (char)iValue );
	}

	return true;
}

/**
 * @ingroup SipPlatform
 * @brief HEX 만 저장된 문자열을 숫자로 변환한 문자열을 생성한다.
 * @param pszInput		HEX 만 저장된 문자열
 * @param iInputSize	HEX 만 저장된 문자열의 길이
 * @param strOutput 숫자로 변환된 문자열 저장용 변수
 * @returns 성공하면 true 를 리턴하고 실패하면 false 를 리턴한다.
 */
bool HexToString( const char * pszInput, int iInputSize, std::string & strOutput )
{
	int iValue;

	strOutput.clear();

	if( iInputSize >= 2 )
	{
		if( pszInput[0] == '0' && pszInput[1] == 'x' )
		{
			pszInput += 2;
			iInputSize -= 2;
		}
	}

	if( iInputSize == 0 || iInputSize % 2 == 1 ) return false;

	for( int i = 0; i < iInputSize; i += 2 )
	{
		sscanf( pszInput + i, "%02x", &iValue );
		strOutput.push_back( (char)iValue );
	}

	return true;
}

/**
 * @ingroup SipPlatform
 * @brief 입력 문자열을 HEX 만 저장된 문자열로 변환한다.
 * @param strInput	입력 문자열
 * @param strOutput HEX 만 저장된 문자열 저장용 변수
 */
void StringToHex( std::string & strInput, std::string & strOutput )
{
	char szHex[3];
	int iLen = (int)strInput.length();

	strOutput.clear();

	for( int i = 0; i < iLen; ++i )
	{
		snprintf( szHex, sizeof(szHex), "%02x", (uint8_t)strInput.at(i) );
		strOutput.append( szHex );
	}
}

/**
 * @ingroup SipPlatform
 * @brief 입력 문자열을 HEX 만 저장된 문자열로 변환한다.
 * @param pszInput		입력 문자열
 * @param iInputSize	입력 문자열의 길이
 * @param strOutput		HEX 만 저장된 문자열 저장용 변수
 */
void StringToHex( const char * pszInput, int iInputSize, std::string & strOutput )
{
	char szHex[3];

	strOutput.clear();

	for( int i = 0; i < iInputSize; ++i )
	{
		snprintf( szHex, sizeof(szHex), "%02x", (uint8_t)pszInput[i] );
		strOutput.append( szHex );
	}
}

/**
 * @ingroup SipPlatform
 * @brief 문자열이 출력 가능한지 검사한다.
 * @param pszText		문자열
 * @param iTextLen	문자열 길이
 * @returns 문자열이 출력 가능하면 true 를 리턴하고 그렇지 않으면 false 를 리턴한다.
 */
bool IsPrintString( const char * pszText, int iTextLen )
{
	for( int i = 0; i < iTextLen; ++i )
	{
		if( isprint( (uint8_t)pszText[i] ) == 0 ) return false;
	}

	return true;
}

/**
 * @ingroup SipPlatform
 * @brief 입력된 문자열에서 " 를 제거한 출력 문자열을 저장한다.
 * @param strInput	입력 문자열
 * @param strOutput 출력 문자열
 */
void DeQuoteString( std::string & strInput, std::string & strOutput )
{
	int iLen = (int)strInput.length();

	strOutput.clear();

	if( iLen > 0 )
	{
		if( strInput.at( 0 ) != '"' || strInput.at( iLen - 1 ) != '"' )
		{
			strOutput = strInput;
		}
		else
		{
			strOutput.append( strInput, 1, iLen - 2 );
		}
	}
}

/**
 * @ingroup SipPlatform
 * @brief URI 인코딩된 문자열을 디코딩한다.
 * @param strInput	URI 인코딩된 문자열
 * @param strOutput [out] 디코딩된 문자열
 */
void DecodeUri( std::string & strInput, std::string & strOutput )
{
	const char * pszInput = strInput.c_str();
	int iLen = (int)strInput.length();
	char szHex[5];
	int iHexPos = 0, iValue;
	bool bHex = false;

	strOutput.clear();

	for( int i = 0; i < iLen; ++i )
	{
		if( pszInput[i] == '%' )
		{
			bHex = true;
		}
		else if( bHex )
		{
			szHex[iHexPos] = pszInput[i];
			++iHexPos;

			if( iHexPos == 2 )
			{
				if( strncmp( szHex, "25", 2 ) )
				{
					szHex[iHexPos] = '\0';
					sscanf( szHex, "%02x", &iValue );
					strOutput.push_back( (char)iValue );
					bHex = false;
				}

				iHexPos = 0;
			}
		}
		else
		{
			strOutput.push_back( pszInput[i] );
		}
	}
}

#ifdef WIN32

/**
 * @ingroup SipPlatform
 * @brief UTF8 문자열을 ANSI 문자열로 변환한다.
 * @param pszUtf8		UTF8 문자열 (input)
 * @param strOutput ANSI 문자열 (output)
 * @returns 성공하면 true 를 리턴하고 실패하면 false 를 리턴한다.
 */
bool Utf8ToAnsi( const char * pszUtf8, std::string & strOutput )
{
	BSTR    strWide = NULL;
	char*   pszAnsi = NULL;
	int     iLength;
	int			iUtf8Length = (int)strlen(pszUtf8) + 1;
	
	iLength = MultiByteToWideChar( CP_UTF8, 0, pszUtf8, iUtf8Length, NULL, NULL );
	if( iLength == 0 )
	{
		CLog::Print( LOG_ERROR, "%s MultiByteToWideChar error(%d)", __FUNCTION__, GetLastError() );
		return false;
	}

	strWide = SysAllocStringLen( NULL, iLength );
	if( strWide == NULL )
	{
		CLog::Print( LOG_ERROR, "%s SysAllocStringLen error(%d)", __FUNCTION__, GetLastError() );
		return false;
	}

	MultiByteToWideChar( CP_UTF8, 0, pszUtf8, iUtf8Length, strWide, iLength );

	iLength = WideCharToMultiByte( CP_ACP, 0, strWide, -1, NULL, 0, NULL, NULL );
	if( iLength == 0 )
	{
		SysFreeString( strWide );
		CLog::Print( LOG_ERROR, "%s WideCharToMultiByte error(%d)", __FUNCTION__, GetLastError() );
		return false;
	}

	pszAnsi = new char[iLength];
	if( pszAnsi == NULL )
	{
		SysFreeString( strWide );
		CLog::Print( LOG_ERROR, "%s new error(%d)", __FUNCTION__, GetLastError() );
		return false;
	}

	WideCharToMultiByte( CP_ACP, 0, strWide, -1, pszAnsi, iLength, NULL, NULL );
	strOutput = pszAnsi;
	
	SysFreeString( strWide );
	delete [] pszAnsi;
	
	return true;
}

/**
 * @ingroup SipPlatform
 * @brief ANSI 문자열을 UTF-8 문자열로 변환한다. EUC-KR 문자열을 UTF-8 문자열로 변환한다.
 * @param pszAnsi		ANSI 문자열
 * @param strOutput UTF-8 문자열을 저장할 변수
 * @returns 성공하면 true 를 리턴하고 실패하면 false 를 리턴한다.
 */
bool AnsiToUtf8( const char * pszAnsi, std::string & strOutput )
{
	BSTR    strWide = NULL;
	char*   pszUtf8 = NULL;
	int     iLength;
	int			iAnsiLength = (int)strlen(pszAnsi) + 1;
	
	iLength = MultiByteToWideChar( CP_ACP, 0, pszAnsi, iAnsiLength, NULL, NULL );
	if( iLength == 0 )
	{
		CLog::Print( LOG_ERROR, "%s MultiByteToWideChar error(%d)", __FUNCTION__, GetLastError() );
		return false;
	}

	strWide = SysAllocStringLen( NULL, iLength );
	if( strWide == NULL )
	{
		CLog::Print( LOG_ERROR, "%s SysAllocStringLen error(%d)", __FUNCTION__, GetLastError() );
		return false;
	}

	MultiByteToWideChar( CP_ACP, 0, pszAnsi, iAnsiLength, strWide, iLength );

	iLength = WideCharToMultiByte( CP_UTF8, 0, strWide, -1, NULL, 0, NULL, NULL );
	if( iLength == 0 )
	{
		SysFreeString( strWide );
		CLog::Print( LOG_ERROR, "%s WideCharToMultiByte error(%d)", __FUNCTION__, GetLastError() );
		return false;
	}

	pszUtf8 = new char[iLength];
	if( pszUtf8 == NULL )
	{
		SysFreeString( strWide );
		CLog::Print( LOG_ERROR, "%s new error(%d)", __FUNCTION__, GetLastError() );
		return false;
	}

	WideCharToMultiByte( CP_UTF8, 0, strWide, -1, pszUtf8, iLength, NULL, NULL );
	strOutput = pszUtf8;
	
	SysFreeString( strWide );
	delete [] pszUtf8;
	
	return true;
}

#endif
