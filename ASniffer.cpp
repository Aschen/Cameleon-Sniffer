#include "ASniffer.hh"

ASniffer::ASniffer(const NetworkInterface &iface, const std::string &name, const std::string &filter, std::ostream *out)
    : AModule(iface, name, out), _sniffer(_iface.name(), Sniffer::PROMISC, filter)
{
}

void ASniffer::sniff(void)
{
    _sniffer.sniff_loop(make_sniffer_handler(this, &ASniffer::handler));
}

void ASniffer::start(void)
{
    std::thread     t(&ASniffer::sniff, this);

    t.detach();
}

void ASniffer::stop(void)
{
    _sniffer.stop_sniff();
}
