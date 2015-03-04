#ifndef HTTPCOOKIESNIFFER_HH
#define HTTPCOOKIESNIFFER_HH

#include "ASniffer.hh"
#include "Http.hh"

class HttpCookieSniffer : public ASniffer
{
private:
    const std::string               _filename;
    const std::vector<std::string>  _keys;

public:
    HttpCookieSniffer(const NetworkInterface &interface, std::ostream *out, const std::string &filename, const std::vector<std::string> &keys);
    ~HttpCookieSniffer(void) { }

public:
    static std::string              help(void);


    // ASniffer
private:
    bool                            handler(PDU &pdu);
public:
    std::string                     info(void) const;
};

#endif // HTTPCOOKIESNIFFER_HH
