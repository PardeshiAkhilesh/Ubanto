#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<dirent.h>
#include<sys/types.h>

void list(char c,char *filename)
{
    DIR *dir;
    int cnt=0;
    struct dirent *entry;
    if((dir=opendir(filename))==NULL)
    {
        printf("Directory not found\n");
        return;
    }

    switch(c)
    {
        case 'f':
        while((entry=readdir(dir)) !=NULL)
        {
            printf("%s\n",entry->d_name);
        } 
        break;
        case 'n':
        while((entry=readdir(dir)) != NULL)
        {
            cnt++;
        }
        printf("Total no, of entries = %d\n",cnt);
        break;
    }
}

int main()
{
    char command[50],t1[10],t2[10],t3[10],t4[10];
    int n;
    fflush(stdin);
    fgets(command,50,stdin);
    n = sscanf(command,"%s %s %s %s",t1,t2,t3,t4);
    switch(n)
    {
        case 1:
            if(strcmp(t1,"exit")==0)
            exit(0);
        if(!fork())
        {
            execlp(t1,t2,NULL);
            perror(t1);
        }
        break;
        case 2:
            if(!fork())
            {
                execlp(t1,t1,t2,NULL);
                perror(t1);
            }
            break;
        case 3:
            if(strcmp(t1,"typeline") == 0)
            list(t2[0],t3);
            if(!fork())
            {
                execlp(t1,t1,t2,t3,NULL);
                perror(t1);
            }
    }
}