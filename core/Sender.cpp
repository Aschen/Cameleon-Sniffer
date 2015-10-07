#include "Sender.hh"

Sender::Sender(const std::string &path, const std::string &msg)
    : _local(path, DomainSocket::CLIENT), _run(false)
{
    if (_local.isRunning())
    {
        // Add first msg
        _local.addMsg(msg);
    }
}

void Sender::start(void)
{
    if (_local.isRunning())
    {
        _run = true;
        while (_run)
        {
            try { handleSockets(); }
            catch (std::runtime_error &e) { _run = false; }
        }
    }
}

int Sender::initSelect(timeval *tv, fd_set *readfds, fd_set *writefds)
{
    int     fd_max = _local.fd();

    // Timeout 100 ms
    tv->tv_sec = 0;
    tv->tv_usec = 100;

    // Initialize bits field for select
    FD_ZERO(readfds);
    FD_SET(_local.fd(), readfds);
    FD_SET(0, readfds);
    // Write
    FD_ZERO(writefds);
    FD_SET(_local.fd(), writefds);
    return fd_max + 1;
}

void Sender::handleSockets(void)
{
    fd_set              readfds;
    fd_set              writefds;
    int                 fd_max;
    struct timeval      tv;

    fd_max = initSelect(&tv, &readfds, &writefds);
    if (::select(fd_max, &readfds, NULL, NULL, &tv) == -1)
    {
        throw std::runtime_error(std::string("Select Error : ") + ::strerror(errno));
    }
    else
    {
        // If something to read on stdin
        if (FD_ISSET(0, &readfds))
            eventTerminal();
        // If something to read on socket
        if (FD_ISSET(_local.fd(), &readfds))
            eventSocketRead();
        if (FD_ISSET(_local.fd(), &writefds))
            eventSocketWrite();
    }
}

void Sender::eventTerminal(void)
{
    _run = false;
}

void Sender::eventSocketRead(void)
{
    std::string         msg;

    try
    {
        _local.recvMsg();
        msg = _local.getMsg();
        std::cout << msg << std::endl;
        _run = false;
    }
    catch (std::runtime_error &e)
    {
        std::cout << e.what() << std::endl;
    }
}

void Sender::eventSocketWrite(void)
{
    if (_local.somethingToSend())
    {
        try { _local.sendMsg(); }
        catch (std::runtime_error &e) { std::cout << e.what() << std::endl; }
    }
}

int main(int ac, char **av)
{
    std::string     cmd;

    if (ac < 2)
    {
        std::cout << "  Usage : " << av[0] << " [commands]" << std::endl;
        return 1;
    }

    for (int i = 1; i < ac; i++)
    {
        cmd += av[i];
        cmd += " ";
    }

    try
    {
        Sender      s("/etc/cameleon/cameleon.sock", cmd);

        s.start();
    }
    catch (std::runtime_error &e)
    {
        std::cout << "  " << e.what() << std::endl;
    }

    return 0;
}
