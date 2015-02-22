#include "ASniffer.hh"

ASniffer::ASniffer(Core &core, const std::string &name, const std::string &filter)
    : AModule(core, name), _sniffer(_core.interface().name(), Sniffer::PROMISC, filter)
{
}
