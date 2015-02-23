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

public:
    // Server or Client socket
    DomainSocket(const std::string &path, TYPE type);
    // Server_client socket
    DomainSocket(int fd, const struct sockaddr_un *socket);

    ~DomainSocket(void);

    DomainSocket                *acceptClient(void);
    void                        sendMsg(const std::string &msg);
    std::string                 recvMsg(void);
    void                        closeSocket(void);

public:
    bool                        isRunning(void) const;
    int                         fd(void) const;
    const struct sockaddr_un    *socket(void) const;
};

#endif // DOMAINSOCKET_HH
