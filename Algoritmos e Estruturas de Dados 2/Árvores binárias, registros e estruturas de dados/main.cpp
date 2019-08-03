#include <clocale>
#include "biblio.h"

//Marco Aurélio Monteiro Lima, Engenharia de Computação 3.
int main(){
    setlocale(LC_ALL, "portuguese");
    TPilha p;
    TArvore a;
    IniciarArvore(a);
    CriaPilhaVazia(p);
    MenuPilha(p,a);
}
