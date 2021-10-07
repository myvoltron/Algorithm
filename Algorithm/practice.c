#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct _node
{
	int key;
	struct _node* next;
} Node;

typedef struct _list
{
	Node* header;
} List;

void initList(List* list);
void insertItem(List* list, int key);
void insertLastItem(List* list, int key);
int removeFirst(List* list);
int seekFirst(List* list);
void printList(List* list);
int isEmpty(List* list);

void mergeSort(List* list, int n);
void partition(List* list, List* L1, List* L2, int n);
void merge(List* list, List* L1, List* L2);

int main(void)
{
	List list;
	initList(&list);

	int n;
	scanf("%d", &n);

	srand(time(NULL));
	for (int i = 0; i < n; i++)
		insertItem(&list, rand() % 100);
	printList(&list);

	mergeSort(&list, n);
	printList(&list);
	return 0;
}

void initList(List* list)
{
	list->header = NULL;
}
void insertItem(List* list, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->key = key;

	newNode->next = list->header;
	list->header = newNode;
}
void insertLastItem(List* list, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->key = key;
	newNode->next = NULL;

	Node* ptr = list->header;

	if (ptr == NULL)
		list->header = newNode;
	else
	{
		while (ptr->next != NULL)
			ptr = ptr->next;
		ptr->next = newNode;

		/*while (1)
		{
			if (ptr->next == NULL)
				break;
			ptr = ptr->next;
		}
		ptr->next = newNode;*/
	}
}
int removeFirst(List* list)
{
	int key = list->header->key;
	Node* ptr = list->header;
	list->header = list->header->next;
	free(ptr);
	return key;
}
int seekFirst(List* list)
{
	return list->header->key;
}
void printList(List* list)
{
	Node* ptr = list->header;

	while (ptr != NULL)
	{
		printf(" %d", ptr->key);
		ptr = ptr->next;
	}
	printf("\n");
}
int isEmpty(List* list)
{
	if (list->header == NULL)
		return 1;
	return 0;
}

void mergeSort(List* list, int n)
{
	List L1, L2;

	if (n > 1)
	{
		partition(list, &L1, &L2, n / 2);
		
		if (n % 2 == 0)
		{
			mergeSort(&L1, n / 2);
			mergeSort(&L2, n / 2);
		}
		else
		{
			mergeSort(&L1, n / 2);
			mergeSort(&L2, n / 2 + 1);
		}

		merge(list, &L1, &L2);
	}
}
void partition(List* list, List* L1, List* L2, int n)
{
	Node* ptr = list->header;
	L1->header = ptr;
	for (int i = 1; i < n; i++)
		ptr = ptr->next;
	L2->header = ptr->next;
	ptr->next = NULL;
}
void merge(List* list, List* L1, List* L2)
{
	List newList;
	initList(&newList);

	while (!isEmpty(L1) && !isEmpty(L2))
	{
		if (seekFirst(L1) <= seekFirst(L2))
			insertLastItem(&newList, removeFirst(L1));
		else 
			insertLastItem(&newList, removeFirst(L2));
	}
	while(!isEmpty(L1))
		insertLastItem(&newList, removeFirst(L1));
	while (!isEmpty(L2))
		insertLastItem(&newList, removeFirst(L2));

	list->header = newList.header;
}