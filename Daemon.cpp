#include "Daemon.hh"

Daemon::Daemon(const std::string &path)
    : _local(path, DomainSocket::SERVER), _remote(NULL)
{    
    if (_local.isRunning())
    {
        if ((_remote = _local.acceptClient()))
        {
            std::string     msg;
            msg = _remote->recvMsg();
            _remote->sendMsg(msg);
        }
    }
}

Daemon::~Daemon(void)
{
    if (_remote)
        delete _remote;
}

int main(int ac, char **av)
{
    Daemon  d(av[1]);

    return 0;
}
