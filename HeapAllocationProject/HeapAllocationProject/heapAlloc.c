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
	void* ptr = my_alloc(12);
	myFree(ptr);
	printf("\t\tReturned Ptr Address: %d\n", (int*)ptr);
	printf("Free head pointer is at %d\n\n", freeHead);
	ptr = my_alloc(12);
	printf("\t\tReturned Ptr Address: %d\n", (int*)ptr);
	printf("Free head pointer is at %d\n\n", freeHead);
	ptr = my_alloc(12);
	printf("\t\tReturned Ptr Address: %d\n", (int*)ptr);
	printf("Free head pointer is at %d\n\n", freeHead);
	ptr = my_alloc(12);
	printf("\t\tReturned Ptr Address: %d\n", (int*)ptr);
	printf("Free head pointer is at %d\n\n", freeHead);
	ptr = my_alloc(12);
	printf("\t\tReturned Ptr Address: %d\n", (int*)ptr);
	printf("Free head pointer is at %d\n\n", freeHead);
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
	printf("Value of pointer: %p\n", freeHead);
	printf("Value at pointer: %d\n", (int*)freeHead);

	void* ptr = freeHead;

	while (*(int*)ptr < size)
	{
		ptr = (int*)ptr + intSize;
	}

	//ptr is at  ->| size | ptr | data | of an accomadating block

	/**((int*)freeHead + intSize) = 0;
	*(int*)(freeHead) = poolSize - overHead;

	printf("Initial data block left: %d\n", *(int*)freeHead);

	printf("Initial next pointer: %d\n", *((int*)freeHead + intSize));*/

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
	freeHead = startOfData;
}

void hDeallocate(void* beginOfAlloc)
{

}