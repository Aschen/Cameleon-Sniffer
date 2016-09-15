#ifndef ABSTRACTWORKER_HPP
# define ABSTRACTWORKER_HPP

# include "Debug.hh"

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

#endif // ABSTRACTWORKER_HPP
