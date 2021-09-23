#pragma warning(disable: 4996)
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
void rBuildHeap(int idx); // 상향식 힙 생성 
void buildHeap();         // 상향식 힙 생성 
void inPlaceHeapSort(); // 정렬 
void printArray(); // 출력 

int main(void)
{
	int numOfKey;
	int key;

	// 힙 초기화 
	heapInit();

	scanf("%d", &numOfKey);
	for (int i = 0; i < numOfKey; i++)
	{
		scanf("%d", &heap.hArr[i + 1]);
		heap.n += 1;
	}
	// rBuildHeap(1);
	buildHeap();

	inPlaceHeapSort();
	heap.n = numOfKey;
	printArray();
	return 0;
}

/*
3
209 400 77

6
24 17 33 50 60 70

8
5 15 10 20 30 25 31 29
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
void inPlaceHeapSort()
{
	int size = heap.n;
	int key;

	for (int i = 0; i < size; i++)
	{
		key = removeMax();
		heap.hArr[heap.n + 1] = key;
	}
}
void printArray()
{
	for (int i = 1; i <= heap.n; i++)
		printf("%d ", heap.hArr[i]);
	printf("\n");
}