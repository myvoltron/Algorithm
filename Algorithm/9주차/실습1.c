#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define M	13

typedef struct HashNode
{
	int key;
	struct HashNode* next;
} HashType; 

int hash(int key)
{
	return key % M;
}

void init(HashType* ht);
void insertItem(HashType* ht, int key);
int findElement(HashType* ht, int key);
int removeElement(HashType* ht, int key);
void printHash(HashType* ht);

int main(void)
{
	int key;
	HashType HT[M];
	init(HT);

	srand(time(NULL));

	for (int i = 0; i < 20; i++)
		insertItem(HT, rand() % 90 + 10);
	printHash(HT);

	printf("\nInput Search Key: ");
	scanf("%d", &key);
	printf(" [%d] count : %d\n", key, findElement(HT, key));

	printf("\nInput delete Key: ");
	scanf("%d", &key);
	printf(" [%d] count : %d\n\n", key, removeElement(HT, key));

	printHash(HT);
	return 0;
}

void init(HashType* ht)
{
	for (int i = 0; i < M; i++)
		ht[i].next = NULL;
}
void insertItem(HashType* ht, int key)
{
	int v = hash(key);
	HashType* newNode = (HashType*)malloc(sizeof(HashType));
	newNode->key = key;
	newNode->next = ht[v].next;
	ht[v].next = newNode;
}
int findElement(HashType* ht, int key)
{
	int v = hash(key);
	int count = 0;
	HashType* ptr;
	for (ptr = ht[v].next; ptr != NULL; ptr = ptr->next)
		if (ptr->key == key)
			count++;

	return count;
}
int removeElement(HashType* ht, int key)
{
	int v = hash(key);
	int count = 0;
	HashType* ptr = &ht[v];
	HashType* qtr;
	
	while (ptr->next != NULL)
	{
		if (ptr->next->key == key)
		{
			count++;
			qtr = ptr->next;
			ptr->next = qtr->next;
			free(qtr);
		}
		else
			ptr = ptr->next;
	}

	return count;
}

void printHash(HashType* ht)
{
	HashType* ptr;
	for (int i = 0; i < M; i++)
	{
		printf("HT[%02d] : ", i);
		for (ptr = ht[i].next; ptr != NULL; ptr = ptr->next)
			printf("(%d) ", ptr->key);
		printf("\n");
	}
}