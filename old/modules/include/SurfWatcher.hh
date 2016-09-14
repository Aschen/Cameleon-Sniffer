#ifndef SURFWATCHER_HH
#define SURFWATCHER_HH

#include "Http.hh"
#include "ASniffer.hh"

class SurfWatcher : public ASniffer
{
public:
    typedef enum    e_type
    {
        ALL = 1,
        IP,
        HOST
    }               TYPE;

private:
    const std::string               _filename;
    const SurfWatcher::TYPE         _type;
    const std::string               _hostname;
    const IPv4Address               _ip;
    const char                      *_extensions[9] = { ".gif", ".jpg", ".css", ".js", ".jpeg", ".png", ".webm", ".flv", NULL };

public:
    SurfWatcher(const NetworkInterface &interface, std::ostream *out, const std::string &filename, IPv4Address ip);
    SurfWatcher(const NetworkInterface &interface, std::ostream *out, const std::string &filename, std::string &hostname);
    SurfWatcher(const NetworkInterface &interface, std::ostream *out, const std::string &filename);

    ~SurfWatcher(void) { }


private:
    void                            watchAll(const HTTP &http, Tins::IP::address_type ip) const;
    void                            watchIp(const HTTP &http, Tins::IP::address_type ip) const;
    void                            watchHost(const HTTP &http, Tins::IP::address_type ip) const;
    void                            isRessource(const std::string &location) const;

public:
    static std::string              help(void);

    // ASniffer
private:
    bool                            handler(PDU &pdu);
public:
    std::string                     info(void) const;
};

#endif // SURFWATCHER_HH
