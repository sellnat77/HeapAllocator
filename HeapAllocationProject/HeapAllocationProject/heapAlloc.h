#include <stdio.h>
#include <math.h>

void* freeHead;
void* nextFree;

const int ptrSize = sizeof(void*);
const int intSize = sizeof(int);
const int overHead = sizeof(void*) + sizeof(int);
int poolSize = 1000;

void my_initialize_heap(int);
void* my_alloc(int);
void my_free(void);

///////////////////////////////////////////////////////
//Standard Dev Program
void* stdDevNums;

void getInput();
void assignInts();
double stdDeviation();
double getAvg();