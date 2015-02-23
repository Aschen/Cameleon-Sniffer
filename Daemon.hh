#ifndef DAEMON_HH
#define DAEMON_HH

#include <cstdlib>
#include <unistd.h>
#include <cerrno>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string>
#include <iostream>
#include <vector>
#include <stdexcept>

#include "DomainSocket.hh"
#include "Prompt.hh"

class Daemon
{
private:
    DomainSocket                _local;
    bool                        _run;
    Prompt                      _prompt;
    std::vector<DomainSocket*>  _clients;

public:
    Daemon(const std::string &path);
    ~Daemon(void);

    void                        start(void);

private:
    int                         initSelect(struct timeval *tv, fd_set *readfds, fd_set *writefds);
    void                        handleSockets(void);
    void                        eventTerminal(void);
    void                        eventServer(void);
    void                        eventClients(fd_set *readfds, fd_set *writefds);
};

#endif // DAEMON_HH
