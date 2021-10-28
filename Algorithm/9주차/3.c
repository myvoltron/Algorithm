#include <stdio.h>
#include <stdlib.h>

typedef struct
{
	int key;
	int coll;
} Bucket;

typedef struct
{
	Bucket* A;
} HashType;

int isEmpty(Bucket buc)
{
	if (buc.key == 0)
		return 1;
	else
		return 0;
}

int hFunc(int key, int M)
{
	return key % M;
}
int hpFunc(int key, int q)
{
	return q - (key % q);
}

int getNextBucket(int v, int i, int M, int q, int key)
{
	return (v + i * hpFunc(key, q)) % M;
}

void initHash(HashType* ht, int M);
int insertItem(HashType* ht, int key, int M, int q);
int findElement(HashType* ht, int key, int M, int q);
void printHash(HashType* ht, int M);

int main(void)
{
	char op;
	int loop;
	int M, n, q, key, addrVal;
	HashType HT;

	scanf("%d %d %d", &M, &n, &q);
	getchar();

	initHash(&HT, M);
	loop = 1;
	while (loop)
	{
		scanf("%c", &op);
		getchar();

		switch (op)
		{
		case 'i':
			if (n == 0)
				break;
			scanf("%d", &key);
			getchar();
			addrVal = insertItem(&HT, key, M, q);
			n -= 1;
			for (int i = 0; i < HT.A[addrVal].coll; i++)
				printf("C");
			printf("%d\n", addrVal);
			break;
		case 's':
			scanf("%d", &key);
			getchar();
			addrVal = findElement(&HT, key, M, q);
			if (addrVal == -1)
				printf("-1\n");
			else
			{
				printf("%d %d\n", addrVal, HT.A[addrVal].key);
			}
			break;
		case 'p':
			printHash(&HT, M);
			break;
		case 'e':
			printHash(&HT, M);
			loop = 0;
		}
	}

	free(HT.A);
	return 0;
}

void initHash(HashType* ht, int M)
{
	ht->A = (Bucket*)malloc(sizeof(Bucket) * M);
	for (int i = 0; i < M; i++)
	{
		ht->A[i].key = 0;
		ht->A[i].coll = 0;
	}
}
int insertItem(HashType* ht, int key, int M, int q)
{
	int v = hFunc(key, M);
	int i = 0;
	int b;
	while (i < M)
	{
		b = getNextBucket(v, i, M, q, key);
		if (isEmpty(ht->A[b]))
		{
			ht->A[b].key = key;
			ht->A[b].coll = i;
			return b;
		}
		else
			i += 1;
	}
}
int findElement(HashType* ht, int key, int M, int q)
{
	int v = hFunc(key, M);
	int i = 0;
	int b;
	while (i < M)
	{
		b = getNextBucket(v, i, M, q, key);
		if (isEmpty(ht->A[b]))
		{
			return -1;
		}
		else if (key == ht->A[b].key)
			return b;
		else
			i += 1;
	}

	return -1;
}

void printHash(HashType* ht, int M)
{
	for (int i = 0; i < M; i++)
		printf(" %d", ht->A[i].key);
	printf("\n");
}