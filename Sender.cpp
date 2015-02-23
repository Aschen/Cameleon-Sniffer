#include "Sender.hh"

Sender::Sender(const std::string &path, const std::string &msg)
    : _local(path, DomainSocket::CLIENT)
{
    if (_local.isRunning())
    {
        try
        {
            _local.sendMsg(msg);
            std::cout << msg << " : Sended to server !" << std::endl;
        }
        catch (std::runtime_error &e)
        {
            std::cout << e.what() << std::endl;
        }
    }
}

int main(int ac, char **av)
{
    try
    {
        Sender      s(av[1], av[2]);
    }
    catch (std::runtime_error &e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
