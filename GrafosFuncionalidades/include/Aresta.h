#ifndef ARESTA_H
#define ARESTA_H

class Aresta
{
    public:
        Aresta(int  dest, float peso);
        Aresta();
        ~Aresta();
        float get_Peso();
        int get_Destino();

    private:
        int  destino;      ///< Guarda o id de destino da aresta/arco.
        float peso_Aresta; ///< Guarda o peso da aresta/arco.
};

#endif // ARESTA_H

