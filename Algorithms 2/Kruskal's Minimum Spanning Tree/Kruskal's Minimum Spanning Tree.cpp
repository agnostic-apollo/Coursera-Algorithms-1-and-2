#include <iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include <list>
#include <iomanip>
#include <boost/pending/disjoint_sets.hpp>
#include <stdlib.h>

using namespace std;


struct edge{
    int node1;
    int node2;
    int cost;
};


struct compare{
    bool operator()(const edge  &edge1, const edge &edge2)
    {
        return edge1.cost<edge2.cost;
    }
}comp;


void clustering(vector< edge >& , int );


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

    vector< edge > graph(0);
    edge temp;

    input>>total_nodes;
    input>>total_edges;

    while(input>>temp.node1)
    {
        input>>temp.node2;
        input>>temp.cost;
        graph.push_back(temp);

    }

    clustering(graph,total_nodes);

    /*
    cout<<graph.size()<<endl;
    cout<<total_nodes<<endl;


    for(i=124740;i!=graph.size();i++)
        cout<<graph[i].node1<<" "<<graph[i].node2<<"   "<<graph[i].cost<<endl;


    */
}



void clustering(vector< edge > &graph, int total_nodes)
{
    int i,parent1,parent2;

    vector<int> rank(total_nodes+1);
    vector<int> parent(total_nodes+1);
    boost::disjoint_sets<int*,int*> graph_set(&rank[0], &parent[0]);
    vector<edge> MST(0);

    sort(graph.begin(),graph.end(), comp);


    for(int i=1;i<=total_nodes;i++)
    {
        graph_set.make_set(i);
    }


    //while(graph_set.count_sets()>4)
    //boost::disjoint_sets<int*,int*>::iterator iter;
    for(i=0;i!=graph.size();i++)
    {
        parent1=graph_set.find_set(graph[i].node1);
        parent2=graph_set.find_set(graph[i].node2);

        if(parent1 != parent2)
        {
            graph_set.link(parent1, parent2);
            MST.push_back(graph[i]);

        }
    }

    long long int total_cost=0;

    for(i=0;i!=MST.size();i++)
    {
        cout<<endl<<i+1<<" "<<MST[i].node1<<" "<<MST[i].node2<<"   "<<MST[i].cost;
        total_cost+=MST[i].cost;

    }

    cout<<"\nMinimum Spanning Tree's cost = "<<total_cost<<endl;

}

