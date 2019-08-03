#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//Autores: Harley de Brito e Marco Aurélio Monteiro Lima


int calculaCusto2(int RCN[3], int mat1[10][10],int mat2[10][10], int mat3[10][10], int origemR, int origemC, int destinoR, int destinoC, int iteracoes)
{
    int deslocMaxR, deslocMaxC, custoMinimo = 1000000;
    int i, j,k=0,Rinicial, Cinicial, Rfinal, Cfinal;  //esquerda,cima,direita,baixo
    deslocMaxR = mat2[origemR][origemC];
    deslocMaxC = mat3[origemR][origemC];
    int custos[10][10];
    int custolocal = mat1[origemR][origemC];

    iteracoes++;

    if (iteracoes >5)  //numero de vezes que a recursividade é chamada consecutivamente
    {
        return -1;
    }
    if (origemR ==destinoR && origemC == destinoC)
    {
        return 0;
    }

    //MONTAR A MATRIZ...
    if(origemR -deslocMaxR < 0)
    {
        Rinicial = 0;
    }
    else
    {
        Rinicial = origemR -deslocMaxR;
    }

    if(origemC -deslocMaxC < 0)
    {
        Cinicial = 0;
    }
    else
    {
        Cinicial = origemC -deslocMaxC;
    }
    if(origemR +deslocMaxR >RCN[0])
    {
        Rfinal = RCN[0];
    }
    else
    {
        Rfinal = origemR +deslocMaxR+1;
    }
    if(origemC +deslocMaxC >RCN[1])
    {
        Cfinal = RCN[1];
    }
    else
    {
        Cfinal = origemC +deslocMaxC+1;
    }
// for para chamar recursivamente a função calculaCusto2 para cada elemnto alcançado pelo deslocamento máximo da origem
    for(i = Rinicial; i < Rfinal ; i++)
    {

        for(j = Cinicial; j < Cfinal; j++)
        {

            if (i == destinoR && j == destinoC)
            {
                return custolocal;
            }
            else
            {
                custos[i][j]= calculaCusto2(RCN, mat1,mat2,mat3, i, j, destinoR, destinoC, iteracoes)+custolocal;
            }
        }
    }

    //for para percorrer todos os elementos de uma matriz fictícia e selecionar o menor custo possível
    for(i = Rinicial; i < Rfinal ; i++)
    {

        for(j = Cinicial; j < Cfinal; j++)
        {
            if (custoMinimo > custos[i][j] &&custos[i][j] > 0)
            {
                custoMinimo = custos[i][j];
            }
        }

        return custoMinimo;

    }
}
//função para tratar o retorno da calculaCusto2 e devolver adequadamente para a main
int calculaCusto1(int RCN[3], int mat1[10][10],int mat2[10][10],int mat3[10][10], int origemR, int origemC, int destinoR, int destinoC, int iteracoes)
{
    int r = calculaCusto2(RCN, mat1, mat2,mat3, origemR, origemC, destinoR, destinoC, iteracoes);
    if (r ==1000000)
    {
        return -1;
    }
    return r;
}


int leArquivo(int RCN[3], int mat1[10][10],int mat2[10][10],int mat3[10][10],int provincia[5][2])
{
    int i, j;


    ifstream leitor("carolina-mirian.txt");
    if(!leitor.is_open())
    {
        cout<<"Nao foi possivel abrir o arquivo";
        return -1;
    }
    leitor >> RCN[0];
    leitor >> RCN[1];
    leitor >> RCN[2];


    cout << RCN[0] << RCN[1] << RCN[2] << endl;

    cout << endl << "MATRIZ 1"  << endl;
    for (i =0 ; i < RCN[0] ; i++)
    {
        for(j = 0; j<RCN[1]; j++)
        {
            leitor >> mat1[i][j];
            cout << mat1[i][j]<< " ";
        }
        cout << endl;
    }
    cout << endl << "MATRIZ 2"  << endl;

    for (i =0 ; i < RCN[0] ; i++)
    {
        for(j = 0; j<RCN[1]; j++)
        {
            leitor >> mat2[i][j];
            cout << mat2[i][j]<< " ";
        }
        cout << endl;
    }

    cout << endl << "MATRIZ 3"  << endl;
    for (i =0 ; i < RCN[0] ; i++)
    {
        for(j = 0; j<RCN[1]; j++)
        {
            leitor >> mat3[i][j];
            cout << mat3[i][j]<< " ";
        }
        cout << endl;
    }
    cout << endl << "Provincias:"  << endl;
    for(i=0; i<RCN[2]; i++)
    {
        leitor >>provincia[i][0];
        leitor >> provincia [i][1];
        cout << provincia[i][0] << "  "<<provincia[i][1]<<endl;
    }


    return 1;

}


int main()
{
    int mat1[10][10];
    int mat2[10][10];
    int mat3[10][10];
    int provincia[5][2];
    int RCN [3];
    int i, j;


    int r =leArquivo( RCN,  mat1,mat2,mat3,provincia);
    cout<< "ok leitura"<< endl;

    for (i=0 ; i<RCN[2]-1; i++)
    {
        int r = calculaCusto1( RCN,  mat1,mat2,mat3, provincia[i][0],provincia[i][1],provincia[i+1][0], provincia[i+1][1],  0);
        cout <<endl << "Custo:  "<< r <<endl;
    }

    return 0;
}
