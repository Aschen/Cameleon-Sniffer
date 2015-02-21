#include "AModule.hh"

AModule::AModule(Core &core, const std::string &name) : _core(core), _name(name) { }

const std::string &AModule::name(void) const { return _name; }
