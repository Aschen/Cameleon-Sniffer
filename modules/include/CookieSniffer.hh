#ifndef COOKIESNIFFER_HH
#define COOKIESNIFFER_HH

#include "ASniffer.hh"
#include "Http.hh"

class CookieSniffer : public ASniffer
{
public:
    typedef enum    e_type
    {
        ALL = 1,
        KEYS,
        HOST
    }               TYPE;

private:
    const std::string               _filename;
    const CookieSniffer::TYPE       _type;
    const std::string               _hostname;
    const std::vector<std::string>  _keys;

public:
    // Sniff cookies matching keys
    CookieSniffer(const NetworkInterface &interface, std::ostream *out, const std::string &filename, const std::vector<std::string> &keys);
    // Sniff cookies matching hostname
    CookieSniffer(const NetworkInterface &interface, std::ostream *out, const std::string &filename, const std::string &hostname);
    // Sniff all cookies
    CookieSniffer(const NetworkInterface &interface, std::ostream *out, const std::string &filename);

    ~CookieSniffer(void) { }


private:
    void                            sniffKeys(const HTTP &http, IP::address_type ip) const;
    void                            sniffHost(const HTTP &http, IP::address_type ip) const;
    void                            sniffAll(const HTTP &http, IP::address_type ip) const;

public:
    static std::string              help(void);


    // ASniffer
private:
    bool                            handler(PDU &pdu);
public:
    std::string                     info(void) const;
};

#endif // COOKIESNIFFER_HH
