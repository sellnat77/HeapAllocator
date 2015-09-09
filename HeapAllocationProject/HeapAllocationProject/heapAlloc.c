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
	my_initialize_heap(poolSize);

	void *myInt = my_alloc(5);

	printf("After allocating, the address of the int is: %d", &myInt);

	myFree(myInt);

	void *myBigInt = my_alloc(24);
	
	printf("After allocating, the address of the int is: %d", &myBigInt);

	myFree(myBigInt);

	return 0;
}

void my_initialize_heap(int size)
{
	freeHead = malloc(size);

	//Null pointer
	//*((int*)(*freeHead + intSize)) = 0;
	*((int*)freeHead + intSize) = 0;
	poolSize -= overHead;
	*(int*)(freeHead) = poolSize;

	printf("Initial data block left: %d\n", *(int*)freeHead);
	
	printf("Initial next pointer: %d\n", *((int*)freeHead+intSize));
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
	int sizeLeft;
	int *nextPointer;
	int data;

	printf("Address of pointer: %p\n", &freeHead);

	void* ptr = freeHead;

	while (*(int*)ptr < size)
	{
		ptr = (int*)ptr + intSize;
	}

	*(int*)(ptr) = size;
	*((int*)ptr + intSize) = (int*)ptr + overHead + size;

	poolSize -= (size + overHead);
	
	*((int*)ptr + size + overHead) = poolSize;
	
	freeHead = (int*)ptr + overHead + size;

	printf("Allocated data block left: %d\n", *(int*)ptr);

	printf("\tAllocated next pointer: %d\n", *((int*)ptr + intSize));

	printf("Post split data block left: %d\n", *((int*)ptr+overHead+size));

	return ptr;
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
	// "Can be as easy as making this block the new free head"

	int sizeFreed = *(int*)startOfData + overHead;

	poolSize += sizeFreed;
	freeHead = startOfData;
}

void hDeallocate(void* beginOfAlloc)
{

}