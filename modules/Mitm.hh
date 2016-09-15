#ifndef MITM_HH
# define MITM_HH

# include <QVector>

# include <tins/tins.h>

# include "AModule.hh"
# include "NetworkAddresses.hh"

class Mitm : public AModule
{
    struct Config
    {
        QString     victimIP;
        QString     gatewayIP;
    };

public:
    static Mitm*  create(const QString & name, const QStringList & args);
    static Tins::SnifferConfiguration   snifferConfiguration();
    static const QStringList  help;

private:
    NetworkAddresses            m_attacker;
    NetworkAddresses            m_gateway;
    NetworkAddresses            m_victim;
    QVector<Tins::EthernetII>   m_originalPackets;
    QVector<Tins::EthernetII>   m_poisonPackets;

public:
    Mitm(const QString & name, const QString & victimIP, const QString & gatewayIP);
};

#endif // MITM_HH
