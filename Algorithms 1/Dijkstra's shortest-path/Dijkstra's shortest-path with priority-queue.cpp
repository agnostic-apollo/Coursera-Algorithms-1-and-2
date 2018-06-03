#include <iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include<sstream>
#include<string>
#include <queue>
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
	vector< nodes > graph(1);
	nodes current_node;

	string edges_string;

	while(!input.eof())
	{

		input>>current_vertice;
		getline(input,edges_string);
		istringstream edges_istring(edges_string);
		current_node.vertex=current_vertice;
		total_vertices++;
		while(edges_istring>>temp)
		   {
				current_node.edge_list.push_back(temp);
				edges_istring>>ignore_comma;
				edges_istring>>temp;
				current_node.length_list.push_back(temp);
		   }
		graph.push_back(current_node);
		current_node.edge_list.clear();
		current_node.length_list.clear();

	}

	total_vertices--;
	graph.resize(total_vertices+1);




	Dijkstras_shortest_path(graph,total_vertices,1);

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



void Dijkstras_shortest_path(vector< nodes > &graph ,int total_vertices, int source)
{
	int i,j;

	vector< int > dist(total_vertices+1,1000000);
	dist[source]=0;

	vector<bool> visited(1);
	visited.resize(total_vertices+1,false);

	//vector< int > prev(total_vertices,0);

	priority_queue< vertex, vector<vertex>, compare > min_heap;
	vertex temp,min_vertex;
	for(i=1;i!=dist.size();i++)
		{
			temp.vertex=i;
			temp.dist=dist[i];
			min_heap.push(temp);
		}

	int heap_size;
	heap_size=min_heap.size();
	for(i=0;i<heap_size;i++)
	{
		min_vertex=min_heap.top();
		min_heap.pop();

		if(visited[min_vertex.vertex]==false)
		{
			for(j=0;j!=graph[min_vertex.vertex].edge_list.size();j++)
			{
				if(dist[min_vertex.vertex] + graph[min_vertex.vertex].length_list[j] < dist[graph[min_vertex.vertex].edge_list[j]])
					{
						dist[graph[min_vertex.vertex].edge_list[j]]=dist[min_vertex.vertex]+graph[min_vertex.vertex].length_list[j];

						temp.vertex=graph[min_vertex.vertex].edge_list[j];
						temp.dist=dist[graph[min_vertex.vertex].edge_list[j]];
						min_heap.push(temp);

					}
			}
		}

   visited[min_vertex.vertex]=true;


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
