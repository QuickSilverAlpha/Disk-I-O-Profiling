#include <sys/time.h>
#include "helpers.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]) { 
    if(argc != 5) {
        printf("Usage: ./run <filename> [-r|-w] <block_size> <block_count> \n");
        exit(0);
    }
    

    char* filename = argv[1]; 
    char* option = argv[2]; 
    unsigned int blocksize = atoi(argv[3]);
    unsigned int blockcount = atoi(argv[4]);

    if (blocksize < 1 ){
        printf("Invalid block size!\n");
        return -1;
    }

    if (blocksize % 4 != 0 ){
        printf("Invalid block size! Block size should be multiple of 4!\n");
        return -1;
    }

    if (blockcount < 1) {
        printf("Invalid block count!\n");
        return -1;
    }

    //printf("Args: %s %s %d %d \n", filename, option, blocksize, blockcount);
    
    if (strcmp(option,"-r") == 0) {
        double start, end;
        start = now();
        readFile(filename, blocksize, blockcount);

        end = now();
        size_t sz = fsize(filename);
        double performance = (end - start);
        double dataRate = (sz/1024.0/1024.0) / ((double)performance); 
        printf("Time to complete read: %f\n", end - start);
        printf("Performance: %f MB/Sec\n", dataRate);
        
       
    }

    else if (strcmp(option,"-w") == 0) {
        double start, end;
        start = now();
        writeFile(filename, blocksize, blockcount);

        end = now();
        size_t sz = fsize(filename);
        double performance = (end - start);
        double dataRate = (sz/1024.0/1024.0) / ((double)performance); 
        printf("Time to complete write: %f\n", end - start);
        printf("Performance: %f MB/Sec\n", dataRate);

    }

    else {
        printf("Error: program only supports '-r' (read) and '-w' (write) operations\n");
        return -1; 
    }

    return 0;

}