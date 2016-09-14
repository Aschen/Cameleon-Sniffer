#include "ModuleWorker.hh"

ModuleWorker::ModuleWorker()
{
}

bool ModuleWorker::addModule(AModule * module)
{
    QMutexLocker    locker(&m_mutex);

    if (m_modules.contains(module->name()))
    {
        DEBUG("ModuleWorker::addModule() : Name" << module->name() << "already in use", true);
        return false;
    }

    m_modules[module->name()] = QSharedPointer<AModule>(module);

    module->moveToThread(this->thread());

    module->start();

    return true;
}

void ModuleWorker::start()
{
    DEBUG("ModuleWorker::start()", true);
}

void ModuleWorker::stop()
{
    DEBUG("ModuleWorker::stop()", true);

    for (auto & module : m_modules)
        module->stop();
}

