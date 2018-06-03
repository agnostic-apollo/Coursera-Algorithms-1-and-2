#include <iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include <stdlib.h>

using namespace std;

int max(int, int );
int knapsack(int, int, vector< int >&, vector< int >&, vector< vector <int> >& );



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
    vector< vector <int> > calculated(total_items+1,vector<int>(knapsack_size+1,0));

    while(input>>temp)
    {
        value.push_back(temp);
        input>>temp;
        weight.push_back(temp);
    }

    cout<<"\nMaximum knapsack value = "<<knapsack(total_items,knapsack_size,value,weight,calculated)<<endl;


    /*
    cout<<knapsack_size<<endl;
    cout<<total_items<<endl;
    cout<<value.size()<<endl;
    cout<<weight.size()<<endl;

    for(i=1;i!=weight.size();i++)
        cout<<i<<" "<<value[i]<<" "<<weight[i]<<endl;
    */
}


int knapsack(int i, int W, vector< int >&value, vector< int >&weight, vector< vector <int> >&calculated)
{
    //cout<<i<<" ";
    if (i == 0 || W<=0 )
        return 0;

    if (calculated[i][W]!=0)
        return calculated[i][W];


    if (weight[i] > W)
        return knapsack(i-1,W,value,weight,calculated);
     else
     {
        calculated[i][W]=max(knapsack(i-1,W,value,weight,calculated) , knapsack(i-1,W-weight[i],value,weight,calculated) + value[i]);
        return calculated[i][W];
     }
}

int max(int value_1, int value_2)
{
    if(value_1>value_2)
        return value_1;
    else
        return value_2;

}

