#include "AModule.hh"

AModule::AModule(Core &core, const std::string &name, std::ostream *out) : _core(core), _name(name), _out(out) { }

const std::string &AModule::name(void) const { return _name; }
