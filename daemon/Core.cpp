#include "Core.hh"

#include "Debug.hh"
#include <QThread>

Core::Core()
{
}

bool Core::addModule(AModule * module)
{
    return m_workerPool.addModule(module);
}

bool Core::removeModule(const QString & name)
{
    return m_workerPool.removeModule(name);
}

