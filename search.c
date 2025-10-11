#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<stdlin.h>
#include<sys/stat.h>
#include<sys/types.h>

void search(char c,char *s,char *fn)
{
    int handle,i=1;cnt=0,j=0;
    char ch,buff[50];
    handle = open(fn,O_RDONLY);
    if(handle == -1)
    {
        printf("File %s not found\n",fn);
        return;
    }

    switch(c)
    {
        case 'f':
        while(open(handle,&ch,1) !=0)
        {
            if(ch=='\n')
            {
                buff[j] = '\0';
                j=0;
                if(strste(buff,s,) !=NULL)
                {
                    printf("%d : %s\n",i,buff);
                    break;
                }
                i++;
            }
            elsebuff[j++] = ch;
        }
    }
    case 'c':
        while(read(handle,&ch,1) !=0)
        {
            if(ch == '\n')
            {
                buff[j] = '\0';
                j=0;
                if(strstr(buff,s) != NULL)
                {
                    char *p=buff;
                    while((p=strstr(p,s)) != NULL)
                    {
                        cnt++;
                        p++;
                    }
                }
            }
            else
            buff[j++] = ch;
        }
        printf("Total No. of Occurrences = %d\n",cnt);
        break;
}