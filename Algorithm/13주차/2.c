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

int vFind(int v[], int vNum)
{
    if (v[vNum] == vNum)
        return vNum;

    // ����� �θ� ��带 ã�� �ö󰣴�. 
    while (v[vNum] != vNum)
        vNum = v[vNum];
    return vNum;
}
void vUnion(int v[], int vNum1, int vNum2)
{
    // �� ���Ұ� ���� Ʈ���� ��Ʈ ��带 ã�´�. 
    int r1 = vFind(v, vNum1);
    int r2 = vFind(v, vNum2);

    if (r1 != r2) // ����
        v[r2] = r1;
}
void edgeSort(Graph* G, Edge* edgeList[])
{
    int i, least;
    Edge* p = G->eHead;
    for (i = 0; i < G->eCount; i++) // �켱 ���� ������ ����ִ´�. 
    {
        edgeList[i] = p;
        p = p->next;
    }

    // ���� 
    for (i = 0; i < G->eCount - 1; i++)
    {
        least = i;
        for (int j = i + 1; j < G->eCount; j++)
        {
            if (edgeList[j]->weight < edgeList[least]->weight)
                least = j;
        }

        p = edgeList[least];
        edgeList[least] = edgeList[i];
        edgeList[i] = p;
    }
}
void kruskalMST(Graph* G, Edge* edgeList[], int v[], int *sum)
{
    int eCnt = 0, i = 0;
    int vNum1, vNum2;
    Edge* p;

    while (eCnt < G->vCount - 1)
    {
        p = edgeList[i];
        vNum1 = vFind(v, p->v1); // �� ������ ���� ������ find����.
        vNum2 = vFind(v, p->v2);

        if (vNum1 != vNum2) // ���� ������ �ٸ��� union�Ѵ�. 
        {
            printf(" %d", p->weight);
            *sum += p->weight; // weight �հ� ���
            eCnt += 1;
            vUnion(v, vNum1, vNum2);
        }
        i++;
    }
    printf("\n");
}

/*
�켱���� ť�� ������� �ʰ� Edge�� �迭�� �и������� �̿��ؼ� ������ Ǯ����. 
https://gmlwjd9405.github.io/2018/08/31/algorithm-union-find.html �и����� ���� 

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
    int root[101]; // �и������� �̿��ؼ� �������� ����ȰŸ� Ȯ���Ѵ�. 
    Edge* edgeList[1000];

    Graph G;
    initGraph(&G);

    scanf("%d %d", &n, &m);

    // vertex ����
    for (int i = 1; i <= n; i++)
    {
        addVertex(&G, i);
        root[i] = i;
    }

    // edge ����
    for (int i = 0; i < m; i++)
    {
        scanf("%d %d %d", &v1, &v2, &weight);
        addEdge(&G, v1, v2, weight);
    }

    // printGraph(&G);

    edgeSort(&G, edgeList);
    sum = 0;
    kruskalMST(&G, edgeList, root, &sum); 
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

