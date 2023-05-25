#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#define INDEX_RECORD_SIZE 16
#define HEADER_SIZE 8

struct index_s {
    double time_mark;
    uint64_t recno;
};

struct index_hdr_s {
    uint64_t records;
    struct index_s idx[];
};

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s filename size_in_MB\n", argv[0]);
        return 1;
    }


    char *filename = argv[1];
    int size = atoi(argv[2]);
    int num_records = (size * 1024 * 1024) / INDEX_RECORD_SIZE;
    int header_size = HEADER_SIZE + num_records * INDEX_RECORD_SIZE;


    struct index_hdr_s *header = (struct index_hdr_s *) malloc(header_size);
    if (header == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    header->records = num_records;

    srand(time(NULL));
    for (int i = 0; i < num_records; i++) {
        struct index_s *record = &(header->idx[i]);

        double days_since_1900 = (double) (rand() % (365 * 123)) + 15020.0;
        double fraction_of_day = (double) rand() / RAND_MAX / 2.0;
        record->time_mark = days_since_1900 + fraction_of_day;

        record->recno = i;
    }


    FILE *fp = fopen(filename, "wb");
    if (fp == NULL) {
        printf("Failed to open file %s\n", filename);
        return 1;
    }

    fwrite(header, header_size, 1, fp);
    fclose(fp);

    printf("Generated %d index records in file %s\n", num_records, filename);

    return 0;
}