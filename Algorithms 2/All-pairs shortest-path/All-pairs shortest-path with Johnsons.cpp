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
};

struct vertex{
    int vertex;
    int dist;
};


class compare {
	public:
		bool const operator()(vertex &vertex1, vertex &vertex2) {
			return (vertex1.dist > vertex2.dist) ;
		}
};

void johnsons(vector< nodes > & , int , int );


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

    johnsons(graph,total_vertices,total_edges);

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



void johnsons(vector< nodes > &graph ,int total_vertices,int total_edges )
{

    int i,j,r,n;

    vector< int > dist(total_vertices+1,10000000);
    list< int > changed_vertices(0);
    unordered_set< int > changed_vertices_set;

    //add vertex 0 to graph with length 0 to each vertex
    graph[0].vertex=0;
    for(i=1;i!=graph.size();i++)
    {
        graph[0].edge_list.push_back(graph[i].vertex);
        graph[0].length_list.push_back(0);
    }


    dist[0]=0; //set source

    //Bellman-Ford Early End from source vertex 0
    for(i=0;i!=graph.size();i++)
        changed_vertices.push_back(graph[i].vertex);

    int total_changed_vertices;
    n=0;
    while (!changed_vertices.empty())
    {
        if(n==total_vertices)
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

    //detect any negative cycles
    for(i=0;i!=graph.size();i++)
        for(j=0;j!=graph[i].edge_list.size();j++)
        {
            if( dist[i] + graph[i].length_list[j] < dist[graph[i].edge_list[j]] )
            {
               cout<<"Negative Cycle found"<<endl;
               exit(0);
            }
        }


    //make new graph with each new_edge_length=edge_length + dist[u] - dist[v]
    vector< nodes > graph_new(total_vertices+1);
    for(i=1;i!=graph.size();i++)
    {
            graph_new[i].vertex=graph[i].vertex;
            for(j=0;j!=graph[i].edge_list.size();j++)
            {
                graph_new[i].edge_list.push_back(graph[i].edge_list[j]);
                graph_new[i].length_list.push_back(graph[i].length_list[j] +  dist[i] - dist[graph[i].edge_list[j]]);
            }
    }


    //Dijkstras with priority queue
    vector< vector< int > > dist_apsp(total_vertices+1,vector< int > (total_vertices+1,10000000));

    vector<bool> visited(total_vertices+1);
    priority_queue< vertex, vector<vertex>, compare > min_heap;
    vertex temp,min_vertex;
    int heap_size;
    for(n=1;n!=graph_new.size();n++)
    {
        dist_apsp[n][n]=0;
        for(i=1;i!=visited.size();i++)
            visited[i]=false;


        for(i=1;i!=dist_apsp[n].size();i++)
        {
            temp.vertex=graph_new[i].vertex;
            temp.dist=dist_apsp[n][i];
            min_heap.push(temp);
        }

        heap_size=min_heap.size();
        for(i=0;i<heap_size;i++)
        {
            min_vertex=min_heap.top();
            min_heap.pop();
            if(visited[min_vertex.vertex]==false)
            {
                for(j=0;j!=graph_new[min_vertex.vertex].edge_list.size();j++)
                {
                    if(dist_apsp[n][min_vertex.vertex] + graph_new[min_vertex.vertex].length_list[j] < dist_apsp[n][graph_new[min_vertex.vertex].edge_list[j]])
                    {
                        dist_apsp[n][graph_new[min_vertex.vertex].edge_list[j]]=dist_apsp[n][min_vertex.vertex]+graph_new[min_vertex.vertex].length_list[j];

                        temp.vertex=graph_new[min_vertex.vertex].edge_list[j];
                        temp.dist=dist_apsp[n][graph_new[min_vertex.vertex].edge_list[j]];
                        min_heap.push(temp);
                    }
                }
            }

           visited[min_vertex.vertex]=true;
        }

        min_heap = priority_queue< vertex, vector<vertex>, compare >();
    }

    //readjusting distances with new_distance = distance(from all n to all v) - dist[n] + dist[v]
    for(n=1;n!=dist_apsp.size();n++)
        for(i=1;i!=dist_apsp[n].size();i++)
            dist_apsp[n][i]=dist_apsp[n][i]-dist[n]+dist[i];


    //for(i=1;i<10;i++)
       // cout<<i<<" "<<dist_apsp[2][i]<<endl;


    //calculating All-pairs shortest-path
    int shortest=10000000;
    for(n=1;n!=dist_apsp.size();n++)
        for(i=1;i!=dist_apsp[n].size();i++)
            if(dist_apsp[n][i]<shortest)
                shortest=dist_apsp[n][i];
    cout<<"All-pairs shortest-path = "<<shortest<<endl;



}


