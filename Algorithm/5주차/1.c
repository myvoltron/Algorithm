#pragma warning(disable: 4996)
#include <stdio.h>
#include <stdlib.h>
// #include <time.h>

typedef struct _node
{
	int elem;
	struct _node* next;
} Node; 
typedef struct _list
{
	Node* head;
} List;

// list func 
void listInit(List* plist);
void listInsert(List* plist, int elem);
void listInsertLast(List* plist, int elem);
int listRemove(List* plist); 
void listPrint(List* plist);
int isEmpty(List* plist);
int listSeek(List* plist);

// sort func 
void mergeSort(List* plist, int n);
void partition(List* plist, List* L1, List* L2, int n);
void merge(List* plist, List* L1, List* L2);

int main(void)
{
	List list;
	listInit(&list);
	
	int elem;
	int numOfList;
	scanf("%d", &numOfList);

	// srand(time(NULL));
	for (int i = 0; i < numOfList; i++)
	{
		scanf("%d", &elem);
		listInsert(&list, elem);
		// listInsert(&list, rand() % 100);
	}
	// listPrint(&list);

	// sort
	mergeSort(&list, numOfList);
	listPrint(&list);
	return 0;
}

void listInit(List* plist)
{
	plist->head = NULL;
}
void listInsert(List* plist, int elem)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->elem = elem;
	newNode->next = plist->head;
	plist->head = newNode;
}
void listInsertLast(List* plist, int elem)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->elem = elem;
	newNode->next = NULL;

	Node* ptr = plist->head;

	if (ptr == NULL)
		plist->head = newNode;
	else
	{
		while (1)
		{
			if (ptr->next == NULL)
				break;
			ptr = ptr->next;
		}
		ptr->next = newNode;
	}
}
int listRemove(List* plist)
{
	int elem = plist->head->elem;
	Node* ptr = plist->head;
	plist->head = plist->head->next;
	free(ptr);
	return elem;
}
void listPrint(List* plist)
{
	Node* ptr = plist->head; 

	while (ptr != NULL)
	{
		printf(" %d", ptr->elem);
		ptr = ptr->next;
	}
	printf("\n");
}
int isEmpty(List* plist)
{
	if (plist->head == NULL)
		return 1;
	return 0;
}
int listSeek(List* plist)
{
	return plist->head->elem;
}

void mergeSort(List* plist, int n)
{
	List L1, L2;

	if (n > 1)
	{
		partition(plist, &L1, &L2, n);

		// listPrint(&L1);
		// listPrint(&L2);

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

		merge(plist, &L1, &L2);
		// printf("After merge : ");
		// listPrint(plist);
	}
}
void partition(List* plist, List* L1, List* L2, int n)
{
	Node* ptr = plist->head;
	L1->head = ptr; 
	for (int i = 1; i < n / 2; i++)
		ptr = ptr->next;
	L2->head = ptr->next;
	ptr->next = NULL;
}
void merge(List* plist, List* L1, List* L2)
{
	Node* ptr1 = L1->head;
	Node* ptr2 = L2->head;
	List newList;
	listInit(&newList);

	while (!isEmpty(L1) && !isEmpty(L2))
	{
		int e1 = listSeek(L1), e2 = listSeek(L2);
		// printf("e1 = [%d], e2 = [%d]\n", e1, e2);
		if (e1 <= e2)
		{
			listInsertLast(&newList, listRemove(L1));
		}
		else
		{
			listInsertLast(&newList, listRemove(L2));
		}
	}
	while (!isEmpty(L1))
		listInsertLast(&newList, listRemove(L1));
	while (!isEmpty(L2))
		listInsertLast(&newList, listRemove(L2));

	// listPrint(&newList);
	plist->head = newList.head;
}