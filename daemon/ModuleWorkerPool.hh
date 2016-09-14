#ifndef MODULEWORKERPOOL_HH
# define MODULEWORKERPOOL_HH

# include <QMap>
# include <QSharedPointer>

# include "modules/AModule.hh"
# include "ModuleWorker.hh"

class ModuleWorkerPool
{
private:
    QMap<QString, QSharedPointer<ModuleWorker>> m_workers;

public:
    ModuleWorkerPool();

    bool        addModule(AModule * module);
    bool        removeModule(const QString & name);
};

#endif // MODULEPOOL_HH
