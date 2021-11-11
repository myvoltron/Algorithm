#include <stdio.h>
#include <stdlib.h>

#define TRUE	1
#define FALSE	0
#define SIZE    100

typedef struct
{
	int elem[SIZE];
	int front, rear;
}QueueType;

typedef struct Edge
{
	int weight;
	int v1, v2;
	struct Edge* next;
} Edge;

typedef struct
{
	Edge* adjMatrix[100][100];
} AdjMatrix;

typedef struct Vertex
{
	int nodeNum;
	int isVisited;
	struct Vertex* next;
} Vertex;

typedef struct
{
	Vertex* vHead;
	Edge* eHead;
} Graph;

void initQueue(QueueType* Q)
{
	Q->front = Q->rear = 0;
}

int isEmpty(QueueType* Q)
{
	return Q->rear == Q->front;
}

int isFull(QueueType* Q)
{
	return (Q->rear + 1) % SIZE == Q->front;
}

void enqueue(QueueType* Q, int vName)
{
	if (isFull(Q))
	{
		printf("FULL\n");
		return;
	}
	Q->rear = (Q->rear + 1) % SIZE;
	Q->elem[Q->rear] = vName;
}

int dequeue(QueueType* Q)
{
	if (isEmpty(Q))
	{
		printf("EMPTY\n");
		return 0;
	}
	Q->front = (Q->front + 1) % SIZE;
	return Q->elem[Q->front];
}

void printGraph(Graph* G, AdjMatrix* AM, int n)
{
	Vertex* ptr = G->vHead;
	int idx = 0;
	for (; ptr != NULL; ptr = ptr->next)
	{
		printf("[%d] : ", ptr->nodeNum);
		for (int j = 0; j < n; j++)
		{
			if (AM->adjMatrix[idx][j] != NULL)
				printf(" %d", j + 1);
		}
		printf("\n");

		idx++;
	}
	printf("\n");
}

void initGraph(Graph* G);
void initAdjMatrix(AdjMatrix* AM, int n);
void createVertex(Graph* G, int nodeNum);
void createEdge(Graph* G, AdjMatrix* AM, int v1, int v2, int w);
void insertAdj(AdjMatrix* AM, Edge* e, int v1, int v2);

Vertex* findVertex(Graph* G, int nodeNum);

void BFS(Graph* G, AdjMatrix* AM, int startPoint, int n)
{
	int idx = 0;
	Vertex* v = findVertex(G, startPoint);
	QueueType Q;
	initQueue(&Q);

	v->isVisited = TRUE;
	printf("%d\n", v->nodeNum);
	enqueue(&Q, v->nodeNum);

	while (!isEmpty(&Q))
	{
		v = findVertex(G, dequeue(&Q));
		idx = v->nodeNum - 1;

		for (int j = 0; j < n; j++)
		{
			if (AM->adjMatrix[idx][j] != NULL) // 간선 존재 
			{
				v = findVertex(G, j + 1); // j + 1을 가지는 vertex 찾기 
				if (v->isVisited == FALSE) // 방문하지 않았으면 
				{
					v->isVisited = TRUE;
					printf("%d\n", v->nodeNum);
					enqueue(&Q, v->nodeNum);
				}
			}
		}
	}
}

int main(void)
{
	int n, m, s;
	int start, end;
	Graph G;
	AdjMatrix AM;
	initGraph(&G);
	

	scanf("%d %d %d", &n, &m, &s);
	for (int i = 1; i <= n; i++)
		createVertex(&G, i);

	initAdjMatrix(&AM, n);
	for (int i = 0; i < m; i++)
	{
		scanf("%d %d", &start, &end);
		createEdge(&G, &AM, start, end, 0);
	}

	// printGraph(&G, &AM, n);
	
	BFS(&G, &AM, s, n);
	return 0;
}

void initGraph(Graph* G)
{
	G->vHead = NULL;
	G->eHead = NULL;
}
void initAdjMatrix(AdjMatrix* AM, int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			AM->adjMatrix[i][j] = NULL;
	}
}
void createVertex(Graph* G, int nodeNum)
{
	Vertex* newVertex = (Vertex*)malloc(sizeof(Vertex));
	Vertex* ptr = G->vHead;
	newVertex->nodeNum = nodeNum;
	newVertex->isVisited = FALSE;
	newVertex->next = NULL;

	if (ptr == NULL)
		G->vHead = newVertex;
	else
	{
		while (ptr->next != NULL)
			ptr = ptr->next;
		ptr->next = newVertex;
	}
}
void createEdge(Graph* G, AdjMatrix* AM, int v1, int v2, int w)
{
	Edge* newEdge = (Edge*)malloc(sizeof(Edge));
	Edge* ptr = G->eHead;
	Vertex* v;
	newEdge->next = NULL;
	newEdge->v1 = v1;
	newEdge->v2 = v2;
	newEdge->weight = w;

	if (ptr == NULL)
		G->eHead = newEdge;
	else
	{
		while (ptr->next != NULL)
			ptr = ptr->next;
		ptr->next = newEdge;
	}

	insertAdj(AM, newEdge, v1, v2);
}
void insertAdj(AdjMatrix* AM, Edge* e, int v1, int v2)
{
	AM->adjMatrix[v1 - 1][v2 - 1] = e;
	AM->adjMatrix[v2 - 1][v1 - 1] = e;
}
Vertex* findVertex(Graph* G, int nodeNum)
{
	Vertex* ptr = G->vHead;
	int flag = 0;

	while (ptr != NULL)
	{
		if (ptr->nodeNum == nodeNum)
		{
			flag = 1;
			break;
		}
		ptr = ptr->next;
	}

	if (flag == 0)
		return NULL;
	return ptr;
}
