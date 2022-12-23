#include <sys/time.h>
#include "helpers.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]) { 
    if(argc != 2) {
        printf("Usage: ./fast <filename>\n");
        exit(0);
    }

    char* filename = argv[1];

    printf("Init...\n");
    readFileFast(filename);
    //printf("Args: %s %s %d %d \n", filename, option, blocksize, blockcount);
    return 0;

}