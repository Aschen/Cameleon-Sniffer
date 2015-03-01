#ifndef DOMAINSOCKET_HH
#define DOMAINSOCKET_HH

#include <cstdlib>
#include <unistd.h>
#include <cerrno>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string>
#include <iostream>
#include <stdexcept>
#include <queue>

# define BUF_SIZE 512

class DomainSocket
{
public:
    class Disconnected : public std::exception
    {
    public:
        Disconnected(void) { }
        ~Disconnected(void) throw() { }
    };

public:
    typedef enum e_type
    {
        SERVER          = 0,
        SERVER_CLIENT,
        CLIENT
    } TYPE;

private:
    bool                        _run;
    DomainSocket::TYPE          _type;
    int                         _fd;
    struct sockaddr_un          _socket;
    std::queue<std::string>     _sendQueue;
    std::queue<std::string>     _recvQueue;

public:
    // Server or Client socket
    DomainSocket(const std::string &path, TYPE type);
    // Server_client socket
    DomainSocket(int fd, const struct sockaddr_un *socket);

    ~DomainSocket(void);

    DomainSocket                *acceptClient(void);
    void                        sendMsg(void);
    void                        recvMsg(void);
    void                        addMsg(const std::string &msg);
    const std::string           getMsg(void);
    void                        closeSocket(void);

public:
    bool                        isRunning(void) const;
    int                         fd(void) const;
    const struct sockaddr_un    *socket(void) const;
    bool                        somethingToSend(void) const;
    bool                        somethingToRecv(void) const;
};

#endif // DOMAINSOCKET_HH
