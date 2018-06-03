#include <iostream>

using namespace std;

void mergesort(int [],int ,int );
void merger(int [],int ,int ,int );
int inversions=0;

int main()
{
    int arr[20]={44,22,34,32,11,23,76,67,45,34,34,66,99,1,5,54,53,21,89,49};

    cout<<"Array Before Sort:";
    for(int i=0;i<20;i++)
        cout<<arr[i]<<" ";
    cout<<endl;

    mergesort(arr,0,19);

    cout<<endl;

    cout<<"Array After Sort:";
    for(int i=0;i<20;i++)
        cout<<arr[i]<<" ";

    cout<<endl<<"Inversion Count:"<<inversions<<endl;
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
