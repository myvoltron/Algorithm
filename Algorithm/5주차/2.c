#pragma warning(disable: 4996)
#include <stdio.h>
#include <stdlib.h> 
#include <time.h> 

#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))

void listPrint(int* list, int n);
void inPlaceQuickSort(int* list, int l, int r);
int inPlacePartition(int* list, int l, int r, int k);
int findPivot(int* list, int l, int r);
// l -> left, r -> right 

int main(void)
{
	int n;
	int* list;

	scanf("%d", &n);
	list = (int*)malloc(sizeof(int) * n);

	for (int i = 0; i < n; i++)
		scanf("%d", &list[i]);
	
	// listPrint(list, n);

	// sort 
	inPlaceQuickSort(list, 0, n - 1);
	listPrint(list, n);
	return 0;
}

/*
8
73 65 48 31 29 20 8 3
*/

void listPrint(int* list, int n)
{
	for (int i = 0; i < n; i++)
		printf("%d ", list[i]);
	printf("\n");
}
void inPlaceQuickSort(int* list, int l, int r)
{
	if (l >= r)
		return;

	int k = findPivot(list, l, r);
	//printf("l = [%d], r = [%d]\n", l, r);
	//printf("k = [%d]\n", k);
	int newidx = inPlacePartition(list, l, r, k);
	inPlaceQuickSort(list, l, newidx - 1);
	inPlaceQuickSort(list, newidx + 1, r);
}
int inPlacePartition(int* list, int l, int r, int k)
{
	int temp;
	
	int P = list[k];
	SWAP(list[k], list[r], temp);
	
	int low = l;
	int high = r - 1; 

	while (low <= high)
	{
		while (low <= high && list[low] <= P)
			low++;
		while (high >= low && list[high] >= P)
			high--;
		if (low <= high)
			SWAP(list[low], list[high], temp);
	}

	SWAP(list[low], list[r], temp);
	return low;
}
int findPivot(int* list, int l, int r)
{
	srand(time(NULL));
	return rand() % (r - l + 1) + l;
}