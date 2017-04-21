#include "Grafo.h"

/********************************************//**
 * \Construtor da classe Grafo.
 *
 * \Parâmetro: Nome do arquivo de entrada do Grafo.
 * \Sem valor de Retorno.
 *
 * Inicializa a qtd_De_Nos com 0 e chama a função de leitura do Grafo.
 ***********************************************/
Grafo::Grafo(string nome_arquivo)
{
    qtd_De_Nos = 0;
    num_Testes = 0;

    cout << "O grafo será lido para Heurística? " << endl << "s para SIM, n para NAO: " ;
    char t = 's';
    if(t != 's')
        le_Grafo(nome_arquivo);
    else
    {
        cout << "PASSOU" << endl;
        aux_Le_Grafo(nome_arquivo);
    }

}


/********************************************//**
 * \Construtor do Grafo sem parâmetros.
 *
 * \Sem valor de retorno
 *
 * Construtor para casos que sejam criados Grafos sem que seja necessário leitura(Ex: Retornar componentes conexas).
 ***********************************************/
Grafo::Grafo()
{
    qtd_De_Nos = 0;
}


/********************************************//**
 * \Insere nós no grafo.
 *
 * \Paramêtro: id que vai identificar o nó.
 * \Sem valor de  retorno.
 *
 * Aumento a variável qtd_De_Nos + 1 e insere o novo nó com o id passado no final da lista de nos do grafo.
 ***********************************************/
void Grafo::insere_No(int id)
{
    qtd_De_Nos += 1;
    Nos.push_back(No(id));
}

/********************************************//**
 * \Insere nó ponderado no grafo.
 *
 * \Parâmetro: id que vai identificar o nó.
 * \Parâmetro: peso do nó.
 * \Sem valor de  retorno.
 *
 * Aumento a variável qtd_De_Nos + 1 e insere o novo nó com o id passado no final da lista de nos do grafo.
 ***********************************************/
void Grafo::insere_No(int id, float peso)
{
    qtd_De_Nos += 1;
    No* insere = new No(id);
    insere->set_Peso_No(peso);
    Nos.push_back(*insere);
}

/********************************************//**
 * \Exclui nó da Lista.
 *
 * \Parâmetro: id do nó a ser removido.
 * \Sem valor de retorno.
 *
 * Função percorre a lista de Nós e exclui o nó passado como parâmetro.
 ***********************************************/
void Grafo::exclui_No(int id)
{
    list<No>::iterator i;
    for(i = Nos.begin(); i != Nos.end(); i++)
    {
        if(i->get_Id() == id)
        {
            Nos.erase(i);
            break;
        }
    }
    ///< Exclui as ocorrências do nó excluído nas adjacências dos outros nós.
    if(i != Nos.end() && !flag_Direcionado)
    {
        for(i = Nos.begin(); i != Nos.end(); i++)
            i->remove_Adjacente(id);

        qtd_De_Nos -= 1;
    }
}


/********************************************//**
 * \ Cria uma nova aresta/arco.
 *
 * \Parâmetro: id1 corresponde a um dos nós da nova aresta.
 * \Parâmetro: id2 corresponde a um dos nós da nova aresta.
 * \Parâmetro que corresponde ao peso da nova aresta a ser criada.
 * \Sem valor de retorno.
 *
 * Dado id1, id2 e peso, é criada uma nova aresta/arco entre esses dois nós se, e somente se, os nós já foram inseridos na Lista de Nós.
 ***********************************************/
void Grafo::insere_Aresta(int id1,int id2, float peso)
{
    if(existe_No(id1) && existe_No(id2))
    {
        if(!flag_Ponderado)
            peso = 1.0;
        aux_Insere_Aresta(id1,id2,peso);
    }
    else
        cout << "Nao existe tais vertices" << endl;
}


/********************************************//**
 * \Exclui uma aresta/arco do grafo.
 *
 * \Parâmetro: id1 corresponde a um dos nós da aresta/arco.
 * \Parâmetro: id2 corresponde a um dos nós da aresta/arco.
 * \Sem valor de retorno.
 *
 * Função exclui aresta/arco que está liga os nós com identificação id1/id2.
 ***********************************************/
void Grafo::exclui_Aresta(int id1, int id2)
{
    list<No>::iterator i;
    for(i = Nos.begin(); i != Nos.end(); i++)
    {
        if((i->get_Id() == id1) || (i->get_Id() == id2))
        {
            ///< Caso encontre o nó id1 na lista e o grafo for direcionado, a função acaba.
            if(i->get_Id() == id1)
            {
                i->remove_Adjacente(id2);
                if(flag_Direcionado)
                    break;
            }
            ///< Caso encontre o nó id2 e não for direcionado, então remove aresta id2-id1.
            if(i->get_Id() == id2)
            {
                if(!flag_Direcionado)
                    i->remove_Adjacente(id1);

            }
        }
    }
}


/********************************************//**
 * \Retorna o grau do nó requisitado.
 *
 * \Parâmetro: id1 representa a identificação do nó que se deseja saber o grau.
 * \Retorna grau do nó.
 *
 * Dado id1 a função retorna um inteiro com o grau do nó com a identificação passada.
 * Se o nó não for encontrado na lista retorna -1.
 ***********************************************/
int Grafo::get_Grau_No(int id)
{
    list<No>::iterator i;
    for(i = Nos.begin(); i != Nos.end(); i++)
    {
        if(i->get_Id() == id)
            return i->get_Grau_No();
    }
    return -1;
}


/********************************************//**
 * \Retorna a sequência de graus do grafo.
 *
 * \Retorna um array com a sequências de graus.
 *
 * Cria um vetor de tamanho qtd_De_Nos e preenche o mesmo com os graus do grafo.
 * O array é ordenado e retornado.
 ***********************************************/
int *Grafo::sequencia_Graus()
{

    int* sequencia = new int[qtd_De_Nos];
    list<No>::iterator it;
    int i = 0;
    for(it = Nos.begin(); it != Nos.end(); it++)
    {
        sequencia[i] = it->get_Grau_No();
        i++;
    }
    sort(sequencia, sequencia + qtd_De_Nos);

    return sequencia;
}


/********************************************//**
 * \Verifica se todos os nós têm mesmo grau.
 *
 * \Retorna um booleano que indica o resultado da verificação.
 *
 * Retorna um booleano que indica se o grafo é k-regular.
 * Caso seja retorna true.
 ***********************************************/
bool Grafo::verifica_Kregular()
{
    list<No>::iterator i;
    i = Nos.begin();
    int k = i->get_Grau_No();
    for(i = Nos.begin(); i != Nos.end(); i++)
        if(i->get_Grau_No() != k)
            return false;

    ///< Se a condição do if foi respeitada para todos os nós, então o grafo é k-regular e a função retorna true.
    return true;
}


/********************************************//**
 * \Verifica se o o grafo é completo.
 *
 * \Retorna um booleano que indica se o grafo é completo ou não.
 *
 * Se todos os nós do grafo tenham grau qtd_De_Nos - 1, o grafo é completo e a função retorna true.
 * Caso contrário retorna false.
 ***********************************************/
bool Grafo::verifica_Completo()
{
    int completo = qtd_De_Nos - 1;
    list<No>::iterator i;
    for(i = Nos.begin(); i != Nos.end(); i++)
        if(i->get_Grau_No() != completo)
            return false;

    return true;
}


/********************************************//**
 * \Verifica se nó com id2 é adjacente ao nó com id1.
 *
 * \Parâmetro: id1 que corresponde ao nó ao qual será verificado a adjacência.
 * \Parâmetro: id2 que corresponde ao nó que se quer saber ser adjacente ou não à id1.
 * \Retorna um booleano que indica se id2 é adjacente de id1.
 *
 * A Lista de nós é percorrida até se encontrar id1.
 * No nó id1 é vericado se id2 está nas suas adjacências.
 * Se sim, retorna true. Senão false.
 ***********************************************/
bool Grafo::verifica_Adjacentes(int id1, int id2)
{
    list<No>::iterator i;
    for(i = Nos.begin(); i != Nos.end(); i++)
        if(i->get_Id() == id1)
            return i->encontra_Adjacente(id2);

    return false;
}


/********************************************//**
 * \Gera um arquivo texto descrevendo a árvore de busca gerada a partir do nó passado como parâmetro.
 *
 * \Parâmetro: id que será a raiz da respectiva árvore de busca que será gerada.
 * \Sem valor de retorno.
 *
 * A funcao utiliza dois vetores auxiliares que marcam o nivel e índice dos predecessores dos nós à medida que eles são encontrados na busca.
 * Uma fila é usada para manter os nós enquanto é feita a busca.
 * No final da função, com os valores dos vetores de nível e predecessores, é gerado o arquivo com a respectiva árvore de busca do nó passado como parâmetro.
 ***********************************************/
void Grafo::busca_Largura(int id)
{
    queue<int> fila_Visitados;
    int nivel[qtd_De_Nos];
    int predecessor[qtd_De_Nos];
    for(int i = 0; i < qtd_De_Nos; i++)
        predecessor[i] = nivel[i] = -1;

    int aux = get_Indice(id);
    nivel[aux] += 1;
    predecessor[aux] = 0;
    fila_Visitados.push(aux);

    int grau;
    int* adjacencias;

    ///< Vetor auxiliar de endereços de nós é criado para facilitar acessos à informações dos nós,
    ///< já que os índices desse vetor foram mapeados de acordo com os índices da lista e dos outros
    ///< vetores auxiliares(nível e predecessor).
    ///< Em suma, os id's reias dos nós não são os indices que são acesssados, mas com o indíce é
    ///< possível saber, através do vetor de endereços, informações como grau e lista de adjacências.
    vector<No*> enderecos(qtd_De_Nos);
    int k = 0;
    list<No>::iterator it;
    for(it = Nos.begin(); it != Nos.end(); it++)
    {
        enderecos[k] = &*it;
        k++;
    }
    ///< Arquivo de saída que irá descrever as informações da árvore.
    ofstream arq_saida;
    arq_saida.open("ArvoreDeBuscaLargura.txt");
    arq_saida << "Arvore de busca em Largura a partir do vértice " << enderecos[aux]->get_Id() << endl;

    while(!fila_Visitados.empty())
    {
        id = fila_Visitados.front();
        fila_Visitados.pop();

        ///< Com o índice retirado da lista é possível obter informações do nó, cujo endereço está armazenado no vetor "enderecos",
        ///< na posição com o índice que acabou de ser removidoda fila.
        No* pont = enderecos[id];

        adjacencias = pont->lista_Adjacencias();
        grau = pont->get_Grau_No();

        arq_saida << enderecos[id]->get_Id() << ": ";
        for(int k = 0; k < grau; k++)
        {
            int indice = get_Indice(adjacencias[k]);
            if(nivel[indice] == -1)
            {
                ///< À medida que são encontrados nós ainda não visitados, o arquivo é atualizado.
                arq_saida << enderecos[indice]->get_Id() << "->";
                nivel[indice] = nivel[id] + 1;
                predecessor[indice] = pont->get_Id();
                fila_Visitados.push(indice);
            }
        }
        arq_saida << endl;
    }
    arq_saida.close();
}


/********************************************//**
 * \Gera um arquivo texto descrevendo a árvore de busca gerada a partir do nó passado como parâmetro.
 *
 * \Parâmetro: id que será a raiz da respectiva árvore de busca que será gerada.
 * \Sem valor de retorno.
 *
 * A funcao utiliza dois vetores auxiliares que marcam o nivel e índice dos predecessores dos nós à medida que eles são encontrados na busca.
 * Uma pilha é usada para manter os nós enquanto é feita a busca.
 * No final da função, com os valores dos vetores de nível e predecessores, é gerado o arquivo com a respectiva árvore de busca do nó passado como parâmetro.
 ***********************************************/
void Grafo::busca_Profundidade(int id)
{
    int *nivel = new int[qtd_De_Nos];
    int *predecessor = new int[qtd_De_Nos];
    for(int i = 0; i < qtd_De_Nos; i++)
        nivel[i] = predecessor[i] = -1;

    ///< Vetor auxiliar de endereços de nós é criado para facilitar acessos à informações dos nós,
    ///< já que os índices desse vetor foram mapeados de acordo com os índices da lista e dos outros
    ///< vetores auxiliares(nível e predecessor).
    ///< Em suma, os id's reias dos nós não são os indices que são acesssados, mas com o indíce é
    ///< possível saber, através do vetor de endereços, informações como grau e lista de adjacências.
    vector<No*> enderecos(qtd_De_Nos);
    list<No>::iterator i;

    ///< start_indice representa o primeiro índice que será incluido na pilha e a partir do qual
    ///< será gerada a árvore.
    int k = 0;
    int start_indice = 0;
    for(i = Nos.begin(); i != Nos.end(); i++)
    {
        enderecos[k] = &*i;
        if(i->get_Id() == id)
            start_indice = k;
        k++;
    }
    stack<int> pilha;
    pilha.push(start_indice);

    ///< Nível da raiz e seu predecessor setados para 0.
    nivel[start_indice] = 0;
    predecessor[start_indice] = 0;

    while(!pilha.empty())
    {
        ///< indice é desempilhado, e serão procurados adjacentes a esse nó que ainda não foram visitados.
        int indice = pilha.top();
        No* pont = enderecos[indice];
        int grau = pont->get_Grau_No();
        int *adjacentes = pont->lista_Adjacencias();
        int j;

        for(j = 0; j < grau; j++)
        {
            int verifica = 0;
            bool entrar = false;
            for(i = Nos.begin(); i != Nos.end(); i++)
            {
                if(i->get_Id() == adjacentes[j])
                {
                    ///< Verifica se os adjacentes do nó que foi desempilhado já foram visitados.
                    ///< Se sim o adjacente é marcado como visitado e a execução sai do escopo do for,
                    ///< condição que garante que a busca é em Profundidade.
                    if(nivel[verifica] == -1)
                    {
                        entrar = true;
                        break;
                    }
                }
                verifica++;
            }
            ///< Índice do nó é empilhado e informações sobre seu nivel e predecessor são alteradas.
            if(entrar)
            {
                pilha.push(verifica);
                nivel[verifica] = nivel[indice] + 1;
                predecessor[verifica] = pont->get_Id();
                break;
            }
        }
        if(j == grau)
            pilha.pop();
    }
    ///< Arquivo de saída é criado para descrever a respectiva árvore de busca que foi gerada.
    ofstream arq_saida;
    arq_saida.open("ArvoreDeBuscaProfundidade.txt");
    arq_saida << "Arvore de busca Profundidade a partir do vértice " << enderecos[start_indice]->get_Id() << endl;

    queue<int> fila;
    fila.push(enderecos[start_indice]->get_Id());
    while(!fila.empty())
    {
        int indice = fila.front();
        fila.pop();
        arq_saida << endl << indice << " :";
        for(int i = 0; i < qtd_De_Nos; i++)
        {
            if(predecessor[i] == indice)
            {
                fila.push(enderecos[i]->get_Id());
                arq_saida << enderecos[i]->get_Id() << " -> ";
            }
        }
    }
    arq_saida.close();
}


/********************************************//**
 * \Verfica se o grafo é conexo.
 *
 * \Retonra um booleano que indica se o grafo é conexo ou não.
 *
 * A função cria um vetor de visitados e inicializa as posições com false.
 * À medida que a busca em largura está sendo executada o vetor de visitados vai sendo alterado e o índice dos vértices encontrados é setado pra true.
 * Se no final da busca algum índice do vetor ainda conter false, significa que o grafo não é conexo e função irá retornar false.
 * Caso contrário retornará true.
 ***********************************************/
bool Grafo::verifica_Conexo()
{
    bool *visitados = new bool[qtd_De_Nos];
    for(int i = 0; i < qtd_De_Nos; i++)
        visitados[i] = false ;


    ///< Vetor auxiliar de endereços de nós é criado para facilitar acessos à informações dos nós,
    ///< já que os índices desse vetor foram mapeados de acordo com os índices da lista e dos outros
    ///< vetores auxiliares(nível e predecessor).
    ///< Em suma, os id's reias dos nós não são os indices que são acesssados, mas com o indíce é
    ///< possível saber, através do vetor de endereços, informações como grau e lista de adjacências.
    list<No>::iterator i;
    vector<No*> enderecos(qtd_De_Nos);
    int k = 0;
    for(i = Nos.begin(); i != Nos.end(); i++)
    {
        enderecos[k] = &*i;
        k++;
    }

    queue<int> fila;
    fila.push(0);
    visitados[0] = true;
    int id, grau;
    int *adjacencias;
    while(!fila.empty())
    {
        id = fila.front();
        fila.pop();
        No* pont = enderecos[id];
        adjacencias = pont->lista_Adjacencias();
        grau = pont->get_Grau_No();
        for(int k = 0; k < grau; k++)
        {
            int indice = get_Indice(adjacencias[k]);
            if(visitados[indice] == false)
            {
                visitados[indice] = true;
                fila.push(indice);
            }
        }
    }

    for(int i = 0; i < qtd_De_Nos ; i++)
        if(visitados[i] == false)
            return false;

    return true;
}


/********************************************//**
 * \Verifica se dois nós estão na mesma componente conexa.
 *
 * \Parâmetro: id1 é o nó de onde será iniciada a busca para verificação.
 * \Parâmetro: id2 é o nó que se quer saber se está na mesma componente de id1.
 * \Retorna um booleano que indica se os nós estão na mesma componente.
 *
 * A função segue procedimento semelhante para a verificação se o grafo é conexo.
 * A diferença é que a comparação no vetor de visitados vai ser referente ao indice do nó id2.
 * Caso essa posição no vetor tenha true significa que id2 é alcançável de id1 e eles estão conectados.
 * Se conter false, não é alcançável.
 ***********************************************/
bool Grafo::verifica_Nos_Conectados(int id1,int id2)
{
    bool *visitados = new bool[qtd_De_Nos];
    for(int i = 0; i < qtd_De_Nos; i++)
        visitados[i] = false;

    ///< Vetor auxiliar de endereços de nós é criado para facilitar acessos à informações dos nós,
    ///< já que os índices desse vetor foram mapeados de acordo com os índices da lista e dos outros
    ///< vetores auxiliares(nível e predecessor).
    ///< Em suma, os id's reias dos nós não são os indices que são acesssados, mas com o indíce é
    ///< possível saber, através do vetor de endereços, informações como grau e lista de adjacências.
    vector<No*> enderecos(qtd_De_Nos);
    list<No>::iterator it;
    int k = 0;
    for(it = Nos.begin(); it != Nos.end(); it++)
    {
        enderecos[k] = &*it;
        k++;
    }

    int aux_id1 = get_Indice(id1);
    queue<int> fila;
    fila.push(aux_id1);
    visitados[aux_id1] = true;
    int id, grau;
    int *adjacencias;
    while(!fila.empty())
    {
        id = fila.front();
        fila.pop();

        No* pont = enderecos[id];

        adjacencias = pont->lista_Adjacencias();
        grau = pont->get_Grau_No();
        for(int k = 0; k < grau; k++)
        {
            int indice = get_Indice(adjacencias[k]);
            if(visitados[indice] == false)
            {
                visitados[indice] = true;
                fila.push(indice);
            }
        }
    }

    ///< Retorna o valor lógico presente na posição do nó no vetor de visitados.
    int aux_id2 = get_Indice(id2);
    return visitados[aux_id2];
}


/********************************************//**
 * \Verifica se a remoção de um nó do grafo aumenta o número de componentes conexas.
 *
 * \Parâmetro: id do nó que se deseja saber ser ou não de articulação.
 * \Retorna um booleano indicando se o nó passado como parâmetro é ou não de articulação.
 *
 * É calculado primeiramente a quantidade de componentes conexas.
 * A lista de adjacências do nó é salva e então se remove o nó do grafo.
 * Mais uma vez é calculado o numero de componenentes.
 * Informações são reinseridas no grafo e se compara o primeiro com o segundo valor calculado de componentes.
 ***********************************************/
bool Grafo::verifica_No_Articulacao(int id)
{
    int componentes_antes = componentes_Conexas();

    No* articulacao = get_Endereco(id);
    int grau = articulacao->get_Grau_No();
    aux_Aresta* info = articulacao->copia_Arestas();

    exclui_No(id);
    int componentes_depois = componentes_Conexas();

    ///< Reinserção dos dados.
    for(int j = 0; j < grau; j++)
        aux_Insere_Aresta(id,info[j].destino,info[j].peso);

    ///> Se os valores das componentes que foram calculados são diferentes pode-se dizer que o nó é de articulação ou não
    return (componentes_antes != componentes_depois);
}


/********************************************//**
 * \Verifica se uma aresta aumenta o número de componentes conexas.
 *
 * \Parâmetro: id1 corresponde à um endpoint da aresta/arco.
 * \Parâmetro: id2 corresponde à outro endpoint da aresta/arco.
 * \Retorna um booleano indicando se a aresta/arco passada(o) como parâmetro é ou não uma aresta/arco ponte.
 *
 * É calculado primeiramente a quantidade de componentes conexas.
 * As informações da aresta/arco são salvas e então se remove a aresta/arco do grafo.
 * Mais uma vez é calculado o numero de componenentes.
 * Informações são reinseridas no grafo e se compara o primeiro com o segundo valor calculado de componentes.
 ***********************************************/
bool Grafo::verifica_Aresta_Ponte(int id1, int id2)
{
    int componentes_antes = componentes_Conexas();
    No* aux_id1 = get_Endereco(id1);
    aux_Aresta* info = aux_id1->copia_Uma_Aresta(id2);

    exclui_Aresta(id1,id2);

    int componentes_depois = componentes_Conexas();
    aux_Insere_Aresta(id1,id2,info[0].peso);

    return (componentes_antes != componentes_depois);
}


/********************************************//**
 * \Retorna a Vizinhaça aberta do nó.
 *
 * \Parâmetro: id do nó que se quer saber a vizinhaça aberta.
 * \Retonra um vetor contendo a vizinhaça aberta.
 *
 * A lista de nós é percorridae até se encontrar o nó desejado.
 * Então é retornada as adjacências do nó
 ***********************************************/
int* Grafo::vizinhaca_Aberta(int id)
{
    list<No>::iterator i;
    for(i = Nos.begin(); i != Nos.end(); i++)
    {
        if(i->get_Id() == id)
            return i->lista_Adjacencias();
    }
    return NULL;
}


/********************************************//**
 * \Retorna a vizinhaça fechada de um nó.
 *
 * \Parâmetro: id é o nó que se quer saber a vizinhaça fechada.
 * \Retorna um vetor contendo a vizinhaça fechada.
 *
 * A lista de nós é percorrida até se encontrar o nó desejado.
 * Um vetor de tamanho grau de id + 1 é criado, já que a vizinhaça fechada contém o próprio nó.
 * Então é retornada o vetor.
 ***********************************************/
int* Grafo::vizinhaca_Fechada(int id)
{
    if(existe_No(id))
    {
        list<No>::iterator i;
        int* vizinhos;
        for(i = Nos.begin(); i != Nos.end(); i++)
        {
            if(i->get_Id() == id)
            {
                vizinhos = i->lista_Adjacencias();
                break;
            }
        }
        int grau = i->get_Grau_No();
        cout << grau << endl;
        int* vizinhaca_fechada = new int[grau + 1];
        vizinhaca_fechada[0] = id;

        for(int j = 0; j < grau; j++)
            vizinhaca_fechada[j + 1] = vizinhos[j];

        return vizinhaca_fechada;
    }
    else
        return NULL;
}


/********************************************//**
 * \Retorna uma lista com id's dos nós que são alcançáveis a partir do nó passado.
 *
 * \Parâmetro: id é o nó a partir do qual se quer saber o Fechamento transitivo direto.
 * \Retorna uma lista como resultado da execução da função.
 *
 * É feita uma busca em largura que tem como raiz o nó id passado como parâmetro.
 * No final do procedimento, os índices no vetor de visitados que foram marcados com true quer dizer que são atingiveis a partir da raiz.
 * Os respectivos nós são adicionados à lista que será retornada.
 ***********************************************/
list<int> Grafo::fechamento_Transitivo_Direto(int id)
{
    bool *visitados = new bool[qtd_De_Nos];
    for(int i = 0; i < qtd_De_Nos; i++)
        visitados[i] = false;


    ///< Vetor auxiliar de endereços de nós é criado para facilitar acessos à informações dos nós,
    ///< já que os índices desse vetor foram mapeados de acordo com os índices da lista e dos outros
    ///< vetores auxiliares(nível e predecessor).
    ///< Em suma, os id's reias dos nós não são os indices que são acesssados, mas com o indíce é
    ///< possível saber, através do vetor de endereços, informações como grau e lista de adjacências.
    list<No>::iterator i;
    vector<No*> enderecos(qtd_De_Nos);
    int k = 0;
    for(i = Nos.begin(); i != Nos.end(); i++)
    {
        enderecos[k] = &*i;
        k++;
    }
    queue<int> fila;
    int aux = get_Indice(id);
    fila.push(aux);
    visitados[aux] = true;
    int aux_id, grau;
    int *adjacencias;
    while(!fila.empty())
    {
        aux_id = fila.front();
        fila.pop();

        No* pont = enderecos[aux_id];

        adjacencias = pont->lista_Adjacencias();
        grau = pont->get_Grau_No();
        for(int k = 0; k < grau; k++)
        {
            int indice = get_Indice(adjacencias[k]);
            if(visitados[indice] == false)
            {
                visitados[indice] = true;
                fila.push(indice);
            }
        }
    }
    int tam = 0;
    for(int i = 0; i < qtd_De_Nos; i++)
        if(visitados[i])
            tam++;

    list<int> ftd;
    for(int i = 0; i < qtd_De_Nos; i++)
    {
        if(visitados[i])
        {
            No* aux = enderecos[i];
            int wt = aux->get_Id();
            ftd.push_back(wt);
        }
    }
    return ftd;
}


/********************************************//**
 * \Retorna os nós que conseguem alcançar um determinado nó.
 *
 * \Parâmetro: id do nó que se quer obter o fechamento indireto.
 * \Retorna uma lista com o resultado
 *
 * Caso o grafo não seja direcioando, o fechamento transitivo direto terá os mesmos valores que o intransitivo.
 * Se for direcionado o algoritmo usa uma matriz de alcançabilidade para marcar se o vértice com id j é alcançável de i.
 * Por fim, os id's da coluna do índice que satisfazem a condição são inseridos na lista.
 ***********************************************/
list<int> Grafo::fechamento_Transitivo_Indireto(int id)
{
    if(!flag_Direcionado)
        return fechamento_Transitivo_Direto(id);
    else
    {
        bool matriz[qtd_De_Nos][qtd_De_Nos];
        for(int i = 0; i < qtd_De_Nos; i++)
            for(int j = 0; j < qtd_De_Nos; j++)
                matriz[i][j] = false;

        ///< Vetor auxiliar de endereços de nós é criado para facilitar acessos à informações dos nós,
        ///< já que os índices desse vetor foram mapeados de acordo com os índices da lista e dos outros
        ///< vetores auxiliares(nível e predecessor).
        ///< Em suma, os id's reias dos nós não são os indices que são acesssados, mas com o indíce é
        ///< possível saber, através do vetor de endereços, informações como grau e lista de adjacências.
        vector<No*> enderecos(qtd_De_Nos);
        int k = 0;
        list<No>::iterator i;
        for(i = Nos.begin(); i != Nos.end(); i++)
        {
            enderecos[k] = &*i;
            k++;
        }
        for(int i = 0; i < qtd_De_Nos; i++)
            for(int j = 0; j < qtd_De_Nos; j++)
            {
                No* pont = enderecos[i];
                No* pont2 = enderecos[j];
                matriz[i][j] = pont->encontra_Adjacente(pont2->get_Id());
            }

        for(int k = 0; k < qtd_De_Nos; k++)
            for(int i = 0; i < qtd_De_Nos; i++)
                for(int j = 0; j < qtd_De_Nos; j++)
                    matriz[i][j] = matriz[i][j] || (matriz[i][k] && matriz[k][j]);

        list<int> fti;
        int indice = get_Indice(id);
        for(int i = 0; i < qtd_De_Nos; i++)
        {
            if(matriz[i][indice])
            {
                No* pont = enderecos[i];
                fti.push_back(pont->get_Id());
            }
        }
        return fti;
    }
}


/********************************************//**
 * \A função monta a DAG de um digrafo.
 *
 * \Retorna vector com a ordenação topológica.
 *
 * A função utiliza de busca em largura para preencher a lista ordenada da DAG, empurra para a solução apenas os nos foram visitaos por
 * aqueles que os atingem.
 ***********************************************/
vector<int> Grafo::ordenacao_Topologica()
{
    vector<int>* grau_entrada[qtd_De_Nos];
    for(int i = 0; i < qtd_De_Nos; i++)
        grau_entrada[i] = 0;

    vector<No*> enderecos(qtd_De_Nos);
    int k = 0;
    list<No>::iterator it;
    for(it = Nos.begin(); it != Nos.end(); it++)
    {
        enderecos[k] = &*it;
        k++;
    }
    for(int i = 0; i < qtd_De_Nos; i++)
    {
        No*aux = enderecos[i];
        int* lista = aux->lista_Adjacencias();
        int grau = aux->get_Grau_No();
        for(int j = 0; j < grau; j++)
        {
            int any = lista[j];
            any = get_Indice(any);
            grau_entrada[any]++;
        }
    }

    queue<int> fila;
    for (int i = 0; i < qtd_De_Nos; i++)
        if (grau_entrada[i] == 0)
            fila.push(i);

    vector<int> ord_top;

    while(!fila.empty())
    {
        int u = fila.front();
        fila.pop();
        No* aux = enderecos[u];
        ord_top.push_back(aux->get_Id());
        int *adjacencias = aux->lista_Adjacencias();
        int grau = aux->get_Grau_No();
        for(int j = 0; j < grau; j++)
        {
            int aux_indice = adjacencias[j];
            aux_indice = get_Indice(aux_indice);
            if(--grau_entrada[aux_indice] == 0)
                fila.push(aux_indice);
        }
    }
    return ord_top;
}


/********************************************//**
 * \Calcula o menor caminho entre dois nós.
 *
 * \Parâmetro: id1 é o nó de onde vai se iniciar a busca.
 * \Parâmetro: id2 ó o nó que vai se verificar a distancias após a procura.
 * \Retorna a menor distâncias entre os nós.
 *
 * O algoritmo mantém um array para as distâncias e um array de visitados.
 * As distâncias são iniciadas com infinito.
 * Distância da raiz setada pra zero.
 *
 ***********************************************/
int Grafo::Dijkstra(int id1, int id2)
{
    float distancias[qtd_De_Nos];
    bool visitados[qtd_De_Nos];

    ///< Vetor auxiliar de endereços de nós é criado para facilitar acessos à informações dos nós,
    ///< já que os índices desse vetor foram mapeados de acordo com os índices da lista e dos outros
    ///< vetores auxiliares(nível e predecessor).
    ///< Em suma, os id's reias dos nós não são os indices que são acesssados, mas com o indíce é
    ///< possível saber, através do vetor de endereços, informações como grau e lista de adjacências.
    vector<No*> enderecos(qtd_De_Nos);

    list<No>::iterator it;
    it = Nos.begin();
    for(int i = 0; i < qtd_De_Nos; i++)
    {
        ///< Distâncias inicializadas com infinito.
        distancias[i] = std::numeric_limits<float>::max();
        visitados[i] = false;
        enderecos[i] = &*it;
        it++;
    }
    int indice1 = get_Indice(id1);

    ///< Distância da raiz recebe 0.
    distancias[indice1] = 0;
    for(int i = 0; i < qtd_De_Nos - 1; i++)
    {
        ///< u recebe o indice da menor distância no vetor de Distâncias.
        int u = indice_Menor_Distancia(distancias,visitados);
        visitados[u] = true;

        No*pont = enderecos[u];
        int grau = pont->get_Grau_No();
        aux_Aresta* adjacencias = pont->copia_Arestas();

        for(int j = 0; j < grau; j++)
        {
            int aux_indice = adjacencias[j].destino;
            aux_indice = get_Indice(aux_indice);

            if(visitados[aux_indice] == false && distancias[u] != std::numeric_limits<float>::max())
            {
                ///< Altera a distância se o adjacente não foi visitado e se há uma aresta que e
                ///< somada à atual distâncias seja menor que o valor da distancia atual para o adjacente.
                if(distancias[u] + adjacencias[j].peso < distancias[aux_indice])
                    distancias[aux_indice] = distancias[u] + adjacencias[j].peso;

            }
        }
    }
    ///< Retorna a distância de id1 para id2;
    return distancias[get_Indice(id2)];
}


/********************************************//**
 * \brief Algoritmo de floyd
 *\par Id do nó onde será gerado floyd
 * \return    Retorna um vetor com as menores distancias que o no id possui para os demais nos do grafo
 *
 * O algoritmo calcula, para cada par de vértices, o menor de todos os caminhos entre os vértices.
 ***********************************************/
int** Grafo::Floyd()
{

    vector<int> listaAux;
    int iteratorVector = 0;

    list<No>::iterator i;
    int id;
    i = Nos.begin();

    int vizinhos;
    id = i->get_Id();
    Aresta* auxiliar;
    int auxiliar1 = 0;
    int auxiliar2 = 0;
    int x = 10*get_Qtd_Nos();
    int** listaIds = new int*[x];

    for(int i = 0; i<x; i++)
    {
        listaIds[i] = new int[x];
    }

    for(i = Nos.begin(); i != Nos.end(); i++)
    {
        auxiliar2 = 0;
        list<No>::iterator j;
        for(j = Nos.begin(); j != Nos.end(); j++)
        {

            if(j->get_Id()!=i->get_Id())
            {

                if((verifica_Nos_Conectados(i->get_Id(),j->get_Id()))== true)
                {


                    listaIds[auxiliar1][auxiliar2] = j->get_Aresta_Peso(i->get_Id());



                }else{

                    listaIds[auxiliar1][auxiliar2] = 99999999;

                }
            }else{

                listaIds[auxiliar1][auxiliar2] = 0;

            }


            auxiliar2++;
        }

        auxiliar1++;


    }



    auxiliar1 = 0;
    auxiliar2 = 0;
    int auxiliar3 = 0;
    Aresta* auxiliar4;
    list<No>::iterator k;

    for(k = Nos.begin(); k != Nos.end(); k++)
    {
        auxiliar2 = 0;
        for(i = Nos.begin(); i != Nos.end(); i++)
        {
            auxiliar3 = 0;
            list<No>::iterator j;
            for(j = Nos.begin(); j != Nos.end(); j++)
            {

                if(j->get_Id()!=i->get_Id())
            {


                if(verifica_Nos_Conectados(i->get_Id(),k->get_Id())==true &&verifica_Nos_Conectados(k->get_Id(),j->get_Id())==true)
                {


                    if(auxiliar1!=auxiliar2)
                    {

                        if(listaIds[auxiliar2][auxiliar3] > (i->get_Aresta_Peso(k->get_Id())+k->get_Aresta_Peso(j->get_Id())))
                        {

                            listaIds[auxiliar2][auxiliar3] = (i->get_Aresta_Peso(k->get_Id())+k->get_Aresta_Peso(j->get_Id()));
                        }


                    }

                }

                auxiliar3++;
            }}
            auxiliar2++;
        }
        auxiliar1++;
    }
    return listaIds;
}


/********************************************//**
 * \Retorna o sub-grafo induzido nos vértoces passados.
 *
 * \O parâmetro lista[] representa os ids dos nos que deverão estar no sub-grafo induzido.
 * \O parâmetro tam, guarda o tamanho do vetor lista[].
 * \A função retorna o sub-grafo induzido.
 *
 * A função cria um grafo que represntará o subgrafo induzido a partir dos vértices contidos na lista.
 ***********************************************/
Grafo* Grafo::sub_Grafo_Induzido(int lista[], int tam)
{
    Grafo* grafo = new Grafo();
    ///< Inclui no novo grafo os nós presentes na lista.
    for(int i = 0; i < tam; i++)
    {
        if(existe_No(lista[i]))
        {
            grafo->insere_No(lista[i]);
        }
    }

    ///< Insere no grafo arestas/arcos existentes entre os nós da lista.
    for(int i = 0; i < tam; i++)
    {
        for(int j = 0; j < tam; j++)
        {
            ///< Condição que verifica se os nós são de fato adjacentes e se essa aresta/arco ja foi inserida ou não.
            if(verifica_Adjacentes(lista[i],lista[j]) && !grafo->verifica_Adjacentes(lista[i],lista[j]))
            {
                if(flag_Ponderado)
                {
                    No* aux = get_Endereco(lista[i]);
                    float peso = aux->get_Aresta_Peso(lista[j]);
                    grafo->aux_Insere_Aresta(lista[i],lista[j],peso);
                }
                else
                {
                    grafo->aux_Insere_Aresta(lista[i],lista[j],1.0);

                }
            }
        }
    }
    return grafo;
}


/********************************************//**
 * \Função responsável por retornar componentes conexas do grafo.
 *
 *
 * \Retorna uma lista de componenetes conexas do Grafo original
 *
 * A função percorre o grafo contando e separando em diferentes indíces as componentes conexas do grafo e as retornando em forma de lista de grafos.
 ***********************************************/
Grafo* Grafo::get_Componentes_Conexas()
{
    bool *visitados = new bool[qtd_De_Nos];
    for(int i = 0; i < qtd_De_Nos; i++)
        visitados[i] = false;

    vector<No*> enderecos(qtd_De_Nos);
    list<No>::iterator it;
    int k = 0;
    for(it = Nos.begin(); it != Nos.end(); it++)
    {
        enderecos[k] = &*it;
        k++;
    }

    Grafo* grafos_componentes = new Grafo[componentes_Conexas()];
    queue<int> fila;
    int componentes = 0;
    int aux_indice;
    for(int i = 0; i < qtd_De_Nos; i++)
    {
        if(visitados[i] == false)
        {
            componentes++;
            fila.push(i);
            visitados[i] = true;
            int id, grau;
            int *adjacencias;
            aux_indice = componentes - 1;
            grafos_componentes[aux_indice].set_Direcionado(flag_Direcionado);
            grafos_componentes[aux_indice].set_Ponderado(flag_Ponderado);

            while(!fila.empty())
            {
                id = fila.front();
                fila.pop();
                No* pont = enderecos[id];
                grau = pont->get_Grau_No();
                adjacencias = pont->lista_Adjacencias();

                if(grau  == 0)
                {
                    grafos_componentes[aux_indice].insere_No(pont->get_Id());
                }
                for(int j = 0; j < grau; j++)
                {
                    int indice = get_Indice(adjacencias[j]);
                    float peso = pont->get_Aresta_Peso(enderecos[indice]->get_Id());

                    if(verifica_Adjacentes(pont->get_Id(),enderecos[indice]->get_Id()) && !grafos_componentes[aux_indice].verifica_Adjacentes(pont->get_Id(),enderecos[indice]->get_Id()))
                        grafos_componentes[aux_indice].aux_Insere_Aresta(pont->get_Id(), enderecos[indice]->get_Id(), peso);
                    if(visitados[indice] == false)
                    {
                        visitados[indice] = true;
                        fila.push(indice);
                    }
                }

        }
        }
    }
    return grafos_componentes;
}


/********************************************//**
 * \brief ALgoritmo de prim
 *
 * \return Arvore geradora mínima
 *
 * Irá adicionar a aresta de menor peso do grafo e os respectivos nos. A partir disto, ira adicionar a menor aresta do grafo que ligue um no do grafo até um nó nao pertencente ao graafo naquele momento.
 ***********************************************/
Grafo* Grafo::Prim()
{
    vector<int> listaAux;
    Grafo* g = new Grafo();
    if(verifica_Conexo()==true)
    {
        list<No>::iterator i;
        int id;
        i = Nos.begin();
        int* t = i->lista_Adjacencias();
        Aresta *a = i->get_Endereco_Aresta(t[0]);
        int vizinhos;
        id = i->get_Id();
        Aresta* auxiliar;
        for(i = Nos.begin(); i != Nos.end(); i++)
        {
            t = i->lista_Adjacencias();

            for(int j = 0; j < i->get_Grau_No(); j++)
            {
                auxiliar = i->get_Endereco_Aresta(t[j]);
                if(auxiliar->get_Peso()<=a->get_Peso())
                {
                    a = auxiliar;
                    id = i->get_Id();
                }
            }

        }
        int y = g->get_Qtd_Nos();

        listaAux.push_back(id);


        g->insere_No(id);



        g->insere_No(a->get_Destino());
        g->insere_Aresta(id,a->get_Destino(),a->get_Peso());
        int id2;
        Aresta a2;


        while(listaAux.size()+1<get_Qtd_Nos())
        {
            int peso = 9999999;
            for(i = Nos.begin(); i != Nos.end(); i++)
            {
                if(std::find(listaAux.begin(), listaAux.end(), i->get_Id()) != listaAux.end())
                {
                    cout << " teste id: "<< i->get_Id()<<endl;
                    t = i->lista_Adjacencias();

                    for(int j = 0; j < i->get_Grau_No(); j++)
                    {
                        if(std::find(listaAux.begin(), listaAux.end(), t[j]) != listaAux.end())
                        {
                            cout << " ok"<< endl;
                        }
                        else
                        {
                            auxiliar = i->get_Endereco_Aresta(t[j]);
                            if(auxiliar->get_Peso()<peso)
                            {
                                a = auxiliar;
                                peso = a->get_Peso();
                                id = i->get_Id();
                            }
                        }
                    }

                }

            }
            cout << " teste id2: "<< a->get_Destino()<<endl;
            listaAux.push_back(a->get_Destino());

            g->insere_No(a->get_Destino());
            g->insere_Aresta(id,a->get_Destino(),a->get_Peso());
        }

    }
    else
    {
        cout << "PRIM FALHOU. GRAFO NAO CONEXO" << endl;
        exit(2);
    }
    return g;

}


/********************************************//**
 * \brief Algoritmo de kruskal
 *
 * \return    Arvore geradora de custo mínimo
 *
 * O algoritmo ira gerar uma floresta com todos os nos do grafo original, sem nenhuma aresta. Irá analisar todas as arestas do grafo. Se ela conecta é mínima para aquele momento e conecta duas árvores,
 *adiciona a aresta e junta as arvores. Senão, descarte a aresta. Irá repetir enquanto existirem arestas disponíveis.
 ***********************************************/
Grafo* Grafo::Kruskal()
{

    vector<Aresta*> listaAux, listaAux1;
    Grafo* g = new Grafo();
    list<No>::iterator i;
    for(i = Nos.begin(); i != Nos.end(); i++)
    {

        g->insere_No(i->get_Id());

    }


    int id;
    i = Nos.begin();
    int* t = i->lista_Adjacencias();
    Aresta *a = i->get_Endereco_Aresta(t[0]);
    int vizinhos;
    id = i->get_Id();
    Aresta* auxiliar;

    for(i = Nos.begin(); i != Nos.end(); i++)
    {

        t = i->lista_Adjacencias();
        int pesoAux = 999999999;
        for(int j = 0; j < i->get_Grau_No(); j++)
        {
            auxiliar = i->get_Endereco_Aresta(t[j]);

            if(auxiliar->get_Peso()<pesoAux)
            {

                a = auxiliar;
                pesoAux = a->get_Peso();
                id = i->get_Id();

            }
        }


    }
    listaAux1.push_back(a);

    g->insere_Aresta(id,a->get_Destino(),a->get_Peso());
    int id2;
    Aresta a2;
    int contador  = 0;


    while(contador+1<=get_Qtd_Nos())
    {
        int peso = 9999999;
        int flag = 0;
        for(i = Nos.begin(); i != Nos.end(); i++)
        {

            t = i->lista_Adjacencias();

            for(int j = 0; j < i->get_Grau_No(); j++)
            {
                if(g->verifica_Nos_Conectados(t[j],i->get_Id() )==false && g->verifica_Nos_Conectados(i->get_Id(),t[j] )==false)
                {
                    auxiliar = i->get_Endereco_Aresta(t[j]);
                    if(std::find(listaAux1.begin(), listaAux1.end(), auxiliar) != listaAux1.end())
                    {

                    }
                    else
                    {

                        if(auxiliar->get_Peso()<=peso)
                        {
                            flag = 1;
                            a = auxiliar;
                            peso = a->get_Peso();
                            id = i->get_Id();
                        }
                    }
                }

            }
        }
        if(flag ==1)
        {
            listaAux1.push_back(a);

            g->insere_Aresta(id,a->get_Destino(),a->get_Peso());
        }

        contador ++;
    }
    return g;
}


/********************************************//**
 * \Verifica a Kconexividade do grafo.
 *
 * \
 * \
 * \Retorno de um bool que representa a veracidade da KConexidade.
 *
 * VOLTAR AQUI DEPOIS
 ***********************************************/
bool Grafo::verificar_KConexidade()
{
    if(verifica_Conexo() == true)
    {
        if (verifica_Completo() == true)
            return true;

        else
        {
            cout << "Nao foi possivel verificar se o grafo é k-conexo" << endl;
            exit(1);
        }
    }
    else
        return false;
}



/********************************************//**
 * \Consulta a possibilidade do grafo ser euleriano.
 *
 * Retorna um bool que responde se o grafo é ou não é euleriano.
 *
 * Verifica se grafo é euleriano.
 ***********************************************/
bool Grafo::verifica_Euleriano()
{
    list<No>::iterator i;
    for(i = Nos.begin(); i != Nos.end(); i++)
    {
        if(i->get_Grau_No()%2 != 0)
            return false;
        i++;
    }
    return true;
}


/********************************************//**
 * \Imprime o grafo.
 *
 * \Sem valor de retorno.
 *
 * Imprime os nos e seus respectivos adjacentes.
 ***********************************************/
void Grafo::imprime()
{
    list<No>::iterator i;
    for(i = Nos.begin(); i != Nos.end(); i++)
    {
        cout << i->get_Id() << " :";
        i->imprime_Adjacentes();
    }
}


/********************************************//**
 * Escreve o grafo atual em um arquivo .txt.
 *
 *
 * \Sem valor retorno.
 *
 * Escrevemos todos os nós e suas adjacências (atuais) em um arquivo de texto juntamente com os pesos dessas arestas/arcos.
 ***********************************************/
void Grafo::escreve_Grafo()
{
    ofstream outputFile;
    outputFile.open("GrafoFinal.txt");
    outputFile << "Grafo Final:\n";
    outputFile << qtd_De_Nos<< "\n";
    outputFile << flag_Direcionado << "\n";
    outputFile << flag_Ponderado << "\n";
    list<No>::iterator it;
    it = Nos.begin();
    while(it != Nos.end())
    {
        int *adjacencias = it->lista_Adjacencias();
        if(flag_Ponderado)
        {
            int *pesos = it->lista_Peso();
            for(int i = 0; i < it->get_Grau_No(); i++)
                outputFile << it->get_Id() << "  " <<  adjacencias[i] << "  " << pesos[i] << endl;
        }
        else
        {
            for(int i = 0; i < it->get_Grau_No(); i++)
                outputFile << it->get_Id() << "  " << adjacencias[i] << endl;
        }
        it++;
    }
    outputFile.close();
}


/********************************************//**
 * \Retorna o grau do grafo
 *
 * \Retorna um inteiro com o valor do grau do grafo.
 *
 * Retorna um inteiro contendo o valor do maior grau entre os nos do grafo.
 ***********************************************/
int Grafo::get_Grau_Grafo()
{
    list<No>::iterator i;
    int grau = 0;
    for(i = Nos.begin(); i != Nos.end(); i++)
    {
        if(i->get_Grau_No() > grau)
            grau = i->get_Grau_No();
    }
    return grau;
}


/********************************************//**
 * \Retorna a quantiade de arestas/arcos contidas no grafo.
 *
 * \Retorna um inteiro com o valor equivalente a quantidade de arestas/arcos no grafo.
 *
 * Função percorre o grafo contando as arestas/arcos através dos graus dos nos.
 * Se o grafo não for direcionado o valor achado é dividido por 2 e retornado.
 ***********************************************/
int Grafo::get_Qtd_Arestas()
{
    int cont = 0;
    list<No>::iterator i;
    for(i = Nos.begin(); i != Nos.end(); i++)
        cont += i->get_Grau_No();

    if(!flag_Direcionado)
        return cont/2;
    else
        return cont;
}


/********************************************//**
 * \Retorna a quantidade de nós.
 *
 * Retorna um inteiro com valor igual a quantidade de nos do grafo.
 *
 * Função retorna a variável qtd_De_Nos que contém a quantidade de nos existentes no grafo.
 ***********************************************/
int Grafo::get_Qtd_Nos()
{
    return qtd_De_Nos;
}


/********************************************//**
 * \Calcula o número de componentes conexas.
 *
 * \Retorna a quantidade de componentes conexas.
 *
 * Ininializa um vetor de visitados com false e mantém uma variável que conta as componentes.
 * Para casa posição com false no vetor de visitados é realizada uma busca em largura.
 ***********************************************/
int Grafo::componentes_Conexas()
{
    bool *visitados = new bool[qtd_De_Nos];
    for(int i = 0; i < qtd_De_Nos; i++)
        visitados[i] = false;

    ///< Vetor auxiliar de endereços de nós é criado para facilitar acessos à informações dos nós,
    ///< já que os índices desse vetor foram mapeados de acordo com os índices da lista e dos outros
    ///< vetores auxiliares(nível e predecessor).
    ///< Em suma, os id's reias dos nós não são os indices que são acesssados, mas com o indíce é
    ///< possível saber, através do vetor de endereços, informações como grau e lista de adjacências.
    vector<No*> enderecos(qtd_De_Nos);
    list<No>::iterator it;
    int k = 0;
    for(it = Nos.begin(); it != Nos.end(); it++)
    {
        enderecos[k] = &*it;
        k++;
    }
    cout << "Teste "<< endl;
    queue<int> fila;
    int componentes = 0;
    for(int i = 0; i < qtd_De_Nos; i++)
    {
        ///< Se algum índice ainda não foi visitado é realizada uma busca em profundidade a partir desse nó,
        ///< que irá marcar como visitado todos os nós que são atingivéis a partir dele.
        if(visitados[i] == false)
        {
            ///< Se entrou aqui, significa que o número de componentes tem que ser incrementado.
            componentes++;
            fila.push(i);
            visitados[i] = true;
            int id, grau;
            int *adjacencias;

            while(!fila.empty())
            {
                id = fila.front();
                fila.pop();

                No* pont = enderecos[id];
                grau = pont->get_Grau_No();
                adjacencias = pont->lista_Adjacencias();

                for(int j = 0; j < grau; j++)
                {
                    int indice = get_Indice(adjacencias[j]);
                    if(visitados[indice] == false)
                    {
                        visitados[indice] = true;
                        fila.push(indice);
                    }
                }
            }
        }
    }
    ///< Retorna o valor encontrado. que representa a quantidade de componentes conexas.
    return componentes;
}


/********************************************//**
 * \ Funcão para construção de uma solução para o problema de conjunto dominante mínimo com peso.
 *
 * \Parâmetro: Alpha,para ajuste do fator randômico da heurística.
 * \Retorna o valor de solução para o problema proposto
 *
 * Inicialmente, todos os ids dos nós são copiados para uma estrutura auxiliar. Dois casos em particular são analisados: se o grau do nó é 0,
 * ele estará na solução; se o grau do nó é 1, é avaliado o melhor custo benefício para se incluir na solução, ele ou seu vizinho.
 * Ao final, repete-se até encontrar a solução:  o nó de melhor custo benefício(grau do no dividido por seu peso) é inserido na solução.
 ***********************************************/

int Grafo::aux_Conjunto_Dominante_Minimo(float alpha)
{


    list<No>::iterator i;
    int contador = 0;
    int contadorAux = 0;



    list<int> listaAux;







    for(i = Nos.begin(); i != Nos.end(); i++)
    {

        listaAux.push_back(i->get_Id());

        i->set_Grau_No_Heuristica();
        if(i->get_Id()==(get_Qtd_Nos()-1))
        {

            break;
        }

    }


    int contador2 = 0;
    for(i = Nos.begin(); i != Nos.end(); i++)
    {
        if(i->get_Grau_No_Heuristica()==0)
        {
            contador += i->get_Peso_No();
            listaAux.remove(i->get_Id());
            exclui_No_Heuristica(i->get_Id());
        }
        else
        {
            if(i->get_Grau_No_Heuristica()==1)
            {
                int *lista = i->lista_Adjacencias();
                int* lista2;
                list<No>::iterator j;
                for(j = Nos.begin(); j != Nos.end(); j++)
                {
                    if(j->get_Id() == lista[0])
                    {
                        if(((i->get_Grau_No_Heuristica())/(i->get_Peso_No()))>((j->get_Grau_No_Heuristica())/(j->get_Peso_No())))
                        {
                            lista2 = j->lista_Adjacencias();
                            int t = j->get_Grau_No();
                            for(int k =0; k< t; k++)
                            {
                                if(std::find(listaAux.begin(), listaAux.end(), lista2[k]) != listaAux.end())
                                {
                                   listaAux.remove(lista2[k]);
                                    exclui_No_Heuristica(lista2[k]);
                                }
                            }
                            listaAux.remove(j->get_Id());
                            exclui_No_Heuristica(j->get_Id());
                            contador += j->get_Peso_No();
                        }
                        else
                        {
                            contador += i->get_Peso_No();
                            exclui_No_Heuristica(i->get_Id());
                            listaAux.remove(i->get_Id());
                        }
                    }
                }
                delete[]lista;
                delete[]lista2;
            }
        }
    }




    int tamanho = (int)(listaAux.size()*alpha);
    int posicao;

    while(!listaAux.empty())
    {
        tamanho = (int)(listaAux.size()*alpha);
        int aux2 = rand();


        int* vet = new int[listaAux.size()];


        int MaiorGrau;

        for(i = Nos.begin(); i != Nos.end(); i++)
        {

            if(i->get_Id() == listaAux.front())
            {
                MaiorGrau = (i->get_Grau_No_Heuristica()/i->get_Peso_No());
            }
        }

        for(int k = 0; k <= tamanho; k++)
        {
            vet[k]=listaAux.front();
        }


        for(i = Nos.begin(); i != Nos.end(); i++)
        {
            if(std::find(listaAux.begin(), listaAux.end(), i->get_Id()) != listaAux.end())
            {
                if((i->get_Grau_No_Heuristica()/i->get_Peso_No())>= MaiorGrau)
                {
                    MaiorGrau = (i->get_Grau_No_Heuristica()/i->get_Peso_No());
                    for(int k = tamanho; k>0; k--)
                    {
                        vet[k] = vet[k-1];
                    }
                    vet[0]=i->get_Id();
                }
            }
        }

        if(tamanho>0)
        {
            posicao = aux2%(tamanho);
        }else{posicao=0;}



        int *lista2;

        for(i = Nos.begin(); i != Nos.end(); i++)
        {
            if(i->get_Id() == vet[posicao])
            {
                lista2 = i->lista_Adjacencias();
                int t = i->get_Grau_No();

                for(int j =0; j< t; j++)
                {
                    if(std::find(listaAux.begin(), listaAux.end(), lista2[j]) != listaAux.end())
                    {


                        listaAux.remove(lista2[j]);


                        exclui_No_Heuristica(lista2[j]);


                    }
                }

                contador += i->get_Peso_No();
                exclui_No_Heuristica(i->get_Id());
                listaAux.remove(i->get_Id());

            }


        }


        delete[] vet;


    }



    listaAux.clear();


    return contador;
}

/********************************************//**
 * \Funcao de cálculo para o problema de conjunto dominante mínimo
 *
 * \Parâmetro: Alpha, ajuste do valor randomico da heurística.
 * \Parâmetro: Iteracoes, quantidade de iterações que deverao ser testadas.
 * \Parâmetro: Media, para cálculo da média das soluções.
 * \Retorna Best, o melhor valor de solução do problema.
 *
 * A função irá chamar iteração vezes a funcao aux_Conjunto_Dominante_Minimo. Ao final, irá identificar e  retornar o melhor resultado dentre essas iterações
 ***********************************************/
int Grafo::conjunto_Dominante_Minimo(float alpha, int iteracoes,float* media2)
{
    int vet[iteracoes];
    float matTempo[iteracoes];

    float media, desvio;
    int soma = 0;
    int best;

    for(int i = 0; i < iteracoes; i++)
    {

        float time1 = clock();


        vet[i] = aux_Conjunto_Dominante_Minimo(alpha);


        valor_Testes[num_Testes] = vet[i];

        num_Testes++;
        float time2 = clock();

        matTempo[i] = time2 - time1;

        if(i == 0)
        {
            best = vet[i];
        }
        else
        {
            if(best>vet[i])
            {
                best = vet[i];
            }
        }
    }

    for(int i = 0; i< iteracoes; i++)
    {
        soma +=vet[i];
    }
    media = soma/iteracoes;
    int parcial[iteracoes];
    for(int i = 0; i< iteracoes; i++)
    {
        parcial[i]= (vet[i]-media)*(vet[i]-media);
    }

    int somaFinal = 0;
    for(int i = 0; i < iteracoes; i++)
    {

        somaFinal += parcial[i];
    }

    desvio = sqrt(somaFinal/iteracoes);


    *media2 = media;

    /*cout << " A media para alpha "<< alpha << "e " << iteracoes << " iteracoes foi de: " << media << endl;
    cout << " O desvio padrao para alpha "<< alpha << "e " << iteracoes << " iteracoes foi de: " << desvio << endl;*/
    for(int i = 0; i< iteracoes; i++)
    {

        //cout << "Resultado com alpha " << alpha <<  " : " << vet[i] << "   Tempo de execução: " << matTempo[i] << endl;
    }
   // cout << "teste best :" << best << endl;
    return best;




}

/********************************************//**
 * \brief Função para teste da heurística gulosa
 *
 * \return    Não há retorno;
 *
 * A função chama a função conjunto dominante minimo com os parâmetros adequados
 ***********************************************/
void Grafo::teste_Heuristica_Gulosa()
{
    float* media =  new float();
    cout << " COMECO DO TESTE HEURISTICA GULOSA ----------------------------------------------------------------------" << endl << endl;

    int x = conjunto_Dominante_Minimo(0.0,1, media);
    cout<< "O RESULTADO FOI: "<<x<<endl;

    cout << " FIM DO TESTE HEURISTICA GULOSA ----------------------------------------------------------------------" << endl  << endl << endl;
}


/********************************************//**
 * \brief Função para teste da heurística gulosa randômica
 *
 * \return    Não há retorno;
 *
 * A função chama a função conjunto dominante minimo com os parâmetros adequados. Este processo irá se repetir até que o melhor resultado não se altere por 5 iterações.
 ***********************************************/
void Grafo::teste_Heuristica_Randomica()
{
    float* media =  new float();
    cout << " COMECO DO TESTE HEURISTICA GULOSA RANDOMICA ----------------------------------------------------------------------" << endl << endl;
    int contador = 0;
    int aux;
    int best = 9999999;
    while(contador<5)

    {
        contador ++;
        aux = conjunto_Dominante_Minimo(0.25,30,media);
        if(aux<best)
        {
            best = aux;
            contador = 0;
        }
    }
    cout << " O MELHOR VALOR FOI : " << best << endl;
    cout << " FIM DO TESTE HEURISTICA GULOSA RANDOMICA ----------------------------------------------------------------------" << endl  << endl << endl;

}


/********************************************//**
* \brief Função para teste da heurística gulosa randômica reativa
*
* \return    Não há retorno;
*
* A função chama a função conjunto dominante minimo com os parâmetros adequados. Este processo irá se repetir até que o melhor resultado não se altere por 25 iterações.
*O alpha de cada iteração é sorteado de acordo com um vetor de probabilidades, este sendo atualizado baseado nos resultados que cada alpha conseguiu em relação ao melhor resultado já encontrado.
***********************************************/
void Grafo::teste_Heuristica_Randomica_Reativa()
{
    float* media =  new float();
    cout << " COMECO DO TESTE HEURISTICA GULOSA RANDOMICA REATIVA ----------------------------------------------------------------------" << endl << endl;
    int contador = 0;
    float vetAlphas[10];
    float probabilisdadesAlpha[10];
    float primeiraProb = 0.05;
    for(int i= 0; i<10; i++)
    {
        probabilisdadesAlpha[i] = 0.1;
        vetAlphas[i] = primeiraProb + primeiraProb*i;
        cout<< vetAlphas[i]<< endl;
    }
    int aux;
    float auxSoma = 1;
    float auxAlpha2;
    float auxAlpha;
    float alpha;
    int flag = 0;
    int best = 9999999999;
    float q;
    float novaSomaProbabilidades = 0;
    int identificador;
    int vetSoma[10];
    int vetIteracao[10];
    for(int i = 0; i< 10; i++)
    {
        vetIteracao[i]=0;
        vetSoma[i] = 0;
    }

    while(contador<25)
    {
        flag = 0;
        novaSomaProbabilidades = 0;
        auxAlpha2 = (float)(rand()%101) ;
        auxAlpha = auxAlpha2*0.01;

        auxSoma = 1;
        flag = 0;
        for(int i= 9; i>=0; i--)
        {
            if(auxAlpha>(auxSoma-probabilisdadesAlpha[i])&& flag ==0)
            {
                alpha = vetAlphas[i];
                flag = 1;
                identificador = i;
            }
            auxSoma -= probabilisdadesAlpha[i];
        }
        contador ++;
        cout<<"alpha"<<alpha<<endl;
        aux = conjunto_Dominante_Minimo(alpha,30,media);
        vetIteracao[identificador]++;
        vetSoma[identificador]+=aux;
        if(aux<best)
        {
            best = aux;
            contador = 0;
        }
        q = best/(vetSoma[identificador]/vetIteracao[identificador]);
        probabilisdadesAlpha[identificador] = q;
        for(int i= 0; i<10; i++)
        {
            novaSomaProbabilidades+=probabilisdadesAlpha[i];
        }
        for(int i= 0; i<10; i++)
        {
            probabilisdadesAlpha[i] = probabilisdadesAlpha[i]/novaSomaProbabilidades;
        }


    }
    cout << " O MELHOR VALOR FOI : " << best << endl;
    cout << " FIM DO TESTE HEURISTICA GULOSA RANDOMICA REATIVA ----------------------------------------------------------------------" << endl  << endl << endl;
}


/********************************************//**
 * \brief Funcao verifica desvio padrao
 *
 * \return    Não há retorno.
 *
 * A função calcula o desvio padrão referentes a todos os testes rodados na execução do programa.
 ***********************************************/
void Grafo:: verifica_Desvio_Padrao()
{
    int soma = 0;
    int somaFinal = 0;
    int media;
    for(int i = 0; i < num_Testes; i++)
    {
        soma+= valor_Testes[i];
    }
    media = soma/num_Testes;
    for(int i = 0; i<num_Testes; i++)
    {
        somaFinal += (valor_Testes[i]-media)*(valor_Testes[i]-media);
    }
    cout << "O DEVIO PADRAO PARA TODOS OS TESTES DESTA INSTANCIA FOI: " << sqrt(somaFinal/num_Testes) << endl;

}

void Grafo::exclui_No_Heuristica(int id)
{
    list<No>::iterator i;
    if(i != Nos.end() && !flag_Direcionado)
    {
        for(i = Nos.begin(); i != Nos.end(); i++)
            if(verifica_Adjacentes(id, i->get_Id())==true)
                i->diminui_Grau_No_Heuristica();
    }
}


/********************************************//**
 *\Atribui valor a variável flag_direcionado.
 *
 *Essa função utiliza o parâmetro flag para atribuir a informação para flag_direcionado assim informando se o grafo em questão é direcionado
 *ou não
 ***********************************************/
void Grafo::set_Direcionado(bool flag)
{
    flag_Direcionado = flag;
}


/********************************************//**
 * \Atribui valor a variável flag_ponderado.
 *
 *Essa função utiliza o parâmetro flag para atribuir a informação para flag_ponderado assim informando se o grafo em questão é ponderado
 *ou não
 ***********************************************/
void Grafo::set_Ponderado(bool flag)
{
    flag_Ponderado = flag;
}


/********************************************//**
 * \Insere nova aresta/arco no Grafo.
 *
 * \Parâmetro: id1 corresponde a um dos nós da nova aresta/arco.
 * \Parâmetro: id2 corresponde a um dos nós da nova aresta/arco.
 * \Parâmetro: peso da nova aresta/arco.
 * \Sem valor de Retorno.
 *
 * Dado id1, id2 e peso, é criada uma nova aresta/arco entre esses dois nós. Caso não exista nós com respectivos id's eles serão criados.
 ***********************************************/
void Grafo::aux_Insere_Aresta(int id1,int id2,float peso)
{
    No* pont_id1 = 0;
    No* pont_id2 = 0;

    list<No>::iterator it;
    ///< Percorre a Lista de Nós e seta os ponteiros criados para os nós, caso existam.
    for(it = Nos.begin(); it != Nos.end(); it++)
    {
        if(it->get_Id() == id1)
            pont_id1 = &*it;
        if(it->get_Id() == id2)
            pont_id2 = &*it;
    }
    ///< Se o ponteiro ainda aponta para nulo, então passará a apontar para novo nó que será incluído no final da Lista de Nós.
    ///< Insere a aresta/arco na adjacencia do nó.
    ///< Aresta/arco id2-id1 é incluída se, e somente se, o grafo não for direcionado.
    if(pont_id1 == 0)
    {
        Nos.push_back(No(id1));
        pont_id1 = &Nos.back();
        pont_id1->add_Adjacente(id2,peso);
        qtd_De_Nos++;

        if(pont_id2 == 0)
        {
            Nos.push_back(No(id2));
            pont_id2 = &Nos.back();
            if(!flag_Direcionado)
                pont_id2->add_Adjacente(id1,peso);
            qtd_De_Nos++;
        }
        else
        {
            if(!flag_Direcionado)
                pont_id2->add_Adjacente(id1,peso);
        }
    }
    else
    {
        pont_id1->add_Adjacente(id2,peso);
        if(pont_id2 == 0)
        {
            Nos.push_back(No(id2));
            pont_id2 = &Nos.back();
            if(!flag_Direcionado)
                pont_id2->add_Adjacente(id1,peso);
            qtd_De_Nos++;
        }
        else
        {
            if(!flag_Direcionado)
                pont_id2->add_Adjacente(id1,peso);
        }
    }
}


/********************************************//**
 * \Retorna um endereço de no.
 *
 * \Parâmetro 'id' carrega o valor da identificação do no a ser achado.
 * \Retorna um ponteiro de no com endereço do vértice com id igual ao que foi passado como parâmetro.
 *
 * Procura pelo no com id igual ao que foi passado por parâmetro, quando achado, retorna o endereço desse no que foi achado.
 ***********************************************/
No* Grafo::get_Endereco(int id)
{
    list<No>::iterator i;
    for(i = Nos.begin(); i != Nos.end(); i++)
    {
        if(i->get_Id() == id)
            return &*i;
    }
    return 0;
}


/********************************************//**
 * \Função auxiliar do Dijkstra que retorna o indice da menor distâncias no vetor de Distâncias.
 *
 * \Parâmetro: vetor de distâncias.
 * \Parâmetro: vetor de visitados
 * \Retorna o indice da menor distância.
 *
 * Percorre o vetor de distâncias e retorna o indice da menor distância no vetor.
 ***********************************************/
int Grafo::indice_Menor_Distancia(float distancias[],bool visitados[])
{

    float minimo = std::numeric_limits<float>::max();
    int indice = 0;

    for(int i = 0; i < qtd_De_Nos; i++)
    {
        if(visitados[i] == false && distancias[i] <= minimo)
        {
            minimo = distancias[i];
            indice = i;
        }
    }
    return indice;
}


/********************************************//**
 * \Lê uma instancia de grafo
 *
 * \O parâmetro 'nome' leva o nome do arquivo a ser lido.
 *
 * \Sem valor de retorno.
 *
 * A função le o arquivo com o nome que foi passado por parâmetro, cria nos e adjacências para os mesmo de acordo com o .txt em questão.
 ***********************************************/
void Grafo::le_Grafo(string nome)
{
    std::ifstream arq_grafo(nome.c_str());
    int qtd_aux;
    arq_grafo >> qtd_aux;
    arq_grafo >> flag_Direcionado;
    arq_grafo >> flag_Ponderado;

    int id1,id2;
    float peso;
    if(!flag_Ponderado)
    {
        while(!arq_grafo.eof())
        {
            arq_grafo >> id1 >> id2;
            aux_Insere_Aresta(id1,id2,1.0);
        }
    }
    else
    {
        while(!arq_grafo.eof())
        {
            arq_grafo >> id1 >> id2;
            arq_grafo >> peso;
            aux_Insere_Aresta(id1,id2,peso);
        }
    }
    arq_grafo.close();
}


void Grafo::aux_Le_Grafo(string nome)
{

    cout << nome << endl;
    std::ifstream arq_grafo(nome.c_str());
    int qtd_aux;
    if(!arq_grafo )
    {
        cout <<"Erro de leitura" << endl;
    }
    else
    {
        arq_grafo >> qtd_aux;

        int id1,id2;
        float peso;
        int variavelAux;


        for(int i = 0; i < qtd_aux; i++)
        {
            id1 = i;
            arq_grafo >> peso;
            insere_No(id1,peso);

        }
        for(int i = 0; i<qtd_aux*qtd_aux; i++)
        {
            arq_grafo >>variavelAux;
            if(variavelAux==1)
            {
                insere_Aresta((int)(i/qtd_aux),i%qtd_aux,1.0);
            }

        }
        arq_grafo.close();

    }

}


/********************************************//**
 * \Verifica a existência de determinado no
 *
 * \O parâmetro 'identificacao' tem o valor do id do No que eu estou a procura.
 * \Retorno um bool com true para existência do no em questão e false caso não.
 *
 *
 ***********************************************/
bool Grafo::existe_No(int identificacao)
{
    list<No>::iterator i;
    for(i = Nos.begin(); i != Nos.end(); i++)
        if(i->get_Id() == identificacao)
            return true;

    return false;
}


/********************************************//**
 * \Retorna o indice do no a ser achado na lista Nos do grafo.
 *
 * \O parâmetro id contém a identificação do no a ser localizado.
 *
 * \Retorna o índice do no com o id passado.
 *
 * De acordo com o parâmetro passado é feita uma busca na lista de nos do grafo para que seja achadd e retornado o indice desse no
 * em questão na lista de vertices do grafo.
 ***********************************************/
int Grafo::get_Indice(int id)
{
    int i = 0;
    list<No>::iterator it;
    for(it = Nos.begin(); it != Nos.end(); it++)
    {
        if(it->get_Id() == id)
            return i;
        i++;
    }
    return -1;
}


/********************************************//**
 * \brief This is a brief description.
 *
 * \param	p1 The first parameter.
 * \param	p2 The second parameter.
 * \return	Return value.
 *
 * This is a detailed description.
 ***********************************************/

Grafo::~Grafo()
{
    list<No>::iterator i;
    for(i = Nos.begin(); i != Nos.end(); i++)
        delete &*i;

    Nos.clear();
}
