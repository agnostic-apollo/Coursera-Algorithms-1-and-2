#include <iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include <stdlib.h>

using namespace std;



struct cal_struct{

    int first;
    int last;
    int value;

};

struct item{

    int value;
    int weight;

};

struct compare{
    bool operator()(const item  &item1, const item &item2)
    {
        return item1.weight>item2.weight;
    }
}comp;


int max(int, int );
int knapsack(int, int, vector< item >& , vector< vector <cal_struct> >& );



int main()
{
    ifstream input;
    input.open("knapsack_big.txt");
    if(input.fail())
    {
        cout<<"Error opening file\n";
        exit(1);
    }

    int temp,num=0,i=0,knapsack_size,total_items;

    input>>knapsack_size;
    input>>total_items;

    vector< item > items(1);

    vector< vector <cal_struct> > calculated(total_items+1,vector<cal_struct>(0));
    item temp_item;

    while(input>>temp)
    {
        temp_item.value=temp;
        input>>temp;
        temp_item.weight=temp;
        items.push_back(temp_item);
    }

    sort(items.begin(),items.end(), comp);
    cout<<"\nMaximum knapsack value = "<<knapsack(total_items,knapsack_size,items,calculated)<<endl;


    /*
    int total_size=0;
    for(i=0;i!=calculated.size();i++)
        total_size+=calculated[i].size();
    cout<<"Total Calculated Vector size = "<<total_size<<endl;

    cout<<knapsack_size<<endl;
    cout<<total_items<<endl;
    cout<<items.size()<<endl;

    for(i=1;i!=items.size();i++)
        cout<<i<<" "<<items[i].value<<" "<<items[i].weight<<endl;
    */
}


int knapsack(int i, int W, vector< item >&items, vector< vector <cal_struct> >&calculated)
{
    //cout<<i<<" ";
    if (i == 0 || W<=0 )
        return 0;

    //check if value already calculated
    for(int j=calculated[i].size()-1;j>=0;j--)
    {
        if(W>=calculated[i][j].first && W<=calculated[i][j].last)
            if (calculated[i][j].value!=0)
                return calculated[i][j].value;
    }

    if (items[i].weight > W)
        return knapsack(i-1,W,items,calculated);
    else
     {
        int max_value;
        max_value=max(knapsack(i-1,W,items,calculated) , knapsack(i-1,W-items[i].weight,items,calculated) + items[i].value);

        //change first and last if max value already exists
        for(int j=calculated[i].size()-1;j>=0;j--)
        {
            if(max_value==calculated[i][j].value)
            {
                if(W<calculated[i][j].first)
                   calculated[i][j].first=W;

                if(W>calculated[i][j].last)
                    calculated[i][j].last=W;

                return calculated[i][j].value;
            }
        }

        //add calculated max value as it didnt exist before
        cal_struct temp;
        temp.first=W;
        temp.last=W;
        temp.value=max_value;
        calculated[i].push_back(temp);
        return max_value;
     }


}

int max(int value_1, int value_2)
{

    if(value_1>value_2)
        return value_1;
    else
        return value_2;

}
