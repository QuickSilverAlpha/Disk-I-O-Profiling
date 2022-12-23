#include <sys/time.h>
#include "helpers.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]) { 
    if(argc != 2) {
        printf("Usage: ./fast_mmap <filename>\n");
        exit(0);
    }

    char* filename = argv[1];
    unsigned int blocksize = 0;
    unsigned int blockcount = 0;

    printf("Init...\n");
    readFileFastMmap(filename, blocksize, blockcount);
    //printf("Args: %s %s %d %d \n", filename, option, blocksize, blockcount);
    return 0;

}