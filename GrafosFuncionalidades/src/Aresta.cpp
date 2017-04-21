#include "Aresta.h"

Aresta::Aresta(int dest,float peso)
{
    destino = dest;
    peso_Aresta = peso;
}
Aresta::Aresta()
{

}
float Aresta::get_Peso()
{
    return peso_Aresta;
}

int Aresta::get_Destino()
{
    return destino;
}
Aresta::~Aresta()
{
    //dtor
}
