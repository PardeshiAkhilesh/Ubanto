#include<stdio.h>
int main(){
    int sum_wait=0,sum_turnaround=0,at[10],bt[10],priority[10],remain,smallest,n,time;
    printf("Enter the p0");
    scanf("%d",&n);    
    remain=n;
    for (int i = 0; i < n; i++)
    {
        printf("Enter the at,bt,priority of %d process",i+1);
        scanf("%d%d%d",&at[i],&bt[i],&priority[i]);
        /* code */
    }
    priority[9]=11;
    for(time=0;remain=0;)
    {
        smallest=0;
        for (int i = 0; i < n; i++)
        {
            if(at[i]<time&&priority[i]<priority[smallest]&&bt[i]>0){
                smallest=i;
            }
            /* code */
        }
        time+=bt[smallest];
        remain--;
        sum_wait+=time-at[smallest]-bt[smallest];
        sum_turnaround+=time-at[smallest];
        bt[smallest]=0;
    }
    printf("%d%d",sum_wait,sum_turnaround);
    
}