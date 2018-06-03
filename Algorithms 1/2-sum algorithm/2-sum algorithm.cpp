#include <iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include <map>
#include <stdlib.h>

using namespace std;

void two_sum(vector< long long int > & );


int main()
{
    ifstream input;
    input.open("2 sum problem.txt");
    if(input.fail())
    {
        cout<<"Error opening file\n";
        exit(1);
    }

    int i=0,j=0;
    long long int temp=0;
    char new_line;
    vector< long long int > integers(0);

    while(!input.eof())
    {
        input>>temp;
        integers.push_back(temp);
    }

    integers.resize(integers.size()-1);
    two_sum(integers);

    /*
    cout<<integers.size()<<endl;
    for(i=0;i!=integers.size();i++)
        cout<<integers[i]<<" ";
    */
}



void two_sum(vector< long long int > &integers )
{

    long long int i,j,count=0,look_up,index1,index2;

    sort(integers.begin(),integers.end());
    integers.erase( unique( integers.begin(), integers.end() ), integers.end() );
    multimap< long long int,long long int > hashmap;
    map< int,int> sums;


    for(i=0;i!=integers.size();i++)
        hashmap.insert(make_pair(integers[i]/20000,integers[i]));


    for(i=0;i!=integers.size();i++)
    {
        index1=(-integers[i]-10000)/20000;
        index2=(-integers[i]+10000)/20000;

        for(multimap< long long int,long long int >::iterator iter=hashmap.lower_bound(index1);iter!=hashmap.upper_bound(index2);iter++)
        {
            if(integers[i]+(iter->second)>=-10000 && integers[i]+(iter->second)<=10000)
            {
                if(sums.find(integers[i]+(iter->second))==sums.end())
                {   count++;
                    sums.insert(make_pair(integers[i]+(iter->second),count));
                }
            }

        }
    }

    cout<<sums.size()<<endl;
    for(map< int,int>::iterator iter=sums.begin();iter!=sums.end();iter++)
        cout<<iter->first<<endl;

}
