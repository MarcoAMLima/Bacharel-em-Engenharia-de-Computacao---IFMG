#ifndef JANTAR_H_INCLUDED
#define JANTAR_H_INCLUDED

#include <cstdlib>
#include <ctime>

class Jantar{
    public:
        Hashi *hashis[5];
        Filosofo *filosofos[5];

        Jantar(){
            this->instancia_dados();
        }
        void instancia_dados();
        void jantar();

};

void Jantar::instancia_dados(){
	for (int i = 0; i < 5; i++){
		this->hashis[i] = new Hashi();
		this->hashis[i]->set_indice(i);
		this->filosofos[i] = new Filosofo();
		this->filosofos[i]->meu_indice = i;
		if(i == 0){
			this->filosofos[0]->hashi2 = 4;
			this->filosofos[0]->hashi1 = 0;
		}else{
			this->filosofos[i]->hashi2 = (i-1);
			this->filosofos[i]->hashi1 = i;
		}
	}
}


void Jantar::jantar(){
    int tempo_c, tempo_p;
    srand(time(NULL));
    int aux;
    aux = rand()%5;
    while(1){
        if(this->filosofos[aux]->bloqueado() == false){ //nao esta bloqueado
            tempo_c = this->filosofos[aux]->comer(this->hashis);
            if(tempo_c != -1){
                cout << "\nFilosofo " << this->filosofos[aux]->meu_indice << " comendo por " << tempo_c << " segundos" << endl;
                this_thread::sleep_for(chrono::seconds(tempo_c));
                this->filosofos[aux]->set_bloqueio(false);
                aux = rand() % 5;
            }else{
                tempo_p = this->filosofos[aux]->pensar(this->hashis);
                cout << "\nFilosofo " << this->filosofos[aux]->meu_indice << " pensando por " << tempo_p << "  segundos" << endl;
                this_thread::sleep_for(chrono::seconds(tempo_p));
                this->filosofos[aux]->set_bloqueio(false);
                aux = rand() % 5;
            }
        }
    }

}


#endif // JANTAR_H_INCLUDED
