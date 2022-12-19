#include "helpers.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int main(int argc, char* argv[]) { 
    if(argc != 3) {
        printf("Usage: ./run2 <filename> <block_size> \n");
        return -1;
    }

    char* filename = argv[1];  
    unsigned int blocksize = atoi(argv[2]);
    
    if (blocksize < 1){
        printf("Invalid block size!\n");
        return -1;
    }

    int numblocks = readFile_run2(filename, blocksize);
    printf("Number of blocks read in a resonable time: %d\n", numblocks);
    return 0;

}