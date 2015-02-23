#include "Daemon.hh"

int main(int ac, char **av)
{
//    std::ostream        *os;
//    std::ofstream       *file;
//    std::stringstream   *ss;

//    file = new std::ofstream();
//    ss = new std::stringstream();

//    file->open("todo.txt");
//    *file << "toto" << std::endl;
//    os = file;

//    *os << "toto" << std::endl;
//    file->close();

    (void)ac;
    (void)av;
    if (getuid() != 0)
    {
        std::cout << "Must be root." << std::endl;
        return 1;
    }

    try
    {
        Daemon      d("/etc/sniffer/sniffer.sock");

        d.start();
    }
    catch (std::runtime_error &e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
