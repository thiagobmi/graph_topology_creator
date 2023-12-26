#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
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

    void removeLink(const int first, const int second){
        if((first || second)>=size){
            cout << "Invalid operation";
            return;
        }

        pound[first][second]=0;
        link[first][second]=0;


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
            do{
                samerand[0] = rand() % size;
                samerand[1] = rand() % size;
            }
            while(link[samerand[0]][samerand[1]]==1 || samerand[0]==samerand[1]);

            link[samerand[0]][samerand[1]] = 1;
            pound[samerand[0]][samerand[1]] = 1 + rand() % 5;
            
        }
    }

private:
    int size;
    bool **link;
    int **pound;
};

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

void DepthFirstSearch(graph_t *graph)
{
    bool *discovered = (bool *)calloc(graph->getSize(), sizeof(bool));
    cout << "DFS:";
    DFSaux(graph, discovered, 0);
    cout << "\n";
}

int main(int argc, char *argv[])
{

    graph_t *graph = new graph_t;

    graph->init(20);
    graph->setLink(0, 5);
    graph->randomize(20);
    //system("(bash graphscript.sh)");

    if (argc > 1)
    {
        graph->printGraphViz();
        return 0;
    }

    graph->print();
    DepthFirstSearch(graph);
}