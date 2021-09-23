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
void rBuildHeap(int idx); // 상향식 힙 생성 || 재귀 
void buildHeap();		  //       "       || 비재귀 
void downHeap(int idx);
void printHeap(); // 출력

int main(void)
{
	// 선언 
	int numOfKey;
	int* KeyArr = NULL;

	// 힙 초기화 
	heapInit();

	// 배열로 받는다 
	scanf("%d", &numOfKey);
	for (int i = 1; i <= numOfKey; i++)
	{
		scanf("%d", &heap.hArr[i]);
		heap.n += 1;
	}

	// 재배치해서 힙 생성, we have 2 way.
	//rBuildHeap(1);
	buildHeap();
	// 출력 
	printHeap();
	return 0;
}

/*
3
209 400 77

8
5 15 10 20 30 25 31 29

6
24 17 33 50 60 70
*/

void heapInit()
{
	heap.n = 0;
}
void rBuildHeap(int idx)
{
	if (idx > heap.n)
		return;
	rBuildHeap(2 * idx);
	rBuildHeap(2 * idx + 1);
	downHeap(idx);
}
void buildHeap()
{
	for (int i = heap.n / 2; i >= 1; i--)
		downHeap(i);
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