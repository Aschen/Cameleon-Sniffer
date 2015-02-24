#ifndef LAUNCHER_HH
#define LAUNCHER_HH

#include <sstream>
#include "Sniff.hh"
#include "AModule.hh"
#include "Mitm.hh"
#include "DnsSpoof.hh"
#include "DnsDump.hh"
#include "HttpPostSniffer.hh"

class Launcher
{
public:
    class       Stop : public std::exception
    {
    public:
        Stop(void) { }
        ~Stop(void) throw() { }
    };

private:
    typedef void    (Launcher::*Command)(std::istringstream &iss);

private:
    bool                            _run;
    Core                            _core;
    std::stringstream               _rep;
    std::map<std::string, Command>  _commands;
    std::map<std::string, AModule*> _modules;

public:
    // Add interface choice for Core creation ?
    Launcher(void);
    ~Launcher(void);

    const std::string   readCmdLine(const std::string &line);

public:
    void                help(std::istringstream &iss);
    void                exit(std::istringstream &iss);
    void                start(std::istringstream &iss);
    void                stop(std::istringstream &iss);
    void                list(std::istringstream &iss);
    void                ps(std::istringstream &iss);

public:
    void                startMitm(std::istringstream &iss);
    void                startDnsSpoof(std::istringstream &iss);
    void                startDnsDump(std::istringstream &iss);
    void                startHttpPostSniffer(std::istringstream &iss);

private:
    void                stopModules(void);
};

#endif // Launcher_HH
