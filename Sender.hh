#ifndef SENDER_HH
#define SENDER_HH

#include <cstdlib>
#include <unistd.h>
#include <cerrno>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string>
#include <iostream>

#include "DomainSocket.hh"

class Sender
{
private:
    DomainSocket                _local;
    bool                        _run;

public:
    Sender(const std::string &path, const std::string &msg);

    void                        start(void);

private:
    int                         initSelect(struct timeval *tv, fd_set *readfds, fd_set *writefds);
    void                        handleSockets(void);
    void                        eventTerminal(void);
    void                        eventSocketRead(void);
    void                        eventSocketWrite(void);
    void                        eventClients(fd_set *readfds, fd_set *writefds);
};

#endif // SENDER_HH
