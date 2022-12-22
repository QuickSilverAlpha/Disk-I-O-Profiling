#include <stddef.h>
double now();
size_t fsize(const char *filename);
unsigned int xorbuf(unsigned int *buffer, int size);
void readFile(char* filename, unsigned int blocksize, unsigned int blockcount);
void runSysCallAnalysis(char* filename, unsigned int blocksize, unsigned int blockcount);
int readFile_run2(char* filename, unsigned int blocksize);
int readFileFast(char* filename, unsigned int blocksize, unsigned int blockcount);
int readFileFastMmap(char* filename, unsigned int blocksize, unsigned int blockcount);
void writeFile(char* filename, unsigned int blocksize, unsigned int blockcount);
