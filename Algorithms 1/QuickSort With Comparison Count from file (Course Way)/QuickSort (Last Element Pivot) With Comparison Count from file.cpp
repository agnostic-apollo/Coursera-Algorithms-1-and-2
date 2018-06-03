#include <iostream>
#include<fstream>
#include <stdlib.h>

using namespace std;

int partitioner(int [],int ,int );
void quicksort(int [],int ,int );
long long int comparisons=0;

int main()
{
    ifstream input;
    input.open("QuickSort.txt");
    if(input.fail())
    {
        cout<<"Error opening file\n";
        exit(1);
    }

    int temp,num=0,i=0;

    while(input>>temp)
        num++;

    input.clear();
    input.seekg(0);

    int *arr=new int[num];

    while(!input.eof())
    {
        input>>arr[i];
        i++;
    }

    quicksort(arr,0,num-1);

    for(i=0;i<num;i++)
        cout<<arr[i]<<" ";

    cout<<endl<<"Comparison Count:"<<comparisons<<endl;
    delete[] arr;


}

void quicksort(int arr[],int l,int r)
{
    if(l<r)
    {
        int p=partitioner(arr,l,r);
        comparisons+=r-l;
        quicksort(arr,l,p-1);
        quicksort(arr,p+1,r);
    }
}

int partitioner(int arr[],int l,int r)
{
    int i=l+1,j,temp;

    temp=arr[r];
    arr[r]=arr[l];
    arr[l]=temp;

    int pivot=arr[l];

    for(j=l+1;j<=r;j++)
    {
        if(arr[j]<arr[l])
        {
            temp=arr[i];
            arr[i]=arr[j];
            arr[j]=temp;
            i++;
        }
    }

    i--;
    temp=arr[l];
    arr[l]=arr[i];
    arr[i]=temp;

    return i;

}
