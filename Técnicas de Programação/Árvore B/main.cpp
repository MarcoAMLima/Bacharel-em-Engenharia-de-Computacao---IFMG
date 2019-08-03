/*
Marco Aurélio Monteiro Lima, 0022933.
Marcus Vinícius Rodrigues Campos, 0022127.
*/
#include <iostream>
#include "header.h"

using namespace std;

int main()
{
    int op;
    do{
        cout << "------------------------MENU------------------------" << endl;
        cout << " opcoes : " << endl;
        cout << " 1- Inserir um valor na arvore." << endl;
        cout << " 2- Remover um valor na  arvore." << endl;
        cout << " 3- Imprimir a pagina da arvore em que a chave esta. " << endl;
        cout << " 4- Buscar um valor na arvore." << endl;
        cout << " 5- Terminar execucao." << endl;
        cin >> op;
        switch (op){
            case 1:
                cout << "Opcao 1 escolhida, inserindo um valor na arvore" << endl;

                break;

            case 2:
                cout << "Opcao 2 escolhida, removendo um valor da arvore" << endl;
                break;

            case 3:
                cout << "Opcao 3 escolhida, imprimindo a pagina da arvore em que a chave esta." << endl;

                break;
            case 4:
                cout << "Opcao 4 escolhida, buscando um valor na arvore" << endl;

            case 5:
                cout << "Finalizando execucao..." << endl;
                break;
            default:
                cout << "Escolha invalida" << endl;
        }
        cout << endl;
    }while(op != 5);
 return 0;
}

