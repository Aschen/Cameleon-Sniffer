#ifndef ABSTRACTWORKER_H
# define ABSTRACTWORKER_H

# include <QDebug>

template < class ParentObject >
class AbstractWorker : public ParentObject
{
public slots:
    virtual void start() = 0;
    virtual void stop()
    {
        qWarning("You're using the default implementation of the stop() function, this is broken");
    }
};

#endif // ABSTRACTWORKER_H
