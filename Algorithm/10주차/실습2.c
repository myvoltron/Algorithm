#include <stdio.h>
#include <stdlib.h>

typedef struct Edge
{
	int weight;
	char v1, v2;
	struct Edge* next;
} Edge;

typedef struct IncidentEdge
{
	char adjVertex;
	Edge* e;
	struct IncidentEdge* next; 
} IncidentEdge;

typedef struct Vertex
{
	char vName;
	IncidentEdge* iHead;
	struct Vertex* next;
} Vertex;

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

void insertIncidentEdge(Vertex* v, char av, Edge* e)
{
	IncidentEdge* p = (IncidentEdge*)malloc(sizeof(IncidentEdge));
	p->adjVertex = av;
	p->e = e; 
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

void insertEdge(Graph* G, int w, char v1, char v2)
{
	Edge* e = (Edge*)malloc(sizeof(Edge));
	e->weight = w;
	e->v1 = v1;
	e->v2 = v2;
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

	Vertex* v = findVertex(G, v1);
	insertIncidentEdge(v, v2, e);
	v = findVertex(G, v2);
	insertIncidentEdge(v, v1, e);
}

//void findAdj(Graph* G, char vName)
//{
//	Edge* q = G->eHead;
//	Vertex* p = findVertex(G, vName);
//	for (; q != NULL; q = q->next)
//	{
//		if (q->v1 == p)
//			printf("(%c) ", q->v2->vName);
//		else if (q->v2 == p)
//			printf("(%c) ", q->v1->vName);
//	}
//	printf("\n");
//}
//
//void isAdj(Graph* G, char v1, char v2)
//{
//	Edge* q = G->eHead;
//	Vertex* p1 = findVertex(G, v1);
//	Vertex* p2 = findVertex(G, v2);
//	for (; q != NULL; q = q->next)
//	{
//		if ((p1 == q->v1 && p2 == q->v2) || (p1 == q->v2 && p2 == q->v1))
//		{
//			printf("(%c) (%c) are adj\n", v1, v2);
//			return;
//		}
//	}
//	printf("(%c) (%c) are not adj\n", v1, v2);
//}

void printGraph(Graph* G)
{
	Vertex* p = G->vHead;
	IncidentEdge* q;
	for (; p != NULL; p = p->next)
	{
		printf("[%c] : ", p->vName);
		for (q = p->iHead; q != NULL; q = q->next)
			printf("[%c, %d] ", q->adjVertex, q->e->weight);
		printf("\n");
	}
	printf("\n");
}

void modifyWeight(Graph* G, char v1, char v2, int weight)
{
	Vertex* p = findVertex(G, v1);
	IncidentEdge* q = p->iHead;
	while (q)
	{
		if (q->adjVertex == v2)
		{
			q->e->weight = weight;
			break;
		}
		else
			q = q->next;
	}
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