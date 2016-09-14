#ifndef CORE_HH
# define CORE_HH

# include "daemon/ModuleWorkerPool.hh"

class Core
{
private:
    ModuleWorkerPool        m_workerPool;

public:
    Core();

    bool                    addModule(AModule * module);
    bool                    removeModule(const QString & name);
};

#endif // CORE_HH
