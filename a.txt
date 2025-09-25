#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>

void count(char ch, char *filename)
{
    int lc=0,wc=0,cc=0;
    int handle;
    char c;
    handle = open(filename,O_RDONLY);
    if (handle==-1)
    {
        printf("\n File not Found %s\n",filename);
        return;
    }

    while (read(handle,&c,1) > 0)
    {
        if (c== ' ' || c== '\t')
        wc++;
        else if (c == '\n')
        {
            lc++;
            wc++;
        }
        cc++;
    }

    close(handle);

    switch (ch)
    {
        case 'c':
            printf("Total no of character = %d\n",cc);
            break;
        case 'w':
            printf("Total no of words = %d\n",wc);
            break;
        case 'l':
            printf("Total no of Lines = %d\n",lc);
            break;
    }
}

int main()
{
    char command[60],t1[20],t2[20],t3[30];
    int n;

    system("clear");

    while(1)
    {
        printf("$myshell $");
        fgets(command, 60,stdin);
        n = sscanf(command, "%s %s %s %s",t1,t2,t3,t3);
        switch(n)
        {
            case 1:
                if (strcmp(t1, "exit")==0)
                exit(0);
                if (fork() == 0)
                execlp(t1,t1,NULL);
                wait(NULL);
                break;
            case 2:
                if (fork() == 0)
                execlp(t1,t1,t2,NULL);
                wait(NULL);
                break;
            case 3:
                if(strcmp(t1, "count")==0)
                count(t2[0],t3);
                else
                {
                    if (fork()==0)
                    execlp(t1,t1,t2,t3,NULL);
                    wait(NULL);
                }
                break;
        }
    }
}