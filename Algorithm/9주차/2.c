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

int getNextBucket(int v, int i, int M)
{
	return (v + i) % M;
}

void initHash(HashType* ht, int M);
int insertItem(HashType* ht, int key, int M);
int findElement(HashType* ht, int key, int M);

int main(void)
{
	char op;
	int loop, M, n, key, addrVal;
	HashType HT;

	scanf("%d %d", &M, &n);
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
			addrVal = insertItem(&HT, key, M);
			n -= 1;
			for (int i = 0; i < HT.A[addrVal].coll; i++)
				printf("C");
			printf("%d\n", addrVal);
			break;
		case 's':
			scanf("%d", &key);
			getchar();
			addrVal = findElement(&HT, key, M);
			if (addrVal == -1)
				printf("-1\n");
			else
			{
				printf("%d %d\n", addrVal, HT.A[addrVal].key);
			}
			break;
		case 'e':
			loop = 0;
		}
	}
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
int insertItem(HashType* ht, int key, int M)
{
	int v = hFunc(key, M);
	int i = 0;
	int b; 
	while (i < M)
	{
		b = getNextBucket(v, i, M);
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
int findElement(HashType* ht, int key, int M)
{
	int v = hFunc(key, M);
	int i = 0;
	int b;
	while (i < M)
	{
		b = getNextBucket(v, i, M);
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