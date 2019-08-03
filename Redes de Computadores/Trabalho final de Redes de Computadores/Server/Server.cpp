/*
    1 - Marco Aurélio Monteiro Lima         RA : 0022933
    2 - Marcus Vinícius Rodrigues Campos    RA : 0022127
    3 - Júlio César Machado Álvares         RA : 0023163
    4 - Pâmela Evelyn Carvalho              RA : 0015669

*/

#include <iostream>
#include <cstdlib>
#include <arpa/inet.h>   //Biblioteca de comunicação em rede
#include <unistd.h>
#include <sys/socket.h> //Biblioteca do socket
#include <thread>    //Biblioteca das threads
#include <cstring>      // Biblioteca de manipulação de strings
#include <vector> 		//Biblioteca para implementar a fila.
#include "Server.h"
#include <cstdio>
#include <sstream>
#include "hash256.h"
#include "base64.h"


using namespace std;

bool replace_string(string &data, const string &str_inicial, const string &str_final) {
    size_t start_pos = data.find(str_inicial);
    if(start_pos == string::npos)
        return false;
    data.replace(start_pos, str_inicial.length(), str_final);
    return true;
}

// str = const_cast<string>(vetor_char);
Server::Server(int port){
		this->sock_server = socket(PF_INET, SOCK_STREAM, 0);
		this->socket_server_len = sizeof(this->address_server);
		this->port = port;
		this->address_server.sin_family = AF_INET;
		this->address_server.sin_port = htons(this->port);
		this->address_server.sin_addr.s_addr = htonl(INADDR_ANY);
		this->sock_client = 0;
		this->flag_close = false;

		if(bind(this->sock_server, (const sockaddr*) &this->address_server, this->socket_server_len) != 0)
			exit(0);
		if(listen(this->sock_server, 255) != 0)
			exit(0);
}

void Server::recv_message(){
	bzero(this->message_recv, 255);
	recvfrom(this->sock_client, this->message_recv, 255, 0, (sockaddr*) &this->addr_client, &this->len_addr_client);
	cout <<  this->message_recv << endl;
}

void Server::send_message(){
	sendto(this->sock_client, this->message_send.str().c_str(),this->message_send.str().length() , 0, (sockaddr*) &this->addr_client, this->len_addr_client);
}

void Server::accept_connection(){
	this->sock_client = accept(this->sock_server, (sockaddr*) &this->addr_client, &this->len_addr_client);
	/*
		gera a conexão com o socket do cliente
		com a conexão feita, é atribuido ao sock_client, que é o descritor de arquivo do socket do cliente
	*/
}


string Server::capture_data(){
	char aux[1024];
	string buffer;
	this->file = fopen("data.txt", "r");
	while(!feof(this->file)){
		if(fgets(aux, 1024, this->file) != NULL)
		buffer += (string)aux;
	}
	fclose(this->file);
	return buffer;
}

string Server::hashing(string pass){
	return encode_sha256(pass);
}



void Server::write_file(string user, string pass, string new_pass){
	string data = this->capture_data();
	string data_aux, data_aux2;
	size_t pos;
	pos = data.find(user);
	int index;
	index = (int)pos;
	while(data[index] != '\n'){
		data_aux += data[index];
		index++;
	}
	data_aux+='\n';
	index ++;
	while(data[index] != '\n'){
		data_aux += data[index];
		index++;
	}
	data_aux+='\n';
	data_aux = "user: " + data_aux;
	data_aux2 = data_aux;
	replace_string(data_aux, pass, new_pass);
	replace_string(data, data_aux2, data_aux);
	this->file = fopen("data.txt", "w");
	fprintf(this->file, "%s", const_cast<char*>(data.c_str()));
	fclose(this->file);
}

bool Server::authenticate(string login, string pass, bool flag_change){
	string data = this->capture_data();
	string login_aux = "", pass_aux = "";
	size_t pos;
	string cr = "";
	int index;

	pos = data.find(login);
	if(pos != string::npos){
		index = (int)pos;
		while(cr != "\n"){
			login_aux += cr;
			cr = data[index];
			index++;
		}
		while(cr != ":"){
			index++;
			cr = data[index];
		}
		index += 2;
		while(data[index] != '\n'){
			pass_aux += data[index];
			index++;
		}
	}

	if(login_aux == login && pass == pass_aux){

		this->message_send.str("");
		this->message_send << "200 Auth OK\n";
		this->flag_close = true;
		if(flag_change == true) return true;
	}else if(login_aux != login){

		this->message_send.str("");
		this->message_send << "450 User doesn't exists\n";
		if(flag_change == true) return false;
	}else if(pass != pass_aux){

		this->message_send.str("");
		this->message_send << "401 Not authorized\n";
		if(flag_change == true) return false;
	}
	this->send_message();
}

string Server::pass_archived(string user){
	string data = this->capture_data();
	size_t pos;
	int index;
	string cr = "";
	string pass;

	pos = data.find(user);
	if(pos != string::npos){
		index = (int)pos;
		while(cr != "\n"){
			cr = data[index];
			index++;
		}
		while(cr != ":"){
			index++;
			cr = data[index];
		}
		index += 2;
		while(data[index] != '\n'){
			pass += data[index];
			index++;
		}
	}
		return pass;

}
void Server::connection(){
	this->recv_message();
	string cod = "";
	int i = 0;
	string pass, user, new_pass, pass_aux;

	/*
		pass -> Senha que está dentro do arquivo
		pass_aux -> senha enviada pela mensagem
		user -> usuário enviado pela mensagem
		new_pass -> nova senha passada pela mensagem
	*/

	while(this->message_recv[i] != '\n'){
		cod+=this->message_recv[i];
		i++;
	}
	if(cod == "auth"){
		while(this->message_recv[i] != ':') i++;
		i+= 2;
		while(this->message_recv[i] != '\n'){
			user+=this->message_recv[i];
			i++;
		}

		while(this->message_recv[i] != ':') i++;
		i+= 2;
		while(this->message_recv[i] != '\n'){
			pass+=this->message_recv[i];
			i++;
		}
		// pass = decodifica_base64();

		size_t len;
		char *pass_out;
		const char *pass_aux;
		pass_aux = const_cast<const char*>(pass.c_str());
		decodifica_base64(pass_aux, &pass_out, &len);
		pass = pass_out;

		pass = this->hashing(pass);
		this->authenticate(user, pass, false);
	}else if(cod == "changepass"){
		while(this->message_recv[i] != ':') i++;
		i+=2;
		while(this->message_recv[i] != '\n'){
			user+=this->message_recv[i];
			i++;
		}
		while(this->message_recv[i] != ':')	i++;
		i+=2;
		while(this->message_recv[i] != '\n'){
			pass_aux+=this->message_recv[i];
			i++;
		}
		i++;
		while(this->message_recv[i] != ':') i++;
		i+=2;
		while(this->message_recv[i] != '\n'){
			new_pass+=this->message_recv[i];
			i++;
		}
		// pass_aux = decodifica_base64();
		pass = this->pass_archived(user);
		new_pass = this->hashing(new_pass);
		pass_aux = this->hashing(pass_aux);
		if(this->authenticate(user, pass_aux, true)){
			this->write_file(user, pass, new_pass);
			this->message_send.str("");
			this->message_send << "250 Pass changed\n";
			this->send_message();
		}else{
			this->message_send.str("");
			this->message_send << "401 Not authorized\n";
			this->send_message();
		}

	}
	//close(this->sock_client);
}

void Server::run(){
	while(true){
		this->accept_connection();
		this->flag_close = false;
		if(this->sock_client < 0){
			cout << "Erro de conexão" << endl;
			exit(0);
		}
		while(this->sock_client > 0){
			this->connection();
			if(this->flag_close == true){
				close(this->sock_client);
			}
		}
		this->sock_client = 0;
	}
}
int main(){
	Server *servidor = new Server(5555);
	servidor->run();
	return 0;
}
