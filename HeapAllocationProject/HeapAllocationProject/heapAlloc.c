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
	printf("Free head pointer is at %d", freeHead);
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

	freeHead = memoryHeap[0];
}

void* hAllocate(int sizeToAlloc)
{
	void* beginOfAlloc = NULL;

	int sizeLeft = poolSize - sizeToAlloc;
	int nextPointer = poolSize - sizeof(int*);

	HdrSize = sizeof(sizeLeft) + sizeof(nextPointer);
	printf("\nSize of header is %d \n", HdrSize);
	printf("Pool size before allocation is %d \n", poolSize);
	poolSize -= (sizeToAlloc + HdrSize);
	printf("Pool size after allocation is %d \n", poolSize);




	return beginOfAlloc;
}

void hDeallocate(void* beginOfAlloc)
{

}