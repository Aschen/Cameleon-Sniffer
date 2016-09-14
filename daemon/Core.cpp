#include "Core.hh"

Core::Core()
{
}

bool Core::addModule(AModule *module)
{
    ModuleWorker*   worker = m_workerPool.get();

    if ( ! worker->addModule(module))
    {
        DEBUG("Core::addModule() : Module not added", true);
        return false;
    }

    DEBUG("Core::addModule() : Module added", true);
    return true;
}

