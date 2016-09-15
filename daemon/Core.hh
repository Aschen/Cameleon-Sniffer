#ifndef CORE_HH
# define CORE_HH

# include <QSharedPointer>

# include "daemon/ModuleWorkerPool.hh"
# include "network/Server.hh"

class Core
{
private:
    ModuleWorkerPool        m_workerPool;
    QSharedPointer<Server>  m_server;
    QString                 m_iface;

public:
    Core();

    void                    startDaemon();

    bool                    addModule(AModule * module);
    bool                    removeModule(const QString & name);

    void                    commandDispatcher(const QVariant & data);

    const QString           &iface() const;
    void                    iface(const QString & newInterface);

private:
    void                    startModule(const QStringList & input);
    void                    stopModule(const QString & moduleName);
};

#endif // CORE_HH
