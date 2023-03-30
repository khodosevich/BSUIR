#include "stdio.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char* argv[])
{
    printf("%s pid: %d ppid: %d \n", argv[0], getpid(), getppid());

    FILE *fp;
    fp = fopen(argv[1], "r");
    
    char* key = (char*) malloc(255*sizeof(char));
    char* key_tmp = (char*) malloc(255*sizeof(char));


    while(!feof(fp))
    {
        fscanf(fp, "%s", key);
        if(!strcmp(key, key_tmp))
            break;
        printf("|%s = %s \n", key, getenv(key));
        strcpy(key_tmp, key);
    }

    fclose(fp);

    return 0;

}
