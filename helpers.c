#include "helpers.h"
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <stddef.h>
#include <sys/time.h>
#include <sys/mman.h>
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
        unsigned int cb_read = 1;
        int current_read;
        unsigned int* buffer;
        buffer = (unsigned int*)malloc(blocksize); //allocate memory in order to make blocksize the size of array
        while((current_read = read(fd, buffer, blocksize)) > 0) { 
            buflen = ceil((double) current_read / sizeof(unsigned int));
            xorvalue ^= xorbuf(buffer, buflen);

            // Checking block count, if blockcount*blocksize < filesize, it will break the loop.
            if (cb_read == blockcount){
                break;
            }
            cb_read++;
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
        

        printf("%x\n", xorvalue);
        free(buffer);
        return blockcount;
    }
    if(close(fd) != 0) { 
        printf("Error closing file: %s", filename);
        return -1; 
    }
    return 0; 
}

void runSysCallAnalysis(char* filename, unsigned int blocksize, unsigned int blockcount){ 
    double read_start, read_end;
    double lseek_start, lseek_end;

    size_t sz = blockcount*blocksize;

    size_t f_sz = fsize(filename);
    
    if(sz > f_sz){
        printf("ERROR: Enter a valid blockcount! (Blockcount* Blocksize) > Filesize!");
        // return -1;
        exit(0);
    }



    int fd = open(filename, O_RDONLY);

    if (fd < 0) { 
        printf("Error opening file %s\n", filename); 
    }
    else {
        unsigned int cb_read = 1;
        unsigned int cb_lseek = 1;
        int current_read;
        unsigned int* buffer;
        buffer = (unsigned int*)malloc(blocksize); //allocate memory in order to make blocksize the size of array

        // Read the entire file and record the time

        printf("Reading file...\n");
        read_start = now();
        while((current_read = read(fd, buffer, blocksize)) > 0) { 
            if (cb_read == blockcount){
                break;
            }
            cb_read++;
        }
        read_end = now();
        free(buffer);

        printf("Lseeking file...\n");
        off_t eof = lseek(fd, 0, SEEK_END);
        off_t pos = lseek(fd, 0, SEEK_SET);

        lseek_start = now();
        // lseek the file block by block to cover the entire file
        while(pos <= eof){

            pos = lseek(fd, blocksize, SEEK_CUR);
            if(cb_lseek == blockcount){
                break;
            }
            cb_lseek++;
        }
        lseek_end = now();

        double read_time_taken = read_end - read_start;
        double read_data_rate_mbps = (sz/1024.0/1024.0) / ((double)read_time_taken);
        double read_data_rate_bps = (sz) / ((double)read_time_taken);

        double lseek_time_taken = lseek_end - lseek_start;
        double lseek_data_rate_mbps = (sz/1024.0/1024.0) / ((double)lseek_time_taken);
        double lseek_data_rate_bps = (sz) / ((double)lseek_time_taken);

        printf("No. of system call(s): %ld\n", sz);
        printf("Read system call time taken: %f Sec\n", read_time_taken);
        printf("Read system call read rate: %f MB/Sec\n", read_data_rate_mbps);
        printf("Read system call read rate: %f B/Sec\n", read_data_rate_bps);
        printf("Lseek system call time taken: %f Sec\n", lseek_time_taken);
        printf("Lseek system call time: %f MB/Sec\n", lseek_data_rate_mbps);
        printf("Lseek system call time: %f B/Sec\n", lseek_data_rate_bps);
    }

    if(close(fd) != 0) { 
        printf("Error closing file: %s", filename);
    }
}

int readFileFast(char* filename, unsigned int blocksize, unsigned int blockcount) {
    //unsigned int n;
    unsigned int xorvalue;
    //double start, curr, end;
    // unsigned int curr_blockcount = 1;
    // unsigned int offset = 0;

    int fd = open(filename, O_RDONLY);
    if (fd < 0) { 
        printf("Error opening file %s\n", filename); 
        return -1; 
    }
    else {

        struct stat statbuf;
        int status;
        size_t f_sz;
        size_t pagesize = getpagesize();

        status = fstat(fd, &statbuf);
        if (status < 0) {
            printf("File status failed: %s", filename);
        }
        f_sz = statbuf.st_size;
        printf("%ld\n", f_sz);

        char *mmap_block_ptr = mmap(NULL, f_sz, PROT_READ, MAP_SHARED, fd, 0);
        if(mmap_block_ptr == MAP_FAILED) {
            printf("Failed mapping!\n");
            return -1;
        }
        printf("Past mmap!\n");

        //ssize_t n = write(1,mmap_block_ptr, f_sz);
        xorvalue ^= xorbuf((unsigned int*) mmap_block_ptr, f_sz);
        printf("xorvalue: %x\n", xorvalue);

        int unmap_block_ptr = munmap(mmap_block_ptr, f_sz);

        if(unmap_block_ptr != 0){
            printf("Failed Unmapping!\n");
            return -1;
        }

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


