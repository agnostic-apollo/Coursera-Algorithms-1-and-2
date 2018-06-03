#include <iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include <queue>
#include <stdlib.h>

using namespace std;

void median_maintenance(vector< int > & );


int main()
{
    ifstream input;
    input.open("Median.txt");
    if(input.fail())
    {
        cout<<"Error opening file\n";
        exit(1);
    }

    int i=0,j=0,temp=0;

    vector< int > integers(0);

    while(!input.eof())
    {
        input>>temp;
        integers.push_back(temp);
    }

    integers.resize(integers.size()-1);
    median_maintenance(integers);

    /*
    cout<<integers.size()<<endl;
    for(i=0;i!=integers.size();i++)
        cout<<integers[i]<<" ";
    */
}



void median_maintenance(vector< int > &integers )
{

    int i,j,median=0,median_sums=0,left_size,right_size;

    priority_queue< int, vector<int>, less<int> > left_heap;
    priority_queue< int, vector<int>, greater<int> > right_heap;

    median_sums=integers[0];
    left_heap.push(integers[0]);


    for(i=1;i!=integers.size();i++)
    {
        //add integer to heap
        if(integers[i]<left_heap.top())
            left_heap.push(integers[i]);
        else
            right_heap.push(integers[i]);

        //balance heaps
        left_size=left_heap.size();
        right_size=right_heap.size();

        if(left_size-right_size>1)
        {
            right_heap.push(left_heap.top());
            left_heap.pop();
        }

        if(right_size-left_size>1)
        {
            left_heap.push(right_heap.top());
            right_heap.pop();
        }

        //calculate median
        left_size=left_heap.size();
        right_size=right_heap.size();

        if(right_size>left_size)
            median=right_heap.top();
        else
            median=left_heap.top();

        median_sums=median_sums+median;
    }

    cout<<"Sum of medians modullo 10000 = "<<median_sums%10000<<endl;
}
