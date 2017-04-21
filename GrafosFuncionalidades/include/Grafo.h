#ifndef GRAFO_H
#define GRAFO_H
#include "Aresta.h"
#include "No.h"
#include <iostream>
#include "stdio.h"
#include <fstream>
#include <string>
#include <algorithm>
#include <queue>
#include <stack>
#include <limits>
#include <cmath>
#include <time.h>

using namespace std;

class Grafo
{
public:
    Grafo(string nome_arquivo);
    Grafo();
    void insere_No(int id);
    void insere_No(int id,float peso);
    void exclui_No(int id);
    void insere_Aresta(int id1, int id2, float peso);
    void exclui_Aresta(int id1, int id2);
    int get_Grau_No(int id);
    int *sequencia_Graus();
    bool verifica_Kregular();
    bool verifica_Completo();
    bool verifica_Adjacentes(int id1,int id2);
    void busca_Largura(int id);
    void busca_Profundidade(int id);
    bool verifica_Conexo();
    bool verifica_Nos_Conectados(int id1,int ad2);
    bool verifica_No_Articulacao(int id1);
    bool verifica_Aresta_Ponte(int id1, int id2);
    int *vizinhaca_Aberta(int id);
    int *vizinhaca_Fechada(int id);
    list<int> fechamento_Transitivo_Direto(int id);
    list<int> fechamento_Transitivo_Indireto(int id);
    vector<int> ordenacao_Topologica();
    int Dijkstra(int id1, int id2);
    int** Floyd();
    Grafo* sub_Grafo_Induzido(int lista[], int tam);
    Grafo* get_Componentes_Conexas();
    Grafo* Prim();
    Grafo* Kruskal();
    bool verificar_KConexidade();
    bool verifica_Euleriano();

    void imprime();
    void escreve_Grafo();
    int get_Grau_Grafo();
    int get_Qtd_Arestas();
    int get_Qtd_Nos();
    int componentes_Conexas();

    int aux_Conjunto_Dominante_Minimo(float alpha);
    int conjunto_Dominante_Minimo(float alpha, int iteracoes, float* media2);
    void teste_Heuristica_Gulosa();
    void teste_Heuristica_Randomica();
    void teste_Heuristica_Randomica_Reativa();
    void verifica_Desvio_Padrao();
    void exclui_No_Heuristica(int id);
	~Grafo();

private:
    void set_Direcionado(bool flag);
    void set_Ponderado(bool flag);
    void aux_Insere_Aresta(int id1, int id2, float peso);
    No* get_Endereco(int id);
    int indice_Menor_Distancia(float distancia[], bool visitados[]);
    void le_Grafo(string nome);
    void aux_Le_Grafo(string nome);
    bool existe_No(int identificacao);
    int get_Indice(int id);

    int valor_Testes[3000];///< Armazena os valores dos testes para a Heurística.
    int num_Testes;		   ///< Número de vezes que a heurística foi testada.
    int qtd_De_Nos;	   	   ///< Armazena Quantidade de Nós.
    bool flag_Direcionado; ///< Valor lógico que indica se o grafo é direcionado ou não.
    bool flag_Ponderado;   ///< Valor lógico que indica ponderado.
    list<No> Nos;		   ///< Lista de Nós do Grafo.
};

#endif // GRAFO_H
