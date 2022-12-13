#include <stdlib.h>
#include <stdio.h>
#include <time.h>


int main(int argc, char* argv[]) { 
    if(argc < 3) {
        printf("Usage: ./run <filename> [-r|-w] <block_size> <block_count> \n");
        exit(0);
    }

    char* filename = argv[1]; 
    char* option = argv[2]; 
    int blocksize = atoi(argv[3]);
    int blockcount = atoi(argv[4]);

    printf("Args: %s %s %d %d \n", filename, option, blocksize, blockcount);
    
    if (option != "-r" || option != "-w") { 
        printf("Error: program only supports '-r' (read) and '-w' (write) operations\n");
        exit(0); 
    }

    clock_t start, end;
    double execution_time;
    start = clock();

    /* Put your code here */

    end = clock();
    execution_time = ((double)(end - start))/CLOCKS_PER_SEC;

    return 0;


}