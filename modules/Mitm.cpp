#include "Mitm.hh"

Mitm *Mitm::create(const QString &name, const QStringList &args)
{
    if (args.size() < 2)
    {
        return nullptr;
    }

    Mitm::Config    config;

    config.victimIP = args[0];
    config.gatewayIP = args[1];


}

Tins::SnifferConfiguration Mitm::snifferConfiguration()
{
    Tins::SnifferConfiguration  config;

    config.set_filter("dst port 53");
    config.set_promisc_mode(true);

    return config;
}

const QStringList Mitm::help = { "Mitm module usage :",
                                  "\t cameleon start Mitm <module name> <victim_ip> <gateway_ip>"
                                };

/* Class Mitm ****************************************************************/

Mitm::Mitm(const QString & name, const QString & victimIP, const QString & gatewayIP)
    : AModule("Mitm", name, "wlan0")
{

}

