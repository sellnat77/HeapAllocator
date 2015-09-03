#include <stdio.h>

// Get the length of an array
#define arrElements(x) ( sizeof(x)/sizeof(x[0]) );	

void* freeHead;
void* nextFree;

char memoryHeap[1000];
int poolSize = arrElements(memoryHeap);
int HdrSize;

void initMemory();
void* hAllocate(int);
void hDeallocate(void*);

int main()
{
	initMemory();

	printf("Heap at 0 is : %c",memoryHeap[0] );
	hAllocate(4);
	printf("Heap at 0 is : %c", memoryHeap[0]);

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

	int sizeLeft = poolSize - sizeToAlloc;
	//int nextPointer = ;

	HdrSize = sizeof(sizeLeft); //+ sizeof(nextFree);

	poolSize -= (sizeToAlloc + HdrSize);



	return beginOfAlloc;
}

void hDeallocate(void* beginOfAlloc)
{

}