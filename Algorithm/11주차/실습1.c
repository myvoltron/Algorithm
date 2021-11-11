#include <stdio.h>
#include <stdlib.h>

#define TRUE	1
#define FALSE	0

typedef struct IncidentEdge
{
	char aName;
	struct IncidentEdge* next;
} IncidentEdge;

typedef struct Vertex
{
	char vName;
	int isVisited;
	IncidentEdge* iHead;
	struct Vertex* next;
} Vertex;

typedef struct
{
	Vertex* vHead;
} Graph;

void initGraph(Graph* G)
{
	G->vHead = NULL;
}

void makeVertex(Graph* G, char vName)
{
	Vertex* v = (Vertex*)malloc(sizeof(Vertex));
	v->vName = vName;
	v->isVisited = FALSE;
	v->iHead = NULL;
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

void insertIncidentEdge(Vertex* v, char aName)
{
	IncidentEdge* p = (IncidentEdge*)malloc(sizeof(IncidentEdge));
	p->aName = aName;
	p->next = NULL;

	IncidentEdge* ptr = v->iHead;
	if (ptr == NULL)
		v->iHead = p;
	else
	{
		while (ptr->next != NULL)
			ptr = ptr->next;
		ptr->next = p;
	}
}

Vertex* findVertex(Graph* G, char vName)
{
	Vertex* ptr = G->vHead;
	while (ptr->vName != vName)
		ptr = ptr->next;
	return ptr;
}

void insertEdge(Graph* G, char v1, char v2)
{
	Vertex* v = findVertex(G, v1);
	insertIncidentEdge(v, v2);
	if (v1 != v2)
	{
		v = findVertex(G, v2);
		insertIncidentEdge(v, v1);
	}
}

void DFS(Graph* G, char startPoint)
{
	Vertex* v = findVertex(G, startPoint);
	IncidentEdge* p; 

	if (v->isVisited == FALSE)
	{
		v->isVisited = TRUE;
		printf("(%c) ", v->vName);
	}

	for (p = v->iHead; p != NULL; p = p->next)
	{
		v = findVertex(G, p->aName);
		if (v->isVisited == FALSE)
			DFS(G, v->vName);
	}
}

void printGraph(Graph* G)
{
	Vertex* p = G->vHead;
	IncidentEdge* q;
	for (; p != NULL; p = p->next)
	{
		printf("[%c] : ", p->vName);
		for (q = p->iHead; q != NULL; q = q->next)
			printf("[%c] ", q->aName);
		printf("\n");
	}
	printf("\n");
}

int main(void)
{
	Graph G;
	initGraph(&G);

	makeVertex(&G, 'a'); makeVertex(&G, 'b'); makeVertex(&G, 'c');
	makeVertex(&G, 'd'); makeVertex(&G, 'e'); makeVertex(&G, 'f');
	insertEdge(&G, 'a', 'b'); insertEdge(&G, 'a', 'c');
	insertEdge(&G, 'a', 'd'); insertEdge(&G, 'a', 'f');
	insertEdge(&G, 'b', 'c'); insertEdge(&G, 'c', 'e');
	insertEdge(&G, 'e', 'e'); insertEdge(&G, 'e', 'f');
	printGraph(&G);
	printf("\n\n");

	DFS(&G, 'a');
	return 0;
}