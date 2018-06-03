#include <iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include <stdlib.h>

using namespace std;

void knapsack(int, int, vector< int >&, vector< int >& );


int main()
{
    ifstream input;
    input.open("knapsack1.txt");
    if(input.fail())
    {
        cout<<"Error opening file\n";
        exit(1);
    }

    int temp,num=0,i=0,knapsack_size,total_items;

    input>>knapsack_size;
    input>>total_items;

    vector< int > value(1);
    vector< int > weight(1);
    while(input>>temp)
    {
        value.push_back(temp);
        input>>temp;
        weight.push_back(temp);
    }

    knapsack(knapsack_size,total_items,value,weight);


    /*
    cout<<knapsack_size<<endl;
    cout<<total_items<<endl;
    cout<<value.size()<<endl;
    cout<<weight.size()<<endl;

    for(i=1;i!=weight.size();i++)
        cout<<i<<" "<<value[i]<<" "<<weight[i]<<endl;
    */
}


void knapsack(int knapsack_size, int total_items, vector< int >&value, vector< int >&weight )
{
    vector< vector <int> > knapsack(total_items+1,vector<int>(knapsack_size+1));
    int i,w;

    for(i=0;i<=knapsack_size;i++)
        knapsack[0][i]=0;

    for(i=1;i<=total_items;i++)
        knapsack[i][0]=0;

    for(i=1;i<knapsack.size();i++)
        for(w=0;w<=knapsack_size;w++)
        {
            if(weight[i]<=w) // item i can be part of the solution
            {
                if(value[i] + knapsack[i-1][w-weight[i]] > knapsack[i-1][w])
                    knapsack[i][w] = value[i] + knapsack[i-1][w-weight[i]];
                else
                    knapsack[i][w] = knapsack[i-1][w];
            }
            else
                knapsack[i][w] = knapsack[i-1][w]; // wi > w

        }

    i=total_items;
    int k=knapsack_size,knapsack_max_value;
    vector <int> knapsack_item(0);
    while ( i>0 && k>0 )
    {
        if (knapsack[i][k] != knapsack[i-1][k]) //then mark the ith item as in the knapsack
        {
            k=k-weight[i];
            knapsack_item.push_back(i);
            i=i-1;
        }
        else
            i=i-1;

    }

    knapsack_max_value=knapsack[total_items][knapsack_size];

    cout<<"\nMaximum knapsack value = "<<knapsack_max_value<<endl<<endl;

    cout<<"Item\tvalue weight\n";
    reverse(knapsack_item.begin(),knapsack_item.end());
    for(i=0;i!=knapsack_item.size();i++)
        cout<<knapsack_item[i]<<"\t"<<value[knapsack_item[i]]<<" "<<weight[knapsack_item[i]]<<endl;

}
