#include<iostream>
#include<vector>
using namespace std;
class Graph
{
    private:
        int vertex;
        vector<vector<int>> adjMatrix;
    public:
        Graph(int v)
        {
            this->vertex = v;
            adjMatrix.resize(vertex);
            for(int i = 0; i<v; i++)
            {
                adjMatrix[i].resize(vertex, 0);
            }
        }
        void addVertex(int x, int y)
        {
            adjMatrix[x][y] = 1;
        }
        void deleteVertex(int x, int y)
        {
            adjMatrix[x][y] = 0;
        }
        void printGraph()
        {
            cout<<"\nPrinting directed graph using adjacency matrix"<<endl;
            for(int i = 0; i<vertex; i++)
            {
                for(int j = 0; j<vertex; j++)
                {
                    cout<<adjMatrix[i][j]<<"\t";
                }
                cout<<endl;
            }
        }
};
int main()
{
    Graph g1(5);
    g1.addVertex(0, 2);
    g1.addVertex(0, 3);
    g1.addVertex(1, 0);
    g1.addVertex(2, 1);
    g1.addVertex(2, 4);

    g1.printGraph();

    g1.deleteVertex(1, 0);

    g1.printGraph();
    return 0;
}