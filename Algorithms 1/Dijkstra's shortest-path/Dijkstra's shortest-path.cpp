#include <iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include<time.h>
#include<sys/time.h>
#include<sstream>
#include<string>
#include<windows.h>
#include<stdlib.h>

using namespace std;

struct nodes{
    int vertex1;
    int vertex2;
    int length;
};

void Dijkstras_shortest_path(vector< nodes > & , int ,int );


int main()
{
    ifstream input;
    input.open("dijkstraData.txt");
    if(input.fail())
    {
        cout<<"Error opening file\n";
        exit(1);
    }

    int temp,i=0,j=0,current_vertice,total_vertices=0;
    char ignore_comma;
    vector< nodes > graph(0);
    nodes current_edge;

    string edges_string;

    while(!input.eof())
    {
        input>>current_vertice;
        getline(input,edges_string);
        istringstream edges_istring(edges_string);
        total_vertices++;
        while(edges_istring>>temp)
        {
            current_edge.vertex1=current_vertice;
            current_edge.vertex2=temp;
            edges_istring>>ignore_comma;
            edges_istring>>temp;
            current_edge.length=temp;
            graph.push_back(current_edge);
            i++;
       }
    }

    graph.resize(i);
    total_vertices--;
    Dijkstras_shortest_path(graph,total_vertices,1);

    /*
    for(i=0;i!=graph.size();i++)
    {
        cout<<graph[i].vertex1<<" "<<graph[i].vertex2<<" "<<graph[i].length;
        cout<<endl;
    }
    */
}



void Dijkstras_shortest_path(vector< nodes > &graph ,int total_vertices, int source)
{

    int i,j,k,temp,v1,v2,min_dist,min_index,index_start,index_end;
    vector< int > dist(total_vertices,1000000);
    dist[source]=0;
    vector< int > prev(total_vertices,0);
    vector<bool> visited(0);
    visited.resize(total_vertices,false);

    for(i=0;i!=graph.size();i++)
    {
        min_dist=1000000;
        for(j=0;j!=dist.size();j++)
        {
            if(!visited[j] && dist[j]<=min_dist)
                {
                    min_dist=dist[j];
                    min_index=j;
                }
        }

        visited[min_index]=true;
        for(j=0;j!=graph.size();j++)
        {
            if(min_index==graph[j].vertex1)
            {   index_start=j;
                for(k=index_start;k!=graph.size();k++)
                    if(min_index!=graph[k].vertex1)
                    {
                        index_end=k-1;
                        break;
                    }
                break;
            }
        }

        for(j=index_start;j<=index_end;j++)
        {
            if(!visited[graph[j].vertex2] && dist[min_index]!=1000000 && (dist[min_index]+graph[j].length)<dist[graph[j].vertex2])
                dist[graph[j].vertex2]=dist[min_index]+graph[j].length;
        }

    }


    cout<<"7 "<<dist[7]<<endl;
    cout<<"37 "<<dist[37]<<endl;
    cout<<"59 "<<dist[59]<<endl;
    cout<<"82 "<<dist[82]<<endl;
    cout<<"99 "<<dist[99]<<endl;
    cout<<"115 "<<dist[115]<<endl;
    cout<<"133 "<<dist[133]<<endl;
    cout<<"165 "<<dist[165]<<endl;
    cout<<"188 "<<dist[188]<<endl;
    cout<<"197 "<<dist[197]<<endl;

}
