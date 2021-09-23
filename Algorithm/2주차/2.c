#include <stdio.h>
#include <stdlib.h>

#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))

int* makeArr(int n)
{
	int* arr = (int*)malloc(sizeof(int) * n);
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &arr[i]);
	}

	return arr;
}

void printStep(int* arr, int n, int step)
{
	printf("    STEP %2d : ", step + 1);
	for (int i = 0; i < n; i++)
		printf("%d ", arr[i]);
	printf("\n");
}

void insertSort(int* arr, int n)
{
	int save, temp;
	int step = 0;
	int j;

	for (int i = 1; i < n; i++)
	{
		save = arr[i];
		j = i - 1;
		while (j >= 0 && arr[j] > save)
		{
			arr[j + 1] = arr[j];
			j -= 1;
		}
		arr[j + 1] = save;
	}
}

int main(void)
{
	int n;
	int* arr;

	scanf("%d", &n);
	arr = makeArr(n);
	insertSort(arr, n);

	for (int i = 0; i < n; i++)
		printf(" %d", arr[i]);
	printf("\n");
	return 0;
}

/*
8
8 31 48 73 3 65 20 29

7
3 73 48 31 8 11 20
*/