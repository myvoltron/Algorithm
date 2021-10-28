#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int key;
	struct node* next;
} HashType;

int hFunc(int key, int M)
{
	return key % M;
}

void initHash(HashType* ht, int M);
void insertItem(HashType* ht, int key, int M);
int findElement(HashType* ht, int key, int M);
int removeElement(HashType* ht, int key, int M);
void printHash(HashType* ht, int M);

int main(void)
{
	char op;
	int loop, M, key, val;
	HashType* HT;

	scanf("%d", &M);
	getchar();

	HT = (HashType*)malloc(sizeof(HashType) * M);
	initHash(HT, M);

	loop = 1;
	while (loop)
	{
		scanf("%c", &op);
		getchar();

		switch (op)
		{
		case 'i':
			scanf("%d", &key);
			getchar();
			insertItem(HT, key, M);
			break;
		case 's':
			scanf("%d", &key);
			getchar();
			val = findElement(HT, key, M);
			printf("%d\n", val);
			break;
		case 'd':
			scanf("%d", &key);
			getchar();
			val = removeElement(HT, key, M);
			printf("%d\n", val);
			break;
		case 'p':
			printHash(HT, M);
			break;
		case 'e':
			loop = 0;
		}
	}
	return 0;
}

void initHash(HashType* ht, int M)
{
	for (int i = 0; i < M; i++)
		ht[i].next = NULL;
}
void insertItem(HashType* ht, int key, int M)
{
	int v = hFunc(key, M);
	HashType* newNode = (HashType*)malloc(sizeof(HashType));
	newNode->key = key;
	newNode->next = ht[v].next;
	ht[v].next = newNode;
}
int findElement(HashType* ht, int key, int M)
{
	int v = hFunc(key, M);
	int count = 0;
	int val = 0;
	HashType* ptr;

	for (ptr = ht[v].next; ptr != NULL; ptr = ptr->next)
	{
		count++;
		if (ptr->key == key)
		{
			val = count;
			break;
		}
	}
	return val;
}
int removeElement(HashType* ht, int key, int M)
{
	int v = hFunc(key, M);
	int count = 0;
	int val = 0;
	HashType* ptr = &ht[v];
	HashType* qtr;

	while (ptr->next != NULL)
	{
		count++;
		if (ptr->next->key == key)
		{
			qtr = ptr->next;
			ptr->next = qtr->next;
			free(qtr);
			val = count;
		}
		else
			ptr = ptr->next;
	}

	return val;
}
void printHash(HashType* ht, int M)
{
	HashType* ptr;
	for (int i = 0; i < M; i++)
	{
		for (ptr = ht[i].next; ptr != NULL; ptr = ptr->next)
			printf(" %d", ptr->key);
	}
	printf("\n");
}
