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

int min_cuts(vector< vector<int> > & );


int main()
{
    ifstream input;
    input.open("kargerMinCut.txt");
    if(input.fail())
    {
        cout<<"Error opening file\n";
        exit(1);
    }

    int temp,num=0,i=0,j=0,ignore_vertice,vertices=0,min_cuts_calc=100000;
    vector< vector<int> > graph(1);
    vector<int> edges(0);

    string edges_string;

    while(!input.eof())
    {
        input>>ignore_vertice;
        getline(input,edges_string);
        istringstream edges_istring(edges_string);
        edges.clear();
        while(edges_istring>>temp)
            edges.push_back(temp);

        vertices++;
        graph.push_back(edges);

    }

    graph.resize(vertices);

    /*
    for(i=1;i<graph.size();i++)
    {
        cout<<i<<" ";
        for(j=0;j<graph[i].size();j++)
            cout<<graph[i][j]<<" ";
        cout<<endl<<endl;
    }

    */
    cout<<endl<<"Min Cuts :"<<min_cuts(graph)<<endl;

    for(i=1;i<graph.size();i++)
    {
        cout<<i<<" ";
        for(j=0;j<graph[i].size();j++)
            cout<<graph[i][j]<<" ";
        cout<<endl<<endl;
    }
}



int min_cuts(vector< vector<int> > &graph )
{
    int i,j,temp,v1,v2;

    srand(time(0));

    while(graph.size()>3)
    {

        v1=1+rand()%(graph.size()-1);
        temp=rand()%(graph[v1].size()-1);
        v2=graph[v1][temp];

        graph[v1].insert( graph[v1].end(), graph[v2].begin(), graph[v2].end() );

        for(i=0;i<graph.size();i++)
            replace (graph[i].begin(), graph[i].end(), v2, v1);

        graph[v1].erase(remove(graph[v1].begin(), graph[v1].end(), v1), graph[v1].end());


        graph.erase(graph.begin()+v2);

        for(i=0;i<graph.size();i++)
            for(j=0;j<graph[i].size();j++)
               if(graph[i][j]>v2)
                   graph[i][j]=graph[i][j]-1;
    }

    return graph[1].size();
}

