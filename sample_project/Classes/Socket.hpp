//
//  Socket.hpp
//  HelloCpp-mobile
//
//  Created by Guan Ying Chen on 2019/5/24.
//

#ifndef _ODSOCKET_H_
#define _ODSOCKET_H_


#ifdef WIN32
#include <winsock.h>
typedef int             socklen_t;
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <arpa/inet.h>
typedef int             SOCKET;
#define INVALID_SOCKET  -1
#define SOCKET_ERROR    -1

#endif


class Socket {
    
public:
    Socket(SOCKET sock = INVALID_SOCKET);
    
    ~Socket();
    
    bool Create(int af, int type, int protocol = 0);
    
    bool Connect(const char* ip, unsigned short port);
    
    bool Bind(unsigned short port);
    
    bool Listen(int backlog = 5);
    
    bool Accept(Socket& s, char* fromip = NULL);
    
    int Send(const char* buf, int len, int flags = 0);
    
    int Recv(char* buf, int len, int flags = 0);
    
    int Close();
    
    int GetError();
    
    static int Init();
    
    static int Clean();
    
    static bool DnsParse(const char* domain, char* ip);
    
    Socket& operator = (SOCKET s);
    
    operator SOCKET ();
    
    void setNonBlocking();
    void setSendTimeOut(int time);
    void setRecvTimeOut(int time);
    
protected:
    SOCKET mySocket;
    
};
#endif
