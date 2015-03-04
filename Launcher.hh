#ifndef LAUNCHER_HH
#define LAUNCHER_HH

#include <tins/tins.h>
#include "IModule.hh"
#include "DnsSpoof.hh"
#include "DnsDump.hh"
#include "PostSniffer.hh"
#include "CookieSniffer.hh"
#include "Mitm.hh"
#include "TcpKill.hh"

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
    NetworkInterface                _iface;
    std::stringstream               _rep;
    std::map<std::string, Command>  _commands;
    std::map<std::string, IModule*> _modules;

public:
    Launcher(const std::string &iface);
    ~Launcher(void);

    const std::string               readCmdLine(const std::string &line);

public:
    void                            help(std::istringstream &iss);
    void                            exit(std::istringstream &iss);
    void                            start(std::istringstream &iss);
    void                            stop(std::istringstream &iss);
    void                            list(std::istringstream &iss);
    void                            ps(std::istringstream &iss);

public:
    void                            startDnsSpoof(std::istringstream &iss);
    void                            startDnsDump(std::istringstream &iss);
    void                            startPostSniffer(std::istringstream &iss);
    void                            startCookieSniffer(std::istringstream &iss);
    void                            startMitm(std::istringstream &iss);
    void                            startTcpKill(std::istringstream &iss);

private:
    void                            stopModules(void);

};

#endif // Launcher_HH
