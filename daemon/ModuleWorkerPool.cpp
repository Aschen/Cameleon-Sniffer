#include "ModuleWorkerPool.hh"

#include "WorkerFactory.hpp"

ModuleWorkerPool::ModuleWorkerPool(quint32 size)
    : m_size(size),
      m_index(0),
      m_workers(m_size)
{
    // Create and start workers
    for (quint32 i = 0; i < m_size; ++i)
    {
        ModuleWorker*   worker =
                WorkerFactory<ModuleWorker>::create(nullptr, QString("Module Worker %1").arg(i + 1));

        m_workers[i] = worker;

        WorkerFactory<ModuleWorker>::go(worker);
    }
}

ModuleWorkerPool::~ModuleWorkerPool()
{
    for (ModuleWorker* worker : m_workers)
    {
        worker->deleteLater();
    }
}

ModuleWorker *ModuleWorkerPool::get()
{
    ModuleWorker*   worker = m_workers[m_index];

    m_index++;

    if (m_index >= m_size)
        m_index = 0;

    return worker;
}

const QVector<ModuleWorker *> &ModuleWorkerPool::workers() const
{
    return m_workers;
}
