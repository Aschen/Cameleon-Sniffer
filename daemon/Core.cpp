#include "Core.hh"

#include <QStringList>

#include "Command.hh"
#include "modules/ModuleFactory.hpp"
#include "Debug.hh"

Core::Core()
{
    m_server = QSharedPointer<Server>(new Server(4242, this));
}

void Core::startDaemon()
{
    DEBUG("Start Cameleon-Sniffer on interface" << m_iface, true);
    m_server->start();
}

bool Core::addModule(AModule * module)
{
    return m_workerPool.addModule(module);
}

bool Core::removeModule(const QString & name)
{
    return m_workerPool.removeModule(name);
}

void Core::commandDispatcher(const QVariant & data)
{
    DEBUG("Core::commandDispatcher() :" << data, false);

    QStringList     input = data.toString().split(" ");

    if (input.size() < 1)
    {
        m_server->sendResponse("No input given");
        return;
    }

    QString&        command = input[0];

    if (command == "start")
    {
        startModule(input.mid(1));
    }
    else if (command == "stop")
    {
        stopModule(input[1]);
    }
    else
    {
        m_server->sendResponse("Unknown command '" + command + "'");
    }
}

const QString &Core::iface() const
{
    return m_iface;
}

void Core::iface(const QString &newInterface)
{
    m_iface = newInterface;
}

void Core::startModule(const QStringList & input)
{
    if (input.size() < 2)
    {
        m_server->sendResponse("Usage: ./cameleon start <module type> <module name> [options..]");
        return;
    }

    StartModuleArgs     startModuleArgs;

    startModuleArgs.iface = m_iface;
    startModuleArgs.type = input[0];
    startModuleArgs.name = input[1];
    startModuleArgs.options = input.mid(2);

    CreatedModule       createdModule;

    createdModule = ModuleFactory::create(startModuleArgs);

    if (createdModule.module != nullptr)
    {
        if (m_workerPool.addModule(createdModule.module))
        {
            m_server->sendResponse("Module '" + startModuleArgs.name + "' created");
        }
        else
        {
            m_server->sendResponse("Module name '" + startModuleArgs.name + "' already exist");
        }
    }
    else
    {
        m_server->sendResponse(createdModule.usage);
    }
}

void Core::stopModule(const QString & moduleName)
{
    if (m_workerPool.removeModule(moduleName))
    {
        m_server->sendResponse("Module '" + moduleName + "' succesfully stoped");
    }
    else
    {
        m_server->sendResponse("Module '" + moduleName + "' not found");
    }
}

