#include <iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include <queue>
#include <iomanip>
#include <stdlib.h>

using namespace std;


struct edge{
    int node2;
    int cost;
};

struct node{
    vector <edge> edges;
};


struct heap_edge{
    int node;
    int key;
};


class compare {
	public:
		bool const operator()(heap_edge  &edge1, heap_edge  &edge2)
        {
            return edge1.key>edge2.key;
        }
};


void Prims_MST(vector< node >& , int , int , int );


int main()
{
    ifstream input;
    input.open("edges.txt");
    if(input.fail())
    {
        cout<<"Error opening file\n";
        exit(1);
    }

    int i=0,j=0,total_edges,total_nodes,node1,node2,cost;

    vector< node > graph(1);
    edge temp;

    input>>total_nodes;
    input>>total_edges;
    graph.resize(total_nodes+1);

    while(input>>node1)
    {
        input>>node2;
        input>>cost;

        temp.node2=node2;
        temp.cost=cost;
        graph[node1].edges.push_back(temp);
        temp.node2=node1;
        graph[node2].edges.push_back(temp);
    }


    Prims_MST(graph,total_nodes,total_edges,1);

    /*
    cout<<graph.size()<<endl;
    cout<<total_nodes<<endl;
    cout<<total_edges<<endl;

    for(i=1;i!=graph.size();i++)
        {
            cout<<endl<<endl<<i<<"\t\t";
            for(j=0;j!=graph[i].edges.size();j++)
                cout<<graph[i].edges[j].node2<<" "<<graph[i].edges[j].cost<<"   ";
        }

    */
}



void Prims_MST(vector< node > &graph, int total_nodes, int total_edges, int start)
{
    priority_queue< int, vector< heap_edge > , compare > min_heap;

    vector<bool> visited(0);
    visited.resize(total_nodes+1,false);

    vector<int> Key(total_nodes+1,1000000);
    Key[start]=0;

    vector<int> MST(total_nodes+1);

    heap_edge temp,current_node;
    for(int i=1;i!=total_nodes+1;i++)
    {
        temp.node=i;
        temp.key=Key[i];
        min_heap.push(temp);
    }

    long long int total_cost=0;
    int node2,node2_cost;

    while(!min_heap.empty())
    {
        current_node=min_heap.top();
        min_heap.pop();

        if(visited[current_node.node]==false)
        {
            for(int i=0;i!=graph[current_node.node].edges.size();i++)
            {
                node2=graph[current_node.node].edges[i].node2;
                node2_cost=graph[current_node.node].edges[i].cost;

                if(visited[node2]==false && node2_cost<Key[node2] )
                {
                    Key[node2]=node2_cost;
                    temp.node=node2;
                    temp.key=node2_cost;
                    min_heap.push(temp);
                    MST[node2]=current_node.node;
                }
            }
            visited[current_node.node]==true;
        }
    }

    for(int i=1;i!=total_nodes+1;i++)
        total_cost+=Key[i];

    cout<<"Minimum Spanning Tree's cost = "<<total_cost<<endl;

    for(int i=1;i!=total_nodes+1;i++)
        cout<<setw(6)<<left<<MST[i]<<" "<<setw(6)<<i<<" "<<setw(6)<<Key[i]<<endl;
}

