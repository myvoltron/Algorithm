#include <stdio.h>
#include <stdlib.h>

typedef struct Vertex
{
	char vName;
	struct Vertex* next;
} Vertex;

typedef struct Edge
{
	int weight;
	Vertex* v1, * v2;
	struct Edge* next;
} Edge;

typedef struct
{
	Vertex* vHead;
	Edge* eHead;
} Graph;

void initGraph(Graph* G)
{
	G->vHead = NULL;
	G->eHead = NULL;
}

void makeVertex(Graph* G, char vName)
{
	Vertex* v = (Vertex*)malloc(sizeof(Vertex));
	v->vName = vName;
	v->next = NULL;

	Vertex* ptr = G->vHead;
	if (ptr == NULL)
		G->vHead = v;
	else
	{
		while (ptr->next != NULL)
			ptr = ptr->next;
		ptr->next = v;
	}
}

Vertex* findVertex(Graph* G, char vName)
{
	Vertex* ptr = G->vHead;
	while (ptr->vName != vName)
		ptr = ptr->next;
	return ptr;
}

void insertEdge(Graph* G, int w, char v1, char v2)
{
	Edge* e = (Edge*)malloc(sizeof(Edge));
	e->weight = w;
	e->v1 = findVertex(G, v1);
	e->v2 = findVertex(G, v2);
	e->next = NULL;

	Edge* ptr = G->eHead;
	if (ptr == NULL)
		G->eHead = e;
	else
	{
		while (ptr->next != NULL)
			ptr = ptr->next;
		ptr->next = e;
	}
}

void printGraph(Graph* G)
{
	Edge* ptr = G->eHead;
	for (; ptr != NULL; ptr = ptr->next)
		printf("(%c)---%d---(%c)\n", ptr->v1->vName, ptr->weight, ptr->v2->vName);
	printf("\n");
}

int main(void)
{
	Graph G;
	initGraph(&G);

	makeVertex(&G, 'u'); makeVertex(&G, 'v'); makeVertex(&G, 'w');
	insertEdge(&G, 2, 'u', 'v'); insertEdge(&G, 3, 'v', 'w');
	printGraph(&G);
	return 0;
}