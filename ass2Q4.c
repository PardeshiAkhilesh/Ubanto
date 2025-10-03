#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
void search(char c, char *filename, char *pattern) {
    int fd, i = 0, cnt = 0, j = 0;
    char ch, buff[256];
    char *p;

    fd = open(filename, O_RDONLY);
    if (fd == -1) {
        printf("The file does not exist\n");
        return;
    }

    switch (c) {
        case 'a': // print all lines with pattern
            while (read(fd, &ch, 1) > 0) {
                if (ch == '\n') {
                    buff[j] = '\0';
                    j = 0;
                    if (strstr(buff, pattern) != NULL) {
                        printf("%d: %s\n", i, buff);
                    }
                    i++;
                } else {
                    buff[j++] = ch;
                }
            }
            break;

        case 'c': // count occurrences
            while (read(fd, &ch, 1) > 0) {
                if (ch == '\n') {
                    buff[j] = '\0';
                    j = 0;
                    if (strstr(buff, pattern) != NULL) {
                        p = buff;
                        while ((p = strstr(p, pattern)) != NULL) {
                            cnt++;
                            p++;
                        }
                    }
                } else {
                    buff[j++] = ch;
                }
            }
            printf("The total occurrences: %d\n", cnt);
            break;

        default:
            printf("Invalid option. Use 'a' or 'c'.\n");
    }

    close(fd);
}
    int handles,i=0,cnt=0,n,j=0;
    char ch,buff[80],*f;
    if((handles=open(fn,O_RDONLY))==-1){
        printf("the file does exist");
        return;
    }
    switch (c)
    {
    case 'f':
    while(read(handles,&ch,1)==0){
        if(ch=='\n'){

            buff[j]='\0';
            j=0;
            if(strstr(buff,s)!=NULL){
                printf("%d %s",i,buff);
                break;
            }
            i++;

        }else{
            buff[j++]=ch;

        }
        
    }
    
        /* code */
        break;
        case 'c':
        while(read(handles,&ch,1)==0){
            if(ch=='\n'){
                buff[j]='\0';
            j=0;
            if(strstr(buff,s)!=NULL){
p=buff;
while((p=strstr(p,s))!=NULL){
    cnt++;
    p++;
}

}
            }else
            {
                buff[j++]=ch;
            }
            printf("The occurence %d",cnt);

            
        }
        break;
        case 'a':
        while (read(handles,&ch,1)!=0)
        {
            if(ch=='\n')
            {
                buff[j]='\0';
                j=0;

                if(strstr(buff,s)!=NULL)
                printf("%d %s",i,buff);
                i++;
            }
            else
            {
                buff[j++]=ch;
            }
            
            /* code */
        }
        close(handles);
        

    
    default:
        break;
    }

}
void main(){
    int command[80],t1[23],t2[23],t3[53],t4[34];
    system("clear");
    int n;
    while(1){
        printf("Myshells");
        fgets(command,80,stdin);
        fflush(stdin);
        n=sscanf(command,"%s %s %s %s",t1,t2,t3,t4);
        switch (n)
        {
        case 1:
        if(strcmp(t1,"exit")==0){
            exit(0);
            
        }
        if(!fork()){

            execlp(t1,t1,NULL);
            perror(t1);
        }
            break;
        case 2:
        if(!fork()){
            execlp(t1,t1,t2,NULL);
            perror(t1);
        }
        break;
        case 3:
        if(strcmp(t1,"search")==0){
            search(t2,t3,t4);

        }
        if(!fork()){
            execlp(t1,t1,t2,t3,NULL);
            perror(t1);
        }
        break;
        case 4:
        if(!fork()){
            execlp(t1,t1,t2,t3,t4,NULL);
            perror(t1);

        }
        default:printf("Invalid");
            break;
        }
    }
}