//
// Created by ivan on 22.11.19.
//
// on most of algorithms program
// think that vertexes are starting calculating from one
//
#include <iostream>
#include "Graph.h"
using namespace GRAPHspace;

using std::cout;
using std::endl;
using std::pair;
using std::vector;
using std::priority_queue;
typedef pair<int,int> V;

Graph::Graph(int nodes)
{
    m_arr = new List<Vertex>[nodes];
    m_edges = 0;
    m_nodes = nodes;
}

Graph::Graph(std::initializer_list<std::initializer_list<int>> list) : Graph::Graph(list.size())
{
    int i1 = 0, j1 = 0;

    for(auto i : list)
    {
        for(int j : i)
        {
            if( j != ZERO )
            {
                m_arr[i1].push_front( Vertex(j1,j));
                m_edges ++;
            }
            j1++;
        }
        i1++;
        j1 = 0;
    }
}

Graph::~Graph()
{
    delete[] m_arr;
}

void Graph::see_graph()
{
    for(int i = 0;i<m_nodes;i++)
    {
        cout << "v(" << i << ") = ";

        Vertex v;
        auto cur = m_arr[i].begin();
        for(int j = 0; j < m_arr[i].size(); j++)
        {
            v = *cur;
            cout<<v;
            cur++;
        }
        cout << endl;
    }
}

Graph& Graph::add_edge(int from, int to, int weight)
{
    assert(m_nodes>0);
    assert((from >=  0 && to < m_nodes) || (to >=  0 && from < m_nodes));

    m_arr[from].push_back(Vertex(to,weight));

    m_edges++;

    return *this;
}

// it won't delete the edge if there are no such edge
Graph& Graph::remove_edge(int from, int to)
{
    assert((from >=  0 && to < m_nodes) || (to >=  0 && from < m_nodes));

    Vertex v;
    for(auto item = m_arr[from].begin();item!=m_arr[from].end();item++ )
    {
        if((*item).V == to)
        {
            m_arr[from].remove(item);
            m_edges--;
            break;
        }
    }
    return *this;
}


void Graph::BFS(int start)
{
    assert(start >= 0 && start < m_nodes);

    bool* visited = new bool[m_nodes]{ false };

    Queue<int> q ;

    q.push(start);

    visited[start] = true;

    int cur_node;

    while(!q.empty())
    {
        cur_node = q.front();
        cout << cur_node << " ";
        q.pop();

        for(auto iter : m_arr[cur_node])
        {
            if(!visited[iter.V])
            {
                q.push(iter.V);

                visited[iter.V] = true;
            }
        }
    }

    delete[] visited;
}

void Graph::DFS(int start,vector<int>& dfs_list,bool print = false )
{
    assert(start >= 0 && start < m_nodes);

    bool* visited = new bool[m_nodes]{ false };

    Stack<int> st ;

    st.push(start);

    while(!st.empty())
    {
        start= st.top();
        st.pop();

        if(!visited[start])
        {
            if(print){cout << start+1 << " ";}

            dfs_list.push_back(start);
            visited[start] = true;
        }

        for(auto iter : m_arr[start])
        {
            if(!visited[iter.V]) {
                st.push(iter.V);
            }
        }
    }

    delete[] visited;

}

int  Graph::Prim(int start = 0)
{
    assert(start >= 0 && start < m_nodes);

    int mst = 0;
    V cur_node;
    int cur_vertex,cur_weight;

    priority_queue< V,vector<V>,std::greater< > >  pq ;

    bool *visited = new bool[m_nodes]{ false };

    for(auto iter :  m_arr[start])
    {
        pq.push(std::make_pair(iter.weight, iter.V));
    }

    visited[start] = true;

    while(!pq.empty())
    {
        cur_node = pq.top();
        pq.pop();

        cur_vertex = cur_node.second;

        cur_weight = cur_node.first;

        if(!visited[cur_vertex])
        {
            visited[cur_vertex] = true;
            mst += cur_weight;
            cout<<"weight = "<<cur_weight<<"  V = "<<cur_vertex<<endl;

        }

        for(auto iter : m_arr[cur_vertex])
        {
            if(!visited[iter.V])
            {
                pq.push(std::make_pair(iter.weight,iter.V));
            }

        }

    }
    delete[] visited;

    return mst;

}

// shortest path from one node to all nodes (negatives not allowed)
void Graph::Deykstra(int start = 0)
{
    int* price = new int[m_nodes]; // price of every node(initially 100 000)

    for(int i =0;i<m_nodes;i++)
    {
        price[i] = inf;
    }

    bool* used_nodes = new bool[m_nodes] {false};

    priority_queue<pair<int, int>> q;

    int res;

    pair<int, int> cur_node = std::make_pair(0, start); // first - node, second - price

    q.push(cur_node);

    price[start] = 0;

    while (!q.empty())
    {
        cur_node = q.top();

        cur_node.first = abs(cur_node.first);

        q.pop();

        used_nodes[cur_node.second] = true;

        for (int j = 0;j < m_arr[cur_node.second].size();j++)
        {
            if (!used_nodes[m_arr[cur_node.second][j].V])
            {
                price[m_arr[cur_node.second][j].V] = std::min(price[m_arr[cur_node.second][j].V], cur_node.first + m_arr[cur_node.second][j].weight);

                q.push(std::make_pair(-price[m_arr[cur_node.second][j].V], m_arr[cur_node.second][j].V));
            }
        }

    }

    for(int i =0;i < m_nodes;i++)
    {
        cout<<"("<<start<<" "<<i<<") = "<<price[i]<<endl;
    }

    delete[] price;
    delete[] used_nodes;
}

//shortest path from one node to all nodes (negatives are allowed)
void Graph::Bellman_Ford(int start = 0)
{
    int *price = new int[m_nodes];

    for(int i =0;i<m_nodes;i++)
    {
        price[i] = inf;
    }

    price[start] = 0;

    bool ok = true;
    int old_price,cur_price;

    while(ok)
    {
        ok = false;

        for(int i = 0;i < m_nodes;i++)
        {
            for(auto iter : m_arr[i])
            {
                old_price = price[iter.V];

                price[iter.V] = std::min(price[iter.V],iter.weight + price[i] );

                cur_price = price[iter.V];
                if(cur_price < 0)
                {
                    cout<<"nagative cycle detected!";
                    return;
                }

                if(cur_price!=old_price)
                {
                    ok = true;
                }

            }
        }
    }

    for(int i =0;i < m_nodes;i++)
    {
        cout<<"("<<start<<" "<<i<<") = "<<price[i]<<endl;
    }

    delete[] price;

}

// shortest path between all pairs of edges(negatives are allowed)
void Graph::Floid_Warshall()
{
    int** dist = new int*[m_nodes];

    for(int i =0;i < m_nodes;i++)
    {
        int* t_arr = new int[m_nodes];
        dist[i] = t_arr;

    }

    for(int i =0;i<m_nodes;i++)
    {
        for(auto iter : m_arr[i])
        {
            dist[i][iter.V] = iter.weight;
        }
        dist[i][i] = 0;
    }
    for(int i =0;i<m_nodes;i++)
	{
         for(int j=0;j<m_nodes;j++)
        {
            if(i!=j && dist[i][j]==0)
            {
                dist[i][j] = inf;
            }
        }
    }
    for(int k = 0;k<m_nodes;k++)
    {
        for(int i =0;i<m_nodes;i++)
        {
            for(int j = 0;j<m_nodes;j++)
            {
                if(dist[i][j] > dist[i][k] + dist[k][j])
                {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }


    for(int i =0;i<m_nodes;i++)
    {
        for(int j=0;j<m_nodes;j++)
        {
            cout<<dist[i][j]<<" ";
        }
        cout<<endl;
    }

    delete[] dist;
}

// transform graph to Matrix
void Graph::transform(int **graph)
{
    for(int i =0;i<m_nodes;i++)
    {
        int *vert = new int[m_nodes];
        graph[i] = vert;
    }
    for(int i =0;i<m_nodes;i++)
    {
        for(auto iter: m_arr[i])
        {
            graph[i][iter.V] = iter.weight;
        }
    }

}
/*
 next_permutation algorithm:
  start from end
  find first decreasing element
  find element that is just larger than that one
  swap them
 1 5 8 4 7 6 5 3 1
       |     |
 4 - first decreasing elem
 5 - elem that just larger from 4
*/
// solving salesman problem using full search O((n-1)!) - like a nub

int  Graph::best_route(int start) // DO NOT FORGET TO erase "+1"
{
    int ** graph = new int*[m_nodes];
    transform(graph);
    vector<int> vertex;
    vector<int> best_route;
    int min_path = inf;

    for(int i =0;i < m_nodes;i++)
    {
        if (i!=start)
        {
            vertex.push_back(i);
            best_route.push_back(i);
        }
    }

    do{
        int cur_pathweight = 0;

        int k = start; // k - cur edge

        for (int i = 0; i < m_nodes-1; i++)
        {
            cur_pathweight += graph[k][vertex[i]];
            k = vertex[i];
        }

        cur_pathweight += graph[k][start];

        if(cur_pathweight < min_path)
        {
            min_path = cur_pathweight;

            for(int i =0;i<m_nodes-1;i++)
            {
                best_route[i] = vertex[i];
            }
        }
    }while (std::next_permutation(vertex.begin(), vertex.end()));

    cout<< start+1<<" ";
    for(int i =0;i<m_nodes-1;i++)
    {
        cout<<best_route[i]+1<<" ";
    }
    cout<< start+1<<" ";
    return min_path;
}

void Graph::copy(List<Vertex> *copy_arr)
{
    copy_arr = new List<Vertex>[m_nodes];

    for(int i =0;i<m_nodes;i++)
    {
        for(auto iter :  m_arr[i])
        {
            copy_arr[i].push_back(iter);
        }
    }
}


// i will use algorithm that is a lot more efficient O(m + n)
// Algorithm assumes that given graph have Euler circuit
void Graph::Euler_cycle(int start)
{
	assert(start>=0 && start <= m_nodes);
	Graph temp_graph = *this;
    Euler_cycle(start,temp_graph);
    cout<<start+1<<" ";
}

void Graph::Euler_cycle(int start,Graph &graph)
{
	if( graph.m_arr[start].size()==0)
	{
		return;
	}
	vector<int> cycle {start};
    Stack<int> st;
    st.push(start);

    int cur_vertex = start;
	int i = 0;
    while(true )
	{
		// if currrent vertex == incedent vertex
    	if(cur_vertex == graph.m_arr[start][0].V)
		{
			graph.remove_edge(cur_vertex,start);
			graph.remove_edge(start,cur_vertex);
    		break;
		}
    	for(auto item: graph.m_arr[cur_vertex])
		{
    		st.push(item.V);
		}
		cur_vertex = st.top();

    	cycle.push_back(cur_vertex);
    	graph.remove_edge(cycle[i],cycle[i+1]);
		graph.remove_edge(cycle[i+1],cycle[i]);
		i++;
	}
	for (int i = 0;i<cycle.size();i++ )
	{
		Euler_cycle(cycle[i],graph);
		cout << cycle[i]+1 << " ";

	}
}










