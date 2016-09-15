#ifndef WORKERFACTORY_H
# define WORKERFACTORY_H

# include <QThread>

# include "AbstractWorker.hpp"
# include "modules/AModule.hh"

template < typename WorkerClass >
class WorkerFactory
{
public:
    static WorkerClass * create(QObject * parent, const QString & name);
    static void go(WorkerClass * worker);
};

template < class WorkerClass >
WorkerClass * WorkerFactory < WorkerClass > ::create(QObject * parent, const QString & name)
{
    // Create the thread where the worker will live
    QThread * thread = new QThread(parent);

    // Set the worker name on its thread
    if (name.size() != 0)
        thread->setObjectName(name);

    // Create the worker
    WorkerClass * worker = new WorkerClass;

    // Throw an error if worker is not inheriting QObject
    QObject * qObjectWorker = static_cast < QObject * > (worker);
    Q_UNUSED(qObjectWorker);

    // Move the worker to its associated thread
    worker->moveToThread(thread);

    // If the worker is destroyed, quit the thread
    thread->connect(worker, SIGNAL(destroyed()), SLOT(quit()));

    // If the thread is finished, delete the worker
    thread->connect(thread, SIGNAL(finished()), SLOT(deleteLater()));

    // When the thread is started, call the worker abstract method start()
    worker->connect(thread, SIGNAL(started()), SLOT(start()));

    return worker;
}

template < class WorkerClass >
void WorkerFactory < WorkerClass > ::go(WorkerClass * worker)
{
    // Start the thread
    worker->thread()->start();
}

#endif // WORKERFACTORY_H
