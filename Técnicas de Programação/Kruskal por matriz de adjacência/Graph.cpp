/*  INSTITUTO FEDERAL DE MINAS GERAIS - Campus Bambuí
    Trabalho Final da Disciplina de Técnicas de Programação - 2017

    Eduardo Augusto de Oliveira Borges - RA:0015501
    Marco Aurélio Monteiro Lima        - RA:0022933
    Marcus Vinícius Rodrigues Campos   - RA:0022127
*/

#include "Graph.h"

using namespace std;

//Construtor do Grafo
Graph::Graph(int Number_Vertex) {
    this->Number_Vertex = Number_Vertex;
    adjacency_list = new list<int>[Number_Vertex];
}

//Adiciona a aresta no Grafo
void Graph::add_edge(int vertex1, int vertex2, int weight) {
    adjacency_list[vertex1].push_back(vertex2);
    adjacency_list[vertex1].push_back(weight);
}

//Adiciona aresta no Grafo
//Utilizado pelo Kruskal pois esse método é não direcional
void Graph::add_edgeKruskal(int vertex1, int vertex2, int weight) {
    adjacency_list[vertex1].push_back(vertex2);
    adjacency_list[vertex2].push_back(vertex1);
    adjacency_list[vertex2].push_back(weight);
    adjacency_list[vertex1].push_back(weight);
}

//Imprime um grafo mostrando o grafo
void Graph::print_with_vertex() {
    int weight=0;
    int index;
    for(int index=0; index<Number_Vertex; index++) {
        list<int>::iterator iterator_list;
        iterator_list = this->adjacency_list[index].begin();

        cout<<index<<": ";
        int j=0;
        for (iterator_list=this->adjacency_list[index].begin(); iterator_list!=this->adjacency_list[index].end();
             iterator_list++) {
            if(j%2 == 0)cout<<*iterator_list<<" ";
            else weight+=*iterator_list;
            j++;
        }
        cout<<endl;
    }
    if(weight>0)cout<<"w: "<<(weight/2)<<endl;
}

//Imprime um grafo mostrando vertice com seu peso
void Graph::print_with_vertex_weight() {
    int i;
    for(i=0; i<Number_Vertex; i++) {
        list<int>::iterator it;
        it = this->adjacency_list[i].begin();

        cout<<i<<" -> ";
        int j=0;
        for (it=this->adjacency_list[i].begin(); it!=this->adjacency_list[i].end(); it++) {
            if(j%2 == 0)cout<<*it;
            else cout<<"["<<*it<<"] ";
            j++;
        }
        cout<<endl;
    }
}

//Verifica se determinada aresta ja está presente na arvore
int Graph::FIND_SET(int index) {
    if(this->Edge[index] == NULL)return index;
    return FIND_SET(Edge[index]);
}

//Faz a uniao de duas Florestas
void Graph::UNION(int vertex1, int vertex2) {
    int vertex1_set = FIND_SET(vertex1);
    int vertex2_set = FIND_SET(vertex2);
    this->Edge[vertex1_set] = vertex2_set;
}

//Empurra todas as arestas pra uma lista do tipo lista<pair<int<pair<int,int>>>
Graph Graph::MAKE_SET(Graph graph, int index) {
    list<int>::iterator iterator_list;
    iterator_list = graph.adjacency_list[index].begin();
    int v_dest=0;
    for (iterator_list=graph.adjacency_list[index].begin(); iterator_list!=graph.adjacency_list[index].end();
         iterator_list++) {
        v_dest = *iterator_list;
        iterator_list++;
        graph.edge.push_back({*iterator_list,{index,v_dest}});
    }
    return graph;
}

//Gera a arvore depois do algoritmo de Kruskal
void Graph::MST_Kruskal(Graph graph) {
    int i,f=0;
    Graph Kruskal(graph.Number_Vertex); //Cria um novo grafo

    for(i=0; i<graph.Number_Vertex; i++)graph = MAKE_SET(graph,i);//Faz a lista de arestas
    graph.edge.sort(); //Ordena a lista de arestas

    list<pair<int,pair<int, int > > >::iterator iterator_edge; //Cria um iterador para percorrer a lista
    this->Edge = new int[graph.Number_Vertex]; //Aloca espaço para as novas florestas

    for(i=0; i<graph.Number_Vertex+1; i++)Edge[i]=NULL; //Determina inicialmente que todas ligções sao florestas
    for(iterator_edge = graph.edge.begin();iterator_edge != graph.edge.end(); iterator_edge++) {
        f++;
        for(int i=0; i<f; i++) {
            //Verifica se a origem e as arestas já estao presentes na floresta
            if(FIND_SET(iterator_edge->second.first) != FIND_SET(iterator_edge->second.second)) {
                //Caso esteja presente a aresta é adicionada no grafo do Kruskal
                Kruskal.add_edgeKruskal(iterator_edge->second.first,iterator_edge->second.second,iterator_edge->first);

                //Faz a união da floresta antiga com a atual, formando uma única
                UNION(FIND_SET(iterator_edge->second.first), FIND_SET(iterator_edge->second.second));
            }
        }
    }
    Kruskal.print_with_vertex(); //Imprime a arvore formada pelo algoritmo de Kruskal
}
