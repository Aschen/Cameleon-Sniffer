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

bool ModuleWorker::removeModule(const QString & name)
{
    QMutexLocker    locker(&m_mutex);

    if ( ! m_modules.contains(name))
    {
        DEBUG("ModuleWorker::removeModule() : Unknown module" << name, true);
        return false;
    }

    m_modules.remove(name);

    return true;
}

bool ModuleWorker::containsModule(const QString & name)
{
    QMutexLocker    locker(&m_mutex);

    return m_modules.contains(name);
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

