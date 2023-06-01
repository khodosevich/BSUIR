#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

struct record_s {
    char name[80];
    char address[80];
    char semester;
};

char* getRandomName(char **names)
{
    int index = rand() % 10;
    return names[index];
}

char* getRandomAdress(char **adresses)
{
    int index = rand() % 6;
    return adresses[index];
}

int getRandomSemester(int *semesters)
{
    int index = rand() % 8;
    return semesters[index];
}


int main()
{
    char* names[10] = {"Matvey", "Vorobey", "Ivan", "Vasya", "Sergey", "Max", "Victor", "Dima", "Rick", "Elisha"};
    char* adresses[6] = {"Minsk", "Grodno", "Gomel", "Brest", "Mogilev", "Vitebsk"};
    int semesters[8] = {1, 2, 3, 4, 5, 6, 7, 8};

    struct record_s arrayRecords[10];
    for(int i = 0; i< 10; i++)
    {
        sprintf(arrayRecords[i].name, getRandomName(names), i);
        sprintf(arrayRecords[i].address, getRandomAdress(adresses), i);
        arrayRecords[i].semester = getRandomSemester(semesters);
    }
    int fd = open("records.bin", O_RDWR);
    if (fd == -1) {
        perror("open");
        exit(1);
    }

    write(fd, &arrayRecords, sizeof(arrayRecords));
    return 0;
}