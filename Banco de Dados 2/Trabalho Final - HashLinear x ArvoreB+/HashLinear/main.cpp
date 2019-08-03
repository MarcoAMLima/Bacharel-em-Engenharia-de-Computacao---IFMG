/*
Nome: Marco Aurélio Monteiro Lima, Matricula: 0022933
Nome: Pâmela Evelyn Carvalho, Matricula: 0015669
A implementação abaixo é de um hash linear, não permite a inserção de indices repetidos,
ela utiliza uma biblioteca boost de manipulação de strings que deve ser instalada.
Instalção no linux debian/ubuntu "sudo apt-get install libboost-dev"

*/

#include <iostream>///Utilização de cout e endl
#include <cstdlib>
#include <string>///Utilização de strings
#include <cstdio>
#include <sstream>///biblioteca que permite a conversão de strings
#include <fstream>///Manipulação de arquivos
#include <vector>///Utilização de vetores dinâmicos
#include <boost/algorithm/string.hpp>///biblioteca split para explosão se strings

using namespace std;
using namespace boost;

///variavel global que define o número máximo de registros da tabela hash
int tamanho=0;

///Classse que defini os campos dos registros
class Hash_{
    public:
        int A1,A2,A3,A4,A5,A6,A7,A8,A9,A10;
        // construtor
        Hash_(int A1,int A2,int A3,int A4,int A5,int A6,int A7,int A8,int A9,int A10){
            this->A1 = A1;
            this->A2 = A2;
            this->A3 = A3;
            this->A4 = A4;
            this->A5 = A5;
            this->A6 = A6;
            this->A7 = A7;
            this->A8 = A8;
            this->A9 = A9;
            this->A10 = A10;
        }
};

/// classe que faz as operações com a tabela aonde os registros são inseridos
class Tabela{
    private:
        Hash_ **tabelinha;
    public:

        Tabela(){//consrutor
            tabelinha = new Hash_ * [tamanho];
            for(int i=0;i<tamanho;i++){//zerando a lista
                tabelinha[i] = NULL;
            }
        }

        int Hash_Funcao(int A1){//função do hash linear retorna o resto da divisao do indice pelo tamanho da tabela.
            return A1 % tamanho;
        }

        void Inserir(int A1,int A2,int A3,int A4,int A5,int A6,int A7,int A8,int A9,int A10){//insere os indices com seus dados
            int hash = Hash_Funcao(A1);
            while(tabelinha[hash] != NULL && tabelinha[hash]->A1 != A1){
                hash = Hash_Funcao(hash +1);
            }
            if (tabelinha[hash] != NULL){//Se houver algum indice na posição exclua
                delete tabelinha[hash];
            }
            tabelinha[hash] = new Hash_(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10);
        }

        int BuscaPorIgualdade(int A1){//Buscar um registro por igualdade de indice
            int hash = Hash_Funcao(A1);
            while(tabelinha[hash] != NULL && tabelinha[hash]->A1 != A1){
                hash = Hash_Funcao(hash +1);
            }
            if (tabelinha[hash] == NULL){//Se não houver indices na tabela
                return -1;
            }else{
                    cout << "====================================================" << endl;
                    cout << tabelinha[hash]->A1 <<", ";
                    cout << tabelinha[hash]->A2 <<", ";
                    cout << tabelinha[hash]->A3 <<", ";
                    cout << tabelinha[hash]->A4 <<", ";
                    cout << tabelinha[hash]->A5 <<", ";
                    cout << tabelinha[hash]->A6 <<", ";
                    cout << tabelinha[hash]->A7 <<", ";
                    cout << tabelinha[hash]->A8 <<", ";
                    cout << tabelinha[hash]->A9 <<", ";
                    cout << tabelinha[hash]->A10 <<". " << endl;
            }
        }

        int ImprimirRegistros(){//Fução que mostra todos os registros que estão no hash
            int hash = Hash_Funcao(1);//começar no primeiro registro
            if (tabelinha[hash] == NULL){//se o hash estiver vazio
                return -1;
            }else{
                while(tabelinha[hash] != NULL){//enquanto houver indices na tabelinha
                    cout << "====================================================" << endl;
                    cout << tabelinha[hash]->A1 <<", ";
                    cout << tabelinha[hash]->A2 <<", ";
                    cout << tabelinha[hash]->A3 <<", ";
                    cout << tabelinha[hash]->A4 <<", ";
                    cout << tabelinha[hash]->A5 <<", ";
                    cout << tabelinha[hash]->A6 <<", ";
                    cout << tabelinha[hash]->A7 <<", ";
                    cout << tabelinha[hash]->A8 <<", ";
                    cout << tabelinha[hash]->A9 <<", ";
                    cout << tabelinha[hash]->A10 << endl;
                    hash = Hash_Funcao(hash+1);
                }
            }
        }

        int BuscaPorIntervalo(int i,int j){//Buscar por intervalos de elementos. ex de 2 a 8
            int hash = Hash_Funcao(i);
            while(tabelinha[hash] != NULL && tabelinha[hash]->A1 < i){//enquanto a tabela na posição for diferente de null e a tabela na posição
                hash = Hash_Funcao(hash+1);
            }if (tabelinha[hash] == NULL){//se não houver elementos
                return -1;
            }else{
                while(tabelinha[hash] != NULL && tabelinha[hash]->A1 <= j){
                    cout << "====================================================" << endl;
                    cout << tabelinha[hash]->A1 << ", ";
                    cout << tabelinha[hash]->A2 << ", ";
                    cout << tabelinha[hash]->A3 << ", ";
                    cout << tabelinha[hash]->A4 << ", ";
                    cout << tabelinha[hash]->A5 << ", ";
                    cout << tabelinha[hash]->A6 << ", ";
                    cout << tabelinha[hash]->A7 << ", ";
                    cout << tabelinha[hash]->A8 << ", ";
                    cout << tabelinha[hash]->A9 << ", ";
                    cout << tabelinha[hash]->A10 << ". "<< endl;
                    hash = Hash_Funcao(hash+1);
                }
            }
        }

        void Deletar(int A1){//Deletar um registro apenas se existir
            int hash = Hash_Funcao(A1);
            while(tabelinha[hash] != NULL){
                if (tabelinha[hash]->A1 == A1){
                    break;//se achar o indice sai do laço
                }
                hash = Hash_Funcao(hash +1);
            }if (tabelinha[hash] == NULL){
                cout << "Indice nao encontrado!" << endl;
                return;
            }else{
                delete tabelinha[hash];//deleta o registro naquela posição do hash
            }
            cout << "Registro excluido!" << endl;
        }

        void Excluir(int A1){//exclui um elemento se existir, se não, nada acontece
            int hash = Hash_Funcao(A1);
            while(tabelinha[hash] != NULL){
                if (tabelinha[hash]->A1 == A1){
                    break;//se achar o indice sai do laço
                }
                hash = Hash_Funcao(hash +1);
            }
            delete tabelinha[hash];//deleta o registro naquela posição do hash
        }

        ~Tabela(){//destrutor
            for (int k=0;k<tamanho;k++){
                if (tabelinha[k] != NULL)
                    delete tabelinha[k];
                delete[] tabelinha;
            }
        }
};

int toInt(string text){/// metodo para coverter strings para inteiro
    int result;
    stringstream convert(text);
    if(!(convert >> result))result = 0;
    return result;
}

int main(){
    cout << "============ Tabela hash Linear ============" << endl;
    int A[9],op=0,aux,aux2;
    cout << "Entre com o tamanho da tabela hash: ";//tamanho máximo de registros
    cin >> tamanho;
    Tabela hash;//declaração de um objeto do tipo da classe tabela
    ifstream arctg;//objeto de leitura de arquivos
    string panelinha;//string auxiliar
    vector<string> separador;//vetor de strings utilizado para alocar a string apos a explosão

    ///Função para ler o registros e inserir ou deletar de acordo com o primeiro caractere
    arctg.open("output.txt");///Abrindo arquivo
    cout << "=== Lendo arquivo ===" << endl;
    while(!arctg.eof()){///le linha por linha ate achar a marca fim de arquivo
    cout << ".";
        getline(arctg,panelinha);
        if(panelinha == "OP,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10"){//ignorar o cabecalho
            continue;
        }else{
            ///lido a linha chama o split para esplodir a string separada pelo delimitador ','
            split(separador,panelinha,is_any_of(","));
            ///inserção ou remoção dos registros
            if(separador[0] == "+"){ /// se o operador for '+' será feita a operação de inserção
                for(int j=0;j<9;j++){
                        A[j] = toInt(separador[j+1]);///como separador é um vetor de strings deve se fazer a conversão para inteiros antes de inserir para o hash
                }
                hash.Inserir(A[0],A[1],A[2],A[3],A[4],A[5],A[6],A[7],A[8],A[9]);
            }else{ /// se o operador for '-' será feita a operação de exclusão
                if(separador[0] == "-"){
                    A[0] = toInt(separador[1]);
                    hash.Excluir(A[0]);
                }
            }
        }
    }
    cout << endl;
    cout << "Arquivo lido!" << endl;
    arctg.close();///fechar o arquivo

    ///menu de posiveis operações que podem ser feitas no hash
    while(op!=6){
        cout << endl;
        cout << "================== MENU HASH LINEAR ====================" <<endl;
        cout << "1. Deletar um registro. " << endl;
        cout << "2. Buscar um registro por igualdade. " << endl;
        cout << "3. Buscar registros por intervalo. " << endl;
        cout << "4. Imprimir registros." << endl;
        cout << "5. Inserir um novo registro." << endl;
        cout << "6. Sair. " << endl;
        cin >> op;
        switch(op){
            case 1:
                cout << "- Deletar registro -" << endl;
                cout << "Digite o indice do registro 'A1': ";
                cin >> aux;
                if(hash.BuscaPorIgualdade(aux)==-1){///Pesquisar se o indice existe para ser deletado
                    cout << "Item: " << aux << " Nao existe..." << endl;
                    continue;
                }else{//se existe deleta
                    hash.Deletar(aux);
                    cout << "Registro " << aux << " deletado."<< endl;
                }
                break;
            case 2:
                cout << "- Busca por igualdade -" << endl;
                cout << "Digite o indice do registro 'A1': ";
                cin >> aux;
                if(hash.BuscaPorIgualdade(aux)==-1){///Pesquisar se o indice existe
                    cout << "Item: " << aux << " nao existe..." << endl;
                    continue;
                }
                break;
            case 3:
                cout << "- Busca por intervalo -" << endl;
                cout << "Digite o intervalo menor: ";
                cin >> aux;
                cout << "Digite o intervalo maior: ";
                cin >> aux2;
                hash.BuscaPorIntervalo(aux,aux2);
                break;
            case 4:
                cout << "- Imprimindo registros -" << endl;
                hash.ImprimirRegistros();
                break;
            case 5:
                cout << "- Insercao de um novo registro -" << endl;
                for(int i=0;i<=9;i++){
                    cout << "Digite "<< i+1 << "º valor: ";
                    cin >> A[i];
                }
                hash.Inserir(A[0],A[1],A[2],A[3],A[4],A[5],A[6],A[7],A[8],A[9]);
                break;
             case 6:
                cout << "Fim!" << endl;
                break;
            default:
                cout << "Opcao invalida tente novamente." << endl;
        }
    }
    return 0;
}
