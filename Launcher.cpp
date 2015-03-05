#include "Launcher.hh"

Launcher::Launcher(const std::string &iface)
    : _run(false), _iface(iface)
{
    // Commands
    _commands["help"] = &Launcher::help;
    _commands["quit"] = &Launcher::quit;
    _commands["start"] = &Launcher::start;
    _commands["stop"] = &Launcher::stop;
    _commands["list"] = &Launcher::list;
    _commands["ps"] = &Launcher::ps;

    // Modules
    _commands["startdnsspoof"] = &Launcher::startDnsSpoof;
    _commands["startdnsdump"] = &Launcher::startDnsDump;
    _commands["startpostsniffer"] = &Launcher::startPostSniffer;
    _commands["startcookiesniffer"] = &Launcher::startCookieSniffer;
    _commands["startmitm"] = &Launcher::startMitm;
    _commands["starttcpkill"] = &Launcher::startTcpKill;
    _commands["startsurfwatcher"] = &Launcher::startSurfWatcher;
}

Launcher::~Launcher(void)
{
    for (std::map<std::string, IModule*>::iterator   it = _modules.begin(); it != _modules.end(); ++it)
        delete (*it).second;

    // Disable ip forward
    system("echo 0 > /proc/sys/net/ipv4/ip_forward");
}

const std::string Launcher::readCmdLine(const std::string &line)
{
    std::map<std::string, Command>::iterator    it;
    std::string             cmd;
    Command                 fptr;
    std::istringstream      iss(line);

    _rep.str("");
    _rep.clear();
    iss >> cmd;
    it = _commands.find(cmd);
    if (it == _commands.end())
        help(iss);
    else
    {
        fptr = (*it).second;
        (this->*fptr)(iss);
    }
    return _rep.str();
}


/* COMMANDS */
void Launcher::list(std::istringstream &iss)
{
    (void)iss;
    _rep << "Availables modules : ";
    for (std::pair<std::string, Command> cmd : _commands)
    {
        try { _rep << cmd.first.substr(5) << " "; }
        catch(std::out_of_range &e) { }
    }
}

void Launcher::help(std::istringstream &iss)
{
    (void)iss;
    _rep << "Available commands : " << std::endl;
    _rep << "\tstart <module> <instance name> [options] : Start module" << std::endl;
    _rep << "\tstop <instance name> : Stop module" << std::endl;
    _rep << "\tlist : Display availables modules" << std::endl;
    _rep << "\tps : Display started modules" << std::endl;
    _rep << "\thelp : Display this help" << std::endl;
    _rep << "\tquit : Stop the daemon";
}

void Launcher::quit(std::istringstream &iss)
{
    (void)iss;
    stopModules();
    _run = false;
    throw Launcher::Stop();
}

void Launcher::start(std::istringstream &iss)
{
    std::map<std::string, Command>::iterator    it;
    std::string     module;
    Command         fptr;

    iss >> module;
    if (module.length())
    {
        it = _commands.find("start" + module);
        if (it == _commands.end())
        {
            list(iss);
            help(iss);
        }
        else
        {
            fptr = (*it).second;
            (this->*fptr)(iss);
        }
    }
    else
        help(iss);
}

void Launcher::stop(std::istringstream &iss)
{
    std::map<std::string, IModule*>::iterator    it;
    std::string     name;

    iss >> name;
    if (!name.length())
        help(iss);
    else
    {
        it = _modules.find(name);
        if (it == _modules.end())
            _rep << "Module " << name << " doesn't exist !";
        else
        {
            // Stop the module and delete it
            (*it).second->stop();
            delete (*it).second;
            _modules.erase(name);
            _rep << "Module " << name << " successfully stopped";
        }
    }
}

void Launcher::ps(std::istringstream &iss)
{
    (void)iss;
    if (_modules.size())
    {
        _rep << std::setw(22) << std::left << "Module" << std::setw(20) << std::left << "Name" << std::setw(15) << std::left << "Options" << std::endl << std::endl;
        for (std::pair<std::string, IModule*> pair : _modules)
            _rep << std::setw(22) << std::left << pair.second->name() << std::setw(20) << std::left << pair.first << std::setw(15) << std::left << pair.second->info() << std::endl;
    }
    else
    {
        _rep << "No module actually running.";
    }
}

void Launcher::stopModules(void)
{
    for (std::pair<std::string, IModule*> pair : _modules)
    {
        _rep << "Stopping module " << pair.first;
        pair.second->stop();
    }
}

/* MODULES STARTER */
void Launcher::startDnsSpoof(std::istringstream &iss)
{
    std::map<std::string, IModule*>::iterator    it;
    std::string     name;
    std::string     hostfile;

    iss >> name;
    iss >> hostfile;
    if (!name.length())
        help(iss);
    else if (!hostfile.length())
        _rep << "Bad parameters." << std::endl << DnsSpoof::help();
    else
    {
        it = _modules.find(name);
        if (it == _modules.end())
        {
            _modules[name] = new DnsSpoof(_iface, &_rep, hostfile);
            _modules[name]->start();
            _rep << "DnsSpoof started : hostfile=" + hostfile;
        }
        else
        {
            _rep << "Module " << name << " already exist !";
        }
    }
}

void Launcher::startDnsDump(std::istringstream &iss)
{
    std::map<std::string, IModule*>::iterator    it;
    std::string     name;
    std::string     file;

    iss >> name;
    iss >> file;
    if (!name.length())
        help(iss);
    else if (!file.length())
        _rep << "Bad parameters." << std::endl << DnsDump::help();
    else
    {
        it = _modules.find(name);
        if (it == _modules.end())
        {
            std::ofstream    *fd = new std::ofstream();

            fd->open(file); // Close fd ? Where ?
            _modules[name] = new DnsDump(_iface, fd, file);
            _modules[name]->start();
            _rep << "DnsDump started : file=" + file;
        }
        else
        {
            _rep << "Module " << name << " already exist !";
        }
    }
}

void Launcher::startPostSniffer(std::istringstream &iss)
{
    std::map<std::string, IModule*>::iterator   it;
    std::string                                 name;
    std::string                                 type;
    std::string                                 filename;

    iss >> name;
    iss >> type;
    iss >> filename;
    if (!name.length())
        help(iss);
    else if (!type.length() || !filename.length())
        _rep << "Bad parameters." << std::endl << PostSniffer::help() << std::endl;
    else
    {
        it = _modules.find(name);
        if (it == _modules.end())
        {
            std::ofstream    *fd = new std::ofstream();

            fd->open(filename);
            if (type == "keys")         // If Type KEYS
            {
                std::string                 key;
                std::vector<std::string>    vKeys;

                iss >> key;
                if (!key.length())
                    _rep << "Bad parameters." << std::endl << PostSniffer::help() << std::endl;
                else
                {
                    // Push first key and then other keys
                    vKeys.push_back(key);
                    while (iss >> key)
                        vKeys.push_back(key);
                    _modules[name] = new PostSniffer(_iface, fd, filename, vKeys);
                }
            }
            else if (type == "host")    // If Type HOSTNAME
            {
                std::string                 hostname;

                iss >> hostname;
                if (!hostname.length())
                    _rep << "Bad parameters." << std::endl << PostSniffer::help() << std::endl;
                else
                    _modules[name] = new PostSniffer(_iface, fd, filename, hostname);
            }
            else if (type == "all")     // If Type ALL
            {
                _modules[name] = new PostSniffer(_iface, fd, filename);
            }
            else
            {
                _rep << "Bad parameters." << std::endl << PostSniffer::help() << std::endl;
                return ;
            }
            _modules[name]->start();
            _rep << "PostSniffer started";
        }
        else
            _rep << "Module " << name << " already exist !";
    }
}

void Launcher::startCookieSniffer(std::istringstream &iss)
{
    std::map<std::string, IModule*>::iterator   it;
    std::string                                 name;
    std::string                                 filename;
    std::string                                 type;

    iss >> name;
    iss >> type;
    iss >> filename;
    if (!name.length())
        help(iss);
    else if (!filename.length() || !type.length())
        _rep << "Bad parameters." << std::endl << CookieSniffer::help() << std::endl;
    else
    {
        it = _modules.find(name);
        if (it == _modules.end())
        {
            std::ofstream    *fd = new std::ofstream();

            fd->open(filename);
            if (type == "keys")
            {
                std::string                 key;
                std::vector<std::string>    vKeys;

                iss >> key;
                if (!key.length())
                    _rep << "Bad parameters." << std::endl << CookieSniffer::help() << std::endl;
                else
                {
                    // Push first key and then other keys (key = cookie name)
                    vKeys.push_back(key);
                    while (iss >> key)
                        vKeys.push_back(key);
                    _modules[name] = new CookieSniffer(_iface, fd, filename, vKeys);
                }

            }
            else if (type == "host")
            {
                std::string                 hostname;

                iss >> hostname;
                if (!hostname.length())
                    _rep << "Bad parameters." << std::endl << CookieSniffer::help() << std::endl;
                else
                    _modules[name] = new CookieSniffer(_iface, fd, filename, hostname);
            }
            else if (type == "all")
            {
                _modules[name] = new CookieSniffer(_iface, fd, filename);
            }
            else
            {
                _rep << "Bad parameters." << std::endl << CookieSniffer::help() << std::endl;
                return ;
            }
            _modules[name]->start();
            _rep << "CookieSniffer started";
        }
        else
            _rep << "Module " << name << " already exist !";
    }
}

void Launcher::startMitm(std::istringstream &iss)
{
    std::map<std::string, IModule*>::iterator    it;
    std::string     name;
    std::string     gatewayIp;
    std::string     file;

    iss >> name;
    iss >> file;
    iss >> gatewayIp;
    if (!name.length())
        help(iss);
    else if (!gatewayIp.length() || !file.length())
        _rep << "Bad parameters." << std::endl << Mitm::help();
    else
    {
        std::ifstream               fd;
        std::vector<std::string>    victims;

        fd.open(file);
        int i = 0;
        for (std::string line; std::getline(fd, line) && i < 40;i++)
            victims.push_back(line);

        it = _modules.find(name);
        if (it == _modules.end())
        {
            _modules[name] = new Mitm(_iface, &_rep, victims, gatewayIp);
            _modules[name]->start();
        }
        else
            _rep << "Module " << name << " already exist !";
    }
}

void Launcher::startTcpKill(std::istringstream &iss)
{
    std::map<std::string, IModule*>::iterator    it;
    std::string     name;
    std::string     dstIp;
    std::string     srcIp;
    std::string     port;

    iss >> name;
    iss >> dstIp;
    iss >> srcIp;
    iss >> port;
    if (!name.length())
        help(iss);
    else if (!dstIp.length() || !port.length() || !srcIp.length())
        _rep << "Bad parameters." << std::endl << TcpKill::help();
    else
    {
        it = _modules.find(name);
        if (it == _modules.end())
        {
            if (dstIp == "0.0.0.0")
                _modules[name] = new TcpKill(_iface, &_rep, srcIp, port, true);
            else if (srcIp == "0.0.0.0")
                _modules[name] = new TcpKill(_iface, &_rep, dstIp, port);
            else
                _modules[name] = new TcpKill(_iface, &_rep, dstIp, srcIp, port);
            _modules[name]->start();
        }
        else
            _rep << "Module " << name << " already exist !";
    }
}

void Launcher::startSurfWatcher(std::istringstream &iss)
{
    std::map<std::string, IModule*>::iterator   it;
    std::string                                 name;
    std::string                                 filename;
    std::string                                 type;

    iss >> name;
    iss >> type;
    iss >> filename;
    if (!name.length())
        help(iss);
    else if (!filename.length() || !type.length())
        _rep << "Bad parameters." << std::endl << SurfWatcher::help() << std::endl;
    else
    {
        it = _modules.find(name);
        if (it == _modules.end())
        {
            std::ofstream       *fd = new std::ofstream();

            fd->open(filename);
            if (type == "all")
            {
                _modules[name] = new SurfWatcher(_iface, fd, filename);
            }
            else if (type == "ip")
            {
                std::string     ip;

                iss >> ip;
                if (!ip.length())
                    _rep << "Bad parameters." << std::endl << SurfWatcher::help() << std::endl;
                else
                    _modules[name] = new SurfWatcher(_iface, fd, filename, IPv4Address(ip));
            }
            else if (type == "host")
            {
                std::string     hostname;

                iss >> hostname;
                if (!hostname.length())
                    _rep << "Bad parameters." << std::endl << SurfWatcher::help() << std::endl;
                else
                    _modules[name] = new SurfWatcher(_iface, fd, filename, hostname);
            }
            else
            {
                _rep << "Bad parameters." << std::endl << SurfWatcher::help() << std::endl;
                return ;
            }
            _modules[name]->start();
            _rep << "SurfWatcher started";
        }
        else
            _rep << "Module " << name << " already exist !";
    }
}












