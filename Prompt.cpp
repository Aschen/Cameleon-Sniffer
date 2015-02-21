#include "Prompt.hh"

Prompt::Prompt(void)
{
    _commands["help"] = &Prompt::help;
}

void Prompt::launch(void)
{
    // Getline from istream ? (file or std::cin)
    while (std::getline(std::cin, line, '\n'))
    {

    }
}

void Prompt::help(void)
{
    std::cout << "Display this help" << std::endl;
}
