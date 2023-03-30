#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include<unistd.h>
#include<stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>


void Fork(char* argv[], char *env[], char *childFromEnviroment)
{
    pid_t pid = fork();
 
    if (pid == -1) 
    {
        fprintf(stderr, "Unable to fork\n");
    }
    else if (pid > 0) {

        printf("I am parent %d\n", getpid());
        printf("Child is %d\n", pid);

        wait(NULL);
    } 
    else { //child
        printf("In child program %s %s %s", childFromEnviroment, argv[0], argv[1]);
        execve(childFromEnviroment, argv, env);
    }
}



char* Increment(int *counter)
{
 char* name = (char*)malloc(9*sizeof(char));

 strcpy(name, "child_");

 if(*counter>=0&&*counter<10)
 {
    name[6]='0';
    name[7]='0'+*counter;
    name[8]='\0';
    
    (*counter)+=1;
 }
 if(*counter>=10&&*counter<=99)
 {
    name[6]='0'+(*counter/10);
    name[7]='0'+(*counter%10);
    name[8]='\0';

    (*counter)+=1;

    if(*counter == 100) 
        *counter = 0;
 }

 return name;

}

void PrintEnv(char* env[])
{

    for(int i = 0; env[i]!=NULL; i++)
        printf("%s\n", env[i]);

}

int main(int argc, char* argv[], char* env[])
{
PrintEnv(env);

char **newArgv = (char**)malloc(2*sizeof(char*));
newArgv[0]=(char*)malloc(256*sizeof(char));
newArgv[1]=(char*)malloc(256*sizeof(char));

strcpy(newArgv[1], getenv("ENV_PATH"));

int counter = 0;
bool flag = true;

while(true){
    if(flag){
    printf("\n\n\nHello! This is the parent process. \n");
    printf("new process: '+','*' or '&' \n");
    printf("'q' - exit \n");
    flag = false;
    }
    else 
        flag = true;

    rewind(stdin);
    char ch;
    scanf("%c", &ch);
    rewind(stdin);
    switch(ch)
    {
        case '+': 
        {
            char* childFromEnviroment = getenv("CHILD_PATH");
            strcpy(newArgv[0], Increment(&counter));
            Fork(newArgv, env, childFromEnviroment);
            break;
        }
        case '*':
        {
            char* childFromEnviroment = (char*)malloc(256*sizeof(char));
            char* tmp = (char*)malloc(256*sizeof(char));

            for(int i = 0; env[i]!=NULL; i++)
            {
                tmp = env[i];
                char* ptr = strstr(tmp, "CHILD_PATH");

                if(ptr != NULL && ptr == tmp)
                {
                    strcpy(childFromEnviroment, tmp + 11);
                    break;
                }
            }

            strcpy(newArgv[0], Increment(&counter));
            Fork(newArgv, env, childFromEnviroment);
            break;
        }
        case '&':
        {
            extern char** environ;

            char* childFromEnviroment = (char*)malloc(256*sizeof(char));
            char* tmp = (char*)malloc(256*sizeof(char));

            for(int i = 0; environ[i]!=NULL; i++)
            {
                tmp = environ[i];
                char* ptr = strstr(tmp, "CHILD_PATH");

                if(ptr != NULL && ptr == tmp)
                {
                    strcpy(childFromEnviroment, tmp + 11);
                    break;
                }
            }
            strcpy(newArgv[0], Increment(&counter));
            Fork(newArgv, env, childFromEnviroment);

            break;
        }
        case 'q':
        {
            exit(0);
        }
        default: break;
    }

}
    
    return 0;
}
