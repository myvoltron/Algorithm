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

void selectSort(int* arr, int n)
{
	int max, temp;
	int step = 0;
	for (int i = n - 1; i >= 1; i--)
	{
		max = i;
		for (int j = i - 1; j >= 0; j--)
		{
			if (arr[j] > arr[max])
			{
				max = j;
			}
		}
		/*temp = arr[max];
		arr[max] = arr[i];
		arr[i] = temp;*/

		SWAP(arr[i], arr[max], temp);
		//printStep(arr, n, step++);
	}
}

int main(void)
{
	int n;
	int* arr;

	scanf("%d", &n);
	arr = makeArr(n);
	selectSort(arr, n);

	for (int i = 0; i < n; i++)
		printf("%d ", arr[i]);
	printf("\n");
	return 0;
}

/*
8
8 31 48 73 3 65 20 29
*/