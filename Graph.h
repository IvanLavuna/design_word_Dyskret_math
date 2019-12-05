//
// Created by ivan on 22.11.19.
//
// Implementation of Graph  and algorithms related to him
// using array of lists
//
//

#ifndef DATA_STRUCTURES_GRAPH_H
#define DATA_STRUCTURES_GRAPH_H

#include  <initializer_list>
#include  <cassert>
#include  "List.h"
#include  "Stack.h"
#include  "Queue.h"
#include  <queue>
#include  <vector>
#include  <algorithm>
# define ZERO 0 // ZERO means there are not vertex
#define inf 200000000 // it can be crushed(better would be to implement class infinity)

namespace GRAPHspace
{
    struct Vertex
    {
        int V;
        int weight;
        Vertex(){};
        Vertex(int V,int weight)
        {
            this->V = V;
            this->weight = weight;
        }

        friend std::ostream & operator<<(std::ostream& out,Vertex& v)
        {
            out << "(v=" << v.V <<',' <<"w=" << v.weight << ')';
            return out;
        }

    };

    class Graph
    {
    private:
        List<Vertex>* m_arr;
        int m_nodes;
        int m_edges;
        void transform(int** graph);
        void copy(List<Vertex>* copy_arr);
        void Euler_cycle(int start,Graph& graph);

    public:
        explicit Graph(int nodes);
        Graph(std::initializer_list<std::initializer_list<int>> list);

        ~Graph();

        Graph& add_edge(int from,int to,int weight);

        Graph& remove_edge(int from,int to);

        void see_graph();

        int get_nodes(){return m_nodes;}

        int get_edges(){return m_edges;}

        void BFS(int start);

        void DFS(int start,std::vector<int>& dfs_list,bool print);

        int Prim(int start);

        friend std::ostream& operator<<(std::ostream& out,Graph& graph)
        {
            for(int i =0; i<graph.m_nodes;i++)
            {
                out<<"V ( "<<i<<" ) = ";

                for(auto iter : graph.m_arr[i])
                {
                    out<<"w("<<iter.weight<<") V("<<iter.V<<"),";
                }
                out<<std::endl;
            }
            return out;
        }

        void Deykstra(int start);

        void Bellman_Ford(int start);

        void Floid_Warshall();

        // solving salesman problem using full search O((n-1)!) - like a nub
        int best_route(int start);

        void Euler_cycle(int start);


    };

}

#endif //DATA_STRUCTURES_GRAPH_H
