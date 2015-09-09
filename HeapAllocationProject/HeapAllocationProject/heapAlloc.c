#include <stdio.h>

// Get the length of an array
#define arrElements(x) ( sizeof(x)/sizeof(x[0]) );	

struct node
{
	int size;
	struct node *nextNode;
	void* data;
};

void* freeHead;
void* nextFree;

struct node *rootNode;

char memoryHeap[1000];
int poolSize = arrElements(memoryHeap);
int HdrSize;
const int ptrSize = sizeof(void*);
const int intSize = sizeof(int);
const int overHead = sizeof(void*) + sizeof(int);

void my_initialize_heap(int);
void initMemory();

void* my_alloc(int);
void* hAllocate(int);

void myFree(void);
void hDeallocate(void*);

int main()
{
	printf("%d is the size of a void pointer",ptrSize);
	my_initialize_heap(poolSize);
	my_alloc(20);
	//initMemory();
	printf("Free head pointer is at %d", freeHead);
	printf("Heap at 0 is : %c",memoryHeap[0] );
	//hAllocate(4);
	printf("Heap at 0 is : %c", memoryHeap[0]);

	return 0;
}

void my_initialize_heap(int size)
{
	freeHead = malloc(size);

	//Null pointer
	//*((int*)(*freeHead + intSize)) = 0;
	*((int*)(&freeHead + intSize)) = 0;
	*(int*)(freeHead) = poolSize - overHead;

	printf("Address of pointer: %p\n", &freeHead);
	printf("Value of pointer: %p\n", freeHead);
	printf("Value at pointer: %d\n", (int*)freeHead);
	
	printf("Address of pointer: %p\n", (&freeHead+intSize));
	printf("Value at pointer: %d\n", (int*)freeHead + intSize);
	//Break into block structure
	// | size | pointer | ******Everything********** |
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

void* my_alloc(int size)
{
	printf("Address of pointer: %p\n", &freeHead);
	printf("Value of pointer: %p\n", freeHead);
	printf("Value at pointer: %d\n", (int*)freeHead);
	// Walk free list
		// Do I need a list structure? or metaphorical list?
	// Find a suitable block
	// If found and larger than what is required, split
		// Request | Everything left

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

void myFree(void *startOfData)
{

}

void hDeallocate(void* beginOfAlloc)
{

}