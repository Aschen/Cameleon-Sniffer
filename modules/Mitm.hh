#ifndef MITM_HH
# define MITM_HH

# include <QVector>

# include <tins/tins.h>

# include "AModule.hh"
# include "NetworkAddresses.hh"
# include "daemon/Command.hh"

class Mitm : public AModule
{
    struct Config
    {
        QString     victimIP;
        QString     gatewayIP;
    };

public:
    static Mitm*  create(const StartModuleArgs &startModuleArgs);
    static Tins::SnifferConfiguration   snifferConfiguration();
    static const QStringList  help;


private:
    Tins::PacketSender          m_packetSender;
    NetworkAddresses            m_attacker;
    NetworkAddresses            m_gateway;
    NetworkAddresses            m_victim;
    QVector<Tins::EthernetII>   m_originalPackets;
    QVector<Tins::EthernetII>   m_poisonPackets;

public:
    Mitm(const StartModuleArgs & startModuleArgs, const Config & config);
    ~Mitm();


private:
    const Tins::HWAddress<6>    arpRequest(const Tins::IPv4Address & targetIp);
    void                        createOriginalPackets();
    void                        createPoisonPackets();

    // AModule interface
public slots:
    void                start();
    void                stop();
};

#endif // MITM_HH
