#ifndef HTPPPOSTSNIFFER_HH
#define HTPPPOSTSNIFFER_HH

#include "ASniffer.hh"
#include "Http.hh"

using namespace Tins;

class HttpPostSniffer : public ASniffer
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
    HttpPostSniffer(const NetworkInterface &interface, std::ostream *out, const std::string &filename, const std::vector<std::string> &keys);
    // Sniff all POST traffic to host
    HttpPostSniffer(const NetworkInterface &interface, std::ostream *out, const std::string &filename, const std::string &hostname);
    // Sniff all POST traffic to all host
    HttpPostSniffer(const NetworkInterface &interface, std::ostream *out, const std::string &filename);

    ~HttpPostSniffer(void) { }


    // AModule
public:
    virtual std::string             info(void) const;
    static std::string              help(void);

    // ASniffer
public:
    bool                            handler(PDU &pdu);

private:
    void                            sniffKeys(const HTTP &http, IP::address_type ip);
    void                            sniffHostname(const HTTP &http, IP::address_type ip);
    void                            sniffAll(const HTTP &http, IP::address_type ip);
};

#endif // HTPPPOSTSNIFFER_HH
