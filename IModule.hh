#ifndef IMODULE_HH
#define IMODULE_HH

#include <string>

class IModule
{
public:
    virtual ~IModule(void) { }
    virtual void                start(void) = 0;
    virtual void                stop(void) = 0;
    virtual std::string         info(void) const = 0;
    virtual const std::string   &name(void) const = 0;
};

#endif // IMODULE_HH
