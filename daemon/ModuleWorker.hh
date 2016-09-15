#ifndef MODULEWORKER_HH
# define MODULEWORKER_HH

# include <QSharedPointer>

# include "AbstractWorker.hpp"
# include "modules/AModule.hh"

class ModuleWorker : public AbstractWorker<QObject>
{
    Q_OBJECT

private:
    QSharedPointer<AModule> m_module;

public:
    ModuleWorker();
    virtual ~ModuleWorker();

    void                    setModule(AModule * module);

public slots:
    void                    start();
    void                    stop();
};

#endif // MODULEWORKER_HH
