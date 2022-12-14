#include <time.h>
#include "helpers.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]) { 
    if(argc < 5) {
        printf("Usage: ./run <filename> [-r|-w] <block_size> <block_count> \n");
        exit(0);
    }

    char* filename = argv[1]; 
    char* option = argv[2]; 
    int blocksize = atoi(argv[3]);
    int blockcount = atoi(argv[4]);

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

    printf("Args: %s %s %d %d \n", filename, option, blocksize, blockcount);
    
    if (strcmp(option,"-r") == 0) {
        clock_t start, end;
        double execution_time;
        start = clock();
        readFile(filename, blocksize, blockcount);

        end = clock();
        execution_time = ((double)(end - start))/CLOCKS_PER_SEC;
        printf("Time to complete read: %lf \n", execution_time);
    }

    else if (strcmp(option,"-w") == 0) {
        clock_t start, end;
        double execution_time;
        start = clock();
        writeFile(filename, blocksize, blockcount);

        end = clock();
        execution_time = ((double)(end - start))/CLOCKS_PER_SEC;
        printf("Time to complete write: %lf \n", execution_time);
    }

    else {
        printf("Error: program only supports '-r' (read) and '-w' (write) operations\n");
        return -1; 
    }

    return 0;

}