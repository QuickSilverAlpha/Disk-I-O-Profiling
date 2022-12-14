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

void readFile(char* filename, int blocksize, int blockcount){ 
    int fd = open(filename, O_RDONLY);
    if (fd < 0) { 
        printf("Error opening file %s\n", filename); 
    }
    else {
        unsigned int xorvalue = 0;
        unsigned int buffer[blocksize];
        for(int i = 0; i < blockcount; i++) { 
            int current_read = read(fd, buffer, blocksize);
            xorvalue ^= xorbuf(buffer, current_read);
        }
        printf("%x\n", xorvalue);
    }
    if(close(fd) != 0) { 
        printf("Error closing file: %s", filename);
    }
}

void writeFile(char* filename, int blocksize, int blockcount){
    int fd = open(filename, O_WRONLY | O_CREAT, 0644);
    if (fd < 0){
        printf("Writing error with file %s!\n",filename);
    }
    else {
        unsigned int buf[blocksize];
        for (int i=0; i < blockcount; i++){
            int n = write(fd,buf,blocksize);
        }
    }
    if(close(fd) != 0) { 
        printf("Error closing file: %s", filename);
    }
}
