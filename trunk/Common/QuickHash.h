/*
*   Copyright (C) 2007 Carnegie Mellon University
*   This file is part of the libjingle file transfer  Test Suite.
*
*   The Test Suite is free software; you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation; either version 3 of the License, or
*   any later version.
*
*   The Test Suite is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*   
*   Contact the original project authors by visiting
*   <http://dogbert.mse.cs.cmu.edu/MSE2007/Projects/Google/team.html>.
*/
/*************************************************************

				QuickHash Library 3.02

Module Name:    QuickHash.h

Abstract:       Master include file for QuickHash Library
			
	
			Copyright (c) 1999-2007, SlavaSoft Inc.
	
	  
*************************************************************/

#ifndef __QUICKHASH_H__
#define __QUICKHASH_H__

#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#if defined (_MSC_VER)
#if !defined( _SL_QUICKHASH_IMPLEMENTATION ) && !defined( _SL_NOFORCE_LIBS )

#ifdef _SL_STATIC
	#pragma comment( lib, "QuickHashS.lib" )
#else
	#pragma comment( lib, "QuickHash.lib" )
#endif //_SL_STATIC

#endif

#endif


#if ( defined (_MSC_VER) && (_MSC_VER >= 800) ) || defined(_STDCALL_SUPPORTED)
#define SL_HASHCALL _stdcall
#else
#define SL_HASHCALL
#endif
#define SLC_MD4_DIGESTSIZE			16
#define SLC_MD4_HEXDIGESTSIZE		( 2 * ( SLC_MD4_DIGESTSIZE ) + 1 )
#define SLC_MD4_CONTEXTSIZE			88
#define SLC_MD4_BLOCKSIZE			64
#define SLC_MD4_ALGID				8

#define SLC_MD5_DIGESTSIZE			16
#define SLC_MD5_HEXDIGESTSIZE		( 2 * ( SLC_MD5_DIGESTSIZE ) + 1 )
#define SLC_MD5_CONTEXTSIZE			88
#define SLC_MD5_BLOCKSIZE			64
#define SLC_MD5_ALGID				0

#define SLC_SHA1_DIGESTSIZE			20
#define SLC_SHA1_HEXDIGESTSIZE		( 2 * ( SLC_SHA1_DIGESTSIZE ) + 1 )
#define SLC_SHA1_CONTEXTSIZE		92
#define SLC_SHA1_BLOCKSIZE			64
#define SLC_SHA1_ALGID				1

#define SLC_SHA256_DIGESTSIZE		32
#define SLC_SHA256_HEXDIGESTSIZE	( 2 * ( SLC_SHA256_DIGESTSIZE ) + 1 )
#define SLC_SHA256_CONTEXTSIZE		104
#define SLC_SHA256_BLOCKSIZE		64
#define SLC_SHA256_ALGID			2

#define SLC_SHA512_DIGESTSIZE		64
#define SLC_SHA512_HEXDIGESTSIZE	( 2 * ( SLC_SHA512_DIGESTSIZE ) + 1 )
#define SLC_SHA512_CONTEXTSIZE		208
#define SLC_SHA512_BLOCKSIZE		128
#define SLC_SHA512_ALGID			3

#define SLC_SHA384_DIGESTSIZE		48
#define SLC_SHA384_HEXDIGESTSIZE	( 2 * ( SLC_SHA384_DIGESTSIZE ) + 1 )
#define SLC_SHA384_CONTEXTSIZE		208
#define SLC_SHA384_BLOCKSIZE		128
#define SLC_SHA384_ALGID			4

#define	SLC_RIPEMD160_DIGESTSIZE	20
#define SLC_RIPEMD160_HEXDIGESTSIZE	( 2 * ( SLC_RIPEMD160_DIGESTSIZE ) + 1 )
#define	SLC_RIPEMD160_CONTEXTSIZE	92
#define SLC_RIPEMD160_BLOCKSIZE		64
#define SLC_RIPEMD160_ALGID			7

#define	SLC_RIPEMD128_DIGESTSIZE	16
#define SLC_RIPEMD128_HEXDIGESTSIZE	( 2 * ( SLC_RIPEMD128_DIGESTSIZE ) + 1 )
#define	SLC_RIPEMD128_CONTEXTSIZE	88
#define SLC_RIPEMD128_BLOCKSIZE		64
#define SLC_RIPEMD128_ALGID			12

#define	SLC_RIPEMD256_DIGESTSIZE	32
#define SLC_RIPEMD256_HEXDIGESTSIZE	( 2 * ( SLC_RIPEMD256_DIGESTSIZE ) + 1 )
#define	SLC_RIPEMD256_CONTEXTSIZE	104
#define SLC_RIPEMD256_BLOCKSIZE		64
#define SLC_RIPEMD256_ALGID			13

#define	SLC_RIPEMD320_DIGESTSIZE	40
#define SLC_RIPEMD320_HEXDIGESTSIZE	( 2 * ( SLC_RIPEMD320_DIGESTSIZE ) + 1 )
#define	SLC_RIPEMD320_CONTEXTSIZE	112
#define SLC_RIPEMD320_BLOCKSIZE		64
#define SLC_RIPEMD320_ALGID			14

#define SLC_PANAMA_DIGESTSIZE		32
#define SLC_PANAMA_HEXDIGESTSIZE	( 2 * ( SLC_PANAMA_DIGESTSIZE ) + 1 )
#define	SLC_PANAMA_CONTEXTSIZE		1280
#define SLC_PANAMA_BLOCKSIZE		32
#define SLC_PANAMA_ALGID			6

#define SLC_TIGER_DIGESTSIZE		24
#define SLC_TIGER_HEXDIGESTSIZE		( 2 * ( SLC_TIGER_DIGESTSIZE ) + 1 )
#define	SLC_TIGER_CONTEXTSIZE		96
#define SLC_TIGER_BLOCKSIZE			64
#define SLC_TIGER_ALGID				5

#define SLC_MD2_DIGESTSIZE			16
#define SLC_MD2_HEXDIGESTSIZE		( 2 * ( SLC_MD2_DIGESTSIZE ) + 1 )
#define SLC_MD2_CONTEXTSIZE			68
#define SLC_MD2_ALGID				9

#define SLC_CRC32_DIGESTSIZE		4
#define SLC_CRC32_HEXDIGESTSIZE		( 2 * ( SLC_CRC32_DIGESTSIZE ) + 1 )
#define SLC_CRC32_CONTEXTSIZE		4
#define SLC_CRC32_ALGID             10

#define SLC_CRC16_DIGESTSIZE		2
#define SLC_CRC16_HEXDIGESTSIZE		( 2 * ( SLC_CRC32_DIGESTSIZE ) + 1 )
#define SLC_CRC16_CONTEXTSIZE		2
#define SLC_CRC16_ALGID             15

#define SLC_CRC16C_DIGESTSIZE		2
#define SLC_CRC16C_HEXDIGESTSIZE		( 2 * ( SLC_CRC32_DIGESTSIZE ) + 1 )
#define SLC_CRC16C_CONTEXTSIZE		2
#define SLC_CRC16C_ALGID            16

#define SLC_ADLER32_DIGESTSIZE		4
#define SLC_ADLER32_HEXDIGESTSIZE	( 2 * ( SLC_ADLER32_DIGESTSIZE ) + 1 )
#define SLC_ADLER32_CONTEXTSIZE		4
#define SLC_ADLER32_ALGID           11


#define SLC_HMAC_CONTEXTSIZE( CONTEXTSIZE, BLOCKSIZE ) ( CONTEXTSIZE + 2 * BLOCKSIZE + sizeof( unsigned int ) )



#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

void				SL_HASHCALL SL_MD4_Init( void* pContext );
void				SL_HASHCALL SL_MD4_Update( void* pContext, const void* pSrc, unsigned int nSrcLength );
void				SL_HASHCALL SL_MD4_UpdateStr( void* pContext, const char* pSrc );
void				SL_HASHCALL SL_MD4_Final( void* pContext, void* pDest );
void				SL_HASHCALL SL_MD4_FinalHex( void* pContext, void* pDest, int bUpper );
void				SL_HASHCALL SL_MD4_Calculate( void* pDest, const void* pSrc, unsigned int nSrcLength );
void				SL_HASHCALL SL_MD4_CalculateStr( void* pDest, const char* pSrc );
void				SL_HASHCALL SL_MD4_CalculateHex( void* pDest, const void* pSrc, unsigned int nSrcLength, int bUpper );
void				SL_HASHCALL SL_MD4_CalculateStrHex( void* pDest, const char* pSrc, int bUpper );

void				SL_HASHCALL SL_MD5_Init( void* pContext );
void				SL_HASHCALL SL_MD5_Update( void* pContext, const void* pSrc, unsigned int nSrcLength );
void				SL_HASHCALL SL_MD5_UpdateStr( void* pContext, const char* pSrc );
void				SL_HASHCALL SL_MD5_Final( void* pContext, void* pDest );
void				SL_HASHCALL SL_MD5_FinalHex( void* pContext, void* pDest, int bUpper );
void				SL_HASHCALL SL_MD5_Calculate( void* pDest, const void* pSrc, unsigned int nSrcLength );
void				SL_HASHCALL SL_MD5_CalculateStr( void* pDest, const char* pSrc );
void				SL_HASHCALL SL_MD5_CalculateHex( void* pDest, const void* pSrc, unsigned int nSrcLength, int bUpper );
void				SL_HASHCALL SL_MD5_CalculateStrHex( void* pDest, const char* pSrc, int bUpper );

void				SL_HASHCALL SL_SHA1_Init( void* pContext );
void				SL_HASHCALL SL_SHA1_Update( void* pContext, const void* pSrc, unsigned int nSrcLength );
void				SL_HASHCALL SL_SHA1_UpdateStr( void* pContext, const char* pSrc);
void				SL_HASHCALL SL_SHA1_Final( void* pContext, void* pDest );
void				SL_HASHCALL SL_SHA1_FinalHex( void* pContext, void* pDest, int bUpper );
void				SL_HASHCALL SL_SHA1_Calculate( void* pDest, const void* pSrc, unsigned int nSrcLength );
void				SL_HASHCALL SL_SHA1_CalculateStr( void* pDest, const char* pSrc );
void				SL_HASHCALL SL_SHA1_CalculateHex( void* pDest, const void* pSrc, unsigned int nSrcLength, int bUpper );
void				SL_HASHCALL SL_SHA1_CalculateStrHex( void* pDest, const char* pSrc, int bUpper );

void				SL_HASHCALL SL_SHA256_Init( void* pContext );
void				SL_HASHCALL SL_SHA256_Update( void* pContext, const void* pSrc, unsigned int nSrcLength );
void				SL_HASHCALL SL_SHA256_UpdateStr( void* pContext, const char* pSrc );
void				SL_HASHCALL SL_SHA256_Final( void* pContext, void* pDest );
void				SL_HASHCALL SL_SHA256_FinalHex( void* pContext, void* pDest, int bUpper );
void				SL_HASHCALL SL_SHA256_Calculate( void* pDest, const void* pSrc, unsigned int nSrcLength );
void				SL_HASHCALL SL_SHA256_CalculateStr( void* pDest, const char* pSrc );
void				SL_HASHCALL SL_SHA256_CalculateHex( void* pDest, const void* pSrc, unsigned int nSrcLength, int bUpper );
void				SL_HASHCALL SL_SHA256_CalculateStrHex( void* pDest, const char* pSrc, int bUpper );

void				SL_HASHCALL SL_SHA512_Init( void* pContext );
void				SL_HASHCALL SL_SHA512_Update( void* pContext, const void* pSrc, unsigned int nSrcLength );
void				SL_HASHCALL SL_SHA512_UpdateStr( void* pContext, const char* pSrc );
void				SL_HASHCALL SL_SHA512_Final( void* pContext, void* pDest );
void				SL_HASHCALL SL_SHA512_FinalHex( void* pContext, void* pDest, int bUpper );
void				SL_HASHCALL SL_SHA512_Calculate( void* pDest, const void* pSrc, unsigned int nSrcLength );
void				SL_HASHCALL SL_SHA512_CalculateStr( void* pDest, const char* pSrc );
void				SL_HASHCALL SL_SHA512_CalculateHex( void* pDest, const void* pSrc, unsigned int nSrcLength, int bUpper );
void				SL_HASHCALL SL_SHA512_CalculateStrHex( void* pDest, const char* pSrc, int bUpper );

void				SL_HASHCALL SL_SHA384_Init( void* pContext );
void				SL_HASHCALL SL_SHA384_Final( void* pContext, void* pDest );
void				SL_HASHCALL SL_SHA384_FinalHex( void* pContext, void* pDest, int bUpper );
void				SL_HASHCALL SL_SHA384_Calculate( void* pDest, const void* pSrc, unsigned int nSrcLength );
void				SL_HASHCALL SL_SHA384_CalculateStr( void* pDest, const char* pSrc );
void				SL_HASHCALL SL_SHA384_CalculateHex( void* pDest, const void* pSrc, unsigned int nSrcLength, int bUpper );
void				SL_HASHCALL SL_SHA384_CalculateStrHex( void* pDest, const char* pSrc, int bUpper );
#define				SL_SHA384_Update		SL_SHA512_Update
#define             SL_SHA384_UpdateStr		SL_SHA512_UpdateStr

void				SL_HASHCALL SL_RIPEMD160_Init( void* pContext );
void				SL_HASHCALL SL_RIPEMD160_Update( void* pContext, const void* pSrc, unsigned int nSrcLength );
void				SL_HASHCALL SL_RIPEMD160_UpdateStr( void* pContext, const char* pSrc );
void				SL_HASHCALL SL_RIPEMD160_Final( void* pContext, void* pDest );
void				SL_HASHCALL SL_RIPEMD160_FinalHex( void* pContext, void* pDest, int bUpper );
void				SL_HASHCALL SL_RIPEMD160_Calculate( void* pDest, const void* pSrc, unsigned int nSrcLength );
void				SL_HASHCALL SL_RIPEMD160_CalculateStr( void* pDest, const char* pSrc );
void				SL_HASHCALL SL_RIPEMD160_CalculateHex( void* pDest, const void* pSrc, unsigned int nSrcLength, int bUpper );
void				SL_HASHCALL SL_RIPEMD160_CalculateStrHex( void* pDest, const char* pSrc, int bUpper );

void				SL_HASHCALL SL_RIPEMD128_Init( void* pContext );
void				SL_HASHCALL SL_RIPEMD128_Update( void* pContext, const void* pSrc, unsigned int nSrcLength );
void				SL_HASHCALL SL_RIPEMD128_UpdateStr( void* pContext, const char* pSrc );
void				SL_HASHCALL SL_RIPEMD128_Final( void* pContext, void* pDest );
void				SL_HASHCALL SL_RIPEMD128_FinalHex( void* pContext, void* pDest, int bUpper );
void				SL_HASHCALL SL_RIPEMD128_Calculate( void* pDest, const void* pSrc, unsigned int nSrcLength );
void				SL_HASHCALL SL_RIPEMD128_CalculateStr( void* pDest, const char* pSrc );
void				SL_HASHCALL SL_RIPEMD128_CalculateHex( void* pDest, const void* pSrc, unsigned int nSize, int bUpper );
void				SL_HASHCALL SL_RIPEMD128_CalculateStrHex( void* pDest, const char* pSrc, int bUpper );

void				SL_HASHCALL SL_RIPEMD256_Init( void* pContext );
void				SL_HASHCALL SL_RIPEMD256_Update( void* pContext, const void* pSrc, unsigned int nSrcLength );
void				SL_HASHCALL SL_RIPEMD256_UpdateStr( void* pContext, const char* pSrc );
void				SL_HASHCALL SL_RIPEMD256_Final( void* pContext, void* pDest );
void				SL_HASHCALL SL_RIPEMD256_FinalHex( void* pContext, void* pDest, int bUpper );
void				SL_HASHCALL SL_RIPEMD256_Calculate( void* pDest, const void* pSrc, unsigned int nSrcLength );
void				SL_HASHCALL SL_RIPEMD256_CalculateStr( void* pDest, const char* pSrc );
void				SL_HASHCALL SL_RIPEMD256_CalculateHex( void* pDest, const void* pSrc, unsigned int nSize, int bUpper );
void				SL_HASHCALL SL_RIPEMD256_CalculateStrHex( void* pDest, const char* pSrc, int bUpper );

void				SL_HASHCALL SL_RIPEMD320_Init( void* pContext );
void				SL_HASHCALL SL_RIPEMD320_Update( void* pContext, const void* pSrc, unsigned int nSrcLength );
void				SL_HASHCALL SL_RIPEMD320_UpdateStr( void* pContext, const char* pSrc );
void				SL_HASHCALL SL_RIPEMD320_Final( void* pContext, void* pDest );
void				SL_HASHCALL SL_RIPEMD320_FinalHex( void* pContext, void* pDest, int bUpper );
void				SL_HASHCALL SL_RIPEMD320_Calculate( void* pDest, const void* pSrc, unsigned int nSrcLength );
void				SL_HASHCALL SL_RIPEMD320_CalculateStr( void* pDest, const char* pSrc );
void				SL_HASHCALL SL_RIPEMD320_CalculateHex( void* pDest, const void* pSrc, unsigned int nSize, int bUpper );
void				SL_HASHCALL SL_RIPEMD320_CalculateStrHex( void* pDest, const char* pSrc, int bUpper );

void				SL_HASHCALL SL_PANAMA_Init( void* pContext );
void				SL_HASHCALL SL_PANAMA_Update( void* pContext, const void* pSrc, unsigned int nSrcLength );
void				SL_HASHCALL SL_PANAMA_UpdateStr( void* pContext, const char* pSrc );
void				SL_HASHCALL SL_PANAMA_Final( void* pContext, void* pDest );
void				SL_HASHCALL SL_PANAMA_FinalHex( void* pContext, void* pDest, int bUpper );
void				SL_HASHCALL SL_PANAMA_Calculate( void* pDest, const void* pSrc, unsigned int nSrcLength );
void				SL_HASHCALL SL_PANAMA_CalculateStr( void* pDest, const char* pSrc );
void				SL_HASHCALL SL_PANAMA_CalculateHex( void* pDest, const void* pSrc, unsigned int nSrcLength, int bUpper );
void				SL_HASHCALL SL_PANAMA_CalculateStrHex( void* pDest, const char* pSrc, int bUpper );

void				SL_HASHCALL SL_TIGER_Init( void* pContext );
void				SL_HASHCALL SL_TIGER_Update( void* pContext, const void* pSrc, unsigned int nSrcLength );
void				SL_HASHCALL SL_TIGER_UpdateStr( void* pContext, const char* pSrc );
void				SL_HASHCALL SL_TIGER_Final( void* pContext, void* pDest );
void				SL_HASHCALL SL_TIGER_FinalHex( void* pContext, void* pDest, int bUpper );
void				SL_HASHCALL SL_TIGER_Calculate( void* pDest, const void* pSrc, unsigned int nSrcLength );
void				SL_HASHCALL SL_TIGER_CalculateStr( void* pDest, const char* pSrc );
void				SL_HASHCALL SL_TIGER_CalculateHex( void* pDest, const void* pSrc, unsigned int nSrcLength, int bUpper );
void				SL_HASHCALL SL_TIGER_CalculateStrHex( void* pDest, const char* pSrc, int bUpper );

void				SL_HASHCALL SL_MD2_Init( void* pContext );
void				SL_HASHCALL SL_MD2_Update( void* pContext, const void* pSrc, unsigned int nSrcLength );
void				SL_HASHCALL SL_MD2_UpdateStr( void* pContext, const char* pSrc );
void				SL_HASHCALL SL_MD2_Final( void* pContext, void* pDest );
void				SL_HASHCALL SL_MD2_FinalHex( void* pContext, void* pDest, int bUpper );
void				SL_HASHCALL SL_MD2_Calculate( void* pDest, const void* pSrc, unsigned int nSrcLength );
void				SL_HASHCALL SL_MD2_CalculateStr( void* pDest, const char* pSrc );
void				SL_HASHCALL SL_MD2_CalculateHex( void* pDest, const void* pSrc, unsigned int nSrcLength, int bUpper );
void				SL_HASHCALL SL_MD2_CalculateStrHex( void* pDest, const char* pSrc, int bUpper );

void				SL_HASHCALL SL_CRC32_Init( void* pContext );
void				SL_HASHCALL SL_CRC32_Update( void* pContext, const void* pSrc, unsigned int nSrcLength );
void				SL_HASHCALL SL_CRC32_UpdateStr( void* pContext, const char* pSrc );
void				SL_HASHCALL SL_CRC32_Final( void* pContext, void* pDest );
void				SL_HASHCALL SL_CRC32_FinalHex( void* pContext, void* pDest, int bUpper );
void				SL_HASHCALL SL_CRC32_Calculate( void* pDest, const void* pSrc, unsigned int nSrcLength );
void				SL_HASHCALL SL_CRC32_CalculateStr( void* pDest, const char* pSrc );
void				SL_HASHCALL SL_CRC32_CalculateHex( void* pDest, const void* pSrc, unsigned int nSrcLength, int bUpper );
void				SL_HASHCALL SL_CRC32_CalculateStrHex( void* pDest, const char* pSrc, int bUpper );

void				SL_HASHCALL SL_CRC16_Init( void* pContext );
void				SL_HASHCALL SL_CRC16_Update( void* pContext, const void* pSrc, unsigned int nSrcLength );
void				SL_HASHCALL SL_CRC16_UpdateStr( void* pContext, const char* pSrc );
void				SL_HASHCALL SL_CRC16_Final( void* pContext, void* pDest );
void				SL_HASHCALL SL_CRC16_FinalHex( void* pContext, void* pDest, int bUpper );
void				SL_HASHCALL SL_CRC16_Calculate( void* pDest, const void* pSrc, unsigned int nSrcLength );
void				SL_HASHCALL SL_CRC16_CalculateStr( void* pDest, const char* pSrc );
void				SL_HASHCALL SL_CRC16_CalculateHex( void* pDest, const void* pSrc, unsigned int nSrcLength, int bUpper );
void				SL_HASHCALL SL_CRC16_CalculateStrHex( void* pDest, const char* pSrc, int bUpper );

void				SL_HASHCALL SL_CRC16C_Init( void* pContext );
void				SL_HASHCALL SL_CRC16C_Update( void* pContext, const void* pSrc, unsigned int nSrcLength );
void				SL_HASHCALL SL_CRC16C_UpdateStr( void* pContext, const char* pSrc );
void				SL_HASHCALL SL_CRC16C_Final( void* pContext, void* pDest );
void				SL_HASHCALL SL_CRC16C_FinalHex( void* pContext, void* pDest, int bUpper );
void				SL_HASHCALL SL_CRC16C_Calculate( void* pDest, const void* pSrc, unsigned int nSrcLength );
void				SL_HASHCALL SL_CRC16C_CalculateStr( void* pDest, const char* pSrc );
void				SL_HASHCALL SL_CRC16C_CalculateHex( void* pDest, const void* pSrc, unsigned int nSrcLength, int bUpper );
void				SL_HASHCALL SL_CRC16C_CalculateStrHex( void* pDest, const char* pSrc, int bUpper );

void				SL_HASHCALL SL_ADLER32_Init( void* pContext );
void				SL_HASHCALL SL_ADLER32_Update( void* pContext, const void* pSrc, unsigned int nSrcLength );
void				SL_HASHCALL SL_ADLER32_UpdateStr( void* pContext, const char* pSrc );
void				SL_HASHCALL SL_ADLER32_Final( void* pContext, void* pDest );
void				SL_HASHCALL SL_ADLER32_FinalHex( void* pContext, void* pDest, int bUpper );
void				SL_HASHCALL SL_ADLER32_Calculate( void* pDest, const void* pSrc, unsigned int nSrcLength );
void				SL_HASHCALL SL_ADLER32_CalculateStr( void* pDest, const char* pSrc );
void				SL_HASHCALL SL_ADLER32_CalculateHex( void* pDest, const void* pSrc, unsigned int nSrcLength, int bUpper );
void				SL_HASHCALL SL_ADLER32_CalculateStrHex( void* pDest, const char* pSrc, int bUpper );

int					SL_HASHCALL SL_HMAC_Init( void* pContext, unsigned int nAlgID, const void* pKey, unsigned int nKeyLength );
int					SL_HASHCALL SL_HMAC_InitKeyStr( void* pContext, unsigned int nAlgID, const char* pKey );
int					SL_HASHCALL SL_HMAC_Update( void* pContext, const void* pSrc, unsigned int nSrcLength );
int					SL_HASHCALL SL_HMAC_UpdateStr( void* pContext, const char* pSrc );
int					SL_HASHCALL	SL_HMAC_Final( void* pContext, void* pDest );
int					SL_HASHCALL SL_HMAC_FinalHex( void* pContext, void* pDest, int bUpper );
int					SL_HASHCALL SL_HMAC_Calculate( unsigned int nAlgID, void* pDest, const void* pSrc, unsigned int nSrcLength, const void* pKey, unsigned int nKeyLength );
int					SL_HASHCALL SL_HMAC_CalculateStr( unsigned int nAlgID, void* pDest, const char* pSrc, const char* pKey );
int					SL_HASHCALL SL_HMAC_CalculateHex( unsigned int nAlgID, void* pDest, const void* pSrc, unsigned int nSrcLength, const void* pKey, unsigned int nKeyLength, int bUpper );
int					SL_HASHCALL SL_HMAC_CalculateStrHex( unsigned int nAlgID, void* pDest, const char* pSrc, const char* pKey, int bUpper );
unsigned int		SL_HASHCALL SL_HMAC_GetDigestSize( const void* pContext );

#ifdef __cplusplus
}

#ifdef NO_NAMESPACE

#ifndef USING_NAMESPACE
#define USING_NAMESPACE( X )
#endif

#ifndef NAMESPACE_BEGIN
#define NAMESPACE_BEGIN( X )
#endif

#ifndef NAMESPACE_END
#define NAMESPACE_END
#endif

#else

#ifndef USING_NAMESPACE
#define USING_NAMESPACE( X ) using namespace X;
#endif

#ifndef NAMESPACE_BEGIN
#define NAMESPACE_BEGIN( X ) namespace X {
#endif

#ifndef NAMESPACE_END
#define NAMESPACE_END }
#endif

#endif


NAMESPACE_BEGIN( QuickHash )


class CMD4
{
public:
	enum{ DIGESTSIZE = SLC_MD4_DIGESTSIZE, HEXDIGESTSIZE = SLC_MD4_HEXDIGESTSIZE, BLOCKSIZE = SLC_MD4_BLOCKSIZE, ID = SLC_MD4_ALGID, CONTEXTSIZE = SLC_MD4_CONTEXTSIZE };

	CMD4(){ SL_MD4_Init( m_context ); }
	~CMD4(){}

	void Update( const unsigned char* pSrc, unsigned int nSrcLength ){ SL_MD4_Update( m_context, pSrc, nSrcLength ); }
	void Update( const char* pSrc ){ SL_MD4_UpdateStr( m_context, pSrc ); }
	void Final( unsigned char* pDest ){ SL_MD4_Final( m_context, pDest ); }
	void FinalHex( char* pDest, bool bUpper = false ){ SL_MD4_FinalHex( m_context, pDest, bUpper ? 1 : 0 ); }

	static void Calculate( unsigned char* pDest, const unsigned char* pSrc, unsigned int nSrcLength ) { SL_MD4_Calculate( pDest, pSrc, nSrcLength ); }
	static void Calculate( unsigned char* pDest, const char* pSrc ) { SL_MD4_CalculateStr( pDest, pSrc ); }
	static void CalculateHex( char* pDest, const unsigned char* pSrc, unsigned int nSrcLength, bool bUpper = false ){ SL_MD4_CalculateHex( pDest , pSrc, nSrcLength, bUpper ? 1 : 0 ); }
	static void CalculateHex( char* pDest, const char* pSrc, bool bUpper = false ){ SL_MD4_CalculateStrHex( pDest , pSrc, bUpper ? 1 : 0 ); }

private:
	unsigned char m_context[ CONTEXTSIZE ];
};

class CMD5
{
public:
	enum{ DIGESTSIZE = SLC_MD5_DIGESTSIZE, HEXDIGESTSIZE = SLC_MD5_HEXDIGESTSIZE, BLOCKSIZE = SLC_MD5_BLOCKSIZE, ID = SLC_MD5_ALGID, CONTEXTSIZE = SLC_MD5_CONTEXTSIZE };

	CMD5(){ SL_MD5_Init( m_context ); }
	~CMD5(){}

	void Update( const unsigned char* pSrc, unsigned int nSrcLength ){ SL_MD5_Update( m_context, pSrc, nSrcLength ); }
	void Update( const char* pSrc ){ SL_MD5_UpdateStr( m_context, pSrc ); }
	void Final( unsigned char* pDest ){ SL_MD5_Final( m_context, pDest ); }
	void FinalHex( char* pDest, bool bUpper = false ){ SL_MD5_FinalHex( m_context, pDest, bUpper ? 1 : 0 ); }

	static void Calculate( unsigned char* pDest, const unsigned char* pSrc, unsigned int nSrcLength ) { SL_MD5_Calculate( pDest, pSrc, nSrcLength ); }
	static void Calculate( unsigned char* pDest, const char* pSrc ) { SL_MD5_CalculateStr( pDest, pSrc ); }
	static void CalculateHex( char* pDest, const unsigned char* pSrc, unsigned int nSrcLength, bool bUpper = false ){ SL_MD5_CalculateHex( pDest , pSrc, nSrcLength, bUpper ? 1 : 0 ); }
	static void CalculateHex( char* pDest, const char* pSrc, bool bUpper = false ){ SL_MD5_CalculateStrHex( pDest , pSrc, bUpper ? 1 : 0 ); }

private:
	unsigned char m_context[ CONTEXTSIZE ];
};

class CSHA1
{
public:
	enum{ DIGESTSIZE = SLC_SHA1_DIGESTSIZE, HEXDIGESTSIZE = SLC_SHA1_HEXDIGESTSIZE, BLOCKSIZE = SLC_SHA1_BLOCKSIZE, ID = SLC_SHA1_ALGID, CONTEXTSIZE = SLC_SHA1_CONTEXTSIZE };

	CSHA1(){ SL_SHA1_Init( m_context ); }
	~CSHA1(){}

	void Update( const unsigned char* pSrc, unsigned int nSrcLength ){ SL_SHA1_Update( m_context, pSrc, nSrcLength ); }
	void Update( const char* pSrc ){ SL_SHA1_UpdateStr( m_context, pSrc ); }
	void Final( unsigned char* pDest ){ SL_SHA1_Final( m_context, pDest ); }
	void FinalHex( char* pDest, bool bUpper = false ){ SL_SHA1_FinalHex( m_context, pDest, bUpper ? 1 : 0 ); }

	static void Calculate( unsigned char* pDest, const unsigned char* pSrc, unsigned int nSrcLength ) { SL_SHA1_Calculate( pDest, pSrc, nSrcLength ); }
	static void Calculate( unsigned char* pDest, const char* pSrc ) { SL_SHA1_CalculateStr( pDest, pSrc ); }
	static void CalculateHex( char* pDest, const unsigned char* pSrc, unsigned int nSrcLength, bool bUpper = false ){ SL_SHA1_CalculateHex( pDest , pSrc, nSrcLength, bUpper ? 1 : 0 ); }
	static void CalculateStrHex( char* pDest, const char* pSrc, bool bUpper = false ){ SL_SHA1_CalculateStrHex( pDest , pSrc, bUpper ? 1 : 0 ); }

private:
	unsigned char m_context[ CONTEXTSIZE ];
};

class CSHA256
{
public:
	enum{ DIGESTSIZE = SLC_SHA256_DIGESTSIZE, HEXDIGESTSIZE = SLC_SHA256_HEXDIGESTSIZE, BLOCKSIZE = SLC_SHA256_BLOCKSIZE, ID = SLC_SHA256_ALGID, CONTEXTSIZE = SLC_SHA256_CONTEXTSIZE };

	CSHA256(){ SL_SHA256_Init( m_context ); }
	~CSHA256(){}

	void Update( const unsigned char* pSrc, unsigned int nSrcLength ){ SL_SHA256_Update( m_context, pSrc, nSrcLength ); }
	void Update( const char* pSrc ){ SL_SHA256_UpdateStr( m_context, pSrc ); }
	void Final( unsigned char* pDest ){ SL_SHA256_Final( m_context, pDest ); }
	void FinalHex( char* pDest, bool bUpper = false ){ SL_SHA256_FinalHex( m_context, pDest, bUpper ? 1 : 0 ); }

	static void Calculate( unsigned char* pDest, const unsigned char* pSrc, unsigned int nSrcLength ) { SL_SHA256_Calculate( pDest, pSrc, nSrcLength ); }
	static void Calculate( unsigned char* pDest, const char* pSrc ) { SL_SHA256_CalculateStr( pDest, pSrc ); }
	static void CalculateHex( char* pDest, const unsigned char* pSrc, unsigned int nSrcLength, bool bUpper = false ){ SL_SHA256_CalculateHex( pDest , pSrc, nSrcLength, bUpper ? 1 : 0 ); }
	static void CalculateHex( char* pDest, const char* pSrc, bool bUpper = false ){ SL_SHA256_CalculateStrHex( pDest , pSrc, bUpper ? 1 : 0 ); }

private:
	unsigned char m_context[ CONTEXTSIZE ];
};

class CSHA512
{
public:
	enum{ DIGESTSIZE = SLC_SHA512_DIGESTSIZE, HEXDIGESTSIZE = SLC_SHA512_HEXDIGESTSIZE, BLOCKSIZE = SLC_SHA512_BLOCKSIZE, ID = SLC_SHA512_ALGID, CONTEXTSIZE = SLC_SHA512_CONTEXTSIZE };

	CSHA512(){ SL_SHA512_Init( m_context ); }
	~CSHA512(){}

	void Update( const unsigned char* pSrc, unsigned int nSrcLength ){ SL_SHA512_Update( m_context, pSrc, nSrcLength ); }
	void Update( const char* pSrc ){ SL_SHA512_UpdateStr( m_context, pSrc ); }
	void Final( unsigned char* pDest ){ SL_SHA512_Final( m_context, pDest ); }
	void FinalHex( char* pDest, bool bUpper = false ){ SL_SHA512_FinalHex( m_context, pDest, bUpper ? 1 : 0 ); }

	static void Calculate( unsigned char* pDest, const unsigned char* pSrc, unsigned int nSrcLength ) { SL_SHA512_Calculate( pDest, pSrc, nSrcLength ); }
	static void Calculate( unsigned char* pDest, const char* pSrc ) { SL_SHA512_CalculateStr( pDest, pSrc ); }
	static void CalculateHex( char* pDest, const unsigned char* pSrc, unsigned int nSrcLength, bool bUpper = false ){ SL_SHA512_CalculateHex( pDest , pSrc, nSrcLength, bUpper ? 1 : 0 ); }
	static void CalculateHex( char* pDest, const char* pSrc, bool bUpper = false ){ SL_SHA512_CalculateStrHex( pDest , pSrc, bUpper ? 1 : 0 ); }

private:
	unsigned char m_context[ CONTEXTSIZE ];
};

class CSHA384
{
public:
	enum{ DIGESTSIZE = SLC_SHA384_DIGESTSIZE, HEXDIGESTSIZE = SLC_SHA384_HEXDIGESTSIZE, BLOCKSIZE = SLC_SHA384_BLOCKSIZE, ID = SLC_SHA384_ALGID, CONTEXTSIZE = SLC_SHA384_CONTEXTSIZE };

	CSHA384(){ SL_SHA384_Init( m_context ); }
	~CSHA384(){}

	void Update( const unsigned char* pSrc, unsigned int nSrcLength ){ SL_SHA384_Update( m_context, pSrc, nSrcLength ); }
	void Update( const char* pSrc ){ SL_SHA384_UpdateStr( m_context, pSrc ); }
	void Final( unsigned char* pDest ){ SL_SHA384_Final( m_context, pDest ); }
	void FinalHex( char* pDest, bool bUpper = false ){ SL_SHA384_FinalHex( m_context, pDest, bUpper ? 1 : 0 ); }

	static void Calculate( unsigned char* pDest, const unsigned char* pSrc, unsigned int nSrcLength ) { SL_SHA384_Calculate( pDest, pSrc, nSrcLength ); }
	static void Calculate( unsigned char* pDest, const char* pSrc ) { SL_SHA384_CalculateStr( pDest, pSrc ); }
	static void CalculateHex( char* pDest, const unsigned char* pSrc, unsigned int nSrcLength, bool bUpper = false ){ SL_SHA384_CalculateHex( pDest , pSrc, nSrcLength, bUpper ? 1 : 0 ); }
	static void CalculateHex( char* pDest, const char* pSrc, bool bUpper = false ){ SL_SHA384_CalculateStrHex( pDest , pSrc, bUpper ? 1 : 0 ); }

private:
	unsigned char m_context[ CONTEXTSIZE ];
};

class CRIPEMD160
{
public:
	enum{ DIGESTSIZE = SLC_RIPEMD160_DIGESTSIZE, HEXDIGESTSIZE = SLC_RIPEMD160_HEXDIGESTSIZE, BLOCKSIZE = SLC_RIPEMD160_BLOCKSIZE, ID = SLC_RIPEMD160_ALGID, CONTEXTSIZE = SLC_RIPEMD160_CONTEXTSIZE };

	CRIPEMD160(){ SL_RIPEMD160_Init( m_context ); }
	~CRIPEMD160(){}

	void Update( const unsigned char* pSrc, unsigned int nSrcLength ){ SL_RIPEMD160_Update( m_context, pSrc, nSrcLength ); }
	void Update( const char* pSrc ){ SL_RIPEMD160_UpdateStr( m_context, pSrc ); }
	void Final( unsigned char* pDest ){ SL_RIPEMD160_Final( m_context, pDest ); }
	void FinalHex( char* pDest, bool bUpper = false ){ SL_RIPEMD160_FinalHex( m_context, pDest, bUpper ? 1 : 0 ); }

	static void Calculate( unsigned char* pDest, const unsigned char* pSrc, unsigned int nSrcLength ) { SL_RIPEMD160_Calculate( pDest, pSrc, nSrcLength ); }
	static void Calculate( unsigned char* pDest, const char* pSrc ) { SL_RIPEMD160_CalculateStr( pDest, pSrc ); }
	static void CalculateHex( char* pDest, const unsigned char* pSrc, unsigned int nSrcLength, bool bUpper = false ){ SL_RIPEMD160_CalculateHex( pDest , pSrc, nSrcLength, bUpper ? 1 : 0 ); }
	static void CalculateHex( char* pDest, const char* pSrc, bool bUpper = false ){ SL_RIPEMD160_CalculateStrHex( pDest , pSrc, bUpper ? 1 : 0 ); }

private:
	unsigned char m_context[ CONTEXTSIZE ];
};

class CRIPEMD128
{
public:
	enum{ DIGESTSIZE = SLC_RIPEMD128_DIGESTSIZE, HEXDIGESTSIZE = SLC_RIPEMD128_HEXDIGESTSIZE, BLOCKSIZE = SLC_RIPEMD128_BLOCKSIZE, ID = SLC_RIPEMD128_ALGID, CONTEXTSIZE = SLC_RIPEMD128_CONTEXTSIZE };

	CRIPEMD128(){ SL_RIPEMD128_Init( m_context ); }
	~CRIPEMD128(){}

	void Update( const unsigned char* pSrc, unsigned int nSrcLength ){ SL_RIPEMD128_Update( m_context, pSrc, nSrcLength ); }
	void Update( const char* pSrc ){ SL_RIPEMD128_UpdateStr( m_context, pSrc ); }
	void Final( unsigned char* pDest ){ SL_RIPEMD128_Final( m_context, pDest ); }
	void FinalHex( char* pDest, bool bUpper = false ){ SL_RIPEMD128_FinalHex( m_context, pDest, bUpper ? 1 : 0 ); }

	static void Calculate( unsigned char* pDest, const unsigned char* pSrc, unsigned int nSrcLength ) { SL_RIPEMD128_Calculate( pDest, pSrc, nSrcLength ); }
	static void Calculate( unsigned char* pDest, const char* pSrc ) { SL_RIPEMD128_CalculateStr( pDest, pSrc ); }
	static void CalculateHex( char* pDest, const unsigned char* pSrc, unsigned int nSrcLength, bool bUpper = false ){ SL_RIPEMD128_CalculateHex( pDest , pSrc, nSrcLength, bUpper ? 1 : 0 ); }
	static void CalculateHex( char* pDest, const char* pSrc, bool bUpper = false ){ SL_RIPEMD128_CalculateStrHex( pDest , pSrc, bUpper ? 1 : 0 ); }

private:
	unsigned char m_context[ CONTEXTSIZE ];
};

class CRIPEMD256
{
public:
	enum{ DIGESTSIZE = SLC_RIPEMD256_DIGESTSIZE, HEXDIGESTSIZE = SLC_RIPEMD256_HEXDIGESTSIZE, BLOCKSIZE = SLC_RIPEMD256_BLOCKSIZE, ID = SLC_RIPEMD256_ALGID, CONTEXTSIZE = SLC_RIPEMD256_CONTEXTSIZE };

	CRIPEMD256(){ SL_RIPEMD256_Init( m_context ); }
	~CRIPEMD256(){}

	void Update( const unsigned char* pSrc, unsigned int nSrcLength ){ SL_RIPEMD256_Update( m_context, pSrc, nSrcLength ); }
	void Update( const char* pSrc ){ SL_RIPEMD256_UpdateStr( m_context, pSrc ); }
	void Final( unsigned char* pDest ){ SL_RIPEMD256_Final( m_context, pDest ); }
	void FinalHex( char* pDest, bool bUpper = false ){ SL_RIPEMD256_FinalHex( m_context, pDest, bUpper ? 1 : 0 ); }

	static void Calculate( unsigned char* pDest, const unsigned char* pSrc, unsigned int nSrcLength ) { SL_RIPEMD256_Calculate( pDest, pSrc, nSrcLength ); }
	static void Calculate( unsigned char* pDest, const char* pSrc ) { SL_RIPEMD256_CalculateStr( pDest, pSrc ); }
	static void CalculateHex( char* pDest, const unsigned char* pSrc, unsigned int nSrcLength, bool bUpper = false ){ SL_RIPEMD256_CalculateHex( pDest , pSrc, nSrcLength, bUpper ? 1 : 0 ); }
	static void CalculateHex( char* pDest, const char* pSrc, bool bUpper = false ){ SL_RIPEMD256_CalculateStrHex( pDest , pSrc, bUpper ? 1 : 0 ); }

private:
	unsigned char m_context[ CONTEXTSIZE ];
};

class CRIPEMD320
{
public:
	enum{ DIGESTSIZE = SLC_RIPEMD320_DIGESTSIZE, HEXDIGESTSIZE = SLC_RIPEMD320_HEXDIGESTSIZE, BLOCKSIZE = SLC_RIPEMD320_BLOCKSIZE, ID = SLC_RIPEMD320_ALGID, CONTEXTSIZE = SLC_RIPEMD320_CONTEXTSIZE };

	CRIPEMD320(){ SL_RIPEMD320_Init( m_context ); }
	~CRIPEMD320(){}

	void Update( const unsigned char* pSrc, unsigned int nSrcLength ){ SL_RIPEMD320_Update( m_context, pSrc, nSrcLength ); }
	void Update( const char* pSrc ){ SL_RIPEMD320_UpdateStr( m_context, pSrc ); }
	void Final( unsigned char* pDest ){ SL_RIPEMD320_Final( m_context, pDest ); }
	void FinalHex( char* pDest, bool bUpper = false ){ SL_RIPEMD320_FinalHex( m_context, pDest, bUpper ? 1 : 0 ); }

	static void Calculate( unsigned char* pDest, const unsigned char* pSrc, unsigned int nSrcLength ) { SL_RIPEMD320_Calculate( pDest, pSrc, nSrcLength ); }
	static void Calculate( unsigned char* pDest, const char* pSrc ) { SL_RIPEMD320_CalculateStr( pDest, pSrc ); }
	static void CalculateHex( char* pDest, const unsigned char* pSrc, unsigned int nSrcLength, bool bUpper = false ){ SL_RIPEMD320_CalculateHex( pDest , pSrc, nSrcLength, bUpper ? 1 : 0 ); }
	static void CalculateHex( char* pDest, const char* pSrc, bool bUpper = false ){ SL_RIPEMD320_CalculateStrHex( pDest , pSrc, bUpper ? 1 : 0 ); }

private:
	unsigned char m_context[ CONTEXTSIZE ];
};

class CPanama
{
public:
	enum{ DIGESTSIZE = SLC_PANAMA_DIGESTSIZE, HEXDIGESTSIZE = SLC_PANAMA_HEXDIGESTSIZE, BLOCKSIZE = SLC_PANAMA_BLOCKSIZE, ID = SLC_PANAMA_ALGID, CONTEXTSIZE = SLC_PANAMA_CONTEXTSIZE };

	CPanama(){ SL_PANAMA_Init( m_context ); }
	~CPanama(){}

	void Update( const unsigned char* pSrc, unsigned int nSrcLength ){ SL_PANAMA_Update( m_context, pSrc, nSrcLength ); }
	void Update( const char* pSrc ){ SL_PANAMA_UpdateStr( m_context, pSrc ); }
	void Final( unsigned char* pDest ){ SL_PANAMA_Final( m_context, pDest ); }
	void FinalHex( char* pDest, bool bUpper = false ){ SL_PANAMA_FinalHex( m_context, pDest, bUpper ? 1 : 0 ); }

	static void Calculate( unsigned char* pDest, const unsigned char* pSrc, unsigned int nSrcLength ) { SL_PANAMA_Calculate( pDest, pSrc, nSrcLength ); }
	static void Calculate( unsigned char* pDest, const char* pSrc ) { SL_PANAMA_CalculateStr( pDest, pSrc ); }
	static void CalculateHex( char* pDest, const unsigned char* pSrc, unsigned int nSrcLength, bool bUpper = false ){ SL_PANAMA_CalculateHex( pDest , pSrc, nSrcLength, bUpper ? 1 : 0 ); }
	static void CalculateHex( char* pDest, const char* pSrc, bool bUpper = false ){ SL_PANAMA_CalculateStrHex( pDest , pSrc, bUpper ? 1 : 0 ); }

private:
	unsigned char m_context[ CONTEXTSIZE ];
};

class CTiger
{
public:
	enum{ DIGESTSIZE = SLC_TIGER_DIGESTSIZE, HEXDIGESTSIZE = SLC_TIGER_HEXDIGESTSIZE, BLOCKSIZE = SLC_TIGER_BLOCKSIZE, ID = SLC_TIGER_ALGID, CONTEXTSIZE = SLC_TIGER_CONTEXTSIZE };

	CTiger(){ SL_TIGER_Init( m_context ); }
	~CTiger(){}

	void Update( const unsigned char* pSrc, unsigned int nSrcLength ){ SL_TIGER_Update( m_context, pSrc, nSrcLength ); }
	void Update( const char* pSrc ){ SL_TIGER_UpdateStr( m_context, pSrc ); }
	void Final( unsigned char* pDest ){ SL_TIGER_Final( m_context, pDest ); }
	void FinalHex( char* pDest, bool bUpper = false ){ SL_TIGER_FinalHex( m_context, pDest, bUpper ? 1 : 0 ); }

	static void Calculate( unsigned char* pDest, const unsigned char* pSrc, unsigned int nSrcLength ) { SL_TIGER_Calculate( pDest, pSrc, nSrcLength ); }
	static void Calculate( unsigned char* pDest, const char* pSrc ) { SL_TIGER_CalculateStr( pDest, pSrc ); }
	static void CalculateHex( char* pDest, const unsigned char* pSrc, unsigned int nSrcLength, bool bUpper = false ){ SL_TIGER_CalculateHex( pDest , pSrc, nSrcLength, bUpper ? 1 : 0 ); }
	static void CalculateHex( char* pDest, const char* pSrc, bool bUpper = false ){ SL_TIGER_CalculateStrHex( pDest , pSrc, bUpper ? 1 : 0 ); }

private:
	unsigned char m_context[ CONTEXTSIZE ];
};

class CMD2
{
public:
	enum{ DIGESTSIZE = SLC_MD2_DIGESTSIZE, HEXDIGESTSIZE = SLC_MD2_HEXDIGESTSIZE, CONTEXTSIZE = SLC_MD2_CONTEXTSIZE };

	CMD2(){ SL_MD2_Init( m_context ); }
	~CMD2(){}

	void Update( const unsigned char* pSrc, unsigned int nSrcLength ){ SL_MD2_Update( m_context, pSrc, nSrcLength ); }
	void Update( const char* pSrc ){ SL_MD2_UpdateStr( m_context, pSrc ); }
	void Final( unsigned char* pDest ){ SL_MD2_Final( m_context, pDest ); }
	void FinalHex( char* pDest, bool bUpper = false ){ SL_MD2_FinalHex( m_context, pDest, bUpper ? 1 : 0 ); }

	static void Calculate( unsigned char* pDest, const unsigned char* pSrc, unsigned int nSrcLength ) { SL_MD2_Calculate( pDest, pSrc, nSrcLength ); }
	static void Calculate( unsigned char* pDest, const char* pSrc ) { SL_MD2_CalculateStr( pDest, pSrc ); }
	static void CalculateHex( char* pDest, const unsigned char* pSrc, unsigned int nSrcLength, bool bUpper = false ){ SL_MD2_CalculateHex( pDest , pSrc, nSrcLength, bUpper ? 1 : 0 ); }
	static void CalculateHex( char* pDest, const char* pSrc, bool bUpper = false ){ SL_MD2_CalculateStrHex( pDest , pSrc,bUpper ? 1 : 0 ); }

private:
	unsigned char m_context[ CONTEXTSIZE ];
};

class CCRC32
{
public:
	enum{ DIGESTSIZE = SLC_CRC32_DIGESTSIZE, HEXDIGESTSIZE = SLC_CRC32_HEXDIGESTSIZE, CONTEXTSIZE = SLC_CRC32_CONTEXTSIZE };

	CCRC32(){ SL_CRC32_Init( m_context ); }
	~CCRC32(){}

	void Update( const unsigned char* pSrc, unsigned int nSrcLength ){ SL_CRC32_Update( m_context, pSrc, nSrcLength ); }
	void Update( const char* pSrc ){ SL_CRC32_UpdateStr( m_context, pSrc ); }
	void Final( unsigned char* pDest ){ SL_CRC32_Final( m_context, pDest ); }
	void FinalHex( char* pDest, bool bUpper = false ){ SL_CRC32_FinalHex( m_context, pDest, bUpper ? 1 : 0 ); }

	static void Calculate( unsigned char* pDest, const unsigned char* pSrc, unsigned int nSrcLength ) { SL_CRC32_Calculate( pDest, pSrc, nSrcLength ); }
	static void Calculate( unsigned char* pDest, const char* pSrc ) { SL_CRC32_CalculateStr( pDest, pSrc ); }
	static void CalculateHex( char* pDest, const unsigned char* pSrc, unsigned int nSrcLength, bool bUpper = false ){ SL_CRC32_CalculateHex( pDest , pSrc, nSrcLength, bUpper ? 1 : 0 ); }
	static void CalculateHex( char* pDest, const char* pSrc, bool bUpper = false ){ SL_CRC32_CalculateStrHex( pDest , pSrc, bUpper ? 1 : 0 ); }

private:
	unsigned char m_context[ CONTEXTSIZE ];
};

class CCRC16
{
public:
	enum{ DIGESTSIZE = SLC_CRC16_DIGESTSIZE, HEXDIGESTSIZE = SLC_CRC16_HEXDIGESTSIZE, CONTEXTSIZE = SLC_CRC16_CONTEXTSIZE };

	CCRC16(){ SL_CRC16_Init( m_context ); }
	~CCRC16(){}

	void Update( const unsigned char* pSrc, unsigned int nSrcLength ){ SL_CRC16_Update( m_context, pSrc, nSrcLength ); }
	void Update( const char* pSrc ){ SL_CRC16_UpdateStr( m_context, pSrc ); }
	void Final( unsigned char* pDest ){ SL_CRC16_Final( m_context, pDest ); }
	void FinalHex( char* pDest, bool bUpper = false ){ SL_CRC16_FinalHex( m_context, pDest, bUpper ? 1 : 0 ); }

	static void Calculate( unsigned char* pDest, const unsigned char* pSrc, unsigned int nSrcLength ) { SL_CRC16_Calculate( pDest, pSrc, nSrcLength ); }
	static void Calculate( unsigned char* pDest, const char* pSrc ) { SL_CRC16_CalculateStr( pDest, pSrc ); }
	static void CalculateHex( char* pDest, const unsigned char* pSrc, unsigned int nSrcLength, bool bUpper = false ){ SL_CRC16_CalculateHex( pDest , pSrc, nSrcLength, bUpper ? 1 : 0 ); }
	static void CalculateHex( char* pDest, const char* pSrc, bool bUpper = false ){ SL_CRC16_CalculateStrHex( pDest , pSrc, bUpper ? 1 : 0 ); }

private:
	unsigned char m_context[ CONTEXTSIZE ];
};

class CCRC16C
{
public:
	enum{ DIGESTSIZE = SLC_CRC16C_DIGESTSIZE, HEXDIGESTSIZE = SLC_CRC16C_HEXDIGESTSIZE, CONTEXTSIZE = SLC_CRC16C_CONTEXTSIZE };

	CCRC16C(){ SL_CRC16C_Init( m_context ); }
	~CCRC16C(){}

	void Update( const unsigned char* pSrc, unsigned int nSrcLength ){ SL_CRC16C_Update( m_context, pSrc, nSrcLength ); }
	void Update( const char* pSrc ){ SL_CRC16C_UpdateStr( m_context, pSrc ); }
	void Final( unsigned char* pDest ){ SL_CRC16C_Final( m_context, pDest ); }
	void FinalHex( char* pDest, bool bUpper = false ){ SL_CRC16C_FinalHex( m_context, pDest, bUpper ? 1 : 0 ); }

	static void Calculate( unsigned char* pDest, const unsigned char* pSrc, unsigned int nSrcLength ) { SL_CRC16C_Calculate( pDest, pSrc, nSrcLength ); }
	static void Calculate( unsigned char* pDest, const char* pSrc ) { SL_CRC16C_CalculateStr( pDest, pSrc ); }
	static void CalculateHex( char* pDest, const unsigned char* pSrc, unsigned int nSrcLength, bool bUpper = false ){ SL_CRC16C_CalculateHex( pDest , pSrc, nSrcLength, bUpper ? 1 : 0 ); }
	static void CalculateHex( char* pDest, const char* pSrc, bool bUpper = false ){ SL_CRC16C_CalculateStrHex( pDest , pSrc, bUpper ? 1 : 0 ); }

private:
	unsigned char m_context[ CONTEXTSIZE ];
};

class CAdler32
{
public:
	enum{ DIGESTSIZE = SLC_ADLER32_DIGESTSIZE, HEXDIGESTSIZE = SLC_ADLER32_HEXDIGESTSIZE, CONTEXTSIZE = SLC_ADLER32_CONTEXTSIZE };

	CAdler32(){ SL_ADLER32_Init( m_context ); }
	~CAdler32(){}

	void Update( const unsigned char* pSrc, unsigned int nSrcLength ){ SL_ADLER32_Update( m_context, pSrc, nSrcLength ); }
	void Update( const char* pSrc ){ SL_ADLER32_UpdateStr( m_context, pSrc ); }
	void Final( unsigned char* pDest ){ SL_ADLER32_Final( m_context, pDest ); }
	void FinalHex( char* pDest, bool bUpper = false ){ SL_ADLER32_FinalHex( m_context, pDest, bUpper ? 1 : 0 ); }

	static void Calculate( unsigned char* pDest, const unsigned char* pSrc, unsigned int nSrcLength ) { SL_ADLER32_Calculate( pDest, pSrc, nSrcLength ); }
	static void Calculate( unsigned char* pDest, const char* pSrc ) { SL_ADLER32_CalculateStr( pDest, pSrc ); }
	static void CalculateHex( char* pDest, const unsigned char* pSrc, unsigned int nSrcLength, bool bUpper = false ){ SL_ADLER32_CalculateHex( pDest , pSrc, nSrcLength, bUpper ? 1 : 0 ); }
	static void CalculateHex( char* pDest, const char* pSrc, bool bUpper = false ){ SL_ADLER32_CalculateStrHex( pDest , pSrc, bUpper ? 1 : 0 ); }

private:
	unsigned char m_context[ CONTEXTSIZE ];
};

template< class T >
class CHMAC
{
public:
	enum { DIGESTSIZE = T::DIGESTSIZE, HEXDIGESTSIZE = T::HEXDIGESTSIZE, BLOCKSIZE = T::BLOCKSIZE, CONTEXTSIZE = SLC_HMAC_CONTEXTSIZE( T::CONTEXTSIZE, T::BLOCKSIZE ), DEFAULTKEYLEN = 16 };
	CHMAC(){ SL_HMAC_Init( m_context, T::ID, NULL, 0 ); }
	explicit CHMAC( const unsigned char* pKey, unsigned int nKeyLength = DEFAULTKEYLEN ){ SL_HMAC_Init( m_context, T::ID, pKey, nKeyLength ); }
	explicit CHMAC( const char* pKey ){ SL_HMAC_InitKeyStr( m_context, T::ID, pKey ); }
	~CHMAC(){}

	void Init( const unsigned char* pKey, unsigned int nKeyLength = DEFAULTKEYLEN ){ SL_HMAC_Init( m_context, T::ID, pKey, nKeyLength ); }
	void Init( const char* pKey ){ SL_HMAC_InitKeyStr( m_context, T::ID, pKey ); }

	void Update( const unsigned char* pSrc, unsigned int nSrcLength ){ SL_HMAC_Update( m_context, pSrc, nSrcLength ); }
	void Update( const char* pSrc ){ SL_HMAC_UpdateStr( m_context, pSrc ); }
	void Final( unsigned char* pDest ){ SL_HMAC_Final( m_context, pDest ); }
	void FinalHex( char* pDest, bool bUpper = false ){ SL_HMAC_FinalHex( m_context, pDest, bUpper ? 1 : 0 ); }

	static void Calculate( unsigned char* pDest, const unsigned char* pSrc, unsigned int nSrcLength, const unsigned char* pKey, unsigned int nKeyLength = DEFAULTKEYLEN )
	{
		SL_HMAC_Calculate( T::ID, pDest, pSrc, nSrcLength, pKey, nKeyLength );
	}
	static void Calculate( unsigned char* pDest, const char* pSrc, const char* pKey )
	{
		SL_HMAC_CalculateStr( T::ID, pDest, pSrc, pKey );
	}
	static void CalculateHex( char* pDest, const unsigned char* pSrc, unsigned int nSrcLength, const unsigned char* pKey, unsigned int nKeyLength = DEFAULTKEYLEN, bool bUpper = false )
	{
		SL_HMAC_CalculateHex( T::ID, pDest, pSrc, nSrcLength, pKey, nKeyLength, bUpper ? 1 : 0 );
	}

	static void CalculateHex( char* pDest, const char* pSrc, const char* pKey, bool bUpper = false )
	{
		SL_HMAC_CalculateStrHex( T::ID, pDest, pSrc, pKey, bUpper ? 1 : 0 );
	}

private:
	unsigned char m_context[ CONTEXTSIZE ];
};

NAMESPACE_END

#endif /* __cplusplus */


#endif//#ifndef __QUICKHASH_H__
