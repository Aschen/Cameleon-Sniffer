#ifndef MITM_HH
# define MITM_HH

# include <QVector>
# include <QTimer>

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

    Q_OBJECT

public:
    static Mitm*  create(const StartModuleArgs &startModuleArgs);
    static Tins::SnifferConfiguration   snifferConfiguration();
    static const QStringList  USAGE;
    static const uint32_t ARP_TIMEOUT;


private:
    Tins::PacketSender          m_packetSender;
    NetworkAddresses            m_attacker;
    NetworkAddresses            m_gateway;
    NetworkAddresses            m_victim;
    QVector<Tins::EthernetII>   m_originalPackets;
    QVector<Tins::EthernetII>   m_poisonPackets;
    QTimer                      m_timer;

public:
    Mitm(const StartModuleArgs & startModuleArgs, const Config & config);
    ~Mitm();


private:
    const Tins::HWAddress<6>    arpRequest(const Tins::IPv4Address & targetIp);
    void                        createOriginalPackets();
    void                        createPoisonPackets();

private slots:
    void                        poison();

signals:
    void                        startTimer(int);
    void                        stopTimer();

    // AModule interface
public slots:
    void                start();
    void                stop();
};

#endif // MITM_HH
