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
/*
* File: /Common/SocketManger.cpp
* Author: Kimyung Han
* Description:
* SocketManager provides TCP/IP connection services to other components 

Updates
=======
------------------------------------------------------------------------
| No. | Date |         Author        |          Reason for update       |
------------------------------------------------------------------------
|  1. |      |                       |									|
------------------------------------------------------------------------

*/


#include "StdAfx.h"
#include "SocketManager.h"

/* 
 * Constructor 
 */

SocketManager::SocketManager(void)
{
	m_Guests = NULL;
	m_nConnected = 0;
	m_nMaxConnected = 0;
}

/** 
 * Destructor 
 */

SocketManager::~SocketManager(void)
{
	if (m_Guests)
		free (m_Guests);
}

/**
 * Initialize connection array for server
 * @param nMaxConn maximum number of connection that a server can accommodate
 * @return none
 */
void SocketManager::InitConnArray(int nMaxConn)
{
	int i = 0;
	
	m_nMaxConnected = ((nMaxConn > 0)? nMaxConn : DEFAULT_CONN);
	m_Guests = (SOCKET *)malloc(sizeof(SOCKET)* m_nMaxConnected);

	for (i = 0; i < nMaxConn; i++) 
	{
		m_Guests[i] = INVALID_SOCKET;
	}
	m_nConnected = 0;
}

/**
* Initialize connection for client
* @param ipAddr server ip address that a client try to connect to 
* @param port port number of a server to which a server is listening to
* @return none
*/

void SocketManager::ClientInit(char *ipAddr, int port) 
{	
	/* 1. Data structure setup */
	WSAStartup(MAKEWORD(2,2), &m_WsaData);
	
	/* 2. socket object creation */
	m_Conn = socket(AF_INET,SOCK_STREAM,0);

	/* 3. address structure initialization */
	memset(&m_Saddr, 0, sizeof(SockAddr));
	m_Saddr.sin_family = AF_INET;
	m_Saddr.sin_addr.s_addr = inet_addr(ipAddr);
	m_Saddr.sin_port = htons(port);
}

/**
* Initialize connection for server
* @param port port number of a server to which a server will listen to
* @return SUCCESS if initialization succeed, SOCKET_ERROR if binding fails
*/

int SocketManager::ServerInit(int port) 
{
	int err = SUCCESS;
	
	/* 1. Data structure setup */
	WSAStartup(MAKEWORD(2,2), &m_WsaData);
	
	/* 2. socket object creation */
	m_Conn = socket(AF_INET,SOCK_STREAM,0);

	/* 3. address structure initialization */
	memset(&m_Saddr, 0, sizeof(sockaddr_in));
	m_Saddr.sin_family = AF_INET;
	m_Saddr.sin_addr.s_addr = INADDR_ANY;
	m_Saddr.sin_port = htons(port);

	/* 4. binding */
	
	err = ::bind(m_Conn, (sockaddr *) &m_Saddr, sizeof(sockaddr_in));

	return err;
}

/**
* accept a request of client for connection
* @param none
* @return SUCCESS if accept succeeds, a negative NO_SPACE and SOCKET_ERROR if accept fails
*/
int SocketManager::Accept() 
{
	int i = 0;
	int ret = -(NO_SPACE);
	int addrSize = sizeof(m_Saddr);

	if (m_nConnected == m_nMaxConnected)
		return ret;

	for (i = 0; i< m_nMaxConnected; i++) 
	{
		if (m_Guests[i] == INVALID_SOCKET)
			break;
	}

	if (i == m_nMaxConnected) 
	{
		return ret;
	} 
	else 
	{
		m_Guests[i] = accept (m_Conn, (sockaddr*)&m_Saddr, &addrSize);
		ret = i; /* connection id */
		m_nConnected++;
	}

	return ret;
}

/**
* Listen to a connection request of a client
* @param nMaxConnected maximum number of connection that a server wants to accommodate
* @return SUCCESS if Listen succeed, SOCKET_ERROR if accept fails
*/

int SocketManager::Listen(int nMaxConnected)
{
	int ret = SUCCESS;
	int nDefaultValue = 5;

	if (!m_Guests && m_nConnected == 0) 
	{ /* initial listening setup */
		InitConnArray(nMaxConnected);
	} 
	m_nMaxConnected = nMaxConnected;
	
	ret = ::listen(m_Conn, m_nMaxConnected);

	return ret;
}

/**
* send data to the other peer
* @param ConID connection id which corresponds to actual socket object. Pass CLIENT_ONLY for client.
* @param buf a pointer to data buffer
* @param nToWrite the size of data to be sent
* @return the number of bytes sent if initialization succeed, a negative INVALID_ARGUMENT if a given
*		 is not valid or a negative FAILURE on any socket error
*/
int SocketManager::SendData(int ConID, char *buf, int nToWrite)
{
	int nWritten = 0;
	int err = SUCCESS;
	int nLeft = 0;
	char *ptr = NULL;
	SOCKET conn = INVALID_SOCKET;

	if (ConID == CLIENT_ONLY)
		conn = m_Conn;
	else 
	{
		if (ConID >= m_nMaxConnected || m_Guests[ConID] == INVALID_SOCKET)
			return (-INVALID_ARGUMENT);
		conn = m_Guests[ConID];
	}
	/* Read data as much as nToWrite */

	nLeft = nToWrite;
	ptr = buf;

	while (nLeft > 0)
	{
		if ((nWritten = send(conn, ptr, nLeft, 0)) < 0) 
		{	
			err = WSAGetLastError();
			if (err == WSAEINTR)
				nWritten = 0; /* call send again */
			else {
				//INFO("socket err: %d", err);			
				return (-FAILURE);
			}
		} 
		nLeft -= nWritten;
		ptr += nWritten;
	}
	return (nToWrite - nLeft);
}

/**
* receive data from the other peer
* @param ConID connection id which corresponds to actual socket object. Pass CLIENT_ONLY for client.
* @param buf a pointer to data buffer
* @param nToRead the size of data to be received
* @return the number of bytes received if initialization succeed, a negative INVALID_ARGUMENT if a given
*		 is not valid or a negative FAILURE on any socket error
*/
int SocketManager::ReceiveData(int ConID, char *buf, int nToRead)
{
	int nReceived = 0;
	int nLeft = 0;
	int err = SUCCESS;
	char *ptr = NULL;
	SOCKET conn = INVALID_SOCKET;
	
	if (ConID == CLIENT_ONLY)
		conn = m_Conn;
	else 
	{
		if (ConID >= m_nMaxConnected || m_Guests[ConID] == INVALID_SOCKET)
			return (-INVALID_ARGUMENT);
		conn = m_Guests[ConID];
	}

	nLeft = nToRead;
	ptr = buf;
	while (nLeft > 0)
	{
		if ((nReceived = recv(conn, ptr, nToRead, 0)) < 0){
			err = WSAGetLastError();
			if (err = WSAEINTR)
				nReceived = 0;
			else
				return (-FAILURE);
		} else if (nReceived == 0) /* end of data */
			break;

		nLeft -= nReceived;
		ptr += nReceived;
	}
	return (nToRead - nLeft);
}

/**
* close connection
* @param none
* @return SUCCESS if connection close succeeds, a negative FAILURE on any socket error
*/
int SocketManager::CloseConnection()
{
	int ret = SUCCESS;
	
	ret = closesocket(m_Conn);

	if (ret == SOCKET_ERROR)
		ret = (-FAILURE);

	WSACleanup();

	return ret;
}

/**
* connect to a server peer
* @param none
* @return SUCCESS if connection succeeds, a negative FAILURE on any socket error
*/
int SocketManager::Connect() 
{
	int ret = SUCCESS;

	ret = connect(m_Conn, (sockaddr *)& m_Saddr, sizeof(sockaddr_in));
	if (ret == SOCKET_ERROR)
		ret = (-FAILURE);
	
	return ret;
}