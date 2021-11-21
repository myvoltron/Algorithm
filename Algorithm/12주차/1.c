#include <stdio.h>
#include <stdlib.h>

#define SIZE	100

typedef struct queue
{
	int elem[SIZE];
	int f, r;
} Queue;

typedef struct incidentEdgeNode
{
	int edgeIdx; // 간선 노드의 순서를 저장
	struct incidentEdgeNode* next;
} IncidentEdge;

typedef struct vertex
{
	char vName;
	int indegree; // 진입차수 

	IncidentEdge *outEdges;
	IncidentEdge *inEdges; 
} Vertex;

typedef struct edge
{
	int origin; // 시점 인덱스 
	int destination; // 종점 인덱스 
} Edge;

typedef struct graph
{
	Vertex *vertexArray;
	Edge *edgeArray;
} Graph;

void initQueue(Queue* Q)
{
	Q->f = Q->r = 0;
}
int isEmpty(Queue* Q)
{
	return Q->r == Q->f; 
}
int isFull(Queue* Q)
{
	return (Q->r + 1) % SIZE == Q->f;
}
void enqueue(Queue* Q, int vIdx)
{
	if (isFull(Q))
	{
		printf("Full\n");
		return;
	}

	Q->r = (Q->r + 1) % SIZE;
	Q->elem[Q->r] = vIdx; 
}
int dequeue(Queue* Q)
{
	if (isEmpty(Q))
	{
		printf("Empty\n");
		return -1;
	}

	Q->f = (Q->f + 1) % SIZE;
	return Q->elem[Q->f];
}

void initGraph(Graph* G);
void buildGraph(Graph* G);
// void printGraph(Graph* G);
void insertVertex(Graph* G, char vName, int idx);
void insertDirectedEdge(Graph* G, char origin, char destination, int idx);
int findIdx(Graph* G, char vName);
void addFirst(IncidentEdge* header, int idx);

void topologicalSort(Graph* G, int* topOrder);

int n, m; 

int main(void)
{
	int* topOrder;
	Graph G;
	buildGraph(&G);

	topOrder = (int*)malloc(sizeof(int) * n); // vertex들이 위상정렬되어 그 index가 들어갈 것이다. 0번째에는 DEG판별, 1번 ~ n까지 위장정렬 idx가 들어갈 것이다.
	topologicalSort(&G, topOrder);
	// 위상순서 출력
	if (topOrder[0] == 1)
	{
		for (int i = 1; i < n + 1; i++)
			printf("%c ", G.vertexArray[topOrder[i]].vName);
	}
	else
		printf("0\n");
	return 0;
}

/*
n, m을 전역변수를 안써도 구조체를 이용해서 충분히 구현할 수 있기는 하다. 
하지만 문제 상에서 전역변수 써도 된다고 나와있으니 일단 미뤄둔다. 
*/

//void printGraph(Graph* G)
//{
//	IncidentEdge* ptr;
//	for (int i = 0; i < n; i++)
//	{
//		printf("vertex[%c] : ", G->vertexArray[i].vName);
//		ptr = G->vertexArray[i].outEdges->next;
//		for (; ptr != NULL; ptr = ptr->next)
//			printf("%d ", G->edgeArray[ptr->edgeIdx].destination);
//		printf("\n");
//	}
//	printf("\n");
//}

void initGraph(Graph* G)
{
	G->vertexArray = (Vertex*)malloc(sizeof(Vertex) * 100); // 동적 배열 
	G->edgeArray = (Edge*)malloc(sizeof(Edge) * 1000);
}
void buildGraph(Graph* G)
{
	char v1, v2;
	initGraph(G);

	scanf("%d", &n); // vertex
	getchar();
	for (int i = 0; i < n; i++)
	{
		scanf("%c", &v1);
		getchar();
		insertVertex(G, v1, i); // vertex v1 added
	}

	scanf("%d", &m); // edge
	getchar();
	for (int i = 0; i < m; i++)
	{
		scanf("%c %c", &v1, &v2);
		getchar();
		insertDirectedEdge(G, v1, v2, i); // v1 -> v2 edge added
	}
}
void insertVertex(Graph* G, char vName, int idx)
{
	G->vertexArray[idx].vName = vName;
	G->vertexArray[idx].indegree = 0;

	G->vertexArray[idx].inEdges = (IncidentEdge*)malloc(sizeof(IncidentEdge)); // 더미 노드 
	G->vertexArray[idx].outEdges = (IncidentEdge*)malloc(sizeof(IncidentEdge));
	G->vertexArray[idx].inEdges->next = NULL;
	G->vertexArray[idx].outEdges->next = NULL;
}
void insertDirectedEdge(Graph* G, char origin, char destination, int idx)
{
	int originIdx = findIdx(G, origin);
	int destinationIdx = findIdx(G, destination);

	G->edgeArray[idx].origin = originIdx;
	G->edgeArray[idx].destination = destinationIdx;

	addFirst(G->vertexArray[originIdx].outEdges, idx); // 인접간선
	addFirst(G->vertexArray[destinationIdx].inEdges, idx);
	G->vertexArray[destinationIdx].indegree++; 
}
int findIdx(Graph* G, char vName) 
{
	for (int i = 0; i < n; i++)
	{
		if (G->vertexArray[i].vName == vName)
			return i;
	}

	return -1; // 없다면 -1 반환, 하지만 입력값을 제대로 주어서 -1을 반환하지 않게 해야함. 
}
void addFirst(IncidentEdge* header, int idx)
{
	IncidentEdge* newNode = (IncidentEdge*)malloc(sizeof(IncidentEdge));
	newNode->edgeIdx = idx;
	newNode->next = header->next;
	header->next = newNode; 
}

void topologicalSort(Graph* G, int *topOrder)
{
	Queue Q;
	IncidentEdge* ptr;
	int t, u, w;
	int* in = (int*)malloc(sizeof(int) * n); // 각 idx는 vertex에 대한 Idx를 의미하고, 그에 따른 값은 진입차수를 의미한다. 
	
	initQueue(&Q);

	for (int i = 0; i < n; i++)
	{
		in[i] = G->vertexArray[i].indegree;
		// 진입차수가 0인 vertex가 감지되면 그 vertex의 idx를 enqueue한다. 
		if (in[i] == 0)
			enqueue(&Q, i);
	}

	t = 1; // 위상 순위 Idx 담당 : 0번째 원소는 DEG, Non-DEG를 판별하므로 비워둔다.  
	while (!isEmpty(&Q)) // 큐가 빌 때까지 계속한다. 
	{
		u = dequeue(&Q); // 큐안에는 진입차수가 0인 원소들이 들어가 있을 것이다. dequeue해서 topOrder에 넣는다. 
		topOrder[t++] = u;

		ptr = G->vertexArray[u].outEdges->next; // u가 가리키는 vertex 노드들의 차수를 줄여야한다. 더미노드의 next부터 탐색을 시작하자. 
		for (; ptr != NULL; ptr = ptr->next) // u의 인접노드들을 모두 탐색한다. 
		{
			w = G->edgeArray[ptr->edgeIdx].destination;
			in[w] -= 1; // 차수를 줄임 
			if (in[w] == 0) // 만약에 해당 vertex의 indegree가 0이면 해당 vertex의 idx를 enqueue해야함. 
				enqueue(&Q, w);
		}
	}

	if (t <= n)
		topOrder[0] = 0; // Non-DAG : 방향사이클 존재 -> 사이클이 존재하게 되면 어느순간부터 진입차수가 1이상인 vertex만 남게되어 당연히 topOrder 배열에 들어간 원소의 수도 n + 1보다 작을 것이다. 
	else
		topOrder[0] = 1; // DAG
}