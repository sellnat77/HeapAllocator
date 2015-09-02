#include <stdio.h>

// Get the length of an array
#define arrElements(x) ( sizeof(x)/sizeof(x[0]) );	

void* freeHead;
void* nextFree;

char memoryHeap[1000];
int poolSize = arrElements(memoryHeap);

void initMemory();
void* hAllocate(int);
void hDeallocate(void*);

int main()
{
	initMemory();

	printf("Heap at 0 is : %s",memoryHeap[0] );

	return 0;
}

void initMemory()
{
	int k;

	for (k = 0; k < poolSize; k++)
	{
		memoryHeap[k] = '0';
	}	
}

void* hAllocate(int sizeToAlloc)
{
	void* beginOfAlloc = NULL;

	return beginOfAlloc;
}

void hDeallocate(void* beginOfAlloc)
{

}