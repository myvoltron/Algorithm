#include <stdio.h>
#include <stdlib.h>

#define TRUE    1
#define FALSE   0
#define INF     99999

typedef struct Edge
{
    int v1, v2;
    int weight;
    struct Edge* next; // edge 연결리스트
} Edge;

typedef struct IncidentEdge
{
    int adjVertexNum; // 가리키고 있는 vertex의 vNum 값을 의미. 
    Edge* e;
    struct IncidentEdge* next; // incidentEdge 연결리스트 (더미) 
} IncidentEdge;

typedef struct Vertex
{
    int vNum;
    int isVisit; // 방문했는가? 
    IncidentEdge* iHead; // 인접노드 단순 더미 연결리스트 
    struct Vertex* next; // vertex 연결리스트 
} Vertex;

typedef struct
{
    Vertex* vHead;
    Edge* eHead;
    int eCount, vCount; // 개수 의미 
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

    // 노드의 부모 노드를 찾아 올라간다. 
    while (v[vNum] != vNum)
        vNum = v[vNum];
    return vNum;
}
void vUnion(int v[], int vNum1, int vNum2)
{
    // 각 원소가 속한 트리의 루트 노드를 찾는다. 
    int r1 = vFind(v, vNum1);
    int r2 = vFind(v, vNum2);

    if (r1 != r2) // 통합
        v[r2] = r1;
}
void edgeSort(Graph* G, Edge* edgeList[])
{
    int i, least;
    Edge* p = G->eHead;
    for (i = 0; i < G->eCount; i++) // 우선 간선 노드들을 집어넣는다. 
    {
        edgeList[i] = p;
        p = p->next;
    }

    // 정렬 
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
        vNum1 = vFind(v, p->v1); // 각 정점이 속한 집합을 find하자.
        vNum2 = vFind(v, p->v2);

        if (vNum1 != vNum2) // 속한 집합이 다르면 union한다. 
        {
            printf(" %d", p->weight);
            *sum += p->weight; // weight 합계 계산
            eCnt += 1;
            vUnion(v, vNum1, vNum2);
        }
        i++;
    }
    printf("\n");
}

/*
우선순위 큐를 사용하지 않고 Edge의 배열과 분리집합을 이용해서 문제를 풀었다. 
https://gmlwjd9405.github.io/2018/08/31/algorithm-union-find.html 분리집합 참고 

입력케이스는 다음과 같다.
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
    int root[101]; // 분리집합을 이용해서 정점들이 연결된거를 확인한다. 
    Edge* edgeList[1000];

    Graph G;
    initGraph(&G);

    scanf("%d %d", &n, &m);

    // vertex 생성
    for (int i = 1; i <= n; i++)
    {
        addVertex(&G, i);
        root[i] = i;
    }

    // edge 생성
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
    // 새로운 vertex 초기화 작업 
    Vertex* newVertex = (Vertex*)malloc(sizeof(Vertex));
    newVertex->vNum = vNum;
    newVertex->iHead = (IncidentEdge*)malloc(sizeof(IncidentEdge)); // 더미노드 연결리스트가 되도록 한다. 
    newVertex->iHead->next = NULL;
    newVertex->next = NULL;
    newVertex->isVisit = FALSE; // 방문하지 않은 상태 
    G->vCount++;

    // Vertex 연결리스트에 추가 
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
    // 새로운 간선 노드를 만든다. 
    Edge* newEdge = (Edge*)malloc(sizeof(Edge));
    newEdge->weight = w;
    newEdge->v1 = v1;
    newEdge->v2 = v2;
    newEdge->next = NULL;
    G->eCount++;

    // 간선 연결리스트에 추가한다. 
    Edge* q = G->eHead;
    if (q == NULL)
        G->eHead = newEdge;
    else
    {
        while (q->next != NULL)
            q = q->next;
        q->next = newEdge;
    }

    // 인접 간선 노드를 추가한다. 
    Vertex* v = findVertex(G, v1);
    addIncidentEdge(v, v2, newEdge);
    if (v1 != v2) // v1과 v2가 같으면 또 추가할 필요가 없다. 
    {
        v = findVertex(G, v2);
        addIncidentEdge(v, v1, newEdge);
    }
}
void addIncidentEdge(Vertex* v, int adjVNum, Edge* e)
{
    // 인접 간선 노드 초기화 작업 
    IncidentEdge* newIncidentEdge = (IncidentEdge*)malloc(sizeof(IncidentEdge));
    newIncidentEdge->adjVertexNum = adjVNum;
    newIncidentEdge->e = e;
    newIncidentEdge->next = NULL;

    // 인접 간선 연결리스트에 추가 
    IncidentEdge* q = v->iHead; // 더미 노드

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
            return vPointer; // 찾았으면 해당 vertex를 반환한다. 

        vPointer = vPointer->next;
    }

    return NULL; // 찾는 vertex가 없다면 NULL을 반환 
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

