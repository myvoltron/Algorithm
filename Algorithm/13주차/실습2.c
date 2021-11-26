#include <stdio.h>
#include <stdlib.h>

#define TRUE    1
#define FALSE   0

typedef struct Edge
{
    char v1, v2;
    int weight;
    struct Edge* next;
}Edge;

typedef struct IncidentEdge
{
    char aName;
    Edge* e;
    struct IncidentEdge* next;
}IncidentEdge;

typedef struct Vertex
{
    char vName;
    int isVisit;
    IncidentEdge* iHead;
    struct Vertex* next;
}Vertex;

typedef struct
{
    Vertex* vHead;
    Edge* eHead;
    int eCount, vCount;
}Graph;

void init(Graph* G)
{
    G->vHead = NULL;
    G->eHead = NULL;
    G->vCount = G->eCount = 0;
}

void makeVertex(Graph* G, char vName)
{
    Vertex* v = (Vertex*)malloc(sizeof(Vertex));
    v->vName = vName;
    v->iHead = NULL;
    v->next = NULL;
    v->isVisit = FALSE; 
    G->vCount++;

    Vertex* q = G->vHead;
    if (q == NULL)
        G->vHead = v;
    else
    {
        while (q->next != NULL)
            q = q->next;
        q->next = v;
    }
}

void makeIncidentEdge(Vertex* v, char aName, Edge* e)
{
    IncidentEdge* p = (IncidentEdge*)malloc(sizeof(IncidentEdge));
    p->aName = aName;
    p->e = e;
    p->next = NULL;
    IncidentEdge* q = v->iHead;
    if (q == NULL)
        v->iHead = p;
    else
    {
        while (q->next != NULL)
            q = q->next;
        q->next = p;
    }
}

Vertex* findVertex(Graph* G, char vName)
{
    Vertex* v = G->vHead;
    while (v->vName != vName)
        v = v->next;
    return v;
}

void insertEdge(Graph* G, char v1, char v2, int w)
{
    Edge* e = (Edge*)malloc(sizeof(Edge));
    e->weight = w;
    e->v1 = v1;
    e->v2 = v2;
    e->next = NULL;
    G->eCount++;

    Edge* q = G->eHead;
    if (q == NULL)
        G->eHead = e;
    else
    {
        while (q->next != NULL)
            q = q->next;
        q->next = e;
    }
    Vertex* v = findVertex(G, v1);
    makeIncidentEdge(v, v2, e);
    v = findVertex(G, v2);
    makeIncidentEdge(v, v1, e);
}

void print(Graph* G)
{
    Vertex* p = G->vHead;
    IncidentEdge* q;
    for (; p != NULL; p = p->next)
    {
        printf("[%c] : ", p->vName);
        for (q = p->iHead; q != NULL; q = q->next)
            printf("[%c, %d] ", q->aName, q->e->weight);
        printf("\n");
    }
    printf("\n");
}

void incSort(Graph* G, Edge* e[])
{
    int i, least;
    Edge* p = G->eHead;
    for (i = 0; i < G->eCount; i++)
    {
        e[i] = p;
        p = p->next;
    }

    for (i = 0; i < G->eCount; i++)
    {
        least = i;
        for (int j = i + 1; j < G->eCount; j++)
        {
            if (e[j]->weight < e[least]->weight)
                least = j;
        }

        p = e[least];
        e[least] = e[i];
        e[i] = p;
    }

    for (i = 0; i < G->eCount; i++)
        printf("[%c%c(%d)] ", e[i]->v1, e[i]->v2, e[i]->weight);
    printf("\n\n");
}

void vUnion(int v[], int vNum1, int vNum2)
{
    int r1 = vFind(v, vNum1);
    int r2 = vFind(v, vNum2);

    if (r1 != r2)
        v[r2] = r1;
}

int vFind(int v[], int vNum)
{
    if (v[vNum] == -1)
        return vNum;

    while (v[vNum] != -1)
        vNum = v[vNum];
    return vNum;
}

void kruskal(Graph* G, Edge* e[], int v[])
{
    int eCnt = 0, i = 0;
    int vNum1, vNum2;
    Edge* p;

    while (eCnt < G->vCount - 1)
    {
        p = e[i];
        vNum1 = vFind(v, p->v1 - 97);
        vNum2 = vFind(v, p->v2 - 97);

        if (vNum1 != vNum2)
        {
            printf("%d.[%c%c (%d)]\n", eCnt + 1, p->v1, p->v2, p->weight);
            eCnt += 1;
            vUnion(v, vNum1, vNum2);
        }
        i++;
    }
}

char getMinVertex(Graph* G, int d[])
{
    Vertex* p = G->vHead;
    char vName;

    for (; p != NULL; p = p->next)
    {
        if (p->isVisit = FALSE)
        {
            vName = p->vName;
            break;
        }
    }

    for (p = G->vHead; p != NULL; p = p->next)
    {
        if (p->isVisit = FALSE && (d[p->vName - 97] < d[vName - 97]))
            vName = p->vName;
    }

    return vName; 
}

void prim(Graph* G, char vName, int d[])
{
    //
    Vertex* p = findVertex(G, vName);
    IncidentEdge* q;
    char c;
    
    d[p->vName - 97] = 0; // 시작 
    
    for (int i = 0; i < G->vCount; i++)
    {
        c = getMinVertex(G, d); // T에 속하는 노드와 T에 속하지 않는 노드들 중에 간선 가중치 값이 최소인 것을 찾는다. 
        p = findVertex(G, c);
        p->isVisit = TRUE;
        printf("(%c) ", p->vName); // 출력

        // p의 인접한 정점들을 순회하면서 dist를 갱신한다. 
        for (q = p->iHead; q != NULL; q = q->next)
        {
            p = findVertex(G, q->aName);
            if (p->isVisit == FALSE)
                d[q->aName - 97] = q->e->weight;
        }
    }
}

int main()
{
    Graph G;
    init(&G);


    makeVertex(&G, 'a'); makeVertex(&G, 'b'); makeVertex(&G, 'c');
    makeVertex(&G, 'd'); makeVertex(&G, 'e'); makeVertex(&G, 'f');
    makeVertex(&G, 'g');

    insertEdge(&G, 'a', 'b', 29); insertEdge(&G, 'a', 'f', 10);
    insertEdge(&G, 'b', 'c', 16); insertEdge(&G, 'b', 'g', 15);
    insertEdge(&G, 'c', 'd', 12); insertEdge(&G, 'd', 'g', 18);
    insertEdge(&G, 'd', 'e', 22); insertEdge(&G, 'e', 'f', 27);
    insertEdge(&G, 'e', 'g', 25);

    print(&G);


    Edge* e[20];
    incSort(&G, e);

    // int v[10] = { -1, -1, -1, -1, -1, -1, -1, -1 };
    // kruskal(&G, e, v);

    int 
}