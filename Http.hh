#ifndef HTTP_HH
#define HTTP_HH

#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <stdexcept>

typedef std::pair<std::string, std::string> StringPair;

class HTTP
{
private:
    std::string                                 _verb;
    std::string                                 _location;
    std::string                                 _version;
    std::map<std::string, std::string>          _headers;
    std::map<std::string, std::string>          _cookies;
    std::map<std::string, std::string>          _data;

public:
    HTTP(std::stringstream &ss);

    const std::string                           getValue(const std::string &key) const;
    const std::string                           getHeader(const std::string &key) const;
    const std::string                           getCookie(const std::string &key) const;

private:
    void                                        parseData(const std::string &buf);
    void                                        parseCookies(const std::string &buf);

public:
    const std::string                           &verb(void) const;
    const std::string                           &location(void) const;
    const std::string                           &version(void) const;
    const std::map<std::string, std::string>    &headers(void) const;
    const std::map<std::string, std::string>    &data(void) const;
    const std::map<std::string, std::string>    &cookies(void) const;
};

#endif // HTTP_HH
