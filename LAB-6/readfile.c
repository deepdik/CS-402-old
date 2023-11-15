#include "readfile.h"
#include <stdio.h>
#include <stdlib.h>

static FILE* file = NULL;

int open_file(const char* filename) {
    file = fopen(filename, "r");
    if (file == NULL) {
        return -1;
    }
    return 0;
}

int read_int(int* value) {
    if (file == NULL) {
        return -1;
    }
    return fscanf(file, "%d", value);
}

int read_string(char* str, int max_length) {
    if (file == NULL) {
        return -1;
    }
    return fscanf(file, "%s", str);
}

int read_float(float* value) {
    if (file == NULL) {
        return -1;
    }
    return fscanf(file, "%f", value);
}

void close_file() {
    if (file != NULL) {
        fclose(file);
        file = NULL;
    }
}
