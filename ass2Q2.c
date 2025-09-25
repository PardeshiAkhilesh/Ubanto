#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<string.h>
#include<sys/stat.h>
#include<dirent.h>
#include<stdlib.h>

void list(char c,char *filename)
{
    DIR *dir;
    int cnt=0;
    struct dirent *entry;
    struct stat buff;
    if((dir=opendir(filename))==NULL)
    {
        printf("Directory not found\n");
        return;
    }
    switch (c)
    {
        case 'f':
            while((entry=readdir(dir)) != NULL)
            {
                printf("%s\n",entry->d_name);
            }
            break;
        case 'n':
            while((entry=readdir(dir)) != NULL)
            {
                cnt++;
            }
            printf("Total no. of entries = %d\n",cnt);
            break;
        case 'i':
            while((entry=readdir(dir)) != NULL)
            {
                printf("\n%s \t %ld\n",entry->d_name,entry->d_ino);
            }
            break;
    }
}

int main()
{
    char command[60],t1[30],t2[40],t3[50],t4[40];
    int n;
    system("clear");
    while(1)
    {
        printf("$myshell $");
        fflush(stdin);
        fgets(command,60,stdin);
        n = sscanf(command,"%s %s %s %s",t1,t2,t3,t4);
        switch(n)
        {
            case 1:
                if(strcmp(t1,"exit")==0)
                    exit(1);
                if(!fork())
                {
                    execlp(t1,t1,NULL);
                    perror(t1);
                }
                break;
            case 2:
                if(!fork())
                {
                    execlp(t1,t1,t1,NULL);
                    perror(t1);
                }
                break;
            case 3:
                if(strcmp(t1,"list")==0)
                {
                    list(t2[0],t3);
                }
                else
                {
                    if(!fork())
                    {
                        execlp(t1,t1,t2,t3,NULL);
                        perror(t1);
                    }
                }
                break;
            case 4:
                if(!fork())
                {
                    execlp(t1,t1,t2,t3,t4,NULL);
                    perror(t1);
                }
        }
    }
}