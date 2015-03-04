#ifndef DAEMON_HH
#define DAEMON_HH

#include "DomainSocket.hh"
#include "Launcher.hh"

class Daemon
{
private:
    DomainSocket                _local;
    bool                        _run;
    Launcher                    _launcher;
    std::vector<DomainSocket*>  _clients;

public:
    Daemon(const std::string &path, const std::string &iface);
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
