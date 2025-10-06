#include<stdio.h>
int main()
{
    int arr[3] = {3,2,4};
    int n = sizeof(arr) / sizeof(arr[0]);
    int count = 0;
    int a;
    for(int i=0;i<n-1;i++)
    {
        for(int j=i+1;j<n;j++)
        {
            a=arr[i]+arr[j];
            int isPrime=1;
            for(int k=2;k<=a/2;k++)
            {
                if(a%k==0)
                {
                    isPrime=0;
                    break;
                }
            }
            if(isPrime==1)
            {
                count++;
                printf("%d %d\n",arr[i],arr[j]);
            }
        }
    }
    printf("%d" ,count); 
    printf("\n");
}