#include "DomainSocket.hh"

DomainSocket::DomainSocket(const std::string &path, DomainSocket::TYPE type) : _run(false), _type(type)
{
    _socket.sun_family = AF_UNIX;
    ::strncpy(_socket.sun_path, path.c_str(), path.length());

    if ((_fd = ::socket(AF_UNIX, SOCK_STREAM, 0)) == -1)
        throw std::runtime_error(strerror(errno));

    // Server Socket
    if (_type == DomainSocket::SERVER)
    {
        ::unlink(path.c_str());
        if (::bind(_fd, (struct sockaddr*)&_socket, path.length() + sizeof(_socket.sun_family)) == -1)
            throw std::runtime_error(strerror(errno));
        else if (::listen(_fd, 5) == -1)
            throw std::runtime_error(strerror(errno));
        _run = true;
}
    else if (_type == DomainSocket::CLIENT)
    {
        if (::connect(_fd, (struct sockaddr*)&_socket, path.length() + sizeof(_socket.sun_family)) == -1)
            throw std::runtime_error(strerror(errno));
        _run =  true;
    }
    else
    {
        throw std::runtime_error("Wrong constructor for a Server_Client socket.");
    }
}

DomainSocket::DomainSocket(int fd, const sockaddr_un *socket) : _run(true), _type(DomainSocket::SERVER_CLIENT), _fd(fd)
{
    std::memcpy(&_socket, socket, strlen(socket->sun_path) + sizeof(socket->sun_family));
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
        throw std::runtime_error("This is not a server socket");

    if ((remoteFd = ::accept(_fd, (struct sockaddr*)&remoteSocket, &size)) == -1)
        throw std::runtime_error(strerror(errno));

    return new DomainSocket(remoteFd, &remoteSocket);
}


void DomainSocket::sendMsg(void)
{
    std::string     msg;

    if (_type == DomainSocket::SERVER)
        throw std::runtime_error("This is a server socket");

    if (_sendQueue.size() == 0)
        throw std::runtime_error("No message in send queue");

    msg = _sendQueue.front();
    if (send(_fd, msg.c_str(), msg.size(), 0) == -1)
        throw std::runtime_error(strerror(errno));
    _sendQueue.pop();

}

void DomainSocket::recvMsg(void)
{
    char        buf[BUF_SIZE] = {0};
    std::string msg;
    int         len;

    if (_type == DomainSocket::SERVER)
        throw std::runtime_error("This is a server socket");

    if ((len = recv(_fd, buf, BUF_SIZE, 0)) == -1)
        throw std::runtime_error(strerror(errno));
    else if (_type == DomainSocket::SERVER_CLIENT && len == 0) // Server_Client disconnected from server
        throw DomainSocket::Disconnected();

    msg.assign(buf, len);
    _recvQueue.push(msg);
}

void DomainSocket::addMsg(const std::string &msg)
{
    _sendQueue.push(msg);
}

const std::string DomainSocket::getMsg(void)
{
    std::string     msg;

    if (_recvQueue.size() == 0)
        throw std::runtime_error("No message in recv queue");
    msg = _recvQueue.front();
    _recvQueue.pop();
    return msg;
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

bool DomainSocket::somethingToSend() const { return _sendQueue.size() == 0 ? false : true; }

bool DomainSocket::somethingToRecv() const { return _recvQueue.size() == 0 ? false : true; }
