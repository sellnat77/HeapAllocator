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
void *userInput;

struct node *rootNode;

char memoryHeap[1000];
int devValues[];
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

void getInput();
void assignInts();
double stdDeviation();
double getAvg();

int main()
{
	int k;
	my_initialize_heap(poolSize);
	/*
	void *myInt = my_alloc(sizeof(int));

	printf("\n\tAfter allocating, the address of the int is: %p", (void*)&myInt);

	myFree(myInt);
	printf("\n\tAfter deallocating, the address of the freeHead is: %p", (void*)&freeHead);

	void *myBigInt = my_alloc(sizeof(int));

	printf("\n\tAfter allocating, the address of the int is: %p", (void*)&myBigInt);

	myFree(myBigInt);

	printf("\n\tAfter deallocating, the address of the freeHead is: %p", (void*)&freeHead);
	
	int one = 1;
	int two = 1;
	
	void *onePtr = my_alloc(sizeof(int));
	void *twoPtr = my_alloc(sizeof(int));

	printf("\n\tAfter allocating, the address of the int1 is: %p", (void*)&onePtr);
	printf("\n\tAfter allocating, the address of the int2 is: %p", (void*)&twoPtr);
	
	void *first = my_alloc(sizeof(int));
	void *second = my_alloc(sizeof(int));
	void *third = my_alloc(sizeof(int));

	printf("\n\tAfter allocating, the address of the first is: %p", (void*)&first);
	printf("\n\tAfter allocating, the address of the second is: %p", (void*)&second);
	printf("\n\tAfter allocating, the address of the third is: %p", (void*)&third);

	void *freedAddress = (void*)&second;

	myFree(second);

	printf("\n\tAfter deallocating, the address of the freeHead is: %p", (void*)&freeHead);

	void *myDoub = my_alloc(sizeof(double));

	printf("\n\tAfter allocating, the address of the myDoub is: %p", (void*)&myDoub);

	void *fourth = my_alloc(sizeof(int));

	printf("\n\tAfter allocating, the address of the fourth is: %p == %p", (void*)&fourth, (void*)&freedAddress);
	

	void *myChar = my_alloc(sizeof(char));
	void *myInt = my_alloc(sizeof(int));

	printf("\n\tAfter allocating, the address of the myChar is: %p", (void*)&myChar);
	printf("\n\tAfter allocating, the address of the myInt is: %p", (void*)&myInt);
	

	void *intArr = my_alloc(100 * sizeof(int));

	printf("\n\tAfter allocating, the address of the intArr is: %p", (void*)&intArr);
	*/

	getInput();
	assignInts();
	printf("\n\n\n\tThe std Deviation is %f",stdDeviation());

	return 0;
}

void my_initialize_heap(int size)
{
	freeHead = malloc(size);
	printf("\n\tThe address of the freeHead is: %p", freeHead);

	*((int*)freeHead + intSize) = 0;
	poolSize = poolSize - overHead;
	*(int*)(freeHead) = poolSize;
	// | size | pointer | ******Everything********** |
}

void* my_alloc(int size)
{
	int sizeLeft;
	int *nextPointer;
	int data;

	printf("\n\n\t\tAddress of pointer that allocator is working with: %p\n", freeHead);

	void* ptr = freeHead;

	while (*(int*)ptr < size)
	{
			//Next Node
		ptr = (int*)ptr + intSize;
	}

	*(int*)(ptr) = size;
	*((int*)ptr + intSize) = overHead + size;

	poolSize = poolSize - (size + overHead);
	
	*((int*)ptr + size + overHead) = poolSize;
	
	freeHead = ((int*)ptr + overHead + size);

	printf("\nAllocated data block left: %d\n", *(int*)ptr);

	printf("\n\tAllocated next pointer: %p\n", ((int*)ptr + intSize));

	printf("\n\t\tPost split data block left: %d\n", *((int*)ptr+overHead+size));

	return ptr;
}

void myFree(void *startOfData)
{
	// "Can be as easy as making this block the new free head"

	int sizeFreed = *(int*)startOfData + overHead;

	poolSize += sizeFreed;
	freeHead = startOfData;
}

void getInput()
{
	int value;
	
	printf("Please enter a positive integer n");
	scanf_s("%d",&value);

	userInput = my_alloc(value*sizeof(int));
}

void assignInts()
{
	int val;
	int k;

	int sizeOfAllocated = (*((int*)userInput))/sizeof(int);

	for (k = 0; k < sizeOfAllocated; k++)
	{
		printf("\nPlease enter a positive integer n");
		scanf_s("%d", &val);

		*((int*)userInput + overHead+(k*sizeof(int))) = val;
		printf("Entered %d\n\n", *((int*)userInput + overHead + (k*sizeof(int))));
	}
}

double stdDeviation()
{
	int k;
	double std = 0;
	double avg = getAvg();

	printf("The average is %3.2f", avg);

	int devValuesCount = (*((int*)userInput)) / sizeof(int);

	for (k = 0; k < devValuesCount; k++)
	{
		int value = *((int*)userInput + overHead + (k*sizeof(int)));

		printf("\nEXPRESSION: %d - %f Squared = %f ", value, avg, pow(((double)value - avg), 2));
		printf("\n%d - %f = %f", value, avg, (value - avg));
		printf("\nSQUARED = %f\n", ((value - avg) * (value - avg)));
		std = std + ((value - avg) * (value - avg));
	}

	printf("Dividing by %d", devValuesCount);

	std = std / (double)devValuesCount;

	printf("Trying to take sqrt of %f", std);

	std = sqrt(std);

	return std;
}

double getAvg()
{
	int k;
	double avg = 0;

	int devValuesCount = (*((int*)userInput)) / sizeof(int);

	for (k = 0; k < devValuesCount; k++)
	{
		avg += (*((int*)userInput + overHead + (k*sizeof(int))));
	}
	avg = avg/devValuesCount;

	return avg;
}
