#include <stdio.h>
#include <stdlib.h>

#define M	13
typedef struct
{
	int key;
	int probeCount;
} Bucket;

typedef struct
{
	Bucket A[M];
} HashType;

int isEmpty(HashType* ht, int b)
{
	if (ht->A[b].key == 0)
		return 1;
	else
		return 0;
}

int hFunc(int key)
{
	return key % M;
}
int h2Func(int key)
{
	return 11 - key % 11;
}

int getNextBucketLinear(int v, int i)
{
	return (v + i) % M;
}
int getNextBucketQuadratic(int v, int i)
{
	return (v + i * i) % M;
}
int getNextBucketDouble(int v, int i, int key)
{
	return (v + i * h2Func(key)) % M;
}

void initHash(HashType* ht);
void insertItem(HashType* ht, int key);
void printHash(HashType* ht);

int main(void)
{
	HashType HT;
	initHash(&HT);

	insertItem(&HT, 25); insertItem(&HT, 13); insertItem(&HT, 16);
	insertItem(&HT, 15); insertItem(&HT, 7); insertItem(&HT, 28);
	insertItem(&HT, 31); insertItem(&HT, 20); insertItem(&HT, 1);
	insertItem(&HT, 38);
	printHash(&HT);

	return 0;
}

void initHash(HashType* ht)
{
	for (int i = 0; i < M; i++)
	{
		ht->A[i].key = 0;
		ht->A[i].probeCount = 0;
	}
}
void insertItem(HashType* ht, int key)
{
	int i, v, count, b; 
	v = hFunc(key);
	i = 0;
	count = 0;

	while (i < M)
	{
		count++;
		b = getNextBucketLinear(v, i);
		if (isEmpty(ht, b)) 
		{
			ht->A[b].key = key;
			ht->A[b].probeCount = count;
			return;
		}
		else
		{
			i++;
		}
	}
}
void printHash(HashType* ht)
{
	printf("Bucket   Key  Probe\n");
	printf("===================\n");

	for (int i = 0; i < M; i++)
	{
		printf("HT[%02d] :  %2d   %d\n", i, ht->A[i].key, ht->A[i].probeCount);
	}
}