#include <stdio.h>
#include <stdlib.h>

#define TRUE    1
#define FALSE   0
#define INF     99999

typedef struct Edge
{
    int v1, v2;
    int weight;
    struct Edge* next; // edge ���Ḯ��Ʈ
} Edge;

typedef struct IncidentEdge
{
    int adjVertexNum; // ����Ű�� �ִ� vertex�� vNum ���� �ǹ�. 
    Edge* e;
    struct IncidentEdge* next; // incidentEdge ���Ḯ��Ʈ (����) 
} IncidentEdge;

typedef struct Vertex
{
    int vNum;
    int isVisit; // �湮�ߴ°�? 
    IncidentEdge* iHead; // ������� �ܼ� ���� ���Ḯ��Ʈ 
    struct Vertex* next; // vertex ���Ḯ��Ʈ 
} Vertex;

typedef struct
{
    Vertex* vHead;
    Edge* eHead;
    int eCount, vCount; // ���� �ǹ� 
} Graph;

void initGraph(Graph* G);
void addVertex(Graph* G, int vNum);
void addEdge(Graph* G, int v1, int v2, int w);
void addIncidentEdge(Vertex* v, int adjVNum, Edge* e);
Vertex* findVertex(Graph* G, int vNum);
void printGraph(Graph* G);

int getMinVertex(Graph* G, int d[])
{
    Vertex* p = G->vHead;
    int vNumber = 0;

    for (; p != NULL; p = p->next)
    {
        if (p->isVisit == FALSE)
        {
            vNumber = p->vNum;
            break;
        }
    }

    for (p = G->vHead; p != NULL; p = p->next)
    {
        if (p->isVisit == FALSE && d[p->vNum] < d[vNumber])
            vNumber = p->vNum;
    }

    return vNumber;
}
void primMST(Graph* G, int startV, int d[], int* sum)
{
    Vertex* p;
    IncidentEdge* q; 
    int vMinimum;

    d[startV] = 0; // ������ ������ ���� ���⼭�� ������ 1���� �����Ѵ�. 

    for (int i = 1; i <= G->vCount; i++)
    {
        vMinimum = getMinVertex(G, d); // �ּ� ����ġ�� ������ ������ �����´�. 
        p = findVertex(G, vMinimum); 
        p->isVisit = TRUE; // T�� ���� 
        *sum += d[vMinimum];
        printf(" %d", p->vNum);
        
        /*for (int j = 1; j <= G->vCount; j++)
            printf(" %d", d[j]);
        printf("\n");
        printf(" %d\n", d[vMinimum]);*/

        // p�� ������ �������� ��ȸ�ϸ鼭 dist�� �����Ѵ�. 
        for (q = p->iHead->next; q != NULL; q = q->next)
        {
            p = findVertex(G, q->adjVertexNum); // ���� ���� vertex�� �����´�. 
            if (p->isVisit == FALSE) // 
            {
                if(d[q->adjVertexNum] > q->e->weight) 
                    d[q->adjVertexNum] = q->e->weight;
            }
        }
    }
    printf("\n");
}

/*
�켱���� ť�� ������� �ʴ� prim �˰����̴�.
https://lsoovmee-rhino.tistory.com/93?category=847612 ����

�Է����̽��� ������ ����. 
5 7
1 2 1
1 4 2
1 5 4
2 5 7
4 5 3
3 5 5
2 3 6

6 9
1 2 3
1 3 20
2 4 25
2 5 17
3 4 34
3 5 1
3 6 12
4 5 5
5 6 37

5 7
1 2 75
1 4 95
1 3 51
2 4 9
4 3 19
4 5 42
3 5 31
*/
int main()
{
    int n, m;
    int v1, v2, weight;
    int sum;
    int dist[101]; // distance, idx = vertex, value = �ش� vertex������ �Ÿ��ǹ� 

    Graph G;
    initGraph(&G);
    
    scanf("%d %d", &n, &m);
    
    // vertex ����
    for (int i = 1; i <= n; i++)
        addVertex(&G, i);

    // edge ����
    for (int i = 0; i < m; i++)
    {
        scanf("%d %d %d", &v1, &v2, &weight);
        addEdge(&G, v1, v2, weight);
    }

    // printGraph(&G);

    sum = 0;
    for (int i = 1; i <= G.vCount; i++)
        dist[i] = INF;
    primMST(&G, 1, dist, &sum);
    printf("%d", sum);
    return 0;
}

void initGraph(Graph* G)
{
    G->vHead = NULL;
    G->eHead = NULL;
    G->vCount = G->eCount = 0;
}
void addVertex(Graph* G, int vNum)
{
    // ���ο� vertex �ʱ�ȭ �۾� 
    Vertex* newVertex = (Vertex*)malloc(sizeof(Vertex));
    newVertex->vNum = vNum;
    newVertex->iHead = (IncidentEdge*)malloc(sizeof(IncidentEdge)); // ���̳�� ���Ḯ��Ʈ�� �ǵ��� �Ѵ�. 
    newVertex->iHead->next = NULL;
    newVertex->next = NULL;
    newVertex->isVisit = FALSE; // �湮���� ���� ���� 
    G->vCount++;

    // Vertex ���Ḯ��Ʈ�� �߰� 
    Vertex* q = G->vHead;
    if (q == NULL)
        G->vHead = newVertex;
    else
    {
        while (q->next != NULL)
            q = q->next;
        q->next = newVertex;
    }
}
void addEdge(Graph* G, int v1, int v2, int w)
{
    // ���ο� ���� ��带 �����. 
    Edge* newEdge = (Edge*)malloc(sizeof(Edge));
    newEdge->weight = w;
    newEdge->v1 = v1;
    newEdge->v2 = v2;
    newEdge->next = NULL;
    G->eCount++;

    // ���� ���Ḯ��Ʈ�� �߰��Ѵ�. 
    Edge* q = G->eHead;
    if (q == NULL)
        G->eHead = newEdge;
    else
    {
        while (q->next != NULL)
            q = q->next;
        q->next = newEdge;
    }

    // ���� ���� ��带 �߰��Ѵ�. 
    Vertex* v = findVertex(G, v1);
    addIncidentEdge(v, v2, newEdge);
    if (v1 != v2) // v1�� v2�� ������ �� �߰��� �ʿ䰡 ����. 
    {
        v = findVertex(G, v2);
        addIncidentEdge(v, v1, newEdge);
    }
}
void addIncidentEdge(Vertex* v, int adjVNum, Edge* e)
{
    // ���� ���� ��� �ʱ�ȭ �۾� 
    IncidentEdge* newIncidentEdge = (IncidentEdge*)malloc(sizeof(IncidentEdge));
    newIncidentEdge->adjVertexNum = adjVNum;
    newIncidentEdge->e = e;
    newIncidentEdge->next = NULL;

    // ���� ���� ���Ḯ��Ʈ�� �߰� 
    IncidentEdge* q = v->iHead; // ���� ���

    while (q->next != NULL)
        q = q->next;
    q->next = newIncidentEdge;
}
Vertex* findVertex(Graph* G, int vNum)
{
    Vertex* vPointer = G->vHead;

    while (1)
    {
        if (vPointer->vNum == vNum)
            return vPointer; // ã������ �ش� vertex�� ��ȯ�Ѵ�. 

        vPointer = vPointer->next;
    }

    return NULL; // ã�� vertex�� ���ٸ� NULL�� ��ȯ 
}
void printGraph(Graph* G)
{
    Vertex* p = G->vHead;
    IncidentEdge* q;
    for (; p != NULL; p = p->next)
    {
        printf("[%d] : ", p->vNum);
        for (q = p->iHead->next; q != NULL; q = q->next)
            printf("[adj : %d] [weight : %d], ", q->adjVertexNum, q->e->weight);
        printf("\n");
    }
    printf("\n");
}

