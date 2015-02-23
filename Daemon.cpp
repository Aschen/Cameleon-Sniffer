#include "Daemon.hh"

Daemon::Daemon(const std::string &path)
    : _local(path, DomainSocket::SERVER), _run(false)
{    
    if (_local.isRunning())
    {
        start();
    }
}

Daemon::~Daemon(void)
{
    for (DomainSocket* client : _clients)
    {
        delete client;
    }
}

void Daemon::start(void)
{
    _run = true;
    while (_run)
    {
        handleSockets();
    }
    std::cout << "Server shutdown" << std::endl;
}

void Daemon::handleSockets(void)
{
    fd_set              readfds;
    fd_set              writefds;
    int                 fd_max;
    struct timeval      tv;

    /*  Preparation et lancement de select() */
    fd_max = initSelect(&tv, &readfds, &writefds);
    if (::select(fd_max, &readfds, NULL, NULL, &tv) == -1)
    {
        throw std::runtime_error(std::string("Select Error : ") + ::strerror(errno));
    }
    else
    {
        /* Si une commande est tapée en console */
        if (FD_ISSET(0, &readfds))
            eventTerminal();
        /* Si un nouveau client essaye de se connecter */
        if (FD_ISSET(_local.fd(), &readfds))
            eventServer();
        /* On regarde si les clients nous envoies des infos */
        eventClients(&readfds, &writefds);
    }

}

int Daemon::initSelect(struct timeval *tv, fd_set *readfds, fd_set *writefds)
{
    int     fd_max = _local.fd();

    // Timeout 100 ms
    tv->tv_sec = 0;
    tv->tv_usec = 100;

    // Initialize bits field for select
    FD_ZERO(readfds);
    FD_SET(_local.fd(), readfds);
    FD_SET(0, readfds);
    if (writefds != NULL)
    {
        FD_ZERO(writefds);
        FD_SET(_local.fd(), writefds);
    }
    for (DomainSocket *client : _clients)
    {
        FD_SET(client->fd(), readfds);
        if (writefds != NULL)
            FD_SET(client->fd(), writefds);
        // Check if client's fd is greater than actual fd_max
        fd_max = (fd_max < client->fd()) ? client->fd() : fd_max;
    }
    return fd_max + 1;
}

void Daemon::eventTerminal(void)
{
    std::string     msg;

    std::cin >> msg;
    if (msg == "exit")
    {
        _run = false;
    }
}

void Daemon::eventServer(void)
{
    DomainSocket    *client;

    try
    {
        client = _local.acceptClient();
        _clients.push_back(client);
    }
    catch (std::runtime_error &e)
    {
        std::cout << e.what() << std::endl;
    }
}

void Daemon::eventClients(fd_set *readfds, fd_set *writefds)
{
    std::string         msg;

    for (std::vector<DomainSocket*>::iterator it = _clients.begin(); it < _clients.end(); ++it)
    {
        // Something to write on client socket
        if (FD_ISSET((*it)->fd(), writefds))
        {
            // Send msg
        }
        // Something to read on client socket
        if (FD_ISSET((*it)->fd(), readfds))
        {
            try
            {
                msg = (*it)->recvMsg();
                std::cout << msg << std::endl;
            }
            catch (DomainSocket::Disconnected &e)
            {
                std::cout << "Client " << (*it)->fd() << " disconnected." << std::endl;
                delete (*it);
                _clients.erase(it);
                it = _clients.begin();
            }
            catch (std::runtime_error &e)
            {
                std::cout << e.what() << std::endl;
            }
        }
    }

}

int main(int ac, char **av)
{
    try
    {
        Daemon  d(av[1]);
    }
    catch (std::runtime_error &e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
