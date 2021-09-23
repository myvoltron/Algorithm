#include <stdio.h>
#include <stdlib.h>

typedef struct _node {
	char elem;
	struct _node* prev;
	struct _node* next;
} Node;

typedef struct _linkedList {
	Node* head;
	Node* trail;
	int numOfelem;
} linkedList;

typedef linkedList List;

void listInit(List* plist);
void listInsert(List* plist, int r, char e);
char listDelete(List* plist, int r);
char listGet(List* plist, int r);
void listPrint(List* plist);

int main(void)
{
	int num;

	char oper;
	int rank;
	char elem;
	char returnVal;

	List list;
	listInit(&list);

	scanf("%d", &num);
	getchar();

	for (int i = 0; i < num; i++)
	{
		scanf("%c", &oper);

		switch (oper)
		{
		case 'A':
			scanf("%d %c", &rank, &elem);
			getchar();
			listInsert(&list, rank, elem);
			break;
		case 'D':
			scanf("%d", &rank);
			getchar();
			returnVal = listDelete(&list, rank);
			break;
		case 'G':
			scanf("%d", &rank);
			getchar();
			returnVal = listGet(&list, rank);
			if (returnVal != -1)
				printf("%c", returnVal);
			break;
		case 'P':
			getchar();
			listPrint(&list);
			break;
		}
	}

	return 0;
}

/*
첫번째 예제
5
A 1 S
A 2 t
A 3 r
A 3 a
P
*/

/*
두번째 예제
9
A 1 D
A 2 a
A 3 y
D 1
P
G 3
A 1 S
P
G 3
*/
void listInit(List* plist)
{
	plist->head = (Node*)malloc(sizeof(Node));
	plist->trail = (Node*)malloc(sizeof(Node));

	plist->head->next = plist->trail;
	plist->trail->prev = plist->head;

	plist->numOfelem = 0;
}
void listInsert(List* plist, int r, char e)
{
	if (r < 1 || r - 1 > plist->numOfelem)
	{
		printf("invalid position\n");
		return;
	}

	Node* pnode = plist->head;
	Node* newNode = (Node*)malloc(sizeof(Node));

	newNode->elem = e;

	for (int i = 0; i < r - 1; i++)
	{
		pnode = pnode->next;
	}

	newNode->next = pnode->next;
	newNode->prev = pnode;
	pnode->next->prev = newNode;
	pnode->next = newNode;

	plist->numOfelem += 1;
}
char listDelete(List* plist, int r)
{
	if (plist->numOfelem == 0 || r > plist->numOfelem)
	{
		printf("invalid position\n");
		return -1;
	}

	Node* pnode = plist->head;
	char returnElem;

	for (int i = 0; i < r; i++)
	{
		pnode = pnode->next;
	}
	returnElem = pnode->elem;

	pnode->prev->next = pnode->next;
	pnode->next->prev = pnode->prev;
	free(pnode);

	plist->numOfelem -= 1;
	return returnElem;
}
char listGet(List* plist, int r)
{
	if (plist->numOfelem == 0 || r > plist->numOfelem)
	{
		printf("invalid position\n");
		return -1;
	}

	Node* pnode = plist->head;
	char returnElem;

	for (int i = 0; i < r; i++)
	{
		pnode = pnode->next;
	}
	returnElem = pnode->elem;
	return returnElem;
}
void listPrint(List* plist)
{
	Node* pnode = plist->head->next;
	while (pnode != plist->trail)
	{
		printf("%c", pnode->elem);
		pnode = pnode->next;
	}
	printf("\n");
}