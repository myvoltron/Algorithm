#include <stdio.h>
#include <stdlib.h>

typedef struct Edge
{
	int weight;
	int v1, v2;
	struct Edge* next;
} Edge;

typedef struct
{
	Edge* adjMatrix[6][6];
} AdjMatrix;

typedef struct Vertex
{
	int nodeNum;
	struct Vertex* next;
} Vertex;

typedef struct
{
	Vertex* vHead;
	Edge* eHead;
} Graph;

void printGraph(Graph* G, AdjMatrix* AM)
{
	Vertex* ptr = G->vHead;
	int idx = 0;
	for (; ptr != NULL; ptr = ptr->next)
	{
		printf("[%d] : ", ptr->nodeNum);
		for (int j = 0; j < 6; j++)
		{
			if (AM->adjMatrix[idx][j] != NULL)
				printf(" %d %d", j + 1, AM->adjMatrix[idx][j]->weight);
		}
		printf("\n");

		idx++;
	}
	printf("\n");
}

void initGraph(Graph* G);
void initAdjMatrix(AdjMatrix* AM);
void createVertex(Graph* G, int nodeNum);
void createEdge(Graph* G, AdjMatrix* AM, int v1, int v2, int w);
void insertAdj(AdjMatrix* AM, Edge* e, int v1, int v2);

Vertex* findVertex(Graph* G, int nodeNum);
void adjacentNode(Graph* G, AdjMatrix *AM, int nodeNum);
void changeWeight(Graph* G, AdjMatrix* AM, int v1, int v2, int w);
void removeEdge(Graph* G, Edge* target);

int main(void)
{
	int loop = 1, w;
	int v1, v2, nodeNum;
	char oper;
	Graph G;
	AdjMatrix AM;
	initGraph(&G);
	initAdjMatrix(&AM);

	for (int i = 1; i <= 6; i++)
		createVertex(&G, i);
	createEdge(&G, &AM, 1, 2, 1); createEdge(&G, &AM, 1, 3, 1);
	createEdge(&G, &AM, 1, 4, 1); createEdge(&G, &AM, 1, 6, 2);
	createEdge(&G, &AM, 2, 3, 1); createEdge(&G, &AM, 3, 5, 4);
	createEdge(&G, &AM, 5, 5, 4); createEdge(&G, &AM, 5, 6, 3);

	// printGraph(&G, &AM);

	while (loop)
	{
		scanf("%c", &oper);
		getchar();

		switch (oper)
		{
		case 'a':
			scanf("%d", &nodeNum);
			getchar();
			adjacentNode(&G, &AM, nodeNum);
			break;
		case 'm':
			scanf("%d %d %d", &v1, &v2, &w);
			getchar();
			changeWeight(&G, &AM, v1, v2, w);
			break;
		case 'q':
			loop = 0;
		}
	}
	return 0;
}

void initGraph(Graph* G)
{
	G->vHead = NULL;
	G->eHead = NULL;
}
void initAdjMatrix(AdjMatrix* AM)
{
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
			AM->adjMatrix[i][j] = NULL;
	}
}
void createVertex(Graph* G, int nodeNum)
{
	Vertex* newVertex = (Vertex*)malloc(sizeof(Vertex));
	Vertex* ptr = G->vHead;
	newVertex->nodeNum = nodeNum;
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

void adjacentNode(Graph* G, AdjMatrix* AM, int nodeNum)
{
	Vertex* ptr = findVertex(G, nodeNum);
	
	if (ptr == NULL)
	{
		printf("-1\n");
		return;
	}
	else
	{
		for (int i = 0; i < 6; i++)
		{
			if(AM->adjMatrix[nodeNum - 1][i] != NULL)
				printf(" %d %d", i + 1, AM->adjMatrix[nodeNum - 1][i]->weight);
		}
		printf("\n");
	}
}
void changeWeight(Graph* G, AdjMatrix* AM, int v1, int v2, int w)
{
	Vertex* v1Pointer = findVertex(G, v1);
	Vertex* v2Pointer = findVertex(G, v2);
	Edge* ptr;
	
	if (!v1Pointer || !v2Pointer)
	{
		printf("-1\n");
		return;
	}

	if (w != 0)
	{
		ptr = AM->adjMatrix[v1 - 1][v2 - 1];
		if (ptr == NULL) // 간선이 존재하지 않으면 생성 
			createEdge(G, AM, v1, v2, w);
		else             // 가중치값을 바꿈. 
			ptr->weight = w;
	}
	else // remove Edge
	{
		removeEdge(G, AM->adjMatrix[v1 - 1][v2 - 1]);
		AM->adjMatrix[v1 - 1][v2 - 1] = NULL;
		AM->adjMatrix[v2 - 1][v1 - 1] = NULL;
	}
}
void removeEdge(Graph* G, Edge* target)
{
	Edge* ptr = G->eHead;
	Edge* temp;

	if (ptr == target)
	{
		G->eHead = G->eHead->next;
		free(ptr);
		return;
	}
	while (ptr->next != NULL)
	{
		if (ptr->next == target)
			break;
		ptr = ptr->next;
	}

	temp = ptr->next;
	ptr->next = ptr->next->next;
	free(temp);
}