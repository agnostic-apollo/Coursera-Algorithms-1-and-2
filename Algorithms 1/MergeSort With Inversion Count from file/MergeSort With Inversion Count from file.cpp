#include <iostream>
#include<fstream>
#include <stdlib.h>

using namespace std;

void mergesort(int [],int ,int );
void merger(int [],int ,int ,int );
long long int inversions=0;

int main()
{
    ifstream input;
    input.open("IntegerArray.txt");

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

    mergesort(arr,0,num);

    for(i=0;i<num;i++)
        cout<<arr[i]<<" ";

    cout<<endl<<"Inversion Count:"<<inversions<<endl;
    delete[] arr;

}

void mergesort(int arr[],int l,int r)
{
    if(l<r)
    {
        int m=l+(r-l)/2;

        mergesort(arr,l,m);
        mergesort(arr,m+1,r);
        merger(arr,l,m,r);

    }
}

void merger(int arr[],int l,int m,int r)
{

    const int s=r-l+1;
    int t[s];

    int i=l,j=m+1,k=0;

    for(;;)
    {   if(i<=m && j<=r)
        {
            if(arr[i]<arr[j])
            {
                t[k]=arr[i];
                i++;
            }
            else if(arr[j]<=arr[i])
            {
                t[k]=arr[j];
                j++;
                inversions+=m-i+1;
            }
            k++;
        }
        else
            break;
    }

    while(i<=m)
        {
            t[k]=arr[i];
            i++;
            k++;
        }

    while(j<=r)
        {
            t[k]=arr[j];
            j++;
            k++;
        }

    for(int i=l,k=0;i<=r;i++,k++)
            arr[i]=t[k];

}
