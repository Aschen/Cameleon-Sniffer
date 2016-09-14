#ifndef MODULEWORKER_HH
# define MODULEWORKER_HH

# include "AbstractWorker.hpp"
# include "modules/AModule.hh"

class ModuleWorker : public AbstractWorker<AModule>
{
private:
    AModule*        m_module;

public:
    ModuleWorker();

    void            setModule(AModule * module);

public slots:
    void            start() Q_DECL_OVERRIDE;
    void            stop() Q_DECL_OVERRIDE;
};

#endif // MODULEWORKER_HH
