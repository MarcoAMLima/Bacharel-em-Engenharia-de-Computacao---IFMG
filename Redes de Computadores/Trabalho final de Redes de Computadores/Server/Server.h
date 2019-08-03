#ifndef SERVER_H_INCLUDED
#define SERVER_H_INCLUDED

#include <iostream>
#include <cstdlib>
#include <arpa/inet.h>  	//Biblioteca de comunicação em rede
#include <sys/socket.h> 	//Biblioteca do socket
//#include <pthread.h>    	//Biblioteca das threads
#include <cstring>      	// Biblioteca de manipulação de strings
#include <vector>
#include <stdio.h>
#include <sstream>
#include <thread>

using namespace std;

class Server{
private:
	int sock_server;
	socklen_t socket_server_len;
	sockaddr_in address_server;
	int port;
	char message_recv[255];
	stringstream message_send;
	int sock_client;
	FILE* file;
public:
	sockaddr_in addr_client;
	socklen_t len_addr_client;
	bool flag_close;

	/*
	Atributos de dados da classe
	Privados:
		1 - Definição do socket, PF_INET para comunicação via TCP, SOCK_STREAM para transmissão em Bytes.
		2 - struct de tamanho do socket
		3 - estrutura do socket para definição de parâmetros e utilização do mesmo.
		4 - porta de conexão.
		5 - estado para a manipulação da mensagem de retorno. (para o método state_machine())

	  //Definições da mensagem
		6 - Mensagem recebida
		7 - Tamanho da mensagem recebida

		8 - Mensagem de envio
		9 - Tamanho da mensagem de envio

	Publicos:
		10 - Fila dinâmica para processamento das requisições.

	  //Definições do remetente
		11 - endereço do remetente
		12 - tamanho do endereço do remetente
		13 - Definição do socket_client
	*/

public:
	Server(int port);
	void accept_connection();
	void recv_message();
	void send_message();
	string capture_data();
	bool authenticate(string login, string pass, bool flag_change);
	void connection();
	void changepass();
	void run();
	void write_file(string user, string pass, string new_pass);
	string hashing(string pass);
	string pass_archived(string user);
	/*
	  Atributos de métodos da classe.
		1 - Construtor do socket.
		2 - Função para fazer o bind da porta, retorna -1 para recusado e 0 para aceito.
		3 - Função para verificar o listen, retorna -1 se a conexão foi recusada e 0 para aceita.
		4 - Função para fazer a conexão com o cliente
		5 - função para fazer o recvfrom
		6 - função para fazer o sendto

		7 - função para ler os dados do arquivo e enviar para a função 8
		8 - faz autenticação do usuário.


		x - Função que faz as conexões
		x+1 - Função para fazer o servidor rodar
	*/
};

#endif // SERVER_H_INCLUDED
