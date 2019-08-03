#include <iostream>
#include <fstream>

//Marco Aurélio Monteiro Lima, Engenharia de Computação 3.

using namespace std;

//qta = Quantidade de temporadas assistidas
//uta = Temporada que está assistindo no momento
//uea = Último episodio assistido
//cod = codigo de cadastro da serie
struct TSerie{
    string nome;
    int qta,uta,uea,cod;
};

struct TCelula{
    TSerie serie;
    TCelula *proximo;
};

struct TPilha{
    TCelula *fundo;
    TCelula *topo;
    int cont;
};

struct TNoh{
   TSerie serie;
   TNoh *esq,*dir;
};

struct TArvore{
    TNoh *raiz;
    int contador;
};

//inicializa uma árvore vazia
void IniciarArvore(TArvore &a){
    a.raiz = NULL;
    a.contador = 0;
}

//cria uma pilha vazia
void CriaPilhaVazia(TPilha &Pilha){
    Pilha.topo = new TCelula;
    Pilha.fundo = Pilha.topo;
    Pilha.topo->proximo = NULL;
    Pilha.cont = 0;
}

//insere um registro na árvore
    void inserirArvore(TSerie s, TNoh *&n, TArvore &a){
        if (n == NULL){
                n = new TNoh;
                n->serie = s;
                n->esq = NULL;
                n->dir = NULL;
            if (a.raiz == NULL){
                a.raiz = n;
            };
            a.contador++;
        }else{
            if (s.cod < n->serie.cod){
                inserirArvore(s,n->esq,a);
            }else{
                if (s.cod > n->serie.cod){
                    inserirArvore(s,n->dir,a);
                }else{
                    cout << "Código de cadastro já existe na árvore." << endl;
                    cout << "O último registro não foi cadastrado." << endl;
                    cout << endl;
                }
            }
        }
    }

//verifica se a pilha está vazia sem registro
bool PilhaEVazia(TPilha Pilha){
    return Pilha.topo==Pilha.fundo;
}

//verifica se a arvore está vazia sem registro
bool ArvoreEVazia(TArvore a){
    return a.raiz == NULL;
}

//retorna o ultimo registro empilhado
void MostrarTopo(TPilha Pilha){
    TCelula *aux;
    aux = Pilha.topo->proximo;
    if(PilhaEVazia(Pilha)){
        cout << "Pilha esta vazia" << endl;
    }else{
            cout << "-------------------------------------------------------" << endl;
            cout << "Codigo de cadastro da serie: " << aux->serie.cod << endl;
            cout << "Nome da serie: " << aux->serie.nome << endl;
            cout << "Temporadas completas: " << aux->serie.qta << endl;
            cout << "Assistindo a: " << aux->serie.uta << "º temporada, episodio: " << aux->serie.uea << endl;
    }
}

//empilha um registro na pilha
void empilharSeries(TPilha &Pilha, TSerie serie){
    TCelula *aux = new TCelula;
    Pilha.topo->serie = serie;
    aux->proximo = Pilha.topo;
    Pilha.topo = aux;
    Pilha.cont++;
}

//esse procedimento pega o registro do topo e guarda
TSerie DesempilhaEPega(TPilha &Pilha){
    TCelula *aux;
    TSerie serie;
    if (PilhaEVazia(Pilha)){
        cout << "Pilha Vazia!!!" << endl;
    }else{
        aux = Pilha.topo;
        serie = aux->proximo->serie;
        Pilha.topo = aux->proximo;
        delete aux;
        Pilha.cont--;
    }
    return serie;
}

//verifica se o código de cadastrado é igual ao de algum registro já cadastrado
bool VerificaIfEIgual(int cod,TPilha p){
    TCelula *f;
    f = p.topo->proximo;
    while(f != NULL){
        if(f->serie.cod == cod){
            cout << "Código já cadastrado!" << endl;
            return true;
        }
        else{
            f = f->proximo;
        }
        return false;
    }
}

//essa função coleta os dados de um registro para ser empilhado
void CadastroDeSeries(TPilha &Pilha){
    TSerie serie;
    string resposta;
        do{
            cout << "-------------------------------------------------------" << endl;
            cout << "================= Cadastrando Séries ==================" << endl;
            do{
                cout << "Digite um código de cadastro da série: ";
                cin >> serie.cod;
            }while(VerificaIfEIgual(serie.cod,Pilha));
            cout << "Digite o nome da série(sem espaços use traços para separar): ";
            cin >> serie.nome;
            cout << "Digite o número de temporadas completas assistidas: ";
            cin >> serie.qta;
            cout << "Digite o número da temporada que esta assistindo: ";
            cin >> serie.uta;
            cout << "Digite o número do último episodio assistido: ";
            cin >> serie.uea;
            empilharSeries(Pilha, serie);
            cout << "Deseja cadastrar mais uma série? S/N: ";
            cin >> resposta;
    }while((resposta == "S") || (resposta == "s"));
}

//essa função busca um registro na árvore através do código de cadastro
void PesquisarSerie(int i, TNoh *&n, TArvore a){
    if (n == NULL){
        cout << "Serie não cadastrada!" << endl;
    }else{
        if( i < n->serie.cod){
            PesquisarSerie(i,n->esq,a);
        }else{
            if(i > n->serie.cod){
                PesquisarSerie(i,n->dir,a);
            }else{
                cout << "---------------    Serie encontrada    ----------------" << endl;
                cout << "-------------------------------------------------------" << endl;
                cout << "Codigo de cadastro da serie: " << n->serie.cod << endl;
                cout << "Nome da serie: " << n->serie.nome << endl;
                cout << "Temporadas completas: " << n->serie.qta << endl;
                cout << "Assistindo a: " << n->serie.uta << "º temporada, episodio: " << n->serie.uea << endl;
            }
        }
    }
}

//Essa função exibi os registros empilhados
void MostrarPilha(TPilha Pilha){
    TCelula *aux;
    aux = Pilha.topo->proximo;
    if (PilhaEVazia(Pilha)){
        cout << "Pilha Vazia" << endl;
    }else{
        while ( aux != NULL){
            cout << "-------------------------------------------------------" << endl;
            cout << "Codigo de cadastro da serie: " << aux->serie.cod << endl;
            cout << "Nome da serie: " << aux->serie.nome << endl;
            cout << "Temporadas completas: " << aux->serie.qta << endl;
            cout << "Assistindo a: " << aux->serie.uta << "º temporada, episodio: " << aux->serie.uea << endl;
          aux = aux->proximo;
        }
    }
}

//essa função desempilha o último registro empilhado e o deleta
void Desempilhar(TPilha &Pilha){
    TCelula *aux;
    if (PilhaEVazia(Pilha)){
        cout << "Pilha Vazia!!!" << endl;
    }else{
        aux = Pilha.topo;
        Pilha.topo = aux->proximo;
        delete aux;
        Pilha.cont--;
    }
}

//Essa função reorganiza a árvore depois que um registro é retirado
void pegarAnteriorArvore(TNoh *q, TNoh *&r){
    if (r->dir != NULL){
        pegarAnteriorArvore(q, r->dir);
    }else{
        q->serie = r->serie;
        q = r;
        r = r->esq;
        delete q;
    }
}

//essa função faz uma busca nos registros através do código de cadastro e o retira da árvore
void retirar(int i, TNoh *&p){
TNoh *aux;
    if (p == NULL){
        cout << "Registro não encontrado" << endl;
    }else{
        if ( i < p->serie.cod){
            retirar(i, *&p->esq);
        }else{
            if (i > p->serie.cod){
                retirar(i, *&p->dir);
            }else{
                if (p->dir == NULL){
                    aux = p;
                    p = p->esq;
                    delete aux;
                    cout << "Serie Apagada!" << endl;
                }else{
                    if (p->esq != NULL){
                        pegarAnteriorArvore(p, p->esq);
                    }else{
                        aux = p;
                        p = p->dir;
                        delete aux;
                        cout << "Serie Apagada!" << endl;
                    }
                }
            }
        }
    }
}

//Essa função transfere os registros de uma pilha para uma árvore
void TransferirPilhaParaArvore (TPilha &p, TArvore &a){
     TSerie s;
     TCelula *aux;
     aux = p.topo->proximo;
     IniciarArvore(a);
    if (PilhaEVazia(p)){
        cout << "Pilha Vazia!" << endl;
    }else{
        while (aux != NULL){
            s = DesempilhaEPega(p);
            aux = aux->proximo;
            inserirArvore(s,a.raiz,a);
        }
    }
}

//Essa função percorre e imprimi a árvore  na sequência IN ORDEM respeitando o codigo de registro da série
void PercorrerInOrdem(TNoh *&n){
    if (n != NULL){
        PercorrerInOrdem(n->esq);
        cout << "-------------------------------------------------------" << endl;
        cout << "Código de cadastro da série: " << n->serie.cod << endl;
        cout << "Nome da série: " << n->serie.nome << endl;
        cout << "Temporadas completas: " << n->serie.qta << endl;
        cout << "Assistindo a: " << n->serie.uta << "º temporada, episódio: " << n->serie.uea << endl;
        PercorrerInOrdem(n->dir);
    }
}

//Essa função percorre e imprimi a árvore  na sequência PRE ORDEM respeitando o codigo de registro da série
void PercorrerPreOrdem(TNoh *&n){
    if (n != NULL){
        cout << "-------------------------------------------------------" << endl;
        cout << "Código de cadastro da série: " << n->serie.cod << endl;
        cout << "Nome da série: " << n->serie.nome << endl;
        cout << "Temporadas completas: " << n->serie.qta << endl;
        cout << "Assistindo a: " << n->serie.uta << "º temporada, episódio: " << n->serie.uea << endl;
       PercorrerPreOrdem(n->esq);
       PercorrerPreOrdem(n->dir);
    }
}

//Essa função percorre e imprimi a árvore  na sequência POS ORDEM respeitando o codigo de registro da série
void PercorrerPosOrdem(TNoh *&n){
    if (n != NULL){
       PercorrerPosOrdem(n->esq);
       PercorrerPosOrdem(n->dir);
        cout << "-------------------------------------------------------" << endl;
        cout << "Código de cadastro da série: " << n->serie.cod << endl;
        cout << "Nome da série: " << n->serie.nome << endl;
        cout << "Temporadas completas: " << n->serie.qta << endl;
        cout << "Assistindo a: " << n->serie.uta << "º temporada, episódio: " << n->serie.uea << endl;
    }
}

//A função abaixo chama os 3 percorrer acima e imprimi a árvore
void MostrarArvore(TArvore a){
    cout << "---------------     Mostrando árvore    ---------------" << endl;
    cout << endl;
    cout << "-------------------------------------------------------" << endl;
    cout << "---------------         IN Ordem        ---------------" << endl;
    PercorrerInOrdem(a.raiz);
    cout << "-------------------------------------------------------" << endl;
    cout << "---------------        Pré Ordem        ---------------" << endl;
    PercorrerPreOrdem(a.raiz);
    cout << "-------------------------------------------------------" << endl;
    cout << "---------------        Pós Ordem        ---------------" << endl;
    PercorrerPosOrdem(a.raiz);
    cout << "-------------------------------------------------------" << endl;
}

//Essa função coleta dados de uma nova série para ser inserida na árvore
void CadastrarSeriesArvore(TArvore &a){
    TSerie serie;
    string resposta;
        do{
            cout << "-------------------------------------------------------" << endl;
            cout << "================= Cadastrando Séries ==================" << endl;
            cout << "Digite um código: ";
            cin >> serie.cod;
            cout << "Digite o nome da série(sem espaços use traços para separar): ";
            cin >> serie.nome;
            cout << "Digite o número de temporadas completas assistidas: ";
            cin >> serie.qta;
            cout << "Digite o número da temporada que esta assistindo: ";
            cin >> serie.uta;
            cout << "Digite o número do ultimo episódio assistido: ";
            cin >> serie.uea;
            inserirArvore(serie,a.raiz,a);
            cout << "Deseja cadastrar mais uma série? S/N: ";
            cin >> resposta;
    }while((resposta == "S") || (resposta == "s"));
}

void PercorrerAndEmpilhar(TNoh *&n,TSerie serie,TPilha &Pilha){
    if (n != NULL){
        PercorrerAndEmpilhar(n->esq,serie,Pilha);
        serie.cod = n->serie.cod;
        serie.nome = n->serie.nome;
        serie.qta = n->serie.qta;
        serie.uta = n->serie.uta;
        serie.uea = n->serie.uea;
        empilharSeries(Pilha,serie);
        PercorrerAndEmpilhar(n->dir,serie,Pilha);
    }
}

//A função Abaixo gera dois arquivos de texto um com os dados cadastrados para que possa ser lido posteriormente pelo programa,
// e outro
void GravarEmTXT(TPilha &pilha, TArvore arvore, TSerie s){
        CriaPilhaVazia(pilha);
        PercorrerAndEmpilhar(arvore.raiz,s,pilha);
        TCelula *n;
        n = pilha.topo->proximo;
        ofstream makefiler;
        ofstream maker;
        cin.clear(ios_base::goodbit);//Limpar txt
        makefiler.open("Séries.txt");
        makefiler << "-------------      Séries Cadastradas     -------------" << endl;
    while(n != NULL){
        makefiler << "-------------------------------------------------------" << endl;
        makefiler << "Codigo de cadastro da série: " << n->serie.cod << endl;
        makefiler << "Nome da série: " << n->serie.nome << endl;
        makefiler << "Temporadas completas: " << n->serie.qta << endl;
        makefiler << "Assistindo a: " << n->serie.uta << "º temporada, episódio: " << n->serie.uea << endl;
        n = n->proximo;
    }
    makefiler.close();
    n = pilha.topo->proximo;
    maker.open("save.txt");
    while (n != NULL){
        maker << n->serie.cod <<endl;
        maker << n->serie.nome <<endl;
        maker << n->serie.qta <<endl;
        maker << n->serie.uta <<endl;
        maker << n->serie.uea <<endl;
        n = n->proximo;
    }
    maker.close();
    cout << "Pronto!" << endl;
    cout << "Os Cadastros foram salvos em dois arquivos: "<< endl;
    cout << "Um com o nome de 'save' que guarda o progresso de cadastro, " << endl;
    cout << "E o outro com o nome de 'Séries', que são informações do cadastro\nque voçê pode consultar depois." << endl;
    cout << "Você pode encontrar eles na pasta do programa." << endl;
    cout << "-------------------------------------------------------" << endl;
}

//Carrega um útimo cadastro salvo
void CarregarUltimoCadastro(TPilha &p,TArvore &a){
        ifstream arq("save.txt");
        int cod,qta,uta,uea;
        string nome;
        CriaPilhaVazia(p);
        TSerie s;
        //ler o arquivo linha por linha até achar a marca de fim de arquivo
            do{
                arq >> cod;
                arq >> nome;
                arq >> qta;
                arq >> uta;
                arq >> uea;
                s.cod = cod;
                s.nome = nome;
                s.qta = qta;
                s.uta = uta;
                s.uea = uea;
                empilharSeries(p,s);
            }while(!arq.eof());
                arq.close();//fecha o arquivo de texto
                Desempilhar(p);
                cout << "Cadastro carregado!" << endl;
}

//O menu abaixo diz respeito as funções e procedimentos que serão feitos na árvore
int MenuArvore(TArvore a,TPilha p){
    int opcao=0, cod=0;
    TSerie s;
    cout << "Séries transferidas." << endl;
    do{
        cout << endl;
        cout << "------------------- Árvore de Séries ------------------" << endl;
        cout << "1 - Mostrar árvore." << endl;
        cout << "2 - Cadastrar mais séries." << endl;
        cout << "3 - Pesquisar série." << endl;
        cout << "4 - Apagar uma série." << endl;
        cout << "5 - Salvar em um documento de texto." << endl;
        cout << "6 - Sair." << endl;
        cout << "-------------------------------------------------------" << endl;
        cout << "opção: ";
        cin >> opcao;
        switch(opcao){
        case 1:
            MostrarArvore(a);
            break;
        case 2:
            CadastrarSeriesArvore(a);
            break;
        case 3:
            cout << "Digite o codigo da série: ";
            cin >> cod;
            cout << endl;
            PesquisarSerie(cod, a.raiz, a);
            break;
        case 4:
            cout << "Digite o codigo da série: ";
            cin >> cod;
            cout << endl;
            retirar(cod, a.raiz);
            break;
        case 5:
            GravarEmTXT(p,a,s);
            break;
        case 6:
            cout << "Fim..." << endl;
            return 0;
            break;
        default:
            cout << "Opção invalida." << endl;
            break;
        }
    }while(opcao != 7);
}

//O menu abaixo diz respeito as funções e procedimentos que serão feitos na pilha
int MenuPilha(TPilha Pilha, TArvore a){
    int op;
    do{
        cout << endl;
        cout << "-------------------------------------------------------" << endl;
        cout << "================== Agenda de Séries ===================" << endl;
        cout << "1- Cadastrar séries." << endl;
        cout << "2- Mostrar séries cadastradas." << endl;
        cout << "3- Mostrar última série cadastrada." << endl;
        cout << "4- Excluir a última série cadastrada." << endl;
        cout << "5- Transferir para a árvore." << endl;
        cout << "6- Carregar útimo cadastro salvo." << endl;
        cout << "7- Sair." << endl;
        cout << "-------------------------------------------------------" << endl;
        cout << "opcao: ";
        cin >> op;
        switch (op){
        case 1:
                CadastroDeSeries(Pilha);
            break;
        case 2:
                MostrarPilha(Pilha);
            break;
        case 3:
                MostrarTopo(Pilha);
            break;
        case 4:
                cout << "Serie apagada." << endl;
                Desempilhar(Pilha);
            break;
        case 5:
                TransferirPilhaParaArvore(Pilha,a);
            break;
        case 7:
                cout << "Fim..." << endl;
                return 0;
            break;
        case 6:
                CarregarUltimoCadastro(Pilha,a);
            break;
        default:
                cout << "Opção inválida!!!" << endl;
        }
    }while((op!=5));
    MenuArvore(a,Pilha);
}
