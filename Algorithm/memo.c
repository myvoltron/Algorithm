#include <stdio.h>
#include <stdlib.h>

typedef struct Edge
{
	int weight;
	int v1, v2;
	struct Edge* next;
	int lable; // 0 == Fresh, 1 == Visited, 2 == Tree, -1 == Back  
} Edge;

typedef struct IncidentEdge
{
	int adjN;
	Edge* e;
	struct IncidentEdge* next;
} IncidentEdge;

typedef struct Vertex
{
	int nodeNum;
	struct Vertex* next;
	IncidentEdge* iHead;
	int lable; // 0 == Fresh, 1 == Visited, 2 == Cross
} Vertex;

typedef struct
{
	Vertex* vHead;
	Edge* eHead;
} Graph;

void printGraph(Graph* G)
{
	Vertex* ptr = G->vHead;
	for (; ptr != NULL; ptr = ptr->next)
	{
		printf("[%d] : ", ptr->nodeNum);
		IncidentEdge* pI = ptr->iHead;
		for (; pI != NULL; pI = pI->next)
			printf(" %d", pI->adjN);
		printf("\n");
	}
	printf("\n");
}

void initGraph(Graph* G);
void createVertex(Graph* G, int nodeNum);
void createEdge(Graph* G, int v1, int v2, int w);
void insertIncident(Vertex* v, Edge*, int nodeNum);
Vertex* findVertex(Graph* G, int nodeNum);

void adjacentNode(Graph* G, int nodeNum);
void changeWeight(Graph* G, int v1, int v2, int w);
void removeEdge(Graph* G, Edge* target);
void removeIncident(Vertex* v, IncidentEdge* target);

void DFS(Graph* G);
void rDFS(Graph* G, Vertex* v);

int main(void)
{
	int loop = 1, w;
	int v1, v2, nodeNum;
	char oper;
	Graph G;
	initGraph(&G);

	for (int i = 1; i <= 6; i++)
		createVertex(&G, i);
	createEdge(&G, 1, 2, 1); createEdge(&G, 1, 3, 1);
	createEdge(&G, 1, 4, 1); createEdge(&G, 1, 6, 2);
	createEdge(&G, 2, 3, 1); createEdge(&G, 3, 5, 4);
	createEdge(&G, 5, 5, 4); createEdge(&G, 5, 6, 3);

	printGraph(&G);

	while (loop)
	{
		scanf("%c", &oper);
		getchar();

		switch (oper)
		{
		case 'a':
			scanf("%d", &nodeNum);
			getchar();
			adjacentNode(&G, nodeNum);
			break;
		case 'm':
			scanf("%d %d %d", &v1, &v2, &w);
			getchar();
			changeWeight(&G, v1, v2, w);
			break;
		case 'd':
			DFS(&G);
			printf("\n\n");
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
void createVertex(Graph* G, int nodeNum)
{
	Vertex* newVertex = (Vertex*)malloc(sizeof(Vertex));
	Vertex* ptr = G->vHead;
	newVertex->nodeNum = nodeNum;
	newVertex->iHead = NULL;
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
void createEdge(Graph* G, int v1, int v2, int w)
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

	v = findVertex(G, v1);
	insertIncident(v, newEdge, v2);
	if (v1 != v2) // 자기 자신을 가리키는 루프가 아니라면 다음 명령들을 실행. 
	{
		v = findVertex(G, v2);
		insertIncident(v, newEdge, v1);
	}
}
void insertIncident(Vertex* v, Edge* e, int nodeNum)
{
	IncidentEdge* ptr;
	IncidentEdge* newIncident = (IncidentEdge*)malloc(sizeof(IncidentEdge));
	newIncident->e = e;
	newIncident->next = NULL;
	newIncident->adjN = nodeNum;

	ptr = v->iHead;
	if (ptr == NULL)
		v->iHead = newIncident;
	else
	{
		// 오름차순 삽입
		if (ptr->adjN > newIncident->adjN)
		{
			newIncident->next = v->iHead;
			v->iHead = newIncident;
			return;
		}
		while (ptr->next != NULL)
		{
			if (ptr->next->adjN > newIncident->adjN)
				break;

			ptr = ptr->next;
		}
		newIncident->next = ptr->next;
		ptr->next = newIncident;
	}
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

void adjacentNode(Graph* G, int nodeNum)
{
	Vertex* ptr = findVertex(G, nodeNum);
	IncidentEdge* incidentPointer;

	if (ptr == NULL)
	{
		printf("-1\n");
		return;
	}
	else
	{
		// 정점의 인접 정점이 없으면 \n만 출력되는 것을 볼 수 있다. 
		incidentPointer = ptr->iHead;
		for (; incidentPointer != NULL; incidentPointer = incidentPointer->next)
			printf(" %d %d", incidentPointer->adjN, incidentPointer->e->weight);
		printf("\n");
	}
}
void changeWeight(Graph* G, int v1, int v2, int w)
{
	int flag = 0;
	Vertex* v1Pointer = findVertex(G, v1);
	Vertex* v2Pointer = findVertex(G, v2);
	IncidentEdge* ptr1;
	IncidentEdge* ptr2;

	if (!v1Pointer || !v2Pointer)
	{
		printf("-1\n");
		return;
	}

	ptr1 = v1Pointer->iHead;
	ptr2 = v2Pointer->iHead;

	for (; ptr1 != NULL; ptr1 = ptr1->next)
	{
		ptr2 = v2Pointer->iHead;
		for (; ptr2 != NULL; ptr2 = ptr2->next)
		{
			if (ptr1->adjN == v2Pointer->nodeNum && ptr2->adjN == v1Pointer->nodeNum)
			{
				if (w != 0)
				{
					ptr1->e->weight = w;
				}
				else
				{
					// 삭제 
					// m 5 5 0 case는 어떻게 해결? 
					removeEdge(G, ptr1->e);
					if (ptr1->adjN != ptr2->adjN) // loop가 아닌 경우와 loop인 경우로 나눴다.
					{
						removeIncident(v1Pointer, ptr1);
						removeIncident(v2Pointer, ptr2);
					}
					else
						removeIncident(v1Pointer, ptr1);
				}

				flag = 1;
				break;
			}
		}

		if (flag == 1)
			break;
	}

	if (flag == 0 && w != 0)
	{
		createEdge(G, v1, v2, w);
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
void removeIncident(Vertex* v, IncidentEdge* target)
{
	IncidentEdge* ptr = v->iHead;
	IncidentEdge* temp;

	if (ptr == target)
	{
		v->iHead = v->iHead->next;
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


void DFS(Graph* G)
{
	Vertex* pg;
	Edge* pe;

	// init each lable of vertex and edge to Fresh 
	pg = G->vHead, pe = G->eHead;
	for (; pg != NULL; pg = pg->next)
		pg->lable = 0; 
	for (; pe != NULL; pe = pe->next)
		pe->lable = 0;

	// DFS 
	for (pg = G->vHead; pg != NULL; pg = pg->next)
	{
		if (pg->lable == 0) // lable of pg is Fresh case 
			rDFS(G, pg);
	}
}
void rDFS(Graph* G, Vertex* v)
{
	IncidentEdge* pie;
	Vertex* w;

	v->lable = 1; // Visited
	printf("vertex[%d] visited!\n", v->nodeNum);
	pie = v->iHead;
	for (; pie != NULL; pie = pie->next)
	{
		if (pie->e->lable == 0) // edge is Fresh
		{
			w = findVertex(G, pie->adjN);
			if (w->lable == 0) // vertex is Fresh 
			{
				pie->e->lable = 2;
				printf("edge[%d -> %d] tree!\n", v->nodeNum, pie->adjN);
				rDFS(G, w);
			}
			else
			{
				pie->e->lable = -1;
				printf("edge[%d -> %d] back!\n", v->nodeNum, pie->adjN);
			}
		}
	}
}