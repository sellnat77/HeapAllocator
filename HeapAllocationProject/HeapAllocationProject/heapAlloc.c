#include "heapAlloc.h"

void main()
{
	
	//Test #1
	my_initialize_heap(poolSize);
	printf("\nBefore allocating, the address of the freeHead is: %p\n", freeHead);
	
	void *myInt = my_alloc(sizeof(int));
	printf("\nAfter allocating, the address of the int pointer is: %p\n", myInt);
	printf("\nThe address of the freeHead is: %p\n", freeHead);

	my_free(myInt);
	printf("\n\tAfter deallocating, the address of the freeHead is: %p\n", freeHead);

	printf("\nBefore allocating, the address of the freeHead is: %p\n", freeHead);
	
	void *myOtherInt = my_alloc(sizeof(int));
	printf("\nAfter allocating, the address of the int pointer is: %p\n", myOtherInt);
	printf("\nThe address of the freeHead is: %p\n", freeHead);

	my_free(myOtherInt);
	printf("\n\tAfter deallocating, the address of the freeHead is: %p\n", freeHead);
	
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
	
	//Test #3
	my_initialize_heap(poolSize);

	void *first = my_alloc(sizeof(int));
	void *second = my_alloc(sizeof(int));
	void *third = my_alloc(sizeof(int));

	printf("\nAfter allocating, the address of the first is: %p", first);
	printf("\nAfter allocating, the address of the second is: %p", second);
	printf("\nAfter allocating, the address of the third is: %p", third);

	void *freedAddress = second;
	printf("\nStoring second address for comparison: %p", freedAddress);

	my_free(second);
	
	printf("\n\t\tStoring second address after deallocating for comparison: %p", freedAddress);

	printf("\n\tAfter deallocating second, the address of the freeHead is: %p", freeHead);

	void *myDoub = my_alloc(sizeof(double));

	printf("\n\tAfter allocating, the address of the myDoub is: %p", myDoub);

	void *fourth = my_alloc(sizeof(int));

	printf("\nAfter allocating, the address of the fourth is: %p == %p", fourth,freedAddress);
	
	my_free(first);
	my_free(third);
	my_free(fourth);
	my_free(myDoub);

	printf("\nMoving to test #4\n");
	system("pause");
	system("cls");
	
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
	void *intArr = my_alloc((100 * sizeof(int)));
	printf("\n\tAfter allocating array, the address of the freeHead is: %p", (int *)&freeHead);
	void *extraInt = my_alloc(sizeof(int));
	printf("\n\tAfter allocating int, the address of the freeHead is: %p", (int *)&freeHead);

	printf("\nAfter allocating, the address of the intArr is: %p", (int *)&intArr);
	printf("\nAfter allocating, the address of the extraInt is: %p", (int *)&extraInt);

	my_free(intArr);

	printf("\n\tAfter deallocating, the address of the freeHead is: %p", (int *)&freeHead);
	printf("\n\tAfter deallocating, the address of the extraInt is: %p", (int *)&extraInt);

	my_free(extraInt);

	printf("\nMoving to standard deviation program\n");
	system("pause");
	system("cls");
	
	
	//Standard deviation program
	my_initialize_heap(poolSize);

	getInput();
	assignInts();
	printf("\n\n\n\tThe std Deviation is %f\n\n", stdDeviation());

	system("pause");
	
}

void my_initialize_heap(int size)
{
	freeHead = malloc(size);
	printf("\n\tThe address of the freeHead is: %p", freeHead);

	*((int*)freeHead + intSize) = 0;
	poolSize = poolSize - overHead;
	*(int*)(freeHead) = poolSize;
}

void* my_alloc(int size)
{
	if (size % ptrSize != 0)
	{
		size = size + (size % ptrSize);
	}
	int sizeLeft;
	int *nextPointer;
	int data;
	int count = 0;

	void* ptr = freeHead;
	if (*((int*)ptr + intSize) != 0)
	{
		while (*(int*)ptr < size)
		{
			count++;
			(int*)ptr = (int*)ptr + intSize;
		}
	}
	*(int*)(ptr) = size;
	*((int*)ptr + intSize) = (overHead + size);

	poolSize = poolSize - (size + overHead);
	
	*((int*)ptr + size + overHead) = poolSize;
	
	if (count == 0)
	{
		//Moving free ptr to next open block
		freeHead = ((int *)ptr + size + overHead);
	}
	
	return ptr;
}

void my_free(void *startOfData)
{
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