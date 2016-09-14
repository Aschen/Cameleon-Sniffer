#ifndef MODULEWORKERPOOL_HH
# define MODULEWORKERPOOL_HH

# include <QVector>
# include <QThread>

# include "ModuleWorker.hh"

class ModuleWorkerPool
{
private:
    quint32                         m_size;
    quint32                         m_index;
    QVector<ModuleWorker*>          m_workers;

public:
    ModuleWorkerPool(quint32 size = QThread::idealThreadCount() - 1);
    ~ModuleWorkerPool();

    ModuleWorker*                   get();

    const QVector<ModuleWorker*>&   workers() const;
};

#endif // MODULEWORKERPOOL_HH
