#include <clocale>
#include "biblio.h"

//Marco Aur�lio Monteiro Lima, Engenharia de Computa��o 3.
int main(){
    setlocale(LC_ALL, "portuguese");
    TPilha p;
    TArvore a;
    IniciarArvore(a);
    CriaPilhaVazia(p);
    MenuPilha(p,a);
}
