#include "DomainSocket.hh"

DomainSocket::DomainSocket(const std::string &path, DomainSocket::TYPE type) : _run(false), _type(type)
{
    _socket.sun_family = AF_UNIX;
    ::strncpy(_socket.sun_path, path.c_str(), path.length());

    if ((_fd = ::socket(AF_UNIX, SOCK_STREAM, 0)) == -1)
    {
        std::cout << "Can't open socket : " << ::strerror(errno) << std::endl;
    }

    // Server Socket
    if (_type == DomainSocket::SERVER)
    {
        ::unlink(path.c_str());
        if (::bind(_fd, (struct sockaddr*)&_socket, path.length() + sizeof(_socket.sun_family)) == -1)
        {
            std::cout << "Can't bind socket" << ::strerror(errno) << std::endl;
        }
        else if (::listen(_fd, 5) == -1)
        {
            std::cout << "Can't listening socket" << ::strerror(errno) << std::endl;
        }
        else // Success, TODO: throw exception if fail
        {
            _run = true;
        }
    }
    else if (_type == DomainSocket::CLIENT)
    {
        if (::connect(_fd, (struct sockaddr*)&_socket, path.length() + sizeof(_socket.sun_family)) == -1)
        {
            std::cout << "Can't connect socket" << ::strerror(errno) << std::endl;
        }
        else
        {
            _run =  true;
        }
    }
    else
    {
        std::cout << "Wrong constructor for a Server_Client socket" << std::endl;
    }
}

DomainSocket::DomainSocket(int fd, const sockaddr_un *socket) : _run(true), _type(DomainSocket::SERVER_CLIENT), _fd(fd)
{
    ::memcpy(&_socket, socket, strlen(socket->sun_path) + sizeof(socket->sun_family));
}

DomainSocket::~DomainSocket(void)
{
    if (_run)
        ::close(_fd);
}

DomainSocket *DomainSocket::acceptClient(void)
{
    int                 remoteFd;
    struct sockaddr_un  remoteSocket;
    socklen_t           size = sizeof(remoteSocket);

    if (_type != DomainSocket::SERVER)
    {
        std::cout << "This is not a server socket" << std::endl;
        return NULL; // TODO: Throw exception
    }

    if ((remoteFd = ::accept(_fd, (struct sockaddr*)&remoteSocket, &size)) == -1)
    {
        std::cout << "Can't accept client" << ::strerror(errno) << std::endl;
        return NULL; // TODO: Throw exception
    }
    return new DomainSocket(remoteFd, &remoteSocket);
}


bool DomainSocket::sendMsg(const std::string &msg)
{
    if (_type == DomainSocket::SERVER)
    {
        std::cout << "This is a server socket" << std::endl;
        return false;
    }

    if (send(_fd, msg.c_str(), msg.size(), 0) == -1)
    {
        std::cout << "Can't send msg" << ::strerror(errno) << std::endl;
        return false;
    }
    return true;
}

std::string DomainSocket::recvMsg(void)
{
    char        buf[BUF_SIZE] = {0};
    std::string ret = "";
    int         len;

    if (_type == DomainSocket::SERVER)
    {
        std::cout << "This is a server socket" << std::endl;
        return ret;
    }

    if ((len = recv(_fd, buf, BUF_SIZE, 0)) == -1)
    {
        std::cout << "Can't recv msg" << ::strerror(errno) << std::endl;
        return ret; // throw exception
    }

    ret.assign(buf, len);
    return ret;
}

void DomainSocket::closeSocket(void)
{
    if (_run)
        close(_fd);
}


/* GETTERS / SETTERS */
bool DomainSocket::isRunning(void) const { return _run; }

int DomainSocket::fd(void) const { return _fd; }

const sockaddr_un *DomainSocket::socket(void) const { return &_socket; }
