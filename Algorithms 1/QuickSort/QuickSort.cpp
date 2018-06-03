#include <iostream>

using namespace std;

int partitioner(int [],int ,int );
void quicksort(int [],int ,int );

int main()
{
    int arr[20]={44,22,34,32,11,23,76,67,45,34,34,66,99,1,5,54,53,21,89,49};

    cout<<"Array Before Sort: ";
    for(int i=0;i<20;i++)
        cout<<arr[i]<<" ";
    cout<<endl;

    quicksort(arr,0,19);

    cout<<endl;

    cout<<"Array After Sort: ";
    for(int i=0;i<20;i++)
        cout<<arr[i]<<" ";

    cout<<endl;
}

void quicksort(int arr[],int l,int r)
{
    if(l<r)
    {
        int p=partitioner(arr,l,r);
        quicksort(arr,l,p-1);
        quicksort(arr,p+1,r);
    }

}

int partitioner(int arr[],int l,int r)
{

    int i=l+1,j=r,pivot=arr[l],temp;


    while(i<=j)
    {
        while(arr[i]<=pivot)
               i++;

        while(arr[j]>pivot)
               j--;

        if(i<j)
        {
            temp=arr[i];
            arr[i]=arr[j];
            arr[j]=temp;
        }

    }

    arr[l]=arr[j];
    arr[j]=pivot;
    return j;

}
