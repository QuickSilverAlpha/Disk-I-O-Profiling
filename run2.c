#include <time.h>
#include "helpers.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>





int main(int argc, char* argv[]) { 
    if(argc != 3) {
        printf("Usage: ./run2 <filename> <block_size> \n");
        exit(0);
    }

    char* filename = argv[1];  
    unsigned int blocksize = atoi(argv[2]);
    
    if (blocksize < 1){
        printf("Invalid block size!\n");
        return -1;
    }
    if (blocksize % 4 != 0 ){
        printf("Invalid block size! Block size should be multiple of 4!\n");
        return -1;
    }
    unsigned int blockcount = computeSize(filename,blocksize);

    
   

    return 0;

}