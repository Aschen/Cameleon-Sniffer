#ifndef MODULEFACTORY_HPP
# define MODULEFACTORY_HPP

# include <QHash>
# include <QStringList>

# include "AModule.hh"
# include "Mitm.hh"
# include "DnsWatcher.hh"
# include "daemon/Command.hh"
# include "Debug.hh"

class ModuleFactory
{
public:
    static CreatedModule        create(const StartModuleArgs & startModuleArgs);
    static const QStringList    help;
};

/**
 * @brief ModuleFactory::create
 * @param args <module type> <module name> [module args..]
 * @return AModule
 */
CreatedModule ModuleFactory::create(const StartModuleArgs & startModuleArgs)
{
    CreatedModule   createdModule;

    createdModule.module = nullptr;

    if (startModuleArgs.type == "DnsWatcher")
    {
        createdModule.module = DnsWatcher::create(startModuleArgs);
        createdModule.usage = DnsWatcher::help.join("\n");
    }
    else if (startModuleArgs.type == "Mitm")
    {
        createdModule.module = Mitm::create(startModuleArgs);
        createdModule.usage = Mitm::help.join("\n");
    }
    else
    {
        DEBUG("ModuleFactory::create() : Unknown module type" << startModuleArgs.type, true);
        createdModule.usage = ModuleFactory::help.join("\n");
    }

    return createdModule;
}

const QStringList ModuleFactory::help = { "Usage :",
                                          "\t cameleon start <module type> <module name> [args..]"
                                        };

#endif // MODULEFACTORY_HPP

