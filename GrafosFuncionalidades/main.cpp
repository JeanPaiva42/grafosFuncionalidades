#include <iostream>
#include "Grafo.h"

using namespace std;

int main()
{
    srand(time(NULL));

    Grafo g("teste.txt");

    g.imprime();
    Grafo* y = g.Kruskal();
    y->imprime();
    exit(4);
    return 0;

}
