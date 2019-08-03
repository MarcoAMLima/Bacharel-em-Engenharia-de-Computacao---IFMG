#ifndef FILOSOFO_H_INCLUDED
#define FILOSOFO_H_INCLUDED
#include <iostream>
#include <cstdlib>
#include "hashi.h"
#include <atomic>


/*
    Resolve a starvation ? Como resolvo a starvation ?
    Os filosofos estão sincronizados ?

*/


class Filosofo{
	public:
		int hashi1, hashi2;
		int meu_indice;
		atomic_bool flag_bloqueado;
		int tempo_de_pensar;
		int tempo_de_comer;

		Filosofo(){
			this->hashi1 = -1;
			this->hashi2 = -1;
		}

		Filosofo(int h1, int h2){
			this->set_hashi1(h1);
			this->set_hashi2(h2);
		}

		void set_hashi1(int h1);
		void set_hashi2(int h2);
		void set_bloqueio(bool bloqueio);
		int pensar(Hashi *h[]);
		int comer(Hashi *h[]);
		bool capturar_h1(Hashi *h[]);
		bool capturar_h2(Hashi *h[]);
		bool bloqueado();
		bool libera_hashi(Hashi *h[]);

};


#endif // FILOSOFO_H_INCLUDED
