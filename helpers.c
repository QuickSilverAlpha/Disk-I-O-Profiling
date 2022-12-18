#include "helpers.h"
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

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
        }
        free(write_buffer);
    }

    if(close(fd) != 0) { 
        printf("Error closing file: %s", filename);
    }
}

unsigned int computeSize(char* filename, unsigned int blocksize){
    int blockcount; 
    
    return blockcount;  
}