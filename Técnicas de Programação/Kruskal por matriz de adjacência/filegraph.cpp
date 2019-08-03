/*  INSTITUTO FEDERAL DE MINAS GERAIS - Campus Bambuí
    Trabalho Final da Disciplina de Técnicas de Programação - 2017

    Eduardo Augusto de Oliveira Borges - RA:0015501
    Marco Aurélio Monteiro Lima        - RA:0022933
    Marcus Vinícius Rodrigues Campos   - RA:0022127
*/

#include<iostream>
#include "filegraph.h"

//Metodo Converte String para inteiro
int toInt(string text) {
    int result;
    stringstream convert(text);
    if(!(convert >> result))result = 0;
    return result;
}

//Lê um arquivo retornando uma lista
list<int> reading(char *nome_arq) {
    ifstream read(nome_arq);
    list<int> list_read;
    string o,p,d,nv;
    int ord,pe,de,nver;
    if(!read.is_open())cout<< "File did not open successfully" << endl;/*
        Caso não consiga ler o arquivo retorna a mensagem de erro
    */
    else{
    read >> nv;
        nver = toInt(nv);
        list_read.push_back(nver);
        do {
            read >> o;
            read >> p;
            read >> d;

            ord = toInt(o);
            pe = toInt(p);
            de = toInt(d);

            list_read.push_back(ord);
            list_read.push_back(pe);
            list_read.push_back(de);

        } while(!read.eof());
        read.close();
    }
    return list_read;
}
