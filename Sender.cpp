#include "Sender.hh"

Sender::Sender(const std::string &path, const std::string &msg)
    : _local(path, DomainSocket::CLIENT)
{
    if (_local.isRunning())
    {
        _local.sendMsg(msg);
        std::cout << _local.recvMsg() << std::endl;
    }
}

//void Sender::echo(const std::string &msg)
//{
//    char    buf[100];

//    memset(buf, '\0', 100);
//    if (send(_fd, msg.c_str(), msg.length(), 0) == -1)
//    {
//        std::cout << "Send error" << std::endl;
//    }

//    if (recv(_fd, buf, 100, 0) == -1)
//    {
//        std::cout << "Recv error" << std::endl;
//    }
//    else
//    {
//        std::string out(buf);
//        std::cout << out << std::endl;
//    }
//}

//bool Sender::connection(const std::string &path)
//{
//    _socket.sun_family = AF_UNIX;
//    strncpy(_socket.sun_path, path.c_str(), path.length());

//    if (connect(_fd, (struct sockaddr*)&_socket, path.length() + sizeof(_socket.sun_family)) == -1)
//    {
//        std::cout << "Connect error" << std::endl;
//        return false;
//    }
//    return true;
//}

int main(int ac, char **av)
{
    Sender      s(av[1], av[2]);

    return 0;
}
