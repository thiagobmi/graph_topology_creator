#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <time.h>

using namespace std;

void printVector(vector<int> *g1)
{

    for (auto i = g1->begin(); i != g1->end(); ++i)
    {
        if (i != g1->end() - 1)
            cout << *i << ",";
        else
            cout << *i;
    }
}

class graph_t
{
public:
    int getSize()
    {
        return size;
    }

    void printGraphViz()
    {
        int count = 0;

        for (int row = 0; row < size; row++)
        {
            for (int i = 0; i < getVectorAdjacents(row)->size(); i++)
            {
                cout << "\n\t" << row << " -> " << getVectorAdjacents(row)->at(i) << " [label=" << pound[row][getVectorAdjacents(row)->at(i)] << "]";
            }
        }
        cout << "\n";
    }

    void printGVfile()
    {
        std::ofstream myfile;
        myfile.open("graphgpmenufile.gv");
        myfile << "graph G {";

        int count = 0;

        for (int row = 0; row < size; row++)
        {
            for (int i = 0; i < getVectorAdjacents(row)->size(); i++)
            {
                myfile << "\n\t" << row << " -- " << getVectorAdjacents(row)->at(i) << " [label=" << pound[row][getVectorAdjacents(row)->at(i)] << "]";
            }
        }
        myfile << "\n";

        myfile << "}";
    }

    void init(const int argsize)
    {
        size = argsize;
        link = (bool **)malloc(sizeof(bool **) * size);
        pound = (int **)malloc(sizeof(int **) * argsize);
        for (int i = 0; i < size; i++)
        {
            link[i] = (bool *)malloc(sizeof(bool *) * size);
            pound[i] = (int *)malloc(sizeof(int *) * argsize);
        }

        clear();
    }

    int getNumberOfAdjacents(const int v)
    {
        int count = 0;

        if (v >= size)
        {
            return -1;
        }

        for (int i = 0; i < size; i++)
            if (link[v][i] == true)
                count++;

        return count;
    }

    void clear()
    {
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                link[i][j] = 0;
    }

    void print()
    {

        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                cout << link[i][j] << " ";
            }
            cout << "\n";
        }
    }

    void setLink(const int first, const int second, int argpound = 1)
    {
        if ((first || second) >= size)
        {
            cout << "Invalid operation";
            return;
        }

        pound[first][second] = argpound;
        link[first][second] = 1;
    }

    void removeLink(const int first, const int second)
    {
        if ((first || second) >= size)
        {
            cout << "Invalid operation";
            return;
        }

        pound[first][second] = 0;
        link[first][second] = 0;
    }

    vector<int> *getVectorAdjacents(const int line)
    {
        vector<int> *G = new vector<int>;

        for (int i = 0; i < size; i++)
            if (link[line][i] == true)
                G->push_back(i);

        return G;
    }

    bool isLinked(const int first, const int second)
    {
        return link[first][second];
    }

    void randomize(const int argnum)
    {
        srand(time(NULL));
        int samerand[2];
        for (int i = 0; i < argnum; i++)
        {
            do
            {
                samerand[0] = rand() % size;
                samerand[1] = rand() % size;
            } while (link[samerand[0]][samerand[1]] == 1 || samerand[0] == samerand[1]);

            link[samerand[0]][samerand[1]] = 1;
            pound[samerand[0]][samerand[1]] = 1 + rand() % 5;
        }
    }

private:
    int size;
    bool **link;
    int **pound;
};

void createImage(graph_t *graph)
{
    graph->printGVfile();
    system("dot -Tpng graphgpmenufile.gv -o graphmenuimage.png");
    system("rm graphgpmenufile.gv");
}

void DFSaux(graph_t *graph, bool *discovered, int v)
{

    cout << " " << v;

    discovered[v] = true;
    vector<int> *adjacent = graph->getVectorAdjacents(v);

    for (int i = 0; i < adjacent->size(); i++)
    {
        if (discovered[adjacent->at(i)] != true)
        {
            DFSaux(graph, discovered, adjacent->at(i));
        }
    }
}

void DepthFirstSearch(graph_t *graph, const int startnode = 0)
{
    bool *discovered = (bool *)calloc(graph->getSize(), sizeof(bool));
    cout << "DFS:";
    DFSaux(graph, discovered, startnode);
    cout << "\n";
}

int main(int argc, char *argv[])
{
    int option = 2, firstnode, secondnode, numrand, size = 0, pound = 0;
    graph_t *graph = new graph_t;

    if (argc > 1)
    {
        graph->init(20);
        graph->randomize(20);
        graph->printGraphViz();
        return 0;
    }

    while (option != 0)
    {
        cout << "\n\t0) Sair";
        cout << "\n\t1) Iniciar grafo";
        cout << "\n\t2) Criar ligação entre nós";
        cout << "\n\t3) Remover ligação entre nós";
        cout << "\n\t4) Limpar grafo";
        cout << "\n\t5) Criar ligações aleatórias";
        cout << "\n\t6) Mostrar ligações";
        cout << "\n\t7) Criar imagem do grafo";
        cout << "\n\t8) Numero de nós adjacentes a um nó";
        cout << "\n\t9) DFS a partir do 0";
        cout << "\n\t10) DFS";
        cout << "\n\nEscolha a opção:\n";
        cin >> option;
        switch (option)
        {
        case 0:
            return 0;
            break;

        case 1:
            cout << "Digite o tamanho desejado do grafo:\n";
            cin >> size;
            graph->init(size);
            createImage(graph);

            break;
        case 2:
            cout << "Digite o node de saída:\n";
            cin >> firstnode;
            cout << "Digite o node de chegada:\n";
            cin >> secondnode;
            cout << "Digite o peso da aresta:\n";
            cin >> pound;
            graph->setLink(firstnode, secondnode, pound);
            createImage(graph);

            break;
        case 3:
            cout << "Digite o node de saída:\n";
            cin >> firstnode;
            cout << "Digite o node de chegada:\n";
            cin >> secondnode;
            graph->removeLink(firstnode, secondnode);
            createImage(graph);
            break;

        case 4:
            graph->clear();
            createImage(graph);
            break;

        case 5:
            cout << "Digite quantas ligações devem ser feitas aleatóriamente:\n";
            cin >> numrand;
            graph->randomize(numrand);
            createImage(graph);
            break;
        case 6:
            graph->print();
            break;
        case 7:
            createImage(graph);
            break;

        case 8:
            cout << "Digite o node desejado:\n";
            cin >> firstnode;
            cout << "\nO nó " << firstnode << "possui " << graph->getNumberOfAdjacents(firstnode) << " nós adjacentes";
            break;

        case 9:
            DepthFirstSearch(graph);
            break;

        case 10:
            cout << "Digite o node de inicio desejado:\n";
            cin >> firstnode;
            DepthFirstSearch(graph, firstnode);
        }
    }
}
