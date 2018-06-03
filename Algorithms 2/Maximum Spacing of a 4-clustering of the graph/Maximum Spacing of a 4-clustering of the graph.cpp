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
    input.open("clustering 1.txt");
    if(input.fail())
    {
        cout<<"Error opening file\n";
        exit(1);
    }

    int i=0,j=0,total_edges,total_nodes,node1,node2,cost;

    vector< edge > graph(0);
    edge temp;

    input>>total_nodes;

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
    vector<int> edges(0);

    sort(graph.begin(),graph.end(), comp);


    for(int i=1;i<=total_nodes;i++)
    {
        graph_set.make_set(i);
        edges.push_back(i);
    }


    vector<int>::iterator iter_first,iter_last;
    iter_first=edges.begin();
    iter_last=edges.end();


    i=0;
    while(graph_set.count_sets(iter_first,iter_last)>4)
    {
        parent1=graph_set.find_set(graph[i].node1);
        parent2=graph_set.find_set(graph[i].node2);

        if(parent1 != parent2)
        {
            graph_set.link(parent1, parent2);
            MST.push_back(graph[i]);
        }
        i++;
    }

    int maximum_spacing=1000000;

    for(;i!=graph.size();i++)
    {
        parent1=graph_set.find_set(graph[i].node1);
        parent2=graph_set.find_set(graph[i].node2);

        if(parent1 != parent2)
        {
            if(graph[i].cost<maximum_spacing)
                maximum_spacing=graph[i].cost;
        }
    }


    //for(i=0;i!=MST.size();i++)
           // cout<<endl<<i+1<<" "<<MST[i].node1<<" "<<MST[i].node2<<"   "<<MST[i].cost;

    cout<<"\nMaximum Spacing of a 4-clustering of the graph = "<<maximum_spacing<<endl;


}

