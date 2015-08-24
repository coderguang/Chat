#ifndef _COMMON_NET_SOCKET_WINSOCKET_H_
#define _COMMON_NET_SOCKET_WINSOCKET_H_

/*
* base in windows socket
* auto:coderguang
* email:royalchen@royalchen.com
*/

namespace GCommon{
	namespace GNet{
		namespace GSocket{		

#include <winsock2.h>
#include <string>
#include "log/CLog.h"
#include "util
			/FuncPtr.h"


class CWinSocket{
public:
	CWinSocket(std::string ip, int port, int family, int sockType);
	virtual ~CWinSocket();
	void init(voFuncStr *newData);
	void send(std::string msg);
	void close();
protected:
	void send();


};		

		}
	}
}

#endif
