#include <stdio.h>
#include <stdlib.h>

typedef struct
{
	int key;
} element;

typedef struct
{
	element* dict;
	int size;
} DictType;

int findElement(DictType* d, int key, int l, int r);

void initDict(DictType* d, int n);
void makeDict(DictType* d, int n);

int main(void)
{
	DictType D;
	int n, key;
	scanf("%d %d", &n, &key);

	initDict(&D, n);
	makeDict(&D, n);

	int keyIdx = findElement(&D, key, 0, n - 1);
	if (keyIdx == -1)
		printf("%d\n", n); // 검색 실패 
	else
		printf(" %d\n", keyIdx);
	return 0;
}

/*
8 55
-92 -31 -7  4 14 20 29 44
*/

int findElement(DictType* d, int key, int l, int r)
{
	/*int mid;
	while (l < r)
	{
		mid = (l + r) / 2;
		if (r - l == 1)
		{
			if (key <= d->dict[l].key)
				return l;
			else if (key <= d->dict[r].key)
				return r;
			else
				return -1;
		}
		if (key == d->dict[mid].key)
			return mid;
		else if (key < d->dict[mid].key)
			r = mid;
		else
			l = mid;
	}
	return -1;*/

	int mid;
	while (l <= r)
	{
		mid = (l + r) / 2;
		if (d->dict[mid].key == key)
			return mid;
		else if (key < d->dict[mid].key)
			r = mid - 1;
		else
			l = mid + 1;
	}
	return l;
}

void initDict(DictType* d, int n)
{
	d->size = 0;
	d->dict = (element*)malloc(sizeof(element) * n);
}
void makeDict(DictType* d, int n)
{
	int key;

	for (int i = 0; i < n; i++)
	{
		scanf("%d", &key);
		d->dict[i].key = key;
	}
}
