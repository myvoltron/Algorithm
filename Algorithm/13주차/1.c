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

    d[startV] = 0; // 임의의 정점을 선택 여기서는 무조건 1부터 시작한다. 

    for (int i = 1; i <= G->vCount; i++)
    {
        vMinimum = getMinVertex(G, d); // 최소 가중치를 가지는 정점을 가져온다. 
        p = findVertex(G, vMinimum); 
        p->isVisit = TRUE; // T에 포함 
        *sum += d[vMinimum];
        printf(" %d", p->vNum);
        
        /*for (int j = 1; j <= G->vCount; j++)
            printf(" %d", d[j]);
        printf("\n");
        printf(" %d\n", d[vMinimum]);*/

        // p의 인접한 정점들을 순회하면서 dist를 갱신한다. 
        for (q = p->iHead->next; q != NULL; q = q->next)
        {
            p = findVertex(G, q->adjVertexNum); // 인접 정점 vertex를 가져온다. 
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
우선순위 큐를 사용하지 않는 prim 알고리즘이다.
https://lsoovmee-rhino.tistory.com/93?category=847612 참고

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
    int dist[101]; // distance, idx = vertex, value = 해당 vertex까지의 거리의미 

    Graph G;
    initGraph(&G);
    
    scanf("%d %d", &n, &m);
    
    // vertex 생성
    for (int i = 1; i <= n; i++)
        addVertex(&G, i);

    // edge 생성
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

