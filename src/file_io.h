#ifndef FILE_IO_HEADER
#define FILE_IO_HEADER

#include <stdio.h>
#include <stdlib.h>

#define file_error(msg) perror(msg); exit(-1); 

// file io
unsigned char* read_file(const char *path) {
    FILE* fs = fopen(path, "r");
    if (fs == NULL) {
        file_error("fopen")
    }
    fseek(fs, 0, SEEK_END);
    size_t size = ftell(fs);
    fseek(fs, 0, SEEK_SET);
    unsigned char* file_content = (unsigned char*)malloc(sizeof(char)*size);
    fread(file_content, size, sizeof(char), fs);
    fclose(fs);
    return file_content;
    
}

#endif