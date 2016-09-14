#ifndef ASNIFFER_HH
# define ASNIFFER_HH

# include <tins/tins.h>

# include "AModule.hh"

class ASniffer : public AModule
{
protected:
    Tins::Sniffer   m_sniffer;

public:
    ASniffer(const QString & type, const QString & name, const Tins::SnifferConfiguration & snifferConfig);
    virtual ~ASniffer();

    // AModule interface
public:
    void            start();
    void            stop();
};

#endif // ASNIFFER_HH
