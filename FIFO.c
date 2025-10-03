#include<stdio.h>
int main()
{
    int i,j,n,pages[50],frame[10],no,avail,count = 0;
    printf("Enter number of pages: ");
    scanf("%d",&n);
    printf("Enter page number: ");
    for(i=0;i<n;i++)
        scanf("%d",&pages[i]);
    printf("Enter number of frames: ");
    scanf("%d",&no);
    for(i=0;i<no;i++)
        frame[i]=-1;
    j=0;
    printf("\nRef String\t Page Frames\t Status\n");
    printf("------------------------------------------------\n");
    for(i=0;i<n;i++)
    {
        avail=0;
        for(int k=0;k<no;k++)
        {
            if(frame[k] == pages[i])
            {
                avail = 1;
                break;
            }
        }
        if (avail == 0)
        {
            frame[j] = pages[i];
            j = (j+1) % no;
            count++;
        }
        printf("    %d\t\t",pages[i]);
        for(int k=0;k<no;k++)
        {
            if(frame[k]!=-1)
                printf("%d ",frame[k]);
            else
                printf("- ");
        }
        if(avail == 0)
        printf("\t\t Fault\n");
        else
        printf("\t\t Hit\n");

        printf("\n");
    }
    printf("Total Page Faults = %d\n",count);
    return 0;
}