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
	int edgeIdx; // ���� ����� ������ ����
	struct incidentEdgeNode* next;
} IncidentEdge;

typedef struct vertex
{
	char vName;
	int indegree; // �������� 

	IncidentEdge *outEdges;
	IncidentEdge *inEdges; 
} Vertex;

typedef struct edge
{
	int origin; // ���� �ε��� 
	int destination; // ���� �ε��� 
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

	topOrder = (int*)malloc(sizeof(int) * n); // vertex���� �������ĵǾ� �� index�� �� ���̴�. 0��°���� DEG�Ǻ�, 1�� ~ n���� �������� idx�� �� ���̴�.
	topologicalSort(&G, topOrder);
	// ������� ���
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
n, m�� ���������� �Ƚᵵ ����ü�� �̿��ؼ� ����� ������ �� �ֱ�� �ϴ�. 
������ ���� �󿡼� �������� �ᵵ �ȴٰ� ���������� �ϴ� �̷�д�. 
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
	G->vertexArray = (Vertex*)malloc(sizeof(Vertex) * 100); // ���� �迭 
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

	G->vertexArray[idx].inEdges = (IncidentEdge*)malloc(sizeof(IncidentEdge)); // ���� ��� 
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

	addFirst(G->vertexArray[originIdx].outEdges, idx); // ��������
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

	return -1; // ���ٸ� -1 ��ȯ, ������ �Է°��� ����� �־ -1�� ��ȯ���� �ʰ� �ؾ���. 
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
	int* in = (int*)malloc(sizeof(int) * n); // �� idx�� vertex�� ���� Idx�� �ǹ��ϰ�, �׿� ���� ���� ���������� �ǹ��Ѵ�. 
	
	initQueue(&Q);

	for (int i = 0; i < n; i++)
	{
		in[i] = G->vertexArray[i].indegree;
		// ���������� 0�� vertex�� �����Ǹ� �� vertex�� idx�� enqueue�Ѵ�. 
		if (in[i] == 0)
			enqueue(&Q, i);
	}

	t = 1; // ���� ���� Idx ��� : 0��° ���Ҵ� DEG, Non-DEG�� �Ǻ��ϹǷ� ����д�.  
	while (!isEmpty(&Q)) // ť�� �� ������ ����Ѵ�. 
	{
		u = dequeue(&Q); // ť�ȿ��� ���������� 0�� ���ҵ��� �� ���� ���̴�. dequeue�ؼ� topOrder�� �ִ´�. 
		topOrder[t++] = u;

		ptr = G->vertexArray[u].outEdges->next; // u�� ����Ű�� vertex ������ ������ �ٿ����Ѵ�. ���̳���� next���� Ž���� ��������. 
		for (; ptr != NULL; ptr = ptr->next) // u�� ���������� ��� Ž���Ѵ�. 
		{
			w = G->edgeArray[ptr->edgeIdx].destination;
			in[w] -= 1; // ������ ���� 
			if (in[w] == 0) // ���࿡ �ش� vertex�� indegree�� 0�̸� �ش� vertex�� idx�� enqueue�ؾ���. 
				enqueue(&Q, w);
		}
	}

	if (t <= n)
		topOrder[0] = 0; // Non-DAG : �������Ŭ ���� -> ����Ŭ�� �����ϰ� �Ǹ� ����������� ���������� 1�̻��� vertex�� ���ԵǾ� �翬�� topOrder �迭�� �� ������ ���� n + 1���� ���� ���̴�. 
	else
		topOrder[0] = 1; // DAG
}