#include "ASniffer.hh"

ASniffer::ASniffer(const NetworkInterface &iface, const std::string &name, const std::string &filter, std::ostream *out)
    : _sniffer(_iface.name(), Sniffer::PROMISC, filter), _iface(iface), _name(name), _out(out)
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

const std::string &ASniffer::name(void) const { return _name; }
