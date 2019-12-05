//
// Created by ivan on 23.11.19.
//
#include "Graph.h"
#include <fstream>
#include <sstream>
using namespace GRAPHspace;
using std::cout;
using std::endl;
using std::pair;
using std::vector;
using std::ios;
std::ostream& operator<<(std::ostream& out,vector<int>& vect)
{
    for(int i =0;i<vect.size();i++)
    {
        out<<vect[i]+1<<" ";
    }
    return out;
}


struct Node
{
    int v1, v2, weight;

    Node() {};

    Node(int v1, int v2, int weight)
    {
        this->v1 = v1;

        this->v2 = v2;

        this->weight = weight;
    }
};



void set_graph(Graph &graph)
{
  graph.add_edge(0,1,8).add_edge(1,2,3).add_edge(2,3,1).add_edge(3,4,7).add_edge(4,5,1);
  graph.add_edge(6,7,1).add_edge(7,8,1).add_edge(8,9,2).add_edge(9,10,8).add_edge(10,11,1);
  graph.add_edge(12,13,1).add_edge(13,14,3).add_edge(14,15,7).add_edge(15,16,4).add_edge(16,17,2);
  graph.add_edge(18,19,7).add_edge(19,20,1).add_edge(20,21,5).add_edge(21,22,3).add_edge(22,23,8);
  graph.add_edge(24,25,4).add_edge(25,26,2).add_edge(26,27,3).add_edge(27,28,7).add_edge(28,29,1);

  graph.add_edge(0,6,4).add_edge(1,7,2).add_edge(2,8,3).add_edge(3,9,6).add_edge(4,10,7).add_edge(5,11,5);
  graph.add_edge(6,12,4).add_edge(7,13,3).add_edge(8,14,1).add_edge(9,15,5).add_edge(10,16,7).add_edge(11,17,7);
  graph.add_edge(12,18,3).add_edge(13,19,2).add_edge(14,20,6).add_edge(15,21,3).add_edge(16,22,4).add_edge(17,23,5);
  graph.add_edge(18,24,3).add_edge(19,25,1).add_edge(20,26,7).add_edge(21,27,8).add_edge(22,28,4).add_edge(23,29,3);

  graph.add_edge(1,0,8).add_edge(2,1,3).add_edge(3,2,1).add_edge(4,3,7).add_edge(5,4,1);
  graph.add_edge(7,6,1).add_edge(8,7,1).add_edge(9,8,2).add_edge(10,9,8).add_edge(11,10,1);
  graph.add_edge(13,12,1).add_edge(14,13,3).add_edge(15,14,7).add_edge(16,15,4).add_edge(17,16,2);
  graph.add_edge(19,18,7).add_edge(20,19,1).add_edge(21,20,5).add_edge(22,21,3).add_edge(23,22,8);
  graph.add_edge(25,24,4).add_edge(26,25,2).add_edge(27,26,3).add_edge(28,27,7).add_edge(29,28,1);

  graph.add_edge(6,0,4).add_edge(7,1,2).add_edge(8,2,3).add_edge(9,3,6).add_edge(10,4,7).add_edge(11,5,5);
  graph.add_edge(12,6,4).add_edge(13,7,3).add_edge(14,8,1).add_edge(15,9,5).add_edge(16,10,7).add_edge(17,11,7);
  graph.add_edge(18,12,3).add_edge(19,13,2).add_edge(20,14,6).add_edge(21,15,3).add_edge(22,16,4).add_edge(23,17,5);
  graph.add_edge(24,18,3).add_edge(25,19,1).add_edge(26,20,7).add_edge(27,21,8).add_edge(28,22,4).add_edge(29,23,3);
}


std::ostream& operator<< (std::ostream& out, Node& node)
{
    out << " v2 = " << node.v1 << "  v1 = " << node.v2 << " weight = " << node.weight;

    return out;
}

void Swap(Node& a, Node& b)
{
    Node c = a;
    a = b;
    b = c;
}

void sort(Node* arr, int size)
{
    bool ok = true;

    while (ok)
    {
        ok = false;

        for (int i = 0; i < size - 1; i++)
        {
            if (arr[i + 1].weight < arr[i].weight)
            {
                Swap(arr[i + 1], arr[i]);

                ok = true;
            }
        }
    }
}

int Kruskal_algorithm(Node* arr, int num_of_edges, int verticies)
{
    int min_sp_tree = 0;

    int* parent = new int[verticies];

    int v1, v2, weight;

    int to_change, changed;

    for (int i = 0; i < verticies; i++)
    {
        parent[i] = i;
    }

    for (int i = 0; i < num_of_edges; i++)
    {
        v1 = arr[i].v1;

        v2 = arr[i].v2;

        weight = arr[i].weight;


        if (parent[v2] != parent[v1])
        {
            cout << arr[i] << endl;

            min_sp_tree += weight;

            to_change = parent[v1];

            changed = parent[v2];

            for (int j = 0; j < verticies; j++)
            {
                if (parent[j] == changed)
                {
                    parent[j] = to_change;
                }
            }
        }
    }
    delete[] parent;

    return min_sp_tree;
}



int main()
{
    Graph graph1
            {
                    {0, 1, 1, 0, 0, 1, 0, 0, 1},
                    {1, 0, 1, 1, 0, 0, 1, 0, 0},
                    {1, 1, 0, 1, 0, 0, 0, 0, 1},
                    {0, 1, 1, 0, 1, 0, 0, 0, 1},
                    {0, 0, 0, 1, 0, 0, 0, 0, 1},
                    {1, 0, 0, 0, 0, 0, 0, 0, 1},
                    {0, 1, 0, 0, 0, 0, 0, 1, 1},
                    {0, 0, 0, 0, 0, 0, 1, 0, 0},
                    {1, 0, 1, 1, 1, 1, 1, 0, 0}
            };

    std::vector<int> dfs_list;
    graph1.DFS(0,dfs_list,0);
    cout<<"DFS: "<< dfs_list<<endl;
////////////////////////////////////////////////////////////////////////////////////////


    Graph graph2_P
            {
                    {0, 1, 2, 3, 0, 0, 0, 0, 0, 0, 0},
                    {1, 0, 0, 0, 3, 0, 2, 0, 0, 0, 0},
                    {2, 0, 0, 0, 7, 5, 0, 0, 0, 0, 0},
                    {3, 0, 0, 0, 0, 2, 3, 0, 0, 0, 0},
                    {0, 3, 7, 0, 0, 0, 0, 4, 6, 0, 0},
                    {0, 0, 5, 2, 0, 0, 0, 7, 0, 4, 0},
                    {0, 2, 0, 3, 0, 0, 0, 0, 1, 7, 0},
                    {0, 0, 0, 0, 4, 7, 0, 0, 0, 0, 4},
                    {0, 0, 0, 0, 6, 0, 1, 0, 0, 0, 5},
                    {0, 0, 0, 0, 0, 4, 7, 0, 0, 0, 4},
                    {0, 0, 0, 0, 0, 0, 0, 4, 5, 4, 0}
            };
    cout<<"Prim algorithm: "<<endl;
    cout<<"start = 0"<<endl;
    cout<<graph2_P.Prim(0);
    cout<<endl;
    cout<<"Kruskal algorithm: "<<endl;
    {
    int graph2_K[11][11]
            {
                    {0, 1, 2, 3, 0, 0, 0, 0, 0, 0, 0},
                    {1, 0, 0, 0, 3, 0, 2, 0, 0, 0, 0},
                    {2, 0, 0, 0, 7, 5, 0, 0, 0, 0, 0},
                    {3, 0, 0, 0, 0, 2, 3, 0, 0, 0, 0},
                    {0, 3, 7, 0, 0, 0, 0, 4, 6, 0, 0},
                    {0, 0, 5, 2, 0, 0, 0, 7, 0, 4, 0},
                    {0, 2, 0, 3, 0, 0, 0, 0, 1, 7, 0},
                    {0, 0, 0, 0, 4, 7, 0, 0, 0, 0, 4},
                    {0, 0, 0, 0, 6, 0, 1, 0, 0, 0, 5},
                    {0, 0, 0, 0, 0, 4, 7, 0, 0, 0, 4},
                    {0, 0, 0, 0, 0, 0, 0, 4, 5, 4, 0}
            };
        int edges = 0;
        const int verticies = 11;
        const int &n = verticies;
        Node arr[50];

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (graph2_K[i][j] != 0) {
                    arr[edges] = Node(i, j, graph2_K[i][j]);

                    edges++;
                }
            }
        }
        sort(arr, edges);
        int min_sp_tree = Kruskal_algorithm(arr, edges, n);
        cout << " MST =  " << min_sp_tree;
    }
    cout<<endl;
/////////////////////////////////////////////////////////////////////////////////////////////
    cout<<"Salesman problem"<<endl;
    Graph graph3
    {
            {0,1,5,1,5,1,6,1},
            {1,0,7,5,6,1,2,3},
            {5,7,0,5,6,2,1,2},
            {1,5,5,0,6,5,1,5},
            {5,6,6,6,0,7,7,7},
            {1,1,2,5,7,0,1,1},
            {6,2,1,1,7,1,0,2},
            {1,3,2,5,7,1,2,0}
    };
    int best_route = graph3.best_route(0);
    cout<<endl<<"best route weight= "<<best_route<<endl;
//////////////////////////////////////////////////////////////////////////////////////////////////////////

    cout<<"Dijkstra algorithm : "<<endl;
    Graph graph4(30);
    set_graph(graph4);
    graph4.Deykstra(0);
    cout<<endl;
////////////////////////////////////////////////////////////////////////////////////////
    cout<<"Euler cycle"<<endl;
    Graph graph5{
			{0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1},
			{1, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0},
			{0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0},
			{0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0},
			{0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0},
			{1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1},
			{1, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 1},
			{0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0},
			{0, 1, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0},
			{0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0},
			{0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1},
			{1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0}
	};

    graph5.Euler_cycle(0);

}