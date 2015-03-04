#ifndef POSTSNIFFER_HH
#define POSTSNIFFER_HH

#include "ASniffer.hh"
#include "Http.hh"

using namespace Tins;

class PostSniffer : public ASniffer
{
public:
    typedef enum    e_type
    {
        KEYS = 1,
        HOSTNAME,
        ALL
    }               TYPE;

private:
    const std::string               _filename;
    const std::string               _hostname;
    const TYPE                      _type;
    const std::vector<std::string>  _keys;

public:
    // Sniff only matchins keys
    PostSniffer(const NetworkInterface &interface, std::ostream *out, const std::string &filename, const std::vector<std::string> &keys);
    // Sniff all POST traffic to host
    PostSniffer(const NetworkInterface &interface, std::ostream *out, const std::string &filename, const std::string &hostname);
    // Sniff all POST traffic to all host
    PostSniffer(const NetworkInterface &interface, std::ostream *out, const std::string &filename);

    ~PostSniffer(void) { }

private:
    void                            sniffKeys(const HTTP &http, IP::address_type ip);
    void                            sniffHostname(const HTTP &http, IP::address_type ip);
    void                            sniffAll(const HTTP &http, IP::address_type ip);


public:
    static std::string              help(void);

    // ASniffer
private:
    bool                            handler(PDU &pdu);
public:
    std::string                     info(void) const;
};

#endif // POSTSNIFFER_HH
