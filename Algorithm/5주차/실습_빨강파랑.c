#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE	10
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))

void arrPrint(char list[]);
void partition(char list[], int left, int right);

int main(void)
{
	char list[SIZE];
	srand(time(NULL));

	for (int i = 0; i < SIZE; i++)
	{
		if (rand() % 2 == 0)
			list[i] = 'W';
		else
			list[i] = 'B'; 
	}
	arrPrint(list);

	partition(list, 0, SIZE - 1);
	return 0;
}

void arrPrint(char list[])
{
	for (int i = 0; i < SIZE; i++)
		printf("[%c] ", list[i]);
	printf("\n\n");
}
void partition(char list[], int left, int right)
{
	int low = left - 1, high = right + 1;
	char temp;

	do
	{
		do
			low++;
		while (list[low] == 'W');

		do
			high--;
		while (list[high] == 'B');

		if (low < high)
			SWAP(list[low], list[high], temp);

		printf("\nlow = %d, high = %d\n", low, high);
		arrPrint(list);
	} while (low < high);
}