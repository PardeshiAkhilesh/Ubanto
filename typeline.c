#include<stdio.h>
#include<sys/types.h>
#include<fcntl.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/stat.h>

void typeline(char *s,char *filename)
{
    int i=1,handle;
    char ch;
    handle = open(filename,O_RDONLY);
    if(handle==-1)
    {
        printf("File Not FOund");
        return;
    }

    if(strcmp(s,"a") == 0)
    {
        while(read(handle,&ch,1) != 0)
        {
            printf("%c",ch);
        }
    }

    int n=atoi(s);

    if(n>0)
    {
        while(read(handle,&ch,1) != 0)
        {
            if(ch=='\n')
            i++;
            if(i==n)
            break;
            printf("%c",ch);
        }
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
            typeline(t2,t3);
            if(!fork())
            {
                execlp(t1,t1,t2,t3,NULL);
                perror(t1);
            }
    }
}