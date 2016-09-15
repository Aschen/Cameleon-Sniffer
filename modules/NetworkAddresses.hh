#ifndef NETWORKADDRESSES
# define NETWORKADDRESSES

# include <tins/ip_address.h>
# include <tins/hw_address.h>

typedef struct  s_nerwork_addresses
{
    Tins::IPv4Address   ip;
    Tins::HWAddress<6>  mac;
}               NetworkAddresses;

#endif // NETWORKADDRESS

