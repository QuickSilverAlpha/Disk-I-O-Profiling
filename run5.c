#include <sys/time.h>
#include "helpers.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]) { 
    if(argc != 4) {
        printf("Usage: ./run <filename> <block_size> <block_count> \n");
        exit(0);
    }

    char* filename = argv[1];
    unsigned int blocksize = atoi(argv[2]);
    unsigned int blockcount = atoi(argv[3]);

    if (blocksize < 1 ){
        printf("Invalid block size!\n");
        return -1;
    }

    // if (blocksize % 4 != 0 ){
    //     printf("Invalid block size! Block size should be multiple of 4!\n");
    //     return -1;
    // }

    if (blockcount < 1) {
        printf("Invalid block count!\n");
        return -1;
    }

    printf("Starting read and lseek sys call analysis...\n");
    runSysCallAnalysis(filename, blocksize, blockcount);
    //printf("Args: %s %s %d %d \n", filename, option, blocksize, blockcount);
    return 0;

}