/*  INSTITUTO FEDERAL DE MINAS GERAIS - Campus Bambuí
    Trabalho Final da Disciplina de Técnicas de Programação - 2017

    Eduardo Augusto de Oliveira Borges - RA:0015501
    Marco Aurélio Monteiro Lima        - RA:0022933
    Marcus Vinícius Rodrigues Campos   - RA:0022127
*/

#include <iostream>
#include <list>
#include "filegraph.h"
#include <iostream>
#include "Graph.h"

using namespace std;

/*Método que inicia o programa, adicionando todas as informações
  lidas do arquivo num grafo
*/
void Start_Program(char *argv){
    cout<<"============================================================\n";
    cout<<"Kruskal Algorithm\n\n";
    cout<<"Minimum Spanning Trees\n\n";

    list<int> listat; //Cria lista para armazenar valores lidos
    listat = reading(argv);//Atribui valores lidos a lista

    int origem,destino,weight; //Variaveis para adicionar o grafo
    list<int>::iterator it; //Chama um iterador para percorrer a lista
    it = listat.begin();
    Graph graph(*it); it++; //Lê a primeira posição e instância um novo grafo

    for (; it!=listat.end(); it++) {
        origem = *it;it++; //Posição da lista representa a origem
        weight = *it;it++; //Posição da lista representa o peso
        destino = *it;     //Posição da lista representa o destino
        graph.add_edge(origem, destino, weight); //Adiciona a Aresta passando por parametro
                                                 //Origem Destino e peso
    }
    graph.MST_Kruskal(graph); //Inicia o algoritmo de Kruskal
    cout<<"\n============================================================\n"<<endl;
}

int main(int argc, char *argv[]) {
    //argv[1] em Program
    Start_Program("grafo.txt");//Inicia o programa, pegando o argumento da main
    return 0;
}
