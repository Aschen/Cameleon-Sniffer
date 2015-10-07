#include "ASender.hh"

ASender::ASender(const NetworkInterface &iface, const std::string &name, std::ostream *out) : _iface(iface), _name(name), _out(out) { }

const std::string &ASender::name(void) const { return _name; }
