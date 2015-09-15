#include "heapAlloc.h"

void main()
{
	/*
	//Test #1
	my_initialize_heap(poolSize);
	printf("\nBefore allocating, the address of the freeHead is: %p\n", (void*)&freeHead);
	
	void *myInt = my_alloc(sizeof(int));
	printf("\nAfter allocating, the address of the int pointer is: %p\n", (void*)&myInt);
	printf("\nThe address of the freeHead is: %p\n", (void*)&freeHead);

	my_free(myInt);
	printf("\n\tAfter deallocating, the address of the freeHead is: %p\n", (void*)&freeHead);

	printf("\nBefore allocating, the address of the freeHead is: %p\n", (void*)&freeHead);
	
	void *myOtherInt = my_alloc(sizeof(int));
	printf("\nAfter allocating, the address of the int pointer is: %p\n", (void*)&myOtherInt);
	printf("\nThe address of the freeHead is: %p\n", (void*)&freeHead);

	my_free(myOtherInt);
	printf("\n\tAfter deallocating, the address of the freeHead is: %p\n", (void*)&freeHead);
	
	printf("\nMoving to test #2\n");
	system("pause");
	system("cls");

	//Test #2
	my_initialize_heap(poolSize);	
	int one = 1;
	int two = 1;
	
	void *onePtr = my_alloc(sizeof(int));
	void *twoPtr = my_alloc(sizeof(int));

	printf("\nAfter allocating, the address of the int1 is: %p", (void*)&onePtr);
	printf("\nAfter allocating, the address of the int2 is: %p", (void*)&twoPtr);
	
	my_free(onePtr);
	my_free(twoPtr);
	

	printf("\nMoving to test #3\n");
	system("pause");
	system("cls");
	*/
	//Test #3
	my_initialize_heap(poolSize);

	void *first = my_alloc(sizeof(int));
	void *second = my_alloc(sizeof(int));
	void *third = my_alloc(sizeof(int));

	printf("\nAfter allocating, the address of the first is: %p", (void*)first);
	printf("\nAfter allocating, the address of the second is: %p", (void*)second);
	printf("\nAfter allocating, the address of the third is: %p", (void*)third);

	void *freedAddress = (void*)&second;
	printf("\nStoring second address for comparison: %p", (void*)freedAddress);

	my_free((void*)second);
	
	printf("\n\t\tStoring second address after deallocating for comparison: %p", (void*)freedAddress);

	printf("\n\tAfter deallocating second, the address of the freeHead is: %p", (void*)freeHead);

	void *myDoub = my_alloc(sizeof(double));

	printf("\n\tAfter allocating, the address of the myDoub is: %p", (void*)myDoub);

	void *fourth = my_alloc(sizeof(int));

	printf("\nAfter allocating, the address of the fourth is: %p == %p", (void*)fourth, (void*)freedAddress);
	
	my_free(first);
	my_free(third);
	my_free(fourth);
	my_free(myDoub);

	printf("\nMoving to test #4\n");
	system("pause");
	system("cls");
	/*
	//Test #4
	my_initialize_heap(poolSize);

	void *myChar = my_alloc(sizeof(char));
	void *myIntTest = my_alloc(sizeof(int));

	printf("\nAfter allocating, the address of the myChar is: %p", (void*)&myChar);
	printf("\nAfter allocating, the address of the myInt is: %p", (void*)&myIntTest);
	
	my_free(myChar);
	my_free(myIntTest);

	printf("\nMoving to test #5\n");
	system("pause");
	system("cls");

	//Test #5
	my_initialize_heap(poolSize);
	void *intArr = my_alloc(100 * sizeof(int));
	void *extraInt = my_alloc(sizeof(int));

	printf("\nAfter allocating, the address of the intArr is: %p", (void*)&intArr);
	printf("\nAfter allocating, the address of the extraInt is: %p", (void*)&extraInt);

	my_free(intArr);

	printf("\n\tAfter deallocating, the address of the freeHead is: %p", (void*)&freeHead);
	printf("\n\tAfter deallocating, the address of the extraInt is: %p", (void*)&extraInt);

	printf("\nMoving to standard deviation program\n");
	system("pause");
	system("cls");
	
	//Standard deviation program
	my_initialize_heap(poolSize);

	getInput();
	assignInts();
	printf("\n\n\n\tThe std Deviation is %f\n\n", stdDeviation());

	system("pause");
	*/
}

void my_initialize_heap(int size)
{
	freeHead = malloc(size);
	printf("\n\tThe address of the freeHead is: %p", (void*)&freeHead);

	*((int*)freeHead + intSize) = 0;
	poolSize = poolSize - overHead;
	*(int*)(freeHead) = poolSize;
	printf("\n\n\t\t\t%d Pointer should be null!", *((int*)freeHead+intSize));
}

void* my_alloc(int size)
{
	if (size % ptrSize != 0)
	{
		size = size % ptrSize;
	}
	int sizeLeft;
	int *nextPointer;
	int data;

	printf("\n\n\t\tAddress of pointer that allocator is working with: %p\n", (void*)freeHead);

	void* ptr = freeHead;

	if (*((int*)ptr + intSize) != 0)
	{
		printf("\n\n\t\t\t%d | %d free list is not null! walking free list", (*(int*)ptr),size);
		while (*(int*)ptr < size)
		{
			printf("Compared %d | %d", *(int*)ptr, size);
			(int*)ptr = (int*)ptr + intSize;
		}
	}
	*(int*)(ptr) = size;
	*((int*)ptr + intSize) = (overHead + size);

	poolSize = poolSize - (size + overHead);
	
	*((int*)ptr + size + overHead) = poolSize;
	
	//freeHead = ((int*)ptr + size + overHead);

	//printf("\nAllocated data block left: %d\n", *(int*)ptr);

	//printf("\n\tAllocated next pointer: %p\n", ((int*)ptr + intSize));

	//printf("\n\t\tPost split data block left: %d\n", *((int*)ptr+overHead+size));

	return ptr;
}

void my_free(void *startOfData)
{
	printf("\n\n\n\n\tDeallocator has been given address: %p", (void*)startOfData);
	freeHead = (void*)startOfData;

	int sizeFreed = *(int*)startOfData + overHead;

	poolSize += sizeFreed;
	
}

///////////////////////////////////////////////////
//Standard dev program

void getInput()
{
	int value;

	printf("\n\nPlease enter a positive integer for data set: ");
	scanf_s("%d", &value);

	stdDevNums = my_alloc(value*sizeof(int));
}

void assignInts()
{
	int val;
	int k;

	int sizeOfAllocated = (*((int*)stdDevNums)) / sizeof(int);

	for (k = 0; k < sizeOfAllocated; k++)
	{
		printf("\nPlease enter a positive integer: ");
		scanf_s("%d", &val);

		*((int*)stdDevNums + overHead + (k*sizeof(int))) = val;
	}
}

double stdDeviation()
{
	int k;
	double std = 0;
	double avg = getAvg();

	printf("\nThe average is %3.2f\n", avg);

	int devValuesCount = (*((int*)stdDevNums)) / sizeof(int);

	for (k = 0; k < devValuesCount; k++)
	{
		int value = *((int*)stdDevNums + overHead + (k*sizeof(int)));
		std = std + ((value - avg) * (value - avg));
	}

	std = std / devValuesCount;

	printf("\nVariance = %f\n", std);

	std = (double)sqrt(std);

	return std;
}

double getAvg()
{
	int k;
	double avg = 0;

	int devValuesCount = (*((int*)stdDevNums)) / sizeof(int);

	for (k = 0; k < devValuesCount; k++)
	{
		avg += (*((int*)stdDevNums + overHead + (k*sizeof(int))));
	}
	avg = avg / devValuesCount;

	return avg;
}