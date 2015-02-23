#include "Sender.hh"

Sender::Sender(const std::string &path, const std::string &msg)
    : _local(path, DomainSocket::CLIENT)
{
    if (_local.isRunning())
    {
        try
        {
            _local.addMsg(msg);
            _local.sendMsg();
            _local.recvMsg();
            std::cout << _local.getMsg() << std::endl;
        }
        catch (std::runtime_error &e)
        {
            std::cout << e.what() << std::endl;
        }
    }
}

int main(int ac, char **av)
{
    std::string     cmd;

    if (ac < 3)
    {
        std::cout << "Usage : " << av[0] << " <socket> [commands]" << std::endl;
        return 1;
    }

    for (int i = 2; i < ac; i++)
    {
        cmd += av[i];
        cmd += " ";
    }

    try
    {
        Sender      s(av[1], cmd);
    }
    catch (std::runtime_error &e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
