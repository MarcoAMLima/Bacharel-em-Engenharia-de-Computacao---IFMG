/*  INSTITUTO FEDERAL DE MINAS GERAIS - Campus Bambuí
    Trabalho Final da Disciplina de Técnicas de Programação - 2017

    Eduardo Augusto de Oliveira Borges - RA:0015501
    Marco Aurélio Monteiro Lima        - RA:0022933
    Marcus Vinícius Rodrigues Campos   - RA:0022127
*/

#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED
#include<iostream>
#include <list>

using namespace std;

class Graph
{
public:
    int Number_Vertex;
    int *Edge;
    list<int> *adjacency_list;
    list<pair<int,pair<int, int > > >edge;

    Graph(int);
    void print_with_vertex();
    void print_with_vertex_weight();
    void add_edge(int, int, int);
    void add_edgeKruskal(int, int, int);

    int FIND_SET(int);
    void UNION(int, int);

    /*int FIND_SET(int[], int);
    void UNION(int[], int, int);
*/
    Graph MAKE_SET(Graph, int);
    void MST_Kruskal(Graph);

};

#endif // GRAPH_H_INCLUDED
