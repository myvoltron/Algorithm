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

int rFindElement(DictType* d, int key, int l, int r);

void initDict(DictType* d, int n);
void makeDict(DictType* d, int n);

int main(void)
{
	DictType D; 
	int n, key;
	scanf("%d %d", &n, &key);

	initDict(&D, n);
	makeDict(&D, n);

	int keyIdx = rFindElement(&D, key, 0, n - 1);
	if (keyIdx == -1)
		printf("-1\n"); // 검색 실패 
	else
		printf(" %d\n", keyIdx);
	return 0;
}

/*
8 55
-92 -31 -7  4 14 20 29 44
*/

int rFindElement(DictType* d, int key, int l, int r)
{
	if (l > r)
		return -1;

	int mid = (l + r) / 2;
	if (r - l == 1)
	{
		if (key >= d->dict[r].key)
			return r;
		else if (key >= d->dict[l].key)
			return l;
		else
			return -1;
	}
	if (key == d->dict[mid].key)
		return mid;
	else if (key < d->dict[mid].key)
		return rFindElement(d, key, l, mid);
	else 
		return rFindElement(d, key, mid, r);
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
