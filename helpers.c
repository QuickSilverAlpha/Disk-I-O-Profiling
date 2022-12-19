#include "helpers.h"
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <stddef.h>
#include <sys/time.h>
#include <math.h>

#define UNUSED(x) (void)(x)

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
    long buflen; 
    if (fd < 0) { 
        printf("Error opening file %s\n", filename); 
    }
    else {
        unsigned int xorvalue = 0;
        unsigned int current_blockcount = 1;
        int current_read;
        unsigned int* buffer;
        buffer = (unsigned int*)malloc(blocksize); //allocate memory in order to make blocksize the size of array
        while((current_read = read(fd, buffer, blocksize)) > 0) { 
            buflen = ceil((double) current_read / sizeof(unsigned int));
            xorvalue ^= xorbuf(buffer, buflen);

            if (current_blockcount == blockcount){
                break;
            }
            current_blockcount++;
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
        long buflen;
        size_t sz;

        buffer = (unsigned int*)malloc(blocksize); //allocate memory in order to make blocksize the size of array
        start = now();
		curr = now();
        //off_t eof = lseek(fd, 0, SEEK_END); //Must reset lseek to the beginning or will continue from eof in while loop 
        // off_t pos = lseek(fd, 0, SEEK_SET);
        while((curr - start <= (double) 15) && (n = read(fd, buffer, blocksize)) > 0) { //(curr - start < 15) &&
            buflen = ceil((double) n / sizeof(unsigned int));

            // pos = lseek(fd, blocksize, SEEK_CUR);
            xorvalue ^= xorbuf(buffer, buflen);
            blockcount++; 
            curr = now();
        }
        end = now();

        if (end - start <= (double) 5) {
            printf("Time to complete read: %f\n", end - start);
            printf("Already Optimized! Use a bigger file!\n");
            return blockcount;
        }
        if (n <= 0) {
            sz = fsize(filename);
        }
        else{
            sz = blocksize*blockcount;
        }
        
        double performance = (end - start);
        double dataRate = (sz/1024.0/1024.0) / ((double)performance); 
        printf("Time to complete read: %f\n", end - start);
        printf("Performance: %f MB/Sec\n", dataRate);
        

        printf("%08x\n", xorvalue);
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
            int n = write(fd, write_buffer, blocksize);
            UNUSED(n);
        }
        free(write_buffer);
    }

    if(close(fd) != 0) { 
        printf("Error closing file: %s", filename);
    }
}


