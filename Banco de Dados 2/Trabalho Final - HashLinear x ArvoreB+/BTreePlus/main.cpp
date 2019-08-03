/*
Nome: Marco Aurélio Monteiro Lima, Matricula: 0022933
Nome: Pâmela Evelyn Carvalho, Matricula: 0015669
A implementação abaixo é de uma Arvore B+,
ela utiliza uma biblioteca boost de manipulação de strings que deve ser instalada.
Instalção no linux debian/ubuntu "sudo apt-get install libboost-dev"
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

typedef struct Btree {
  int *key , nkeys,leaf;
  struct record **datas; //vetor que aponta para as informacoes
  struct Btree **childrens, *next;
} Ttree;

typedef struct record {
    int A1,A2,A3,A4,A5,A6,A7,A8,A9,A10;
} Trecord;

Ttree* root(Ttree* a);
Trecord* createData(int A1, int A2, int A3, int A4, int A5, int A6, int A7, int A8, int A9, int A10);

//imprimir a Arvore passando a raiz e o nivel
void PrintTree(Ttree *a, int level){
  if(a){
    int k,i;
    for(k=0; k<=a->nkeys-1; k++){
        PrintTree(a->childrens[i],level+1);
        for(i=0; i<=level; i++){
            cout << " ";
        }
      cout << a->key[i] << endl;
    }
    PrintTree(a->childrens[i],level+1);
  }
}

//Criar arvore passando o level
Ttree *CreateNode(int t){
  Ttree* newNode = (Ttree *) malloc (sizeof(Ttree));
  newNode->nkeys = 0;
  newNode->key = (int *) malloc (sizeof(int)*((t*2)-1));
  newNode->leaf = 1;
  newNode->datas = (Trecord **) malloc (sizeof(Trecord*)*((t*2)-1));
  newNode->childrens = (Ttree **) malloc (sizeof(Ttree*)*t*2);
  newNode->next = (Ttree *) malloc (sizeof(Ttree));
  int i;
  for(i=0; i<(t*2); i++) newNode->childrens[i] = NULL;
  for(i=0; i<((2*t)-1); i++) newNode->childrens[i] = NULL;
  newNode->next = NULL;
  return newNode;
}

//Liberacao da arvore
void freeTree(Ttree *a){
  if(a){
    if(!a->leaf){
      for(int i = 0; i <= a->nkeys; i++){
            a->childrens[i];
      }
    }
    free(a->key);
    free(a->childrens);
    free(a->datas);
    free(a->next);
    free(a);
  }
}

//busca por igualdadde passando a raiz e a chave
Ttree *SearchTree(Ttree *x, int n){
	Ttree *resp = NULL;
	if(!x){//se a raiz estiver vazia
        return resp;
	}
	int i=0;
	if (x->leaf) {
		while ((i < x->nkeys)&&(n > x->key[i])) i++;
		if (n == x->key[i]){
            return x;
		}
	}
	while ((i < x->nkeys)&&(n > x->key[i])) i++;
	if (n == x->key[i]){
        return SearchTree(x->childrens[i+1],n);
	}
	return SearchTree(x->childrens[i],n);
}

Ttree *removeTree(Ttree* tree, int n, int t);

//retirar um registro passando a arvore, a chave, e a ordem
Ttree *retirar(Ttree* tree, int n, int t){
  if(!tree || !SearchTree(tree, n)){//buscar a chave na arvore
	cout << "Chave nao encontrada!!!" << endl;
	return tree;
  }
  return removeTree(tree, n, t);
}

//Aplicar os possiveis casos de remocao passando a arvore, chave, level
Ttree *removeTree(Ttree* tree, int n, int t){
	if(!tree) {
		cout << "Chave não encontrada" << endl;
		return tree;
	}
	int i=0;
	//cout << "removendo..." << n << endl;
	for(i = 0; i<tree->nkeys && tree->key[i] < n; i++);
	if(tree->leaf){ //CASO 1
      		//cout << "caso 1" << endl;
      		int j;
      		for(j=i; j<tree->nkeys-1;j++){
			  tree->key[j] = tree->key[j+1];
			  tree->datas[j] = tree->datas[j+1];
			  tree->datas[j+1] = NULL;
		}
		tree->nkeys--;
		return tree;
	}
	Ttree *y = tree->childrens[i], *z = NULL, *anterior = NULL;
	if (y->nkeys == t-1){
		//Caso 3A
		if((i < tree->nkeys) && (tree->childrens[i+1]->nkeys >=t)){
			//cout << "Caso 3A" << endl;
			z = tree->childrens[i+1];
			if (y->leaf){
				y->key[t-1] = z->key[0];
				y->datas[t-1] = z->datas[0];
				z->datas[0] = NULL;
				tree->key[i] = z->key[1];
				y->nkeys++;
				int k;
				for (k=1; k < z->nkeys; k++){
					z->key[k-1] = z->key[k];
					z->datas[k-1] = z->datas[k];
					z->datas[k] = NULL;
				}
				z->nkeys--;
				tree->childrens[i] = removeTree(tree->childrens[i], n, t);
				return tree;
			}
			y->key[t-1] = tree->key[i];
			y->nkeys++;
			tree->key[i] = z->key[0];     //dar a arv uma chave de z
			int j;
			for(j=0; j < z->nkeys-1; j++)  //ajustar chaves de z
				z->key[j] = z->key[j+1];
			y->childrens[y->nkeys] = z->childrens[0]; //enviar ponteiro menor de z para o novo elemento em y
			for(j=0; j < z->nkeys; j++)       //ajustar filhos de z
				z->childrens[j] = z->childrens[j+1];
			z->nkeys--;
			tree->childrens[i] = removeTree(tree->childrens[i], n, t);
			return tree;
    }
		if((i > 0) && (!z) && (tree->childrens[i-1]->nkeys >=t)){
			//cout << "Aplicando o Caso 3A" << endl;
			z = tree->childrens[i-1];
			if (y->leaf){
				int k;
				y->nkeys++;
				for (k=y->nkeys; k > 0; k--){
					y->key[k] = y->key[k-1];
					y->datas[k] = y->datas[k-1];
					y->datas[k-1] = NULL;
				}
				y->key[0] = z->key[z->nkeys-1];
				y->datas[0] = z->datas[z->nkeys-1];
				z->datas[z->nkeys-1] = NULL;
				tree->key[i] = y->key[0];
				z->nkeys--;
				tree->childrens[i] = removeTree(y, n, t);
				return tree;
			}
			int j;
			for(j = y->nkeys; j>0; j--)               //encaixar lugar da nova chave
				y->key[j] = y->key[j-1];
			for(j = y->nkeys+1; j>0; j--)             //encaixar lugar dos filhos da nova chave
				y->childrens[j] = y->childrens[j-1];
			y->key[0] = tree->key[i-1];              //dar a y a chave i da arv
			y->nkeys++;
			tree->key[i-1] = z->key[z->nkeys-1];   //dar a arv uma chave de z
			y->childrens[0] = z->childrens[z->nkeys];         //enviar ponteiro de z para o novo elemento em y
			z->nkeys--;
			tree->childrens[i] = removeTree(y, n, t);
			return tree;
		}
		//Caso 3B
		if(!z){ //CASO 3B
		  if(i < tree->nkeys && tree->childrens[i+1]->nkeys == t-1){
			//cout << "Aplicando caso 3b" << endl;
			z = tree->childrens[i+1];
			if (y->leaf){
				int k;
				for (k=0; k < z->nkeys; k++){
					y->key[t-1+k] = z->key[k];
					y->datas[t-1+k] = z->datas[k];
				}
				y->nkeys += z->nkeys;
				y->next = z->next;
				for (k=i; k < tree->nkeys; k++){
					tree->key[k] =	tree->key[k+1];
					tree->childrens[k+1] = tree->childrens[k+2];
				}
				tree->nkeys--;
				tree->childrens[i] = removeTree(tree->childrens[i],n,t);
				return tree;
			}
			y->key[t-1] = tree->key[i];     //pegar chave [i] e coloca ao final de filho[i]
			y->nkeys++;
			int j;
			for(j=0; j < t-1; j++){
			  y->key[t+j] = z->key[j];     //passar filho[i+1] para filho[i]
			  y->nkeys++;
			}
			if(!y->leaf){
			  for(j=0; j<t; j++){
				y->childrens[t+j] = z->childrens[j];
			  }
			}
			for(j=i; j < tree->nkeys-1; j++){ //limpar referências de i
			  tree->key[j] = tree->key[j+1];
			  tree->childrens[j+1] = tree->childrens[j+2];
			}
			tree->nkeys--;
			tree = removeTree(tree, n, t);
			return tree;
		  }
		  if((i > 0) && (tree->childrens[i-1]->nkeys == t-1)){
			//cout << "CASO 3B: i igual a nchaves" << endl;
			z = tree->childrens[i-1];
			if (y->leaf){
				//cout << "Nao rola" << endl;
				return tree;
			}
			if(i == tree->nkeys)
			  z->key[t-1] = tree->key[i-1]; //pegar chave[i] e poe ao final de filho[i-1]
			else
			  z->key[t-1] = tree->key[i];   //pegar chave [i] e poe ao final de filho[i-1]
			z->nkeys++;
			int j;
			for(j=0; j < t-1; j++){
			  z->key[t+j] = y->key[j];     //passar filho[i+1] para filho[i]
			  z->nkeys++;
			}
			if(!z->leaf){
			  for(j=0; j<t; j++){
				z->childrens[t+j] = y->childrens[j];
			  }
			}
			tree->nkeys--;
			tree->childrens[i-1] = z;
			tree = removeTree(tree, n, t);
			return tree;
		  }
		}
	}
	tree->childrens[i+1] = removeTree(tree->childrens[i+1], n, t);
	return tree;
}

//divisao em nós cheios,passando no pai,posicao da chave,folha esquerda, ordem
Ttree *SplitChildren(Ttree *x, int i, Ttree* y, int t){
  Ttree *z = CreateNode(t);
  z->nkeys = t-1;
  z->leaf = y->leaf;
  int j;
  if (y->leaf){
	for(j=0;j<t-1;j++){
	  z->key[j] = y->key[j+t];
	  z->datas[j] = y->datas[j+t];
	  y->datas[j+t] = NULL;
    }
	z->next = y->next;
	y->next = z;
  }
  for(j=0;j<t-1;j++) z->key[j] = y->key[j+t];
  if(!y->leaf){
    for(j=0;j<t;j++){
      z->childrens[j] = y->childrens[j+t];
      y->childrens[j+t] = NULL;
    }
  }
  if (y->leaf) {
	y->nkeys -= t-1;
  } else {
	y->nkeys = t-1;
  }
  for(j=x->nkeys; j>=i; j--) x->childrens[j+1]=x->childrens[j];
  x->childrens[i] = z;
  for(j=x->nkeys; j>=i; j--) x->key[j] = x->key[j-1];
  if (y->leaf){
	x->key[i-1] = z->key[0];
  } else {
	x->key[i-1] = y->key[t-1];
  }
  x->nkeys++;
  return x;
}

//Inserir dado em um nó não completo,passando a arvore,chave,ordem,dados
Ttree *InsertIncomplet(Ttree *x, int n, int t, Trecord *dado){
  int i = x->nkeys-1;
  if(x->leaf){
    while((i>=0) && (n<x->key[i])){
      x->key[i+1] = x->key[i];
      x->datas[i+1] = x->datas[i];
      x->datas[i] = NULL;
      i--;
    }
    x->key[i+1] = n;
    x->datas[i+1] = dado;
    x->nkeys++;
    return x;
  }
  while((i>=0) && (n<x->key[i])) i--;
  i++;
  if(x->childrens[i]->nkeys == ((2*t)-1)){
    x = SplitChildren(x, (i+1), x->childrens[i], t);
    if(n>x->key[i]) i++;
  }
  x->childrens[i] = InsertIncomplet(x->childrens[i], n, t, dado);
  return x;
}

 //insecao, passando a arvore,chave,ordem,dados
Ttree *InsertTree(Ttree *a, int n, int t, Trecord *dado){
	if (!a){
        return NULL;
	}
	Ttree *aux = SearchTree(a,n);
	if (aux){
		int i=0;
		while ((i<aux->nkeys) && (n>aux->key[i])) i++;
		aux->datas[i] = dado;
		return a;
	}
	if(a->nkeys == (2*t)-1){
		Ttree *P = CreateNode(t);
		P->nkeys = 0;
		P->leaf = 0;
		P->childrens[0] = a;
		P = SplitChildren(P,1,a,t);
		P = InsertIncomplet(P,n,t,dado);
		return P;
	}
	a = InsertIncomplet(a,n,t,dado);
	return a;
}

 //Aponta para a folha mais a esquerda,nó ancestral do nó folha procurado ou o proprio nó folha, retorna NULL se a arvore for nula, e t caso t seja folha
Ttree *firstLeaf(Ttree* first){
  if (!first){
        return NULL;
  }
  if (first->leaf){
        return first;
  } return first;
  return firstLeaf(first->childrens[0]);
}

//Criar o regisro
Trecord *createData(int B1,int B2,int B3,int B4,int B5,int B6,int B7,int B8,int B9,int B10){
	Trecord *d=(Trecord*)malloc(sizeof(Trecord));
	d->A1 = B1;
	d->A2 = B2;
	d->A3 = B3;
	d->A4 = B4;
	d->A5 = B5;
	d->A6 = B6;
	d->A7 = B7;
	d->A8 = B8;
	d->A9 = B9;
	d->A10 = B10;
	return d;
}

// metodo para coverter strings para inteiro
int toInt(string text){
    int result;
    stringstream convert(text);
    if(!(convert >> result))result = 0;
    return result;
}

void PrintRecord(Ttree* b, int a1){
    Ttree *aux = (Ttree*) malloc (sizeof(Ttree));
    aux = SearchTree(b,a1);
    if (!aux){
        cout << "Arquivo não existe" << endl;
    	return;
    }
    int i=0;
    while ((i < aux->nkeys) && (a1 > aux->key[i])){
        i++;
    }
    cout << aux->datas[i]->A1 << ", " << aux->datas[i]->A2 << ", " << aux->datas[i]->A3 << ", " << aux->datas[i]->A4 << ", " << aux->datas[i]->A5 << ", ";
    cout << aux->datas[i]->A6 << ", " << aux->datas[i]->A7 << ", " << aux->datas[i]->A8 << ", " << aux->datas[i]->A9 << ", " << aux->datas[i]->A10 << ", ";
}

int main () {
    int t = -1;
    ifstream arctg;//objeto de leitura de arquivos
    string panelinha;//string auxiliar
    vector<string> separador;//vetor de strings utilizado para alocar a string apos a explosão
    Ttree *auxTree = NULL;
    int A[9],op=1,aux=0,aux2=0;
    Ttree *g = NULL;

    cout << "============ Arvore B+ ============" << endl;
    cout << "Informe a ordem da Arvore B+ :";
    cin >> t;

    ///Criação de uma nova arvore
    freeTree(auxTree);
    auxTree = CreateNode(t);

    //Função para ler o registros e inserir ou deletar de acordo com o primeiro caractere
    arctg.open("teste.txt");//Abrindo arquivo
    cout << "=== Lendo arquivo ===" << endl;
    while(!arctg.eof()){//le linha por linha ate achar a marca fim de arquivo
    cout << ".";
        getline(arctg,panelinha);
        if(panelinha == "OP,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10"){//ignorar o cabecalho
            continue;
        }else{
            //lido a linha chama o split para esplodir a string separada pelo delimitador ','
            split(separador,panelinha,is_any_of(","));
            //inserção ou remoção dos registros
            if(separador[0] == "+"){ // se o operador for '+' será feita a operação de inserção
                for(int j=0;j<9;j++){
                        A[j] = toInt(separador[j+1]);//como separador é um vetor de strings deve se fazer a conversão para inteiros antes de inserir para o hash
                }
                Trecord* newRecord=(Trecord*)calloc(1,sizeof(Trecord));//Alocar um novo nó
                newRecord->A1 = A[0];
                newRecord->A2 = A[1];
                newRecord->A3 = A[2];
                newRecord->A4 = A[3];
                newRecord->A5 = A[4];
                newRecord->A6 = A[5];
                newRecord->A7 = A[6];
                newRecord->A8 = A[7];
                newRecord->A9 = A[8];
                newRecord->A10 = A[9];
                auxTree = InsertTree(auxTree,A[0],t,newRecord);
            }else{ // se o operador for '-' será feita a operação de exclusão
                if(separador[0] == "-"){
                    A[0] = toInt(separador[1]);
                    Ttree *g = SearchTree(auxTree,A[0]);
                    if(g!=NULL){
                        auxTree = retirar(auxTree,A[0],t);
                    }
                    continue;
                }
            }
        }
    }
    cout << endl;
    cout << "Arquivo lido!" << endl;
    arctg.close();///fechar o arquivo

    while(op!=6){
        cout << endl;
        cout << "================== MENU ARVORE B+ ====================" <<endl;
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
                g = SearchTree(auxTree,aux);
                if(g!=NULL){
                   auxTree = retirar(auxTree,aux,t);
                }else{
                    cout << "Indice nao esta na Arvore!!!" << endl;
                }
                break;
            case 2:
                cout << "- Busca por igualdade -" << endl;
                cout << "Digite o indice do registro 'A1': ";
                cin >> aux;
                PrintRecord(auxTree,aux);
                break;
            case 3:
                cout << "- Busca por intervalo -" << endl;
                cout << "Digite o intervalo menor: ";
                cin >> aux;
                cout << "Digite o intervalo maior: ";
                cin >> aux2;

                break;
            case 4:
                cout << "- Imprimindo registros -" << endl;
                PrintTree(auxTree,0);
                break;
            case 5:
                {
                cout << "- Insercao de um novo registro -" << endl;
                for(int i=0;i<=9;i++){
                    cout << "Digite "<< i+1 << "º valor: ";
                    cin >> A[i];
                }
                Trecord* newRecordi=(Trecord*)calloc(1,sizeof(Trecord));//Alocar um novo nó
                newRecordi->A1 = A[0];
                newRecordi->A2 = A[1];
                newRecordi->A3 = A[2];
                newRecordi->A4 = A[3];
                newRecordi->A5 = A[4];
                newRecordi->A6 = A[5];
                newRecordi->A7 = A[6];
                newRecordi->A8 = A[7];
                newRecordi->A9 = A[8];
                newRecordi->A10 = A[9];
                auxTree = InsertTree(auxTree,A[0],t,newRecordi);
                break;
                }
             case 6:
                cout << "Fim!" << endl;
                return 0;
                break;
            default:
                cout << "Opcao invalida tente novamente." << endl;
        }
    }
}
