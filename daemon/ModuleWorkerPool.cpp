#include "ModuleWorkerPool.hh"

#include "WorkerFactory.hpp"
#include "Debug.hh"

ModuleWorkerPool::ModuleWorkerPool()
{

}

bool ModuleWorkerPool::addModule(AModule * module)
{
    if (m_workers.contains(module->name()))
    {
        DEBUG("ModuleWorkerPool::addModule() : Module" << module->name() << "already exist", false);
        return false;
    }

    ModuleWorker*       worker = WorkerFactory<ModuleWorker>::create(nullptr, module->objectName());

    m_workers[module->name()] = QSharedPointer<ModuleWorker>(worker);

    worker->setModule(module);

    WorkerFactory<ModuleWorker>::go(worker);

    return true;
}

bool ModuleWorkerPool::removeModule(const QString & name)
{
    if ( ! m_workers.contains(name))
    {
        DEBUG("ModuleWorkerPool::addModule() : Module" << name << "does not exist", false);
        return false;
    }

    m_workers[name]->stop();
    m_workers.remove(name);

    return true;
}

