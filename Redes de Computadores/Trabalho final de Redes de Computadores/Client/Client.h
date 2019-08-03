#ifndef CLIENT_H_INCLUDED
#define CLIENT_H_INCLUDED
#include <arpa/inet.h>
#include <sys/socket.h>
#include <iostream>
#include <cstring>
#include <sstream>
using namespace std;


class Client{
private:
	int port;
	int sock_server;
	sockaddr_in address_server;
	socklen_t address_server_len;
	stringstream message_send;
	char message_recv[255];
	/*
	1 - Porta de conexão
	2 - Descritor do socket
	3 - Struct de configuração do socket
	4 -  ""
	5 - buffer de mensagem
	6 - buffer de mensagem recebida
	*/

public:
	Client(int port, string host);
	void create_connection();
	void send_message();
	void recv_message();
	void close_sck();
	void connection(bool flag);
};



#endif // CLIENT_H_INCLUDED
