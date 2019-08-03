#ifndef HASHI_H_INCLUDED
#define HASHI_H_INCLUDED
#include <iostream>
#include <atomic>
#include <cstdlib>
using namespace std;

class Hashi{
	public:
		atomic_int indice;
		atomic_bool flag_bloq;

		Hashi(){
			this->flag_bloq.store(false, memory_order_acquire);
		}
		~Hashi(){}
		void set_indice(int indice);
		void set_flag(bool flag);
		int get_indice();
		bool get_bloqueado();
};


void Hashi::set_indice(int indice){
	this->indice.store(indice, memory_order_acquire);
}

void Hashi::set_flag(bool flag){
	this->flag_bloq.store(flag, memory_order_acquire);
}

int Hashi::get_indice(){
	int x;
	x = this->indice.load(memory_order_acquire);
	return x;
}

bool Hashi::get_bloqueado(){
	bool f;
	f = this->flag_bloq.load(memory_order_acquire);
	return f;
}


#endif // HASHI_H_INCLUDED
