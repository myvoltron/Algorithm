#pragma warning(disable: 4996)
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Heap Setting 
#define HEAP_LEN	100

typedef struct
{
	int hArr[HEAP_LEN];
	int n;
} Heap;

// Stack Setting 
typedef struct _node
{
	int elem;
	struct _node *next;
} Node;
typedef struct _stack 
{
	Node* t;
} Stack;

// Heap Function 
void heapInit(); // Heap init 
void insertItem(int key); // 삽입
int removeMax(); // 삭제
void upHeap(int idx);
void downHeap(int idx);
void printHeap(); // 출력

int findLastNode(int v, int n); // find index of lastNode 
void binaryExpansion(int i, Stack* stack); // decimal -> binary 

// Stack Function 
void stackInit(Stack* stack);
void push(Stack* stack, int e);
int pop(Stack* stack);
int SIsEmpty(Stack* stack);

Heap heap; // Heap 

int main(void)
{
	int numOfHeap;
	int elem;
	int lastNodeIndex;

	// init 
	heapInit();
	srand(time(NULL));

	// make Heap
	scanf("%d", &numOfHeap);
	for (int i = 0; i < numOfHeap; i++)
	{
		elem = rand() % 100 + 1;
		insertItem(elem);
	}
	printf("Heap print :");
	printHeap();
	
	lastNodeIndex = findLastNode(1, numOfHeap);
	printf("Last Node's Index : %d\n", lastNodeIndex);
	printf("Last Node's Value : %d\n", heap.hArr[lastNodeIndex]);
	return 0;
}

void heapInit()
{
	heap.n = 0;
}
void insertItem(int key)
{
	heap.n += 1;
	heap.hArr[heap.n] = key;
	upHeap(heap.n);
}
int removeMax()
{
	int key = heap.hArr[1];
	heap.hArr[1] = heap.hArr[heap.n];
	heap.n -= 1;
	downHeap(1);
	return key;
}
void upHeap(int idx)
{
	if (idx == 1)
		return;

	int lastIdx = idx;
	int lastNode = heap.hArr[lastIdx];

	while ((lastIdx != 1) && (lastNode > heap.hArr[lastIdx / 2]))
	{
		heap.hArr[lastIdx] = heap.hArr[lastIdx / 2];
		lastIdx /= 2;
	}
	heap.hArr[lastIdx] = lastNode;
}
void downHeap(int idx)
{
	int fKey = heap.hArr[idx];
	int fIdx = idx;
	int leftIdx = fIdx * 2;

	while (leftIdx <= heap.n)
	{
		if ((leftIdx < heap.n) && (heap.hArr[leftIdx] < heap.hArr[leftIdx + 1]))
		{
			leftIdx += 1;
		}
		if (fKey >= heap.hArr[leftIdx])
			break;

		heap.hArr[fIdx] = heap.hArr[leftIdx];
		fIdx = leftIdx;
		leftIdx *= 2;
	}

	heap.hArr[fIdx] = fKey;
}
void printHeap()
{
	for (int i = 1; i <= heap.n; i++)
		printf(" %d", heap.hArr[i]);
	printf("\n");
}

void stackInit(Stack* stack)
{
	stack->t = NULL;
}
void push(Stack* stack, int e)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->elem = e;
	newNode->next = stack->t;
	stack->t = newNode; 
}
int pop(Stack* stack)
{
	int elem = stack->t->elem; 
	Node* ptr = stack->t;
	stack->t = stack->t->next;
	free(ptr);
	return elem;
}
int SIsEmpty(Stack* stack)
{
	if (stack->t == NULL)
		return 1;
	return 0;
}

int findLastNode(int v, int n)
{
	int bit;
	int trash;
	int step = 1; 
	Stack stack;

	stackInit(&stack);
	binaryExpansion(n, &stack);
	trash = pop(&stack); // remove highest-order bit 

	while (!SIsEmpty(&stack))
	{
		bit = pop(&stack);
		if (bit == 0)
			v = v * 2;
		else
			v = v * 2 + 1;
		printf("step#%d : index : %d || value : %d\n", step++, v, heap.hArr[v]);
	}
	return v;
}
void binaryExpansion(int i, Stack* stack)
{
	while (i >= 2)
	{
		push(stack, i % 2);
		i /= 2; 
	}
	push(stack, i);
}