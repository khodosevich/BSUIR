#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#define MAX_RECORDS 10

struct record_s {
    char name[80];
    char address[80];
    char semester;
};

int fd;
struct flock lock;

void print_record(int rec_no) {

    struct record_s record;
    off_t offset = rec_no * sizeof(record);

    lseek(fd, offset, SEEK_SET);
    read(fd, &record, sizeof(record));
    printf("%d) %s, %s, %d semester\n", rec_no, record.name, record.address, record.semester);
}

void get_record(int rec_no, struct record_s *record) {

    off_t offset = rec_no * sizeof(*record);
    lseek(fd, offset, SEEK_SET);
    read(fd, record, sizeof(*record));
}

void modify_record(int rec_no, struct record_s *record) {

    off_t offset = rec_no * sizeof(*record);
    lseek(fd, offset, SEEK_SET);
    write(fd, record, sizeof(*record));
}

void save_record(struct record_s *record, struct record_s *new_record, int rec_no) {

    if (rec_no < 0 || rec_no >= MAX_RECORDS) {
        printf("Invalid record number\n");
        return;
    }

    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = rec_no * sizeof(*record);
    lock.l_len = sizeof(*record);

    while (fcntl(fd, F_SETLK, &lock) == -1) {
        if (errno == EAGAIN) {
            printf("Record %d is locked. Waiting...\n", rec_no);
            sleep(1);
        } else {
            perror("fcntl");
            exit(1);
        }
    }

    struct record_s current_record;
    lseek(fd, rec_no * sizeof(current_record), SEEK_SET);
    if (read(fd, &current_record, sizeof(current_record)) == -1) {
        perror("read");
        exit(1);
    }

    if (strcmp(current_record.name, record->name) != 0 || strcmp(current_record.address, record->address) != 0 || current_record.semester != record->semester) {

        printf("Record %d has been modified by another process. Trying again...\n", rec_no);
        get_record(rec_no, record);
        lock.l_type = F_UNLCK;
        fcntl(fd, F_SETLK, &lock);
        save_record(record, new_record, rec_no);
    } else {
        printf("Writing...\n");
        modify_record(rec_no, new_record);
        lock.l_type = F_UNLCK;
        fcntl(fd, F_SETLK, &lock);
    }
}

void print_menu() {
    printf("\tEnter:\n");
    printf("1) - view all records\n");
    printf("2) - get a record\n");
    printf("3) - modify and save record\n");
    printf("0) - exit the program\n");
}

int main() {

    system("clear");
    fd = open("records.bin", O_RDWR);
    if (fd == -1) {
        perror("open");
        exit(1);
    }

    print_menu();
    int command;
    int rec_no;
    struct record_s current_record;

    while (1) {
        printf("\n> ");
        scanf("%d", &command);

        switch(command){

            case 1:{
                printf("\tRecords:\n");
                for (int i = 0; i < MAX_RECORDS; i++)
                    print_record(i);
                break;
            }

            case 2:{
                printf("Enter record number: ");
                scanf("%d", &rec_no);

                if(rec_no < 0 || rec_no >= MAX_RECORDS) {
                    printf("Record not found!");
                    break;
                }
                get_record(rec_no, &current_record);
                printf("Record %d) %s, %s, %d semester\n", rec_no, current_record.name, current_record.address, current_record.semester);
                break;
            }

            case 3:{
                printf("Enter record number: ");
                scanf("%d", &rec_no);

                if(rec_no < 0 || rec_no >= MAX_RECORDS) {
                    printf("Record not found!");
                    break;
                }
                get_record(rec_no, &current_record);

                struct record_s new_record;
                printf("Name: ");
                scanf("%s", new_record.name);
                printf("Address: ");
                scanf("%s", new_record.address);
                printf("Semester: ");
                scanf("%hhu", &new_record.semester);
                save_record(&current_record, &new_record, rec_no);
                printf("Record %d saved successfully\n", rec_no);
                break;
            }

            case 0:{
                printf("Exiting program...\n");
                close(fd);
                return 0;
            }

            default:{
                printf("Invalid command\n");
                break;
            }
        }

    }

}