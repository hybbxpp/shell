#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
//#include <sys/wait.h>
#include <errno.h>
#include <sys/stat.h>
void NAME();
void path();
void aim(char get[1024]);
int turn(char *getr);
void mid(int get);
//void program();
void grep_function();

char *info[1024];

int main(){
    char input[1024],*order,*location;
    int i = 0;
    NAME();
    while(1){
        path();
        memset(input,0,1024);
        fgets(input,1024,stdin);
        input[strlen(input)-1]=0;
        info[0] = strtok(input, " ");
        while(info[i] != NULL){
            i += 1;
            info[i] = strtok(NULL, " ");
        }
        info[i+1] = NULL;
        mid(turn(info[0]));
    }
    printf("\n");
    return 0;
}



void NAME(){
    fprintf(stdout,"XJCO2211 Simplified Shell by Butterburger\n");
}

void path(){
    char path[256];
    getcwd(path, sizeof(path));
    printf("%s$", path);
}

void aim(char *location){
    if(chdir(location) == -1){
        perror("Error");
    }
}

int turn(char *getr){
    if(strcasecmp(getr,"cd") == 0)
        return 1;
	else if(strcasecmp(getr,"exit") == 0)
		exit(1);
    else if(strcasecmp(getr,"ex") == 0)
        return 2;
    else if(strcasecmp(getr,"mygrep") == 0)
        return 3;
    else
        printf("Error: Invalid argument\n");
}

/*void program(){
    pid_t pid;
    int status;
    pid = fork();
    if(pid == 0){
        if(execvp(info[1],info)==-1)
            perror("error");
        exit(EXIT_FAILURE);
    }
    else if(pid < 0)
        perror("Failure");
    else{
        do{
            waitpid(pid, &status, WUNTRACED);
        }
        while(!WIFEXITED(status) && !WIFSIGNALED(status));
    }
}*/

void mid(int get){
    switch(get){
        case 1:aim(info[1]);break;
        //case 2:program();break;
        case 3:grep_function();break;
    }
}

void grep_function(){
    if(info[1] == NULL || info[2] == NULL || info[3] == NULL){
        printf("Error: wrong input\n");
    }
    else{
        FILE *fp;
        int count = 0;
        char p[4096];
        char *str1 = p,*str2 = info[2],*save;
        if(strcmp(info[1],"-c") != 0)
            printf("Error: command not found\n");
        else{
            fp = fopen(info[3],"r");
            if(fp == NULL)
                printf("Error: no such file or direction\n");
            else{
                fgets(p,4096,fp);
                while(str1)
                {
                    if((save=strstr(str1,str2)) != NULL){
                        count++;
                        str1 = ++save;
                    }
                    else
                        break;
                }
                printf("%d\n",count);
            }
        }
    }
}