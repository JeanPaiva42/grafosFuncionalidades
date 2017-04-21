#include "No.h"
#include <iostream>

using namespace std;

/********************************************//**
 * \Construtor da classe No.
 *
 * \Parâmetro: id do no a ser criado.
 * \Sem valor de Retorno.
 *
 *Inicializa a peso_No com 1 e grau_No com 0. Atribui a id o valor de identificacao.
 ***********************************************/
No::No(int identificacao)
{
    id = identificacao;
    peso_No = 1.0;
    grau_No = 0;
}


/********************************************//**
 * \Atribui peso ao no.
 *
 * \Parâmetro: peso.
 *
 * \Sem valor de Retorno.
 *
 * Atribui ao peso_No o peso atributo passado por parâmetro que altera o valor atual do peso do No.
 ***********************************************/
void No::set_Peso_No(float peso)
{
    peso_No = peso;
}


/********************************************//**
 * \Imprime lista de adjacentes.
 *
 *
 * \Sem valor de Retorno.
 *
 * Imprime toda a lista de adjacentes do No.
 ***********************************************/
void No::imprime_Adjacentes()
{
    list<Aresta>::iterator i;
    for(i = Adj.begin(); i != Adj.end(); i++)
        cout << "->" <<  i->get_Destino();

    cout << endl;
}


/********************************************//**
 * Retorna a identificação do nó.
 ***********************************************/
int No::get_Id()
{
    return id;
}


/********************************************//**
 * Retorna o inteiro peso_No.
 ***********************************************/
int No::get_Peso_No()
{
    return peso_No;
}


/********************************************//**
* Retorna o inteiro grau_No.
 ***********************************************/
int No::get_Grau_No()
{
    return grau_No;
}


/********************************************//**
 * \Adiciona nova adjacencia ao no.
 *
 * \Parâmetros: id (identificação do no da nova adjacencia) e peso(peso da nova adjacencia).
 * \Sem valor de Retorno.
 *
 * É colocado na última posição da lista de arestas a nova adjacencia criada e é incrementado o grau do no.
 ***********************************************/
void No::add_Adjacente(int id, float peso)
{
    Adj.push_back(Aresta(id,peso));
    incrementa_Grau();
}



/********************************************//**
 * \Remove um aresta/arco da lista de adjacências.
 *
 * \Parâmetro: id do destino da aresta/arco a ser removido.
 * \Sem valor de Retorno.
 *
 * Percorre a lista de adjacências do Nó e exclui a aresta com o id passado se não chegou no fim da lista.
 ***********************************************/
void No::remove_Adjacente(int id)
{
    list<Aresta>::iterator i;
    for(i = Adj.begin(); i != Adj.end(); i++)
    {
        if(i->get_Destino() == id)
        {
            Adj.erase(i);
            break;
        }
    }
    if(i != Adj.end())
        decrementa_Grau();
}


/********************************************//**
 * \Verifica se o id passado está na lista de adjacência do nó.
 *
 * \Parâmetro: id que é passado para procurar na lista de adjcências.
 * \Sem valor de Retorno.
 *
 * Percorre a lista de adjacências do nó e retorna true caso o id passado esteja na lista.
 ***********************************************/
bool No::encontra_Adjacente(int id)
{
    list<Aresta>::iterator i;
    for(i = Adj.begin(); i != Adj.end(); i++)
    {
        if(i->get_Destino() == id)
            return true;
    }
    return false;
}


/********************************************//**
 * \Retornar a lista de adjacências.
 *
 * \Retorna um vetor com os ids das adjacências do nó.
 *
 * Percorre a lista de adjacências à medida que adiciona o id destino das arestas num vetor.
 ***********************************************/
int* No::lista_Adjacencias()
{
    int* lista = new int[grau_No];
    int j = 0;
    list<Aresta>::iterator i;
    for(i = Adj.begin(); i != Adj.end(); i++)
    {
        lista[j] = i->get_Destino();
        j++;
    }
    return lista;
}


/********************************************//**
 * \Retorna um vetor de Struct aux_Aresta contendo os id's destinos e os pesos.
 *
 * \Retorna um vetor com as arestas dispostas na struct aux_Aresta.
 *
 * Percorre a lista de adjacências à medida que cria caminha pela vetor de struct e cria modifica a estrutur que será retornada.
 ***********************************************/
aux_Aresta* No::copia_Arestas()
{
    aux_Aresta* passar = new aux_Aresta[grau_No];
    list<Aresta>::iterator i;
    int k = 0;
    for(i = Adj.begin(); i != Adj.end(); i++)
    {
        passar[k].destino = i->get_Destino();
        passar[k].peso = i->get_Peso();
        k++;
    }
    return passar;
}


/********************************************//**
 * \Retonra uma struct aux_Aresta com informações de uma aresta/arco.
 *
  * \Parâmetro: id com o destino da aresta/arco que se quer copiar.
 * \Retorna uma struct.
 *
 * Guarda o endereço da aresta e copia para a struct.
 ***********************************************/
aux_Aresta* No::copia_Uma_Aresta(int id)
{
    Aresta* copiar = get_Endereco_Aresta(id);
    aux_Aresta* passar = new aux_Aresta;
    passar[0].destino = copiar->get_Destino();
    passar[0].peso = copiar->get_Peso();

    return passar;
}


/********************************************//**
 * \Construtor da classe No.
 *
 * \Parâmetro: id do no a ser criado.
 * \Sem valor de Retorno.
 *
 * Inicializa a peso_No com 1 e grau_No com 0. Atribui a id o valor de identificacao.
 ***********************************************/
int* No::lista_Peso()
{
    int* lista = new int[grau_No];
    int j = 0;
    list<Aresta>::iterator i;
    for(i = Adj.begin(); i != Adj.end(); i++)
    {
        lista[j] = i->get_Peso();
        j++;
    }
    return lista;
}


/********************************************//**
 * \Retorna um endereço de aresta.
 *
 * \Parâmetro: id da aresta a se encontrar.
 * \ É retornado o endereço da aresta procurada ou null se nada for achado.
 *
 * .
 ***********************************************/
Aresta* No::get_Endereco_Aresta(int id)
{
    list<Aresta>::iterator it;
    for(it = Adj.begin(); it != Adj.end(); it++)
        if(it->get_Destino() == id)
            return &*it;
    return 0;
}


/********************************************//**
 *Dado o parâmetro id_aresta se percorre  a lista de adjacencias
 *do no até encontrar uma adjacencia == id_aresta.
 * Após achar tal aresta retorno o peso da mesma. Caso não se ache nada retorno da função é 0.
 ***********************************************/
float No :: get_Aresta_Peso(int id_aresta)
{
    list<Aresta>::iterator it;
    for(it = Adj.begin(); it != Adj.end(); it++)
        if(it->get_Destino() == id)
            return it->get_Peso();
    return 0;
}



/********************************************//**
 * Atribui ao grau_No_Heuristica grau_No.
 ***********************************************/
void No::set_Grau_No_Heuristica()
{
    grau_No_Heuristica = grau_No;
}



/********************************************//**
 * \Retorna o grau_No_Heuristica.
 *
 * Função que retorna o campo grau_No_Heuristica.
 ***********************************************/
int No::get_Grau_No_Heuristica()
{
    return grau_No_Heuristica;
}



/********************************************//**
 * \Decrementa grau do no heurística
 *
 *
 * \Sem valor de Retorno.
 *
 * Decrementa em um o grau do No heuristica.
 ***********************************************/
void No::diminui_Grau_No_Heuristica()
{
  grau_No_Heuristica--;

}


/********************************************//**
 * \Destrutor do No.
 *
 * \
 * \Sem valor de Retorno.
 *
 * Deleta No.
 ***********************************************/
No::~No(){
	Adj.clear();
}


/********************************************//**
 * \Incrementa grau do No.
 *
 * \Sem valor de Retorno.
 *
 * Encrementa em um o grau do No.
 ***********************************************/
void No::incrementa_Grau()
{
    grau_No += 1;
}


/********************************************//**
 * \Decrementa grau do No.
 *
 * \
 * \Sem valor de Retorno.
 *
 * Decrementa em um o grau do No se esse tiver previamente grau maior que zero.
 ***********************************************/
void No::decrementa_Grau()
{
    if(grau_No == 0)
        cout << "Nao eh possivel realizar essa operacao!" << endl;
    else
        grau_No -= 1;
}
