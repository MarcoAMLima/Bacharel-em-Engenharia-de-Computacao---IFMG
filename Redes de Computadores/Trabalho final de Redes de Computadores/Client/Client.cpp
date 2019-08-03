/*
    1 - Marco Aurélio Monteiro Lima         RA : 0022933
    2 - Marcus Vinícius Rodrigues Campos    RA : 0022127
    3 - Júlio César Machado Álvares         RA : 0023163
    4 - Pâmela Evelyn Carvalho              RA : 0015669

*/


#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include "Client.h"
#include <cstring>
#include <sstream>
#include "base64.h"

using namespace std;

Client::Client(int port, string host){
	this->port = port;
	this->sock_server = socket(PF_INET, SOCK_STREAM, 0);
	this->address_server.sin_family = AF_INET;
	this->address_server.sin_port = htons(this->port);
	this->address_server.sin_addr.s_addr = inet_addr(host.c_str());
	this->address_server_len = sizeof(this->address_server);
}

void Client::create_connection(){
	bool state = connect(this->sock_server, (const sockaddr*)&this->address_server, this->address_server_len);
	if(state != 0) {
		cout << "Erro de conexão" << endl;
		exit(0);
	}
}

void Client::send_message(){
	sendto(this->sock_server, this->message_send.str().c_str(), this->message_send.str().length(), 0, (sockaddr*)&this->address_server, this->address_server_len);
	cout << "Enviado: \n" << this->message_send.str() << endl;
}

void Client::recv_message(){
	bzero(this->message_recv, 255);
	recvfrom(this->sock_server, this->message_recv, 255, 0, (sockaddr*)&this->address_server, &this->address_server_len);
	cout << this->message_recv;
}

void Client::connection(bool flag){
	if(!flag){
		this->create_connection();
	}

	string user;
	string pass;
	string new_pass;
	int index_erase;
	int i = 0;
	string code;

	cout << "user: ";
	cin >> user;
	cout << "pass: ";
	cin >> pass;
	cout << endl;

	// pass = codifica_base64();
	char *pass_code, *pass_aux;
	pass_aux = const_cast<char*>(pass.c_str());
	codifica_base64(pass_aux, strlen(pass_aux), &pass_code);
	pass = pass_code;

	if(user[0] == '*'){
		while(pass[i] != '*'){
			i++;
		}
		index_erase = i;
		i+=1;
		while(i < pass.size()){
			new_pass += pass[i];
			i++;
		}
		pass.erase(index_erase, pass.size()-1);
		user.erase(user.begin());
		this->message_send.str("");
		this->message_send << "changepass\nuser: " << user << "\n" << "pass: " << pass << "\n" << "newpass: " << new_pass << "\n\n";
		this->send_message();
		this->recv_message();
	}else{
		this->message_send.str("");
		this->message_send << "auth\nuser: " << user << "\n" << "pass: " << pass << "\n\n";
	}
	this->send_message();
	this->recv_message();
	string msg(this->message_recv);
	for(int i = 0; i < 3; i++) code += msg[i];
	cout << endl;

	if(code == "200"){
		return;
	}else{
		this->connection(true);
	}
}


int main(int argc, char** argv){
	Client *cliente = new Client(5555, "127.0.0.1");
	cliente->connection(false);
	return 0;
}
