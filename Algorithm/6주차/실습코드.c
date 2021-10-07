#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE	20

typedef struct
{
	int key;
	char value[10];
} element;

typedef struct
{
	element dict[SIZE];
	int size;
} DictType;

void insertionSort(DictType* d);
int rFindElement(DictType* d, int key, int l, int r);

void initDict(DictType* d);
void insertKey(DictType* d);
void insertValue(DictType* d);
void makeDict(DictType* d);
void printDict(DictType* d);

int main(void)
{
	DictType D;

	initDict(&D);
	srand(time(NULL));
	makeDict(&D);
	printDict(&D);
	getchar();

	printf("\n");
	insertionSort(&D);
	printDict(&D);
	getchar();

	printf("\n검색할 키 값을 입력 : ");
	int key;
	scanf("%d", &key);
	int keyIdx = rFindElement(&D, key, 0, SIZE - 1);

	if (keyIdx == -1)
		printf("\n 검색 실패\n");
	else
	{
		printf("\n위치 %d에서 키 : %d, 값 : ", keyIdx, key);
		for (int j = 0; j < 5; j++)
			printf("%c", D.dict[keyIdx].value[j]);
		printf("이 검색되었음\n");
	}
	return 0;
}

void insertionSort(DictType* d)
{
	int i, j;
	element item;
	for (i = 1; i < SIZE; i++)
	{
		item = d->dict[i];
		for (j = i - 1; j >= 0 && d->dict[j].key > item.key; j--)
			d->dict[j + 1] = d->dict[j];
		d->dict[j + 1] = item;
	}
}
int rFindElement(DictType* d, int key, int l, int r)
{
	if (l > r)
		return -1;
	int mid = (l + r) / 2;
	if (key == d->dict[mid].key)
		return mid;
	else if (key < d->dict[mid].key)
		return rFindElement(d, key, l, mid - 1);
	else
		return rFindElement(d, key, mid + 1, r);
}

void initDict(DictType* d)
{
	d->size = 0;
}
void insertKey(DictType* d)
{
	for (int i = 0; i < SIZE; i++)
	{
		d->dict[i].key = rand() % 30 + 1;
		for (int j = 0; j < i; j++)
			if (d->dict[i].key == d->dict[j].key)
				i--;
	}
}
void insertValue(DictType* d)
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < 5; j++)
			d->dict[i].value[j] = rand() % 26 + 97;
		d->size++;
	}
}
void makeDict(DictType* d)
{
	insertKey(d);
	insertValue(d);
}
void printDict(DictType* d)
{
	printf("key value \n==========\n");
	for (int i = 0; i < d->size; i++)
	{
		printf("%2d  ", d->dict[i].key);
		for (int j = 0; j < 5; j++)
			printf("%c", d->dict[i].value[j]);
		printf("\n");
	}
}
}