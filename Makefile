##
## Makefile for  in /home/maret_a/Projets/AbstractVM/cpp_abstractvm/sources
## 
## Made by Adrien Maret
## Login   <maret_a@epitech.net>
## 
## 
## Started on  19/02/2014 15:26
##

CXX		=	clang++

CXXFLAGS	=	-Wall -W -Wextra -pedantic -std=c++11 -g3

SRCS_DAEMON	=	Launcher.cpp \
			DomainSocket.cpp \
			Daemon.cpp \
			Http.cpp \
			Addresses.cpp\
			AModule.cpp \
			ASniffer.cpp \
			DnsSpoof.cpp \
			DnsDump.cpp \
			ReflectedFlood.cpp \
			HttpPostSniffer.cpp \
			HttpCookieSniffer.cpp \
			Mitm.cpp \
			TcpKill.cpp \
			main.cpp

SRCS_SENDER	=	DomainSocket.cpp \
			Sender.cpp

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
		cp $(SENDER) /usr/bin/$(SENDER)	
		cp $(DAEMON) /usr/bin/$(DAEMON)

clean:
		rm -f $(OBJS_DAEMON)
		rm -f $(OBJS_SENDER)

fclean:		clean
		rm -f $(DAEMON)
		rm -f $(SENDER)

re:	 	fclean all
