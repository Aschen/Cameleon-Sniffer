#include "ASniffer.hh"

ASniffer::ASniffer(Core &core, const std::string &name, const std::string &filter)
    : AModule(core, name), _sniffer(_core.interface().name(), Sniffer::PROMISC, filter)
{
}

void ASniffer::sniff(void)
{
    _sniffer.sniff_loop(make_sniffer_handler(this, &ASniffer::handler));
}

void ASniffer::start(void)
{
    std::cout << "Start " << _name << std::endl;
    std::thread     t(&ASniffer::sniff, this);

    t.detach();
}

void ASniffer::stop(void)
{
    _sniffer.stop_sniff();
}
