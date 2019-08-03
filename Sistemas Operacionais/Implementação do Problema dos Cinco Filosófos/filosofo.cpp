#include <iostream>
#include <cstdlib>
#include <ctime>
#include "filosofo.h"
#include "hashi.h"
#include <atomic>
#include <ctime>

using namespace std;

void Filosofo::set_hashi1(int h1){
	this->hashi1 = h1;
}

void Filosofo::set_hashi2(int h2){
	this->hashi2 = h2;
}

void Filosofo::set_bloqueio(bool bloqueio){
	this->flag_bloqueado.store(bloqueio, std::memory_order_seq_cst);
}

int Filosofo::pensar(Hashi *h[]){
	srand(time(NULL));
	if(this->libera_hashi(h)){
		this->tempo_de_pensar = int(rand() % 10) + 1;
		this->set_bloqueio(true);
		return this->tempo_de_pensar;
	}
	return -1;
}

int Filosofo::comer(Hashi *h[]){
	srand(time(NULL));
	if(this->capturar_h1(h) == true && this->capturar_h2(h) == true){
		this->tempo_de_comer = int(rand() % 5) + 1;
		this->set_bloqueio(true);
		return this->tempo_de_comer;
	}
	return -1; // pensar?
}


bool Filosofo::capturar_h1(Hashi *h[]){
	if(h[this->hashi1]->get_bloqueado() == false){
		h[this->hashi1]->set_flag(true);
		return true;
	}
	return false;
}


bool Filosofo::capturar_h2(Hashi *h[]){
	if(h[this->hashi2]->get_bloqueado() == false){
		h[this->hashi2]->set_flag(true);
		return true;
	}
	return false;
}


bool Filosofo::bloqueado(){
	bool f = this->flag_bloqueado.load(memory_order_seq_cst);
	return f;
}

bool Filosofo::libera_hashi(Hashi *h[]){
	h[this->hashi1]->set_flag(false);
	h[this->hashi2]->set_flag(false);
	return true;
}




