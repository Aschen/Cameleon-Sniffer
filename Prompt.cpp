#include "Prompt.hh"

Prompt::Prompt(void) : _run(false)
{
    _commands["help"] = &Prompt::help;
    _commands["quit"] = &Prompt::quit;
    _commands["start"] = &Prompt::start;
    _commands["startmitm"] = &Prompt::startMitm;
    _commands["startdnsspoof"] = &Prompt::startDnsSpoof;
    _commands["stop"] = &Prompt::stop;
    _commands["list"] = &Prompt::list;
    _commands["ps"] = &Prompt::ps;
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
    std::map<std::string, Command>::iterator    it;
    std::string     cmd;
    Command         fptr;

    // Getline from istream ? (file or std::cin)
    _run = true;
    std::cout << " #  ";
    for (std::string line; _run && std::getline(std::cin, line, '\n');)
    {
        std::istringstream      iss(line);

        iss >> cmd;
        it = _commands.find(cmd);
        if (it == _commands.end())
            help(iss);
        else
        {
            fptr = (*it).second;
            (this->*fptr)(iss);
        }
        std::cout << " #  ";
    }
}

void Prompt::help(std::istringstream &iss)
{
    (void)iss;
    std::cout << "Available commands : " << std::endl;
    std::cout << "\tstart <module> <instance name> [options] : Start module" << std::endl;
    std::cout << "\tstop <instance name> : Stop module" << std::endl;
    std::cout << "\tlist : Display availables modules" << std::endl;
    std::cout << "\tps : Display started modules" << std::endl;
    std::cout << "\thelp : Display this help" << std::endl;
    std::cout << "\tquit : Exit" << std::endl;
}

void Prompt::quit(std::istringstream &iss)
{
    (void)iss;
    stopModules();
    std::cout << "Bye :)" << std::endl;
    _run = false;
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
            std::cout << "Module " << name << " doesn't exist !" << std::endl;
        else
        {
            // Stop the module and delete it
            (*it).second->stop();
            delete (*it).second;
            _modules.erase(name);
            std::cout << "Module " << name << " successfully stopped" << std::endl;
        }
    }
}

void Prompt::list(std::istringstream &iss)
{
    (void)iss;
    std::cout << "Availables modules : mitm dnsspoof" << std::endl;
}

void Prompt::ps(std::istringstream &iss)
{
    (void)iss;
    for (std::map<std::string, AModule*>::iterator   it = _modules.begin(); it != _modules.end(); ++it)
    {
        std::cout << (*it).second->name() << " '" << (*it).first << "' Options : " << (*it).second->info() << std::endl;
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
        std::cout << "Bad parameters." << std::endl << Mitm::help();
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
            std::cout << "Module " << name << " already exist !" << std::endl;
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
        std::cout << "Bad parameters." << std::endl << DnsSpoof::help();
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
            std::cout << "Module " << name << " already exist !" << std::endl;
        }
    }
}

void Prompt::stopModules(void)
{
    for (std::map<std::string, AModule*>::iterator   it = _modules.begin(); it != _modules.end(); ++it)
    {
        std::cout << "Stopping module " << (*it).first << std::endl;
        (*it).second->stop();
    }
}













