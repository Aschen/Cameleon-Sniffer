#include "AModule.hh"

AModule::AModule(const NetworkInterface &iface, const std::string &name, std::ostream *out) : _iface(iface), _name(name), _out(out) { }

const std::string AModule::getDate(void) const
{
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];

    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);

    return buf;
}

const std::string &AModule::name(void) const { return _name; }
