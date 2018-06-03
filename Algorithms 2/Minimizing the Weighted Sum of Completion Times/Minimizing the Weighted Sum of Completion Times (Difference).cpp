#include <iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include <queue>
#include <stdlib.h>

using namespace std;

struct job_info{
    int weight;
    int length;
};

class compare {
	public:
		bool const operator()(job_info  &job1, job_info  &job2)
        {
            if(job1.weight-job1.length<job2.weight-job2.length)
                   return true;
            if(job1.weight-job1.length>job2.weight-job2.length)
                   return false;
            if(job1.weight-job1.length==job2.weight-job2.length)
            {
              if(job1.weight<=job2.weight)
                 return true;
              if(job1.weight>job2.weight)
                 return false;
            }
         }
};


void calculate_weighted_sum(vector< job_info > & );


int main()
{
    ifstream input;
    input.open("jobs.txt");
    if(input.fail())
    {
        cout<<"Error opening file\n";
        exit(1);
    }

    int i=0,j=0,total_jobs;

    vector< job_info > jobs(0);
    job_info temp;

    input>>total_jobs;
    while(!input.eof())
    {
        input>>temp.weight;
        input>>temp.length;
        jobs.push_back(temp);
    }

    jobs.resize(jobs.size()-1);
    calculate_weighted_sum(jobs);

    /*
    cout<<jobs.size()<<endl;
    cout<<total_jobs<<endl;

    for(i=0;i!=jobs.size();i++)
        cout<<jobs[i].weight<<" "<<jobs[i].length<<"\t";
    */
}


void calculate_weighted_sum(vector< job_info > &jobs )
{
    priority_queue< int, vector< job_info > , compare > max_heap;

    for(int i=0;i!=jobs.size();i++)
         max_heap.push(jobs[i]);

    long long int current_sum_length=0,weighted_sum=0;
    job_info temp;

    while(!max_heap.empty())
    {
        temp=max_heap.top();
        current_sum_length+=temp.length;
        weighted_sum+=current_sum_length*temp.weight;
        max_heap.pop();
    }


    cout<<"Weighted sum of completion times in decreasing order of difference = "<<weighted_sum<<endl;
}
