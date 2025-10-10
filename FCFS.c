#include<stdio.h>
typedef struct process{
    int pno;
    float tat,at,bt,wt,st,ft;
}process;

typedef struct gantt{
    int pno;
    float st,ft;
}gantt;

gantt g[20];
process p[20];

void sortfcfs(int n)
{
    process temp;
    for(int i=0;i<n;i++)
    {
        for(int j=i+1;j<n;j++)
        {
            if(p[i].at > p[j].at)
            {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
}

void getPCB(int n)
{
    for(int i=0;i<n;i++)
    {
        printf("Enter process no :- ");
        scanf("%d",&p[i].pno);
        printf("Enter Arrival time :- ");
        scanf("%f",&p[i].at);
        printf("Enter Bust Time :- ");
        scanf("%f",&p[i].bt);
    }
}

void putPCB(int n)
{
    printf("PNo \t BT\t AT\t ST\t TAT\t FT\n");
    for(int i=0;i<n;i++)
    {
        printf("\n");
        printf("%d \t",p[i].pno);
        printf("%f \t",p[i].bt);
        printf("%f \t",p[i].at);
        printf("%f \t",p[i].st);
        printf("%f \t",p[i].tat);
        printf("%f \t",p[i].ft);
    }
    printf("\n\n\n---------------------------------\n\n\n");
}

void fillPCB(int n)
{
    for(int i=0;i<n;i++)
    {
        p[i].at = g[i].st;
        p[i].wt = p[i].st - p[i].at;
        p[i].ft = g[i].ft;
        p[i].tat = p[i].ft - p[i].at;
    }
}

void fillGantt(int n)
{
    float curr=0;
    for(int i=0;i<n;i++)
    {
        g[i].pno = p[i].pno;
        if(curr > p[i].at)
        g[i].st = curr;

        g[i].st = p[i].at;
        g[i].ft = g[i].st + p[i].bt;
        curr = g[i].ft;
    }
}

void putGantt(int n){
    float curr;
    for (int i = 0; i < n; i++)
    {
        printf("\n%d\t",g[i].pno);
        printf("%f\t",g[i].st);
        printf("%f\t",g[i].ft);
        /* code */
    }
}

int main(){
    int n;
    printf("Enter the no of process");
    scanf("%d",&n);
    getPCB(n);
    sortfcfs(n);
    fillGantt(n);
    fillPCB(n);
    putPCB(n);
    putGantt(n);
}