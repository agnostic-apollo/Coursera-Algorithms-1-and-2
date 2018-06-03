#include <iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include<sstream>
#include<string>
#include <queue>
#include <list>
#include <unordered_set>
#include <stdlib.h>

using namespace std;

struct nodes{
    int vertex;
    vector< int > edge_list;
    vector< int > length_list;
    int vertex_length;
};


void bellman_ford(vector< nodes > & , int , int , int );


int main()
{
    ifstream input;
    input.open("g3.txt");
    if(input.fail())
    {
        cout<<"Error opening file\n";
        exit(1);
    }

    int temp,i=0,j=0,current_vertex,total_vertices,total_edges;

    input>>total_vertices;
    input>>total_edges;
    vector< nodes > graph(total_vertices+1);

    while(input>>current_vertex)
    {
        if(current_vertex!=graph[current_vertex].vertex)
            graph[current_vertex].vertex=current_vertex;

        input>>temp;
        graph[current_vertex].edge_list.push_back(temp);
        input>>temp;
        graph[current_vertex].length_list.push_back(temp);

    }

    bellman_ford(graph,total_vertices,total_edges,1);

    /*
    for(i=1;i!=graph.size();i++)
    {
        cout<<graph[i].vertex<<" ";
        for(j=0;j!=graph[i].edge_list.size();j++)
            cout<<graph[i].edge_list[j]<<","<<graph[i].length_list[j]<<" ";
        cout<<endl<<endl;
    }
    cout<<total_vertices<<endl;
    cout<<graph[1].edge_list.size()<<endl;

    */

}



void bellman_ford(vector< nodes > &graph ,int total_vertices,int total_edges , int source)
{
    int i,j,r,n;

    vector< int > dist(total_vertices+1,10000000);
    list< int > changed_vertices(0);
    unordered_set< int > changed_vertices_set;
    dist[source]=0;

    //vector<bool> visited(1);
    //visited.resize(total_vertices,false);

    //vector< int > prev(total_vertices,0);
    for(i=1;i!=graph.size();i++)
        changed_vertices.push_back(graph[i].vertex);

    int total_changed_vertices;
    n=0;

    while (!changed_vertices.empty())
    {
        if(n==total_vertices-1)
            break;
        changed_vertices_set.erase(changed_vertices_set.begin(),changed_vertices_set.end());
        total_changed_vertices=changed_vertices.size();
        for(r=0;r<total_changed_vertices;r++)
        {
            i=changed_vertices.front();
            changed_vertices.pop_front();
            for(j=0;j!=graph[i].edge_list.size();j++)
            {
                if( dist[i] + graph[i].length_list[j] < dist[graph[i].edge_list[j]] )
                {
                    dist[graph[i].edge_list[j]] = dist[i] + graph[i].length_list[j];
                    if(changed_vertices_set.find(graph[i].edge_list[j])==changed_vertices_set.end())
                    {
                        changed_vertices.push_back(graph[i].edge_list[j]);
                        changed_vertices_set.insert(graph[i].edge_list[j]);
                    }
                }
            }
        }
        n++;
    }

    for(i=1;i!=graph.size();i++)
        for(j=0;j!=graph[i].edge_list.size();j++)
        {

            if( dist[i] + graph[i].length_list[j] < dist[graph[i].edge_list[j]] )
            {
               cout<<"Negative Cycle found"<<endl;
               exit(0);
            }
        }

    for(i=1;i<10;i++)
        cout<<i<<" "<<dist[i]<<endl;

    int shortest=10000000;
    for(i=1;i!=dist.size();i++)
        if(dist[i]<shortest)
            shortest=dist[i];
    cout<<shortest<<endl;

}


