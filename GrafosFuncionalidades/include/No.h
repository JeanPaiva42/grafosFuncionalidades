#ifndef NO_H
#define NO_H
#include <iostream>
#include <list>
#include "Aresta.h"

using namespace std;

typedef struct Aresta_aux
{
    int destino;
    float peso;
} aux_Aresta;

class No
{
public:
    No(int identificacao);
    void set_Peso_No(float peso);
    void imprime_Adjacentes();
    int get_Id();
    int get_Peso_No();
    int get_Grau_No();
    void add_Adjacente(int id, float peso);
    void remove_Adjacente(int id);
    bool encontra_Adjacente(int id);
    int* lista_Adjacencias();
    aux_Aresta* copia_Arestas();
    aux_Aresta* copia_Uma_Aresta(int id);
    int* lista_Peso();
    Aresta* get_Endereco_Aresta(int id);
    float get_Aresta_Peso(int id_aresta);
    void set_Grau_No_Heuristica();
    int get_Grau_No_Heuristica();
    void diminui_Grau_No_Heuristica();
    ~No();

private:
    void incrementa_Grau();
    void decrementa_Grau();
    int grau_No_Heuristica; ///< Armazena grau auxiliar para ser usado na heurística.
    int id;
    float peso_No;         ///< Armazena peso do Nó.
    int grau_No;           ///< Armazena o grau do Nó.
    list <Aresta> Adj;     ///< Lista de Arestas do Grafo.
};

#endif // NO_H
