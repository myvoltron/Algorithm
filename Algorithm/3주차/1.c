#include <stdio.h>
#include <stdlib.h>

#define HEAP_LEN	100

typedef struct
{
	int hArr[HEAP_LEN];
	int n;
} Heap;

Heap heap; // 힙 전역 선언 

void heapInit(); // 힙의 크기 초기화 
void insertItem(int key); // 삽입
int removeMax(); // 삭제
void upHeap(int idx);
void downHeap(int idx);
void printHeap(); // 출력

int main(void)
{
	// 선언 
	char oper;
	int key;
	int returnKey;

	// 힙 초기화 
	heapInit();

	// 명령어 
	while (1)
	{
		scanf("%c", &oper);
		getchar();

		if (oper == 'i')
		{
			scanf("%d", &key);
			getchar();
			insertItem(key);
			printf("0\n");
		}
		else if (oper == 'd')
		{
			returnKey = removeMax();
			printf("%d\n", returnKey);
		}
		else if (oper == 'p')
		{
			printHeap();
		}
		else if (oper == 'q')
			break;
	}
	return 0;
}

/*
* 입력예시1
i 209
i 400
d
i 77
d
p
q
*/
/*
* 입력예시2
i 5
i 15
i 10
i 20
i 30
i 25
p
d
i 31
i 29
d
p
q
*/

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