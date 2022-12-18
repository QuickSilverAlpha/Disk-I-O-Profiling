#include <stddef.h>
unsigned int xorbuf(unsigned int *buffer, int size);
void readFile(char* filename, unsigned int blocksize, unsigned int blockcount);
int readFile_run2(char* filename, unsigned int blocksize);
void writeFile(char* filename, unsigned int blocksize, unsigned int blockcount);
unsigned int computeBlockCt(char* filename, unsigned int blocksize); 
size_t fize(const char* filename); 