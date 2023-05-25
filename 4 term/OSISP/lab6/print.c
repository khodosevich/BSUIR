#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

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

void binaryToText(const char* binaryFile, const char* textFile) {
    FILE* input = fopen(binaryFile, "rb");
    FILE* output = fopen(textFile, "w");

    if (input == NULL || output == NULL) {
        printf("Error opening files\n");
        return;
    }

    struct index_hdr_s header;
    fread(&header, sizeof(struct index_hdr_s), 1, input);

    fprintf(output, "Number of records: %lu\n", header.records);

    for (int i = 0; i < header.records; i++) {
        struct index_s record;
        fread(&record, sizeof(struct index_s), 1, input);
        fprintf(output, "Record %d:\n", i + 1);
        fprintf(output, "  Time mark: %lf\n", record.time_mark);
        fprintf(output, "  Recno: %lu\n", record.recno);
    }

    fclose(input);
    fclose(output);

    printf("Conversion completed successfully\n");
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s binary_filename text_filename\n", argv[0]);
        return 1;
    }

    const char* binaryFile = argv[1];
    const char* textFile = argv[2];
    binaryToText(binaryFile, textFile);

    return 0;
}
