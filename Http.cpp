#include "Http.hh"

HTTP::HTTP(std::stringstream &ss)
{
    int             sep;

    ss >> _verb;
    ss >> _location;
    ss >> _version;
    for (std::string line; std::getline(ss, line);)
    {
        if ((sep = line.find(':')) != -1)
        {
            _headers[line.substr(0, sep)] = line.substr(sep);
        }
        else if (_verb == "POST")
        {
            // If there is data on line (and not only \n)
            if (line.length() > 1)
                parseData(line);
        }
    }
}

const std::string HTTP::getHeader(const std::string &key) const
{
    std::map<std::string, std::string>::const_iterator it = _headers.find(key);

    if (it == _headers.end())
        throw std::out_of_range("Key" + key + "don't exist");
    return (*it).second;
}

const std::string HTTP::getValue(const std::string &key) const
{
    std::map<std::string, std::string>::const_iterator it = _data.find(key);

    if (it == _data.end())
        throw std::out_of_range("Key" + key + "don't exist");
    return (*it).second;
}

void HTTP::parseData(const std::string &buf)
{
    std::istringstream  ss(buf);
    int                 sep;

    for (std::string pair; std::getline(ss, pair, '&');)
    {
        sep = pair.find('=');
        _data[pair.substr(0, sep)] = pair.substr(sep + 1);
    }
}

const std::string &HTTP::verb(void) const { return _verb; }

const std::string &HTTP::location(void) const { return _location; }

const std::string &HTTP::version(void) const { return _version; }

const std::map<std::string, std::string> &HTTP::headers(void) const { return _headers; }

const std::map<std::string, std::string> &HTTP::data(void) const { return _data; }
