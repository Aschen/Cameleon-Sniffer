#ifndef PROMPT_HH
#define PROMPT_HH

#include <sstream>
#include "Sniff.hh"
#include "AModule.hh"
#include "Mitm.hh"
#include "DnsSpoof.hh"
#include "DnsDump.hh"

class Prompt // CHANGE CLASSNAME !!
{
    typedef void    (Prompt::*Command)(std::istringstream &iss);

private:
    bool                            _run;
    Core                            _core;
    std::map<std::string, Command>  _commands;
    std::map<std::string, AModule*> _modules;

public:
    // Add interface choice for Core creation ?
    Prompt(void);
    ~Prompt(void);

    // TODO : Read and launch commands from a file
    void                launch(void);
    void                readCmdLine(const std::string &line);

public:
    void                help(std::istringstream &iss);
    void                quit(std::istringstream &iss);
    void                start(std::istringstream &iss);
    void                stop(std::istringstream &iss);
    void                list(std::istringstream &iss);
    void                ps(std::istringstream &iss);

public:
    void                startMitm(std::istringstream &iss);
    void                startDnsSpoof(std::istringstream &iss);
    void                startDnsDump(std::istringstream &iss);

private:
    void                stopModules(void);
};

#endif // PROMPT_HH
