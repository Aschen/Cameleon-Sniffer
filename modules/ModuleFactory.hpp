#ifndef MODULEFACTORY_HPP
# define MODULEFACTORY_HPP

# include <QHash>
# include <QStringList>

# include "AModule.hh"
# include "DnsWatcher.hh"
# include "Debug.hh"

class ModuleFactory
{
public:
    static AModule*             create(const QStringList & args);
    static const QStringList    help;
};

/**
 * @brief ModuleFactory::create
 * @param args <module type> <module name> [module args..]
 * @return AModule
 */
AModule * ModuleFactory::create(const QStringList & args)
{
    if (args.size() < 2)
    {
        DEBUG("ModuleFactory::create() : 0 arguments provided", true);
        return nullptr;
    }

    AModule*        module = nullptr;
    QStringList     usage;
    const QString&  moduleType = args[0];
    const QString&  moduleName = args[1];
    QStringList     moduleArgs = args.mid(2);

    if (moduleType == "DnsWatcher")
    {
        module = DnsWatcher::create(moduleName, moduleArgs);
        usage = DnsWatcher::help;
    }
    else
    {
        DEBUG("ModuleFactory::create() : Unknown module type" << moduleType, true);
        usage = ModuleFactory::help;
    }

    // Display help if arguments were not correct to create the module
    if ( ! module)
    {
        for (const QString & line : usage)
            DEBUG(line, true);
    }

    return module;
}

const QStringList ModuleFactory::help = { "Usage :",
                                          "\t cameleon start <module type> <module name> [args..]"
                                        };

#endif // MODULEFACTORY_HPP

