#include "Prompt.hh"

Prompt::Prompt(void) : _run(false), _core("wlan0")
{
    // Commands
    _commands["help"] = &Prompt::help;
    _commands["exit"] = &Prompt::exit;
    _commands["start"] = &Prompt::start;
    _commands["stop"] = &Prompt::stop;
    _commands["list"] = &Prompt::list;
    _commands["ps"] = &Prompt::ps;

    // Modules
    _commands["startmitm"] = &Prompt::startMitm;
    _commands["startdnsspoof"] = &Prompt::startDnsSpoof;
    _commands["startdnsdump"] = &Prompt::startDnsDump;
}

Prompt::~Prompt(void)
{
    for (std::map<std::string, AModule*>::iterator   it = _modules.begin(); it != _modules.end(); ++it)
    {
        delete (*it).second;
    }
}

void Prompt::launch(void)
{

    // Getline from istream ? (file or std::cin)
    _run = true;
    std::cout << " #  ";
    for (std::string line; _run && std::getline(std::cin, line, '\n');)
    {
        readCmdLine(line);
        std::cout << " #  ";
    }
}

const std::string Prompt::readCmdLine(const std::string &line)
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
void Prompt::help(std::istringstream &iss)
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

void Prompt::exit(std::istringstream &iss)
{
    (void)iss;
    stopModules();
    _run = false;
    throw Prompt::Stop();
}

void Prompt::start(std::istringstream &iss)
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

void Prompt::stop(std::istringstream &iss)
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

void Prompt::list(std::istringstream &iss)
{
    (void)iss;
    _rep << "Availables modules : mitm dnsspoof dnsdump";
}

void Prompt::ps(std::istringstream &iss)
{
    (void)iss;
    if (_modules.size())
    {
        for (std::map<std::string, AModule*>::iterator   it = _modules.begin(); it != _modules.end(); ++it)
        {
            _rep << (*it).second->name() << " '" << (*it).first << "' Options : " << (*it).second->info() << std::endl;
        }
    }
    else
    {
        _rep << "No module actually running.";
    }
}

void Prompt::stopModules(void)
{
    for (std::map<std::string, AModule*>::iterator   it = _modules.begin(); it != _modules.end(); ++it)
    {
        _rep << "Stopping module " << (*it).first;
        (*it).second->stop();
    }
}


/* MODULES STARTER */
void Prompt::startMitm(std::istringstream &iss)
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
            _modules[name] = new Mitm(_core, victimIp, gatewayIp);
            _modules[name]->start();
        }
        else
        {
            _rep << "Module " << name << " already exist !";
        }
    }
}

void Prompt::startDnsSpoof(std::istringstream &iss)
{
    std::map<std::string, AModule*>::iterator    it;
    std::string     name;
    std::string     filename;

    iss >> name;
    iss >> filename;
    if (!name.length())
        help(iss);
    else if (!filename.length())
        _rep << "Bad parameters." << std::endl << DnsSpoof::help();
    else
    {
        it = _modules.find(name);
        if (it == _modules.end())
        {
            _modules[name] = new DnsSpoof(_core, filename, _core.interface().name());
            _modules[name]->start();
        }
        else
        {
            _rep << "Module " << name << " already exist !";
        }
    }
}

void Prompt::startDnsDump(std::istringstream &iss)
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
        {
            _modules[name] = new DnsDump(_core);
            _modules[name]->start();
        }
        else
        {
            _rep << "Module " << name << " already exist !";
        }
    }
}













