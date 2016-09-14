#ifndef CORE_HH
# define CORE_HH

# include "ModuleWorkerPool.hh"

class Core
{
private:
    ModuleWorkerPool        m_workerPool;

public:
    Core();

    bool                    addModule(AModule * module);
};

#endif // CORE_HH
