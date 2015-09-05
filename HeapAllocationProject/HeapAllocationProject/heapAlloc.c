#include <stdio.h>

// Get the length of an array
#define arrElements(x) ( sizeof(x)/sizeof(x[0]) );	

void* freeHead;
void* nextFree;

char memoryHeap[1000];
int poolSize = arrElements(memoryHeap);
int HdrSize;

struct memoryBlock
{
	int sizeLeft;
	int* nextPointer;
	int sizeToAlloc;
};

void initMemory();
void* hAllocate(int);
void hDeallocate(int*);
void printHeap();

int main()
{
	initMemory();
	printHeap();
	printf("\n");
	printf("\nFree head pointer is at %d\n", &freeHead);
	printf("\nHeap at 0 is : %c\n",memoryHeap[0] );
	int* a = hAllocate(8);
	printf("\nAddress of allocation is : %d\n", &a);
	printf("\nValue of allocation in heap is : %d\n", a);
	printHeap();
	hDeallocate(a);
	printf("\n");
	printf("\nFree head pointer is at %d\n", &freeHead);
	printf("\nHeap at 0 is : %c\n", memoryHeap[0]);
	a = hAllocate(16);
	printf("\nAddress of allocation is : %d\n", &a);
	printf("\nValue of allocation in heap is : %d\n", a);
	printf("\n\n\n\n");
	printHeap();
	printf("\nFree head pointer is at %d\n", &freeHead);
	printf("\nHeap at 0 is : %c\n", memoryHeap[0]);
	a = hAllocate(50);
	printf("\nAddress of allocation is : %d\n", &a);
	printf("\nValue of allocation in heap is : %d\n", a);
	printf("\n\n\n\n");
	printHeap();
	printf("\nFree head pointer is at %d\n", &freeHead);
	printf("\nHeap at 0 is : %c\n", memoryHeap[0]);
	hAllocate(20);
	printf("\n\n\n\n");
	printHeap();
	printf("\nFree head pointer is at %d\n", &freeHead);
	printf("\nHeap at 0 is : %c\n", memoryHeap[0]);
	hAllocate(10);
	printf("\n\n\n\n");
	printHeap();
	printf("\nFree head pointer is at %d\n", &freeHead);
	printf("\nHeap at 0 is : %c\n", memoryHeap[0]);
	hAllocate(800);
	printf("\n\n\n\n");
	printHeap();
	printf("\nFree head pointer is at %d\n", &freeHead);
	printf("\nHeap at 0 is : %c\n", memoryHeap[0]);
	hAllocate(800);
	printf("\n\n\n\n");
	printHeap();
	printf("\nFree head pointer is at %d\n", &freeHead);
	printf("\nHeap at 0 is : %c\n", memoryHeap[0]);
	hAllocate(40);
	printf("\n\n\n\n");
	printHeap();
	printf("\nFree head pointer is at %d\n", &freeHead);
	printf("\nHeap at 0 is : %c\n", memoryHeap[0]);
	hAllocate(1);
	printf("\n\n\n\n");
	printHeap();
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

	if (sizeToAlloc + HdrSize > poolSize)
	{
		printf("ERROR OUT OF MEMORY");
	}
	else
	{
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

		beginOfAlloc = dataIdx;
		freeHead = &memoryHeap[dataIdx] + sizeToAlloc;
		//place data
		int k;

		for (k = 0; k < sizeToAlloc; k++)
		{
			memoryHeap[dataIdx + (k + 1)] = '.';
		}

		poolSize -= (sizeToAlloc + HdrSize);
		printf("Pool size after allocation is %d \n", poolSize);
	}
	return beginOfAlloc;
}

void hDeallocate(int* beginOfAlloc)
{
	int k;
	int size;
	int ptr;
	int dataidx = beginOfAlloc;
	printf("Data is ");
	for (k = 0; k < sizeof(int); k++)
	{
		printf("%d", (int)memoryHeap[(dataidx-1)-(k+1)]);
	}
	printf("\n\nBefore deallocation: ");
	for (k = 0; k < sizeof(int); k++)
	{
		printf("%c", memoryHeap[dataidx - (k + 1)]);
	}
	for (k = 0; k < sizeof(int); k++)
	{
		memoryHeap[(dataidx - 1) + k] = '0';
	}
	printf("\n\nAfter deallocation:");
	for (k = 0; k < sizeof(int); k++)
	{
		printf("%c", memoryHeap[dataidx - (k + 1)]);
	}

	printf("\n\n\n");	
}

void printHeap()
{
	int k;
	int memElements = arrElements(memoryHeap);
	for (k = 0; k < memElements; k++)
	{
		printf("%c",memoryHeap[k]);
	}
}