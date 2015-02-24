#ifndef HTPPPOSTSNIFFER_HH
#define HTPPPOSTSNIFFER_HH

#include "ASniffer.hh"
#include "Http.hh"

using namespace Tins;

class HttpPostSniffer : public ASniffer
{
private:
    const std::string               _filename;
    const std::vector<std::string>  _keys;

public:
    HttpPostSniffer(Core &core, const std::string &name, std::ostream *out, const std::string &filename, const std::vector<std::string> &keys);
    ~HttpPostSniffer(void) { }

    // AModule
public:
    virtual std::string             info(void);
    static std::string              help(void);

    // ASniffer
public:
    bool                            handler(PDU &pdu);

};

#endif // HTPPPOSTSNIFFER_HH
