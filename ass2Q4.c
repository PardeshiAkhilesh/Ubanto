#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
#include<string.h>

void search(char c, char *s,char *filename)
{
    int handle,i=1,cnt=0,j=0;
    char ch,buff[80],*p;
    handle = open(filename,O_RDONLY);
    if (handle==-1)
    {
        printf("File %s not found\n",filename);
        return;
    }

    switch(c)
    {
        case 'f':
        while(read(handle,&ch,1) != 0)
        {
            if(ch=='\n')
            {
                buff[j] = '\0';
                j=0;
                if(strstr(buff,s) != NULL){
                    printf("%d : %s\n",i,buff);
                    break;
                }
                i++;
            }
            else
                buff[j++] = ch;
        }
        break;

        case 'c':
        while(read(handle,&ch,1) != 0)
        {
            if(ch == '\n')
            {
                buff[j]='\0';
                j=0;
                if(strstr(buff,s) != NULL)
                {
                    p=buff;
                    while((p=strstr(p,s)) != NULL)
                    {
                        cnt++;
                        p++;
                    }
                }
                else
                buff[j++] = ch;
            }
        }
        printf("Total No. of Occurrences = %d\n",cnt);
        break;
        case 'a':
        while(read(handle,&ch,1) != 0)
        {
            if(ch=='\n')
            {
                buff[j] = '\0';
                j=0;
                if(strstr(buff,s) != NULL)
                printf("%d : %s\n",i,buff);
                i++;
            }
            else
            buff[j++] = ch;
        }
    }
    close(handle);
}

int main()
{
    char command[20],t1[20],t2[20],t3[20],t4[20];
    int n;
    system("clear");
    while(1)
    {
        printf("$myshell ");
        fflush(stdin);
        fgets(command,20,stdin);
        command[strcspn(command, "\n")] = '\0';
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
                if(!fork())
                {
                    execlp(t1,t1,t2,t3,t4,NULL);
                    perror(t1);
                }
                break;
            case 4:
                if(strcmp(t1,"search")==0)
                search(t2[0],t3,t4);
                else{
                    if(!fork())
                    {
                        execlp(t1,t1,t2,t3,t4,NULL);
                        perror(t1);
                    }
                }
                break;
        }
    }
}