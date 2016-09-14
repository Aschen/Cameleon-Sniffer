##
## Makefile for  Cameleon Sniffer
## 
## Made by Aschen
## Login   maret_a
## 


CXX		=	g++

CXXFLAGS	=	-Wall -W -Wextra -pedantic -std=c++11 -Icore/include -Imodules/include -g3

SRCS_DAEMON	=	core/Launcher.cpp \
			core/DomainSocket.cpp \
			core/Daemon.cpp \
			core/Http.cpp \
			core/Addresses.cpp\
			modules/ASender.cpp \
			modules/ASniffer.cpp \
			modules/DnsSpoof.cpp \
			modules/DnsDump.cpp \
			modules/PostSniffer.cpp \
			modules/CookieSniffer.cpp \
			modules/Mitm.cpp \
			modules/TcpKill.cpp \
			modules/SurfWatcher.cpp \
			core/main.cpp

SRCS_SENDER	=	core/DomainSocket.cpp \
			core/Sender.cpp

OBJS_DAEMON	=	$(SRCS_DAEMON:.cpp=.o)

OBJS_SENDER	=	$(SRCS_SENDER:.cpp=.o)

DAEMON		=	cameleon-daemon

SENDER		=	cameleon

all:		$(DAEMON) $(SENDER)

$(DAEMON):	$(OBJS_DAEMON)
		$(CXX) -o $(DAEMON) $(OBJS_DAEMON) -ltins -lpthread

$(SENDER):	$(OBJS_SENDER)
		$(CXX) -o $(SENDER) $(OBJS_SENDER)

install:
		mkdir /etc/cameleon
		cp $(SENDER) /usr/bin/$(SENDER)	
		cp $(DAEMON) /usr/bin/$(DAEMON)

clean:
		rm -f $(OBJS_DAEMON)
		rm -f $(OBJS_SENDER)

fclean:		clean
		rm -f $(DAEMON)
		rm -f $(SENDER)

re:	 	fclean all
