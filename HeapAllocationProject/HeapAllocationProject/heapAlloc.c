#include <stdio.h>

// Get the length of an array
#define arrElements(x) ( sizeof(x)/sizeof(x[0]) );	

void* freeHead;
void* nextFree;

char memoryHeap[1000];
int poolSize;
int HdrSize;

struct memoryBlock
{
	int sizeLeft;
	int* nextPointer;
	int sizeToAlloc;
};

void initMemory();
void* hAllocate(int);
void hDeallocate(void*);
void printHeap();

int main()
{
	initMemory();
	printHeap();
	printf("Free head pointer is at %d", freeHead);
	printf("Heap at 0 is : %c",memoryHeap[0] );
	hAllocate(8);
	printHeap();
	printf("Heap at 0 is : %c", memoryHeap[0]);
	hAllocate(16);
	printf("\n\n\n\n");
	printHeap();

	return 0;
}

void initMemory()
{
	int k;

	for (k = 0; k < poolSize; k++)
	{
		memoryHeap[k] = 'f';
	}	

	freeHead = memoryHeap[0];
	poolSize = arrElements(memoryHeap);
}

void* hAllocate(int sizeToAlloc)
{
	//Instantiate a pointer for "next free"
	//Instantiate size var
	//Instantiate pointer var
	//Calculate size of remaining data bits
	//Assign size var
	//Calculate address of next pointer
	//Assign pointer var
	//Calculate size of header

	void* beginOfAlloc = NULL;

	struct memoryBlock allocBlock;

	allocBlock.sizeLeft = poolSize - sizeToAlloc;
	allocBlock.sizeToAlloc = sizeToAlloc;
	allocBlock.nextPointer = &memoryHeap[9];

	HdrSize = sizeof(allocBlock.sizeLeft) + sizeof(allocBlock.nextPointer);
	printf("\nSize of header is %d \n", HdrSize);

	printf("Pool size before allocation is %d \n", poolSize);
	
	//Allocation
	//place sizeLeft
	int arrayEles = arrElements(memoryHeap);
	int sizeLeftIdx = arrayEles - poolSize;
	
	printf("\n\tNumber of arr elements = %d", arrayEles);
	printf("\n\tPool Size = %d", poolSize);
	printf("\n\tPool Size minus memoryHeap = %d", (arrayEles - poolSize));
	printf("\n\tSize left index = %d", sizeLeftIdx);
	memoryHeap[sizeLeftIdx] = (char)allocBlock.sizeLeft;
	//place pointer
	int ptrIdx = sizeLeftIdx + sizeof(sizeLeftIdx);
	printf("\n\tPointer left index = %d", ptrIdx);
	memoryHeap[ptrIdx] = (char)allocBlock.nextPointer;

	int dataIdx = ptrIdx + sizeof(ptrIdx);
	printf("\n\tData index = %d", dataIdx);
	//place data
	int k;

	for (k = 0; k < sizeToAlloc; k++)
	{
		memoryHeap[dataIdx + (k + 1)] = '.';
	}
	
	poolSize -= (sizeToAlloc + HdrSize);
	printf("Pool size after allocation is %d \n", poolSize);

	return beginOfAlloc;
}

void hDeallocate(void* beginOfAlloc)
{

}

void printHeap()
{
	int k;
	for (k = 0; k < poolSize; k++)
	{
		printf("%c",memoryHeap[k]);
	}
}