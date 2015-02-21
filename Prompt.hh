#ifndef PROMPT_HH
#define PROMPT_HH

#include "Sniff.hh"
#include "AModule.hh"



class Prompt
{
    typedef void    (Prompt::*Command)(void);

private:
    std::map<std::string, Command>  _commands;

public:
    Prompt(void);

    // TODO : Read and launch commands from a file
    void                launch(void);

public:
    void                help(void);
};

#endif // PROMPT_HH
