#include "Core.hh"

Core::Core()
{
}

bool Core::addModule(AModule * module)
{
    ModuleWorker*   worker = m_workerPool.get();

    if ( ! worker->addModule(module))
    {
        return false;
    }

    DEBUG("Core::addModule() : Module added", true);
    return true;
}

bool Core::removeModule(const QString & name)
{
    bool    success = false;

    for (ModuleWorker * worker : m_workerPool.workers())
    {
        if (worker->containsModule(name))
        {
            success = worker->removeModule(name);
            break;
        }
    }

    if (success)
        DEBUG("Core::removeModule() : Module" << name << "removed", true);

    return success;
}

