#include "helpers.h"
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <stddef.h>
#include <sys/time.h>

double now() {
    struct timeval tv;
    gettimeofday(&tv, 0);
    return tv.tv_sec + tv.tv_usec / 1000000.0;
}


size_t fsize(const char *filename) {
    struct stat st; 

    if (stat(filename, &st) == 0)
        return st.st_size;

    return -1; 
}

unsigned int xorbuf(unsigned int *buffer, int size) {
    unsigned int result = 0;
    for (int i = 0; i < size; i++) {
        result ^= buffer[i];
    }
    return result;
}

void readFile(char* filename, unsigned int blocksize, unsigned int blockcount){ 
    int fd = open(filename, O_RDONLY);
    if (fd < 0) { 
        printf("Error opening file %s\n", filename); 
    }
    else {
        unsigned int xorvalue = 0;

        unsigned int* buffer;
        buffer = (unsigned int*)malloc(blocksize*(sizeof(unsigned int))); //allocate memory in order to make blocksize the size of array
        for(int i = 0; i < blockcount; i++) { 
            int current_read = read(fd, buffer, blocksize);
            xorvalue ^= xorbuf(buffer, current_read);
        }
        printf("%x\n", xorvalue);
        free(buffer);
    }
    if(close(fd) != 0) { 
        printf("Error closing file: %s", filename);
    }
}

int readFile_run2(char* filename, unsigned int blocksize) {
    int fd = open(filename, O_RDONLY);
    int n;
    double start, curr, end;
    if (fd < 0) { 
        printf("Error opening file %s\n", filename); 
        return -1; 
    }
    else {
        unsigned int xorvalue = 0;
        unsigned int blockcount = 0;
        unsigned int* buffer;
        buffer = (unsigned int*)malloc(blocksize*(sizeof(unsigned int))); //allocate memory in order to make blocksize the size of array
        start = now();
		curr = now();
        
        while((curr - start < 15) && (n = pread(fd, buffer, blocksize, 0) > 0)) {
            xorvalue ^= xorbuf(buffer, blocksize);
            blockcount++; 
            curr = now();
        }
        end = now();
        printf("Time to complete read: %f\n", end - start);


        printf("%x\n", xorvalue);
        free(buffer);
        return blockcount;
    }
    if(close(fd) != 0) { 
        printf("Error closing file: %s", filename);
        return -1; 
    }
    return 0; 
}

void writeFile(char* filename, unsigned int blocksize, unsigned int blockcount){
    int fd = open(filename, O_WRONLY | O_CREAT, 0644);
    if (fd < 0){
        printf("Writing error with file %s!\n",filename);
    }
    else {
        unsigned int* write_buffer;
        write_buffer = (unsigned int*)malloc(blocksize*(sizeof(unsigned int))); //allocate memory in order to make blocksize the size of array

        for (int i=0; i < blockcount; i++){
            int size = write(fd, write_buffer, blocksize);
            printf("Wrote %d bytes to file", size); 
        }
        free(write_buffer);
    }

    if(close(fd) != 0) { 
        printf("Error closing file: %s", filename);
    }
}


