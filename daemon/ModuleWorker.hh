#ifndef MODULEWORKER_H
# define MODULEWORKER_H

# include <QMutexLocker>
# include <QMap>
# include <QSharedPointer>

# include "AbstractWorker.hpp"
# include "modules/AModule.hh"
# include "Debug.hh"

class ModuleWorker : public AbstractWorker<QObject>
{
    Q_OBJECT

private:
    QMutex                                  m_mutex;
    QMap<QString, QSharedPointer<AModule>>  m_modules;

public:
    ModuleWorker();

    bool            addModule(AModule * module);
    bool            removeModule(const QString & name);
    bool            containsModule(const QString & name);

public slots:
    void            start() Q_DECL_OVERRIDE;
    void            stop() Q_DECL_OVERRIDE;
};

#endif // MODULEWORKER_H
