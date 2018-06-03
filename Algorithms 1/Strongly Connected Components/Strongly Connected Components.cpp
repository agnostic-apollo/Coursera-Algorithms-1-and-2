#include <iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include<iterator>
#include<stack>
#include <stdlib.h>


using namespace std;

void Strongly_connected_components_finder(vector< vector<int> > & );
void First_depth_first_search(vector< vector<int> > & , int , vector<bool> & , stack<int> & );
void transpose_graph(vector< vector<int> > & , vector< vector<int> > &);
void Second_depth_first_search(vector< vector<int> > &, int , vector<bool> & , int &);

int main()
{
    ifstream input;

    int vertice,prev_vertice=1,edge,i,j;
    input.open("SCC.txt");
    if(input.fail())
    {
        cout<<"Error opening file\n";
        exit(1);
    }

    vector< vector<int> > graph(1);
    vector<int> edges(0);


    //take input from file and file 2d vector
    while(!input.eof())
    {
        input>>vertice;

        if(vertice==prev_vertice)
        {
             input>>edge;
             edges.push_back(edge);
        }

        else
        {
            graph.push_back(edges);
            edges.clear();
            while(graph.size()!=vertice)
                    graph.push_back(edges);
            input>>edge;
            edges.push_back(edge);
            prev_vertice=vertice;
        }

    }
    graph.push_back(edges);


    Strongly_connected_components_finder(graph);

    /*
    cout<<graph.size()<<endl;
    for(i=graph.size()-10;i!=graph.size();i++)
    {
        cout<<i<<" ";
        for(j=0;j!=graph[i].size();j++)
            cout<<graph[i][j]<<" ";
        cout<<endl<<endl;
    }
    */

}

void Strongly_connected_components_finder(vector< vector<int> > &graph )
{

    vector<bool> visited(0);
    visited.resize(graph.size(),false);
    stack<int> finish_time;


    //first DFS to find finish times
    for(int i=1;i!=graph.size();i++)
        if(!visited[i])
            First_depth_first_search(graph,i,visited,finish_time);


    //transpose graph
    vector< vector<int> > reverse_graph(graph.size());
    transpose_graph(graph,reverse_graph);

    //second DFS to find finish times strongly connected components
    for(int i=0;i!=visited.size();i++)
        visited[i]=false;

    vector<int> largest_5_scc(5,0);

    while(!finish_time.empty())
    {
        int vertice;
        vertice=finish_time.top();
        finish_time.pop();


        if(!visited[vertice])
        {   int s=0;
            Second_depth_first_search(reverse_graph,vertice,visited,s);

            //calculate 5 largest scc
            if(s>largest_5_scc[0])
                largest_5_scc.insert(largest_5_scc.begin(),s);
            else if(s>largest_5_scc[1])
                largest_5_scc.insert(largest_5_scc.begin()+1,s);
            else if(s>largest_5_scc[2])
                largest_5_scc.insert(largest_5_scc.begin()+2,s);
            else if(s>largest_5_scc[3])
                largest_5_scc.insert(largest_5_scc.begin()+3,s);
            else if(s>largest_5_scc[4])
                largest_5_scc.insert(largest_5_scc.begin()+4,s);

            largest_5_scc.resize(5);
        }

    }

    //print 5 largest scc
    cout<<"5 largest Strongly connected component sizes : ";
    for(int i=0;i!=largest_5_scc.size();i++)
        cout<<largest_5_scc[i]<<" ";
    cout<<endl;
}

void First_depth_first_search(vector< vector<int> > &graph, int vertice, vector<bool> &visited, stack<int> &finish_time )
{
    visited[vertice]=true;

    for(int j=0;j!=graph[vertice].size();j++)
    {
        if(!visited[graph[vertice][j]])
        {
            First_depth_first_search(graph,graph[vertice][j],visited,finish_time);
        }
    }

    finish_time.push(vertice);
}

void transpose_graph(vector< vector<int> > &graph,vector< vector<int> > &reverse_graph)
{
    for(int i=1;i!=graph.size();i++)
    {
        for(int j=0;j!=graph[i].size();j++)
        {
            reverse_graph[graph[i][j]].push_back(i);
        }
    }
}

void Second_depth_first_search(vector< vector<int> > &reverse_graph, int vertice, vector<bool> &visited , int &s)
{
    visited[vertice]=true;
    s++;
    for(int j=0;j!=reverse_graph[vertice].size();j++)
    {
        if(!visited[reverse_graph[vertice][j]])
        {
            Second_depth_first_search(reverse_graph,reverse_graph[vertice][j],visited,s);
        }
    }
}



