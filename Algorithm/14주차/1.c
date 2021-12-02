#include <stdio.h>
#include <stdlib.h>

#define TRUE    1
#define FALSE   0
#define INF     9999
#define N       101 

typedef struct vertex
{
	int vNum;
	struct vertex* next; // ���Ḯ��Ʈ 
} Vertex;

typedef struct edge
{
	int v1, v2;
	int weight;
	struct edge* next; // ���Ḯ��Ʈ
} Edge;

typedef struct
{
	Vertex* vHead;      // ���Ḯ��Ʈ�� head
	Edge* eHead; 

	Edge* adjMatrix[101][101]; // �������
	int vCount, eCount; // ���� 
} Graph; 

void initGraph(Graph* G, int n);
void addVertex(Graph* G, int vNum);
void addEdge(Graph* G, int v1, int v2, int weight);

int findMin(Graph* G, int dist[], int isVisit[])
{
	int min = INF + 1, minIdx = 0;

	for (int i = 1; i <= G->vCount; i++)
	{
		if (dist[i] < min && isVisit[i] == FALSE)
		{
			min = dist[i];
			minIdx = i; 
		}
	}

	return minIdx; 
}
void dijkstra(Graph* G, int start, int dist[])
{
	// �ʱ�ȭ
	int isVisit[N];

	for (int i = 1; i <= G->vCount; i++)
	{
		dist[i] = INF;
		isVisit[i] = FALSE;
	}

	// ���� ���� ���� 
	dist[start] = 0;
	isVisit[start] = TRUE;
	for (int j = 1; j <= G->vCount; j++)
	{
		if (G->adjMatrix[start][j]) // ���� ������ �� 
		{
			dist[j] = G->adjMatrix[start][j]->weight; // �ش� ������ ���Ը� �����ص� 
		}
	}

	// ������ ���鿡 ���� �ݺ� 
	for (int i = 0; i < G->vCount - 1; i++) // �̹� ���� ������ �湮�߱� ������ ������ 
	{
		int now = findMin(G, dist, isVisit); // 
		isVisit[now] = TRUE;

		for (int j = 1; j <= G->vCount; j++)
		{
			if (G->adjMatrix[now][j]) // ���� ���� 
			{
				int cost = dist[now] + G->adjMatrix[now][j]->weight;
				if (cost < dist[j])
				{
					dist[j] = cost;
				}
			}
		}
	}
}

int main(void)
{
	Graph G; 
	int n, m, s; 
	int v1, v2, weight; 
	int dist[N];

	scanf("%d %d %d", &n, &m, &s);
	initGraph(&G, n);

	// add vertex 
	for (int i = 1; i <= n; i++)
	{
		addVertex(&G, i);
	}

	// add edge 
	for (int i = 0; i < m; i++)
	{
		scanf("%d %d %d", &v1, &v2, &weight);
		addEdge(&G, v1, v2, weight);
	}

	dijkstra(&G, s, dist);

	// ���
	for (int i = 1; i <= G.vCount; i++)
	{
		if (dist[i] == 0 || dist[i] == INF)
			continue;
		printf("%d %d\n", i, dist[i]);
	}
	return 0;
}

void initGraph(Graph* G, int n)
{
	G->vCount = G->eCount = 0;
	G->vHead = NULL;
	G->eHead = NULL;

	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
			G->adjMatrix[i][j] = NULL;
	}
}
void addVertex(Graph* G, int vNum)
{
	// ��带 ���� 
	Vertex* ptr = G->vHead; 
	Vertex* newVertex = (Vertex*)malloc(sizeof(Vertex));
	newVertex->vNum = vNum;
	newVertex->next = NULL; 

	// ���Ḯ��Ʈ�� �� ��带 �߰� 
	if (ptr == NULL)
	{
		G->vHead = newVertex;
	}
	else
	{
		while (ptr->next != NULL)
			ptr = ptr->next;
		ptr->next = newVertex;
	}

	G->vCount += 1;
}
void addEdge(Graph* G, int v1, int v2, int weight)
{
	// ��� ���� 
	Edge* newEdge = (Edge*)malloc(sizeof(Edge));
	newEdge->v1 = v1;
	newEdge->v2 = v2;
	newEdge->weight = weight;

	// ��� �߰� 
	newEdge->next = G->eHead;
	G->eHead = newEdge; 

	G->adjMatrix[v1][v2] = newEdge;

	G->eCount += 1;
}