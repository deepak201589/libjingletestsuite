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
#ifndef __socketmanager_h
#define __socketmanager_h

#pragma once

#include <winSock2.h>
#include <stdlib.h>
#include "Common.h"
#include "ErrorCode.h"
#include "Debugging.h"


#define DEFAULT_CONN	5
#define CLIENT_ONLY		-5

typedef struct sockaddr_in SockAddr;

class COMMON_API SocketManager
{
public:
	SocketManager(void);
	~SocketManager(void);

public:
	/* functions for server */
	int ServerInit(int);
	int Listen(int);
	int Accept();

	/* functions for client */
	void ClientInit(char *, int);
	int Connect();

	/* common functions */
	int SendData(int, char *, int);
	int ReceiveData(int, char *, int);
	int CloseConnection();

private:
	void InitConnArray(int);

private:

	SOCKET m_Conn;
	SOCKET *m_Guests; /* only for server side */
	WSADATA m_WsaData;
	SockAddr m_Saddr;
	int m_nConnected; /* the number of clients connected */
	int m_nMaxConnected;
};

#endif