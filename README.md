# Cameleon-Sniffer
A modular network sniffer written in c++

I make this project on my free time to improve my understanding of networks and networks protocol.

I'm not responsible of what you do with this software. Use it only for testing purpose on your local network.


## How it work


There is a programm running in background (cameleon-daemon) and a programm to send command to the daemon (cameleon).

I was inspired by Docker for there daemon system. The client communicate with the daemon via Unix domain socket.

I use the libtins from Mathias Frontanini for all network operations. Thanks to him for this amazing lib !

## Installation

You will need libtins on your system, please see here : http://libtins.github.io/download/

You MUST compile the library with c++11 support !

You will also need clang++. (You can use g++ if you want, just change the Makefile)

Then download the whole repository then extract it somewhere and run :
```
make
sudo make install
```

This will make the programm then create a directory /etc/cameleon for the unix socket and finally copy cameleon-daemon and cameleon to /usr/bin.

## Usage

  * First run the daemon root privilege
  ```
  sudo cameleon-daemon
  ```
  * Then you can send command to the daemon. See help
  ```
  cameleon help
  ```
  * Start module 
  ```
  cameleon start <module_name> <instance_name> [options]
  ```
  * Display running modules
  ```
  cameleon ps
  ```
  * Stop module
  ```
  cameleon stop <instance_name>
  ```
  * Stop the daemon
  ```
  cameleon exit
  ```

Filename must by provided with ABSOLUTE path.

## Availables Modules

See all availables module :
```
> cameleon list
```


### Mitm

Start Man In The Middle attack by arp poisoning.

You have to provide a file with the hosts you want spoof and the gateway ip.

The hosts file must contain only one ip address per line.
```
> cameleon start mitm myMitm /path/to/file/hosts.txt 192.168.1.1
```

### DnsDump

Dump all dns queries with the source ip in a file.
```
> cameleon start dnsdump my-dump /path/to/file/queries.txt
```

### DnsSpoof

Forge replies to specifics dns queries.

You must provide a hostfile with the host to spoof. This file must be in hosts(5) format. (eg: 127.0.0.1    google.fr)

```
> cameleon start dnsspoof spoof /path/to/file/hosts
```

### PostSniffer

Capture POST request. 

You can capture all request.
```
> cameleon start postsniffer allreq all /path/to/file/allposts.txt
```

Or only request to a specific hostname.
```
> cameleon start postsniffer allhost host /path/to/file/allhost.txt  yoursite.com
```

Or only request who contains the specified keys.
```
> cameleon start postsniffer my_keys keys /path/to/file/postkeys.txt foo bar toto
```

### CookieSniffer

Capture the specified cookies.

```
> cameleon start cookiesniffer cookies /path/to/file/cookies.txt session_id __utm 
```

