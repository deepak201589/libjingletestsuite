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
* File: /Common/LibjingleWrapper.cpp
* Author: Renuka Wariyar
* Description:
* The libjingle wrapper acts as an interface between the test suite and libjingle.
* This file is the implementation of the class LibjingleWrapper
* This component is called by the sender agent to transfer a file between peers.
* This component is called by the report generator to get the results of file transfer.

* Everything except the members of LibjingleWrapper class are taken
* from the program pcp_main from libjingle code

Updates
=======
------------------------------------------------------------------------
| No. | Date |         Author        |          Reason for update       |
------------------------------------------------------------------------
|  1. |      |                       |									|
------------------------------------------------------------------------

*/

#include "StdAfx.h"
#include "LibjingleWrapper.h"

LibjingleWrapper::LibjingleWrapper(void)
{
	utils = new Utils();
	cfg = ConfigManager::Instance();
}

LibjingleWrapper::~LibjingleWrapper(void)
{
	if (utils)
		delete utils;
}

buzz::Jid j;
buzz::XmppClientSettings xcs;

class FileShareClient : public sigslot::has_slots<>, public talk_base::MessageHandler {
public:
	FileShareClient(buzz::XmppClient *xmppclient, const buzz::Jid &send_to, const cricket::FileShareManifest *manifest, std::string root_dir) :
	  xmpp_client_(xmppclient),
		  root_dir_(root_dir),
		  send_to_jid_(send_to),
		  waiting_for_file_(send_to == buzz::JID_EMPTY),  
		  manifest_(manifest) {}

	  void OnStateChange(buzz::XmppEngine::State state) {
		  switch (state) {
	case buzz::XmppEngine::STATE_START:
		std::cout << "Connecting..." << std::endl;
		break;
	case buzz::XmppEngine::STATE_OPENING:
		std::cout << "Logging in. " << std::endl;
		break;
	case buzz::XmppEngine::STATE_OPEN:
		std::cout << "Logged in as " << xmpp_client_->jid().Str() << std::endl;
		if (!waiting_for_file_)
			std::cout << "Waiting for " << send_to_jid_.Str() << std::endl;
		OnSignon();
		break;
	case buzz::XmppEngine::STATE_CLOSED:
		std::cout << "Logged out." << std::endl;
		break;
		  }
	  }

private:

	enum {
		MSG_STOP,
	};

	void OnJingleInfo(const std::string & relay_token,
		const std::vector<std::string> &relay_addresses,
		const std::vector<talk_base::SocketAddress> &stun_addresses) {
			port_allocator_->SetStunHosts(stun_addresses);
			port_allocator_->SetRelayHosts(relay_addresses);
			port_allocator_->SetRelayToken(relay_token);
	}


	void OnStatusUpdate(const buzz::Status &status) {
		if (status.available() && status.fileshare_capability()) {

			// A contact's status has changed. If the person we're looking for is online and able to receive
			// files, send it.
			if (send_to_jid_.BareEquals(status.jid())) {
				std::cout << send_to_jid_.Str() << " has signed on." << std::endl;
				cricket::FileShareSession* share = file_share_session_client_->CreateFileShareSession();
				share->Share(status.jid(), const_cast<cricket::FileShareManifest*>(manifest_));
				send_to_jid_ = buzz::Jid("");
			}

		}
	}

	void OnMessage(talk_base::Message *m) {
		ASSERT(m->message_id == MSG_STOP);
		talk_base::Thread *thread = talk_base::ThreadManager::CurrentThread();
		delete session_;
		thread->Stop();
	}

	std::string filesize_to_string(unsigned int size) {
		double size_display;
		std::string format;
		std::stringstream ret;

		// the comparisons to 1000 * (2^(n10)) are intentional
		// it's so you don't see something like "1023 bytes",
		// instead you'll see ".9 KB"

		if (size < 1000) {
			format = "Bytes";
			size_display = size;
		} else if (size < 1000 * 1024) {
			format = "KiB";
			size_display = (double)size / 1024.0;
		} else if (size < 1000 * 1024 * 1024) {
			format = "MiB";
			size_display = (double)size / (1024.0 * 1024.0);
		} else {
			format = "GiB";
			size_display = (double)size / (1024.0 * 1024.0 * 1024.0);
		}

		ret << std::setprecision(1) << std::setiosflags(std::ios::fixed) << size_display << " " << format;    
		return ret.str();
	}

	void OnSessionState(cricket::FileShareState state) {
		talk_base::Thread *thread = talk_base::ThreadManager::CurrentThread();
		std::stringstream manifest_description;

		switch(state) {
	case cricket::FS_OFFER:

		// The offer has been made; print a summary of it and, if it's an incoming transfer, accept it

		if (manifest_->size() == 1)
			manifest_description <<  session_->manifest()->item(0).name;
		else if (session_->manifest()->GetFileCount() && session_->manifest()->GetFolderCount())
			manifest_description <<  session_->manifest()->GetFileCount() << " files and " <<
			session_->manifest()->GetFolderCount() << " directories";
		else if (session_->manifest()->GetFileCount() > 0)
			manifest_description <<  session_->manifest()->GetFileCount() << " files";
		else
			manifest_description <<  session_->manifest()->GetFolderCount() << " directories"; 

		size_t filesize;
		if (!session_->GetTotalSize(filesize)) {
			manifest_description << " (Unknown size)";
		} else {
			manifest_description << " (" << filesize_to_string(filesize) << ")";
		}    
		if (session_->is_sender()) {
			std::cout << "Offering " << manifest_description.str()  << " to " << send_to_jid_.Str() << std::endl;
		} else if (waiting_for_file_) {
			std::cout << "Receiving " << manifest_description.str() << " from " << session_->jid().BareJid().Str() << std::endl;
			session_->Accept();
			waiting_for_file_ = false;
		}
		break;
	case cricket::FS_TRANSFER:
		std::cout << "File transfer started." << std::endl;
		break;
	case cricket::FS_COMPLETE:
		thread->Post(this, MSG_STOP);
		std::cout << std::endl << "File transfer completed." << std::endl;
		break;
	case cricket::FS_LOCAL_CANCEL:
	case cricket::FS_REMOTE_CANCEL:
		std::cout << std::endl << "File transfer cancelled." << std::endl;
		thread->Post(this, MSG_STOP);
		break;
	case cricket::FS_FAILURE:
		std::cout << std::endl << "File transfer failed." << std::endl;
		thread->Post(this, MSG_STOP);
		break;
		}
	}

	void OnUpdateProgress(cricket::FileShareSession *sess) {
		// Progress has occured on the transfer; update the UI

		size_t totalsize, progress;
		std::string itemname;
		unsigned int width = 79;

		if(sess->GetTotalSize(totalsize) && sess->GetProgress(progress) && sess->GetCurrentItemName(&itemname)) {
			float percent = (float)progress / totalsize;
			unsigned int progressbar_width = (width * 4) / 5;

			const char *filename = itemname.c_str();
			std::cout.put('\r');
			for (unsigned int l = 0; l < width; l++) {
				if (l < percent * progressbar_width)
					std::cout.put('#');
				else if (l > progressbar_width && l < progressbar_width + 1 + strlen(filename))
					std::cout.put(filename[l-(progressbar_width + 1)]);
				else
					std::cout.put(' ');
			}
			std::cout.flush();
		}
	}

	void OnResampleImage(std::string path, int width, int height, talk_base::HttpTransaction *trans) {  

		talk_base::FileStream *s = new talk_base::FileStream();
		if (s->Open(path.c_str(), "rb"))
			session_->ResampleComplete(s, trans, true);  
		else {
			delete s;
			session_->ResampleComplete(NULL, trans, false);
		}
	}

	void OnFileShareSessionCreate(cricket::FileShareSession *sess) {
		session_ = sess;
		sess->SignalState.connect(this, &FileShareClient::OnSessionState);
		sess->SignalNextFile.connect(this, &FileShareClient::OnUpdateProgress);
		sess->SignalUpdateProgress.connect(this, &FileShareClient::OnUpdateProgress);
		sess->SignalResampleImage.connect(this, &FileShareClient::OnResampleImage);
		sess->SetLocalFolder(root_dir_);
	}

	void OnSignon() {
		std::string client_unique = xmpp_client_->jid().Str();
		cricket::InitRandom(client_unique.c_str(), client_unique.size());

		buzz::PresencePushTask *presence_push_ = new buzz::PresencePushTask(xmpp_client_);
		presence_push_->SignalStatusUpdate.connect(this, &FileShareClient::OnStatusUpdate);
		presence_push_->Start();

		buzz::Status my_status;
		my_status.set_jid(xmpp_client_->jid());
		my_status.set_available(true);
		my_status.set_show(buzz::Status::SHOW_ONLINE);
		my_status.set_priority(0);
		my_status.set_know_capabilities(true);
		my_status.set_fileshare_capability(true);
		my_status.set_is_google_client(true);
		my_status.set_version("1.0.0.66");

		buzz::PresenceOutTask* presence_out_ =
			new buzz::PresenceOutTask(xmpp_client_);
		presence_out_->Send(my_status);
		presence_out_->Start();

		port_allocator_.reset(new cricket::HttpPortAllocator(&network_manager_, "pcp"));

		session_manager_.reset(new cricket::SessionManager(port_allocator_.get(), NULL));

		cricket::SessionManagerTask * session_manager_task = new cricket::SessionManagerTask(xmpp_client_, session_manager_.get());
		session_manager_task->EnableOutgoingMessages();
		session_manager_task->Start();

		buzz::JingleInfoTask *jingle_info_task = new buzz::JingleInfoTask(xmpp_client_);
		jingle_info_task->RefreshJingleInfoNow();
		jingle_info_task->SignalJingleInfo.connect(this, &FileShareClient::OnJingleInfo);
		jingle_info_task->Start();

		file_share_session_client_.reset(new cricket::FileShareSessionClient(session_manager_.get(), xmpp_client_->jid(), "pcp"));
		file_share_session_client_->SignalFileShareSessionCreate.connect(this, &FileShareClient::OnFileShareSessionCreate);
		session_manager_->AddClient(NS_GOOGLE_SHARE, file_share_session_client_.get());
	}

	talk_base::NetworkManager network_manager_;
	talk_base::scoped_ptr<cricket::HttpPortAllocator> port_allocator_;
	talk_base::scoped_ptr<cricket::SessionManager> session_manager_;
	talk_base::scoped_ptr<cricket::FileShareSessionClient> file_share_session_client_;
	buzz::XmppClient *xmpp_client_;
	buzz::Jid send_to_jid_;
	const cricket::FileShareManifest *manifest_;
	cricket::FileShareSession *session_;
	bool waiting_for_file_;
	std::string root_dir_;
};



static unsigned int get_dir_size(const char *directory) {
  unsigned int total = 0;
  talk_base::DirectoryIterator iter;
  talk_base::Pathname path;
  path.AppendFolder(directory);
  iter.Iterate(path.pathname());
  while (iter.Next())  {
    if (iter.Name() == "." || iter.Name() == "..")
      continue;
    if (iter.IsDirectory()) {
      path.AppendPathname(iter.Name());
      total += get_dir_size(path.pathname().c_str());
    }
    else
      total += iter.FileSize();
  }
  return total;
}

/** 
 * TransferFile: Private method called by DoTransfer to send the file
 * @param filename   Filename with absolute path <e.g.: C:\testfiles\file1.jpg>
 * @param receiverId Username of receiver <e.g.: receiver@gmail.com>
 * @see 
 * @return bool If the transfer was successful or not
 */
bool LibjingleWrapper::TransferFile(char* filename, char* receiverId){
	bool success = true;
	talk_base::PhysicalSocketServer ss;
	talk_base::Thread main_thread(&ss);
	talk_base::ThreadManager::SetCurrent(&main_thread);
	XmppPump pump;

	char cwd[256];
	getcwd(cwd, sizeof(cwd));

	// Read the file
	cricket::FileShareManifest *manifest = new cricket::FileShareManifest();

	// Additionally, we should check for image files here, and call
    // AddImage on the manifest with their file size and image size.
    // The receiving client can then request previews of those images
    if (talk_base::Filesystem::IsFolder(std::string(filename))) {
		manifest->AddFolder(filename, get_dir_size(filename));
    } else {
      size_t size = 0;
      talk_base::Filesystem::GetFileSize(std::string(filename), &size);
      manifest->AddFile(filename, size);
    }

	buzz::Jid receiverJid = buzz::Jid(receiverId);

	FileShareClient fs_client(pump.client(), receiverJid, manifest, cwd);

	//Open connection

	pump.client()->SignalStateChange.connect(&fs_client, &FileShareClient::OnStateChange);

	pump.DoLogin(xcs, new XmppSocket(true), NULL);
	//send file
	main_thread.Run();

	//Close connection
	pump.DoDisconnect();
	
	// Access violation
	//if (manifest)
	//	delete manifest;

	return success;
}
/** 
 * Login: Private method called by DoTransfer to validate and set 
 *		  the username and password to XmppClientSettings 
 * @param username Username of sender <e.g.: sender@gmail.com>
 * @param password Password of sender <e.g.: p9sSw0rD>
 * @see 
 * @return bool If the username was valid or not 
 */
bool LibjingleWrapper::Login(char* username, char* password){
		bool status=true;
		talk_base::InsecureCryptStringImpl pass;

		j = buzz::Jid(username);
		if (!j.IsValid() || j.node() == "") {
			printf("Invalid JID. JIDs should be in the form user@domain\n");
			status = false;
		}
		pass.password() = password;

		xcs.set_user(j.node());

		//TODO: Check what this means
		xcs.set_resource("TestAgent");

		xcs.set_host(j.domain());
		xcs.set_use_tls(true);

		xcs.set_pass(talk_base::CryptString(pass));
		xcs.set_server(talk_base::SocketAddress("talk.google.com", 5222));

		return status;
	}

/**
 * DoTransfer: Public method called by Sender agent to transfer a file
 * @param scenario Scenario object
 * @see Login(),transferFile()
 * @return success If the transfer has been successful or not
 */
bool LibjingleWrapper::DoTransfer(Scenario* scenario)
{
	char* username = utils->StringToCharPointer(scenario->GetSenderLoginId());
	char* password = utils->StringToCharPointer(scenario->GetSenderPassword());
	char* receiverId = utils->StringToCharPointer(scenario->GetReceiverLoginId());
	char* filePath = utils->StringToCharPointer(scenario->GetSenderFilePath());

	//1.login
	bool loginStatus = Login(username, password);
	bool transferStatus = false;

	//2.transfer file

	if(loginStatus)
	{
		transferStatus = TransferFile(filePath, receiverId);
	}

	delete username;
	delete password;
	delete filePath;
	delete receiverId;

	return transferStatus;
}

/**
 * method description
 * @param param1 the description of param1
 * @param param2 the description of param2
 * @see othermethod()
 * @return returnValue the description of returnValue
 * 
 */
bool LibjingleWrapper::ReceiveFile(string username, string password, string recvPath)
{
	bool transferStatus = false;

	char* uname = utils->StringToCharPointer(username);
	char* passwd = utils->StringToCharPointer(password);

	transferStatus = Login(uname, passwd);

	talk_base::PhysicalSocketServer ss;
	talk_base::Thread main_thread(&ss);
	talk_base::ThreadManager::SetCurrent(&main_thread);

	buzz::Jid j = buzz::JID_EMPTY;
	XmppPump pump;
	char cwd[256];
	getcwd(cwd, sizeof(cwd));

	// Read the file
	cricket::FileShareManifest *manifest = new cricket::FileShareManifest();

	strcpy(cwd, recvPath.c_str());
	FileShareClient fs_client(pump.client(), j, manifest, cwd);

	pump.client()->SignalStateChange.connect(&fs_client, &FileShareClient::OnStateChange);

	pump.DoLogin(xcs, new XmppSocket(true), NULL);
	main_thread.Run();
	pump.DoDisconnect();

	delete uname;
	delete passwd;
	return transferStatus;
}
