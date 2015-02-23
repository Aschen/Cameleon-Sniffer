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

#include "DomainSocket.hh"

class Daemon
{
private:
    DomainSocket                _local;
    DomainSocket                *_remote;

public:
    Daemon(const std::string &path);
    ~Daemon(void);

};

#endif // DAEMON_HH
