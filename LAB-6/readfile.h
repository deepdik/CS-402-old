#ifndef READFILE_H
#define READFILE_H

int open_file(const char* filename);
int read_int(int* value);
int read_string(char* str, int max_length);
int read_float(float* value);
void close_file();

#endif // READFILE_H
