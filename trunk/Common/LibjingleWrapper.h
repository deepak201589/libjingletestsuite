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
* Relative Path: /Common/LibjingleWrapper.h
* The libjingle wrapper acts as an interface between the test suite and libjingle.
* This file is the header description of LibjingleWrapper
* This component is called by the sender agent to transfer a file between peers.
* This component is called by the report generator to get the results of file transfer.
*/

#ifndef __libjinglewrapper_h
#define __libjinglewrapper_h

#pragma once
#include "Common.h"
#include "Utils.h"
#include <iomanip>
#include <time.h>
#include <string.h>

#include "talk/base/fileutils.h"
#include "talk/base/pathutils.h"
#include "talk/base/helpers.h"
#include "talk/base/httpclient.h"
#include "talk/base/logging.h"
#include "talk/base/physicalsocketserver.h"
#include "talk/base/ssladapter.h"
#include "talk/xmpp/xmppclientsettings.h"
#include "talk/examples/login/xmppthread.h"
#include "talk/examples/login/xmppauth.h"
#include "talk/p2p/client/httpportallocator.h"
#include "talk/p2p/client/sessionmanagertask.h"
#include "talk/session/fileshare/fileshare.h"
#include "talk/examples/login/presencepushtask.h"
#include "talk/examples/login/presenceouttask.h"
#include "talk/examples/login/jingleinfotask.h"
#include "talk/examples/login/jingleinfotask.cc"
#include "talk/examples/login/presenceouttask.cc"
#include "talk/examples/login/presencepushtask.cc"

#include "Scenario.h"
#include "ConfigManager.h"

#ifndef WIN32
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <iomanip>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/wait.h>
#else
#include <direct.h>
#include "talk/base/win32.h"
//typedef _getcwd getcwd;
#endif


/*
* Class Name: LibjingleWrapper
* Purpose: The libjingle wrapper acts as an interface between the test suite and libjingle.
*/

class COMMON_API LibjingleWrapper
{
public:
	LibjingleWrapper(void);
	~LibjingleWrapper(void);
	bool DoTransfer(Scenario* secenario);
	bool ReceiveFile(string username, string password, string recvPath);

private:
	bool TransferFile(char* fname, char* recvId);
	bool Login(char* username, char* password);
	void PrepareForTransfer(void);
	std::string GetTransferStatus();
	bool StopTransfer();

	Utils* utils;
	ConfigManager* cfg;
};

#endif
