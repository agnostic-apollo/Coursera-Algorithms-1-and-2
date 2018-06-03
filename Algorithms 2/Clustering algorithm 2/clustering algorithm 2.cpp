#include <iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include <list>
#include <iomanip>
#include <boost/pending/disjoint_sets.hpp>
#include <bitset>
#include <stdlib.h>
#include <string>
#include <cstring>
#include <map>
#include <unordered_set>
#include <chrono>


using namespace std;
using namespace std::chrono;

struct edge{
    int node1;
    int node2;
    int ham_dist;
};


void clustering(vector< int >& , int , int );


int main()
{
    ifstream input;
    input.open("clustering_big.txt");
    if(input.fail())
    {
        cout<<"Error opening file\n";
        exit(1);
    }

    int i=0,j=0,total_nodes,bits_per_node,current_node,bit;
    string node_bits;
    char cstyle_node_bits[24];

    input>>total_nodes;
    input>>bits_per_node;
    vector< int > nodes(total_nodes+1,0);
    current_node=0;
    while(!input.eof())
    {
        getline(input,node_bits);
        node_bits.erase(remove(node_bits.begin(),node_bits.end(),' '),node_bits.end());
        nodes[current_node]=strtol(node_bits.c_str(),NULL,2);
        current_node++;

    }


    clustering(nodes,total_nodes,bits_per_node);

    /*

    cout<<nodes.size()<<endl;
    cout<<total_nodes<<endl;
    cout<<bits_per_node<<endl;

    for(i=total_nodes-10;i<=total_nodes;i++)
         cout<<int(nodes[i])<<endl;

    */

}



void clustering(vector< int > &nodes, int total_nodes, int bits_per_node)
{

    int i,j,parent1,parent2,bit_count,int_num;
    unordered_set< int > node_set;

    sort(nodes.begin(),nodes.end());
    nodes.erase( unique( nodes.begin(), nodes.end() ), nodes.end() );

    //add nodes to hashmap
    for(i=1;i!=nodes.size();i++)
        node_set.insert(nodes[i]);


    vector< int > hamming_distance_1(0);
    vector< int > hamming_distance_2(0);
    vector< edge > nodes_with_ham1or2(0);
    edge temp;
    bitset<24> num;


    for(i=0;i<16777215;i++)
    {
        num=i;
        bit_count=num.count();
        if(bit_count==1)
        {
           int_num=num.to_ulong();
            hamming_distance_1.push_back(int_num);
        }
        if(bit_count==2)
        {
           int_num=num.to_ulong();
           hamming_distance_2.push_back(int_num);
        }
    }



    //map< int,int > nodes_with_ham1or2_hashmap;
    bitset<24> find_node;
    int find_node_int;

    for(i=1;i!=nodes.size();i++)
    {
        for(j=0;j!=hamming_distance_1.size();j++)
        {
            find_node=bitset<24> (nodes[i]) ^ bitset<24> (hamming_distance_1[j]);
            find_node_int=find_node.to_ulong();

            if( node_set.find(find_node_int)!=node_set.end() )
            {
                temp.node1=nodes[i];
                temp.node2=find_node_int;
                temp.ham_dist=1;
                nodes_with_ham1or2.push_back(temp);
            }
        }
    }


    for(i=1;i!=nodes.size();i++)
    {

        for(j=0;j!=hamming_distance_2.size();j++)
        {
            find_node=bitset<24> (nodes[i]) ^ bitset<24>(hamming_distance_2[j]);
            find_node_int=find_node.to_ulong();

            if( node_set.find(find_node_int)!=node_set.end() )
            {
                temp.node1=nodes[i];
                temp.node2=find_node_int;
                temp.ham_dist=2;
                nodes_with_ham1or2.push_back(temp);
            }
        }

    }


    vector< int > node_list(0);
    for(i=0;i!=nodes_with_ham1or2.size();i++)
    {
        node_list.push_back(nodes_with_ham1or2[i].node1);
        //node_list.push_back(nodes_with_ham1or2[i].node2);
    }


    sort(node_list.begin(),node_list.end());
    node_list.erase( unique( node_list.begin(), node_list.end() ), node_list.end() );



    vector< int > rank(node_list[node_list.size()-1]); //maximum node value(range of nodes)
    vector< int > parent(node_list[node_list.size()-1]);
    boost::disjoint_sets<int*,int* > graph_set(&rank[0], &parent[0]);
    vector<edge> MST(0);



    for(int i=0;i!=node_list.size();i++)
    {
        graph_set.make_set(node_list[i]);
    }


    vector< int >::iterator iter_first,iter_last;
    iter_first=node_list.begin();
    iter_last=node_list.end();


    for(i=0;i!=nodes_with_ham1or2.size();i++)
    {
        parent1=graph_set.find_set(nodes_with_ham1or2[i].node1);
        parent2=graph_set.find_set(nodes_with_ham1or2[i].node2);

        if(parent1 != parent2)
        {
            graph_set.link(parent1, parent2);
            //MST.push_back(nodes_with_ham1or2[i]);
        }
    }


    cout<<"\nMaximum number of clusters with spacing at least 3 = "<<(graph_set.count_sets(iter_first,iter_last))+(nodes.size()-1)-node_list.size()<<endl;

}
