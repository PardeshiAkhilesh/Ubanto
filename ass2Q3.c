#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>

void typeline(char *s,char *filename)
{
    int handle,i=0,cnt=0,n;
    char ch;
    handle = open(filename,O_RDONLY);
    if(handle == -1)
    {
        printf("File not found\n");
        return;
    }
    if(strcmp(s,"a")==0)
    {
        while(read(handle,&ch,1) !=0)
        printf("%c",ch);
        close(handle);
        return;
    }

    n = atoi(s);

    if(n>0)
    {
        while(read(handle,&ch,1) !=0)
        {
            if(ch=='\n')
            i++;
            if(i==n)
            break;
            printf("%c",ch);
        }
        printf("\n");
        close(handle);
        return;
    }

    if(n<0)
    {
        while(read(handle,&ch,1) !=0) // First loop → counts total number of lines (cnt).
        {
            if(ch=='\n')
            cnt++;
        }
        lseek(handle,0,SEEK_SET); //lseek(handle, 0, SEEK_SET) → moves file pointer back to start.
        while(read(handle,&ch,1) !=0) // Second loop → skips lines until reaching (cnt + n - 1) (meaning last |n| lines).
        {
            if(ch=='\n')
            i++;
            if(i==cnt+n-1)
            break;
        }
        while(read(handle,&ch,1) != 0)
            printf("%c",ch);
        printf("\n");
        close(handle);
    }
}

int main()
{
    char command[20],t1[20],t2[20],t3[20],t4[20];
    int n;
    system("clear");
    while(1)
    {
        printf("$myshell $");
        fflush(stdin);
        fgets(command,20,stdin);
        n = sscanf(command,"%s %s %s %s",t1,t2,t3,t4);
        switch(n)
        {
            case 1:
                if(strcmp(t1,"exit")==0)
                exit(1);
                if(fork()==0)
                {
                    execlp(t1,t1,NULL);
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
                if(strcmp(t1,"typeline")==0)
                typeline(t2,t3);
                else{
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