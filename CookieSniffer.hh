#ifndef COOKIESNIFFER_HH
#define COOKIESNIFFER_HH

#include "ASniffer.hh"
#include "Http.hh"

class CookieSniffer : public ASniffer
{
private:
    const std::string               _filename;
    const std::vector<std::string>  _keys;

public:
    CookieSniffer(const NetworkInterface &interface, std::ostream *out, const std::string &filename, const std::vector<std::string> &keys);
    ~CookieSniffer(void) { }

public:
    static std::string              help(void);


    // ASniffer
private:
    bool                            handler(PDU &pdu);
public:
    std::string                     info(void) const;
};

#endif // COOKIESNIFFER_HH
