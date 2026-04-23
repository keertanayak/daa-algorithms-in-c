#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#define MAXV 25
#define MAXE 200
#define ITERATIONS 10000

typedef struct {
    int src, dest, weight;
} Edge;

typedef struct Node {
    int dest, weight;
    struct Node* next;
} Node;

Node* adj[MAXV];
Edge edges[MAXE];
int edgeCount = 0;

// add edge to both adjacency list and edge list
void addEdge(int u, int v, int w) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->dest = v;
    node->weight = w;
    node->next = adj[u];
    adj[u] = node;

    node = (Node*)malloc(sizeof(Node));
    node->dest = u;
    node->weight = w;
    node->next = adj[v];
    adj[v] = node;

    edges[edgeCount++] = (Edge){u, v, w};
}

// free graph memory
void clearGraph(int V) {
    for (int i = 0; i < V; i++) {
        Node* temp = adj[i];
        while (temp) {
            Node* t = temp;
            temp = temp->next;
            free(t);
        }
        adj[i] = NULL;
    }
    edgeCount = 0;
}

// generate a connected random graph
void generateGraph(int V, int E) {
    clearGraph(V);

    // step 1: create a spanning tree to ensure connectivity
    for (int i = 1; i < V; i++) {
        int parent = rand() % i;               // connect to any previous node
        int weight = rand() % 20 + 1;
        addEdge(parent, i, weight);
    }

    // step 2: add remaining edges randomly
    int extraEdges = E - (V - 1);

    while (extraEdges > 0) {
        int u = rand() % V;
        int v = rand() % V;

        if (u != v) {                         // avoid self-loop
            int weight = rand() % 20 + 1;
            addEdge(u, v, weight);
            extraEdges--;
        }
    }
}

// prim's algorithm
int primMST(int V) {
    int key[MAXV];
    int visited[MAXV] = {0};
    int total = 0;

    for (int i = 0; i < V; i++)
        key[i] = INT_MAX;

    key[0] = 0;  // start from vertex 0

    for (int count = 0; count < V; count++) {
        int u = -1;

        // select minimum key vertex not yet included in mst
        for (int i = 0; i < V; i++)
            if (!visited[i] && (u == -1 || key[i] < key[u]))
                u = i;

        visited[u] = 1;
        total += key[u];  // add weight of chosen edge

        // update keys for adjacent vertices
        Node* temp = adj[u];
        while (temp) {
            int v = temp->dest;

            // relax edge if better option found
            if (!visited[v] && temp->weight < key[v])
                key[v] = temp->weight;

            temp = temp->next;
        }
    }

    return total;
}

// disjoint set for kruskal
int parent[MAXV], rankArr[MAXV];

void makeSet(int v) {
    parent[v] = v;
    rankArr[v] = 0;
}

int findSet(int v) {
    if (v != parent[v])
        parent[v] = findSet(parent[v]);  // path compression
    return parent[v];
}

void unionSet(int a, int b) {
    a = findSet(a);
    b = findSet(b);

    if (a != b) {
        // attach smaller tree under larger tree
        if (rankArr[a] < rankArr[b])
            parent[a] = b;
        else if (rankArr[a] > rankArr[b])
            parent[b] = a;
        else {
            parent[b] = a;
            rankArr[a]++;
        }
    }
}

// sort edges by weight
int cmp(const void* a, const void* b) {
    return ((Edge*)a)->weight - ((Edge*)b)->weight;
}

// kruskal's algorithm
int kruskalMST(int V) {
    qsort(edges, edgeCount, sizeof(Edge), cmp);

    for (int i = 0; i < V; i++)
        makeSet(i);

    int total = 0, count = 0;

    for (int i = 0; i < edgeCount && count < V - 1; i++) {
        Edge e = edges[i];

        // include edge only if it doesn't form a cycle
        if (findSet(e.src) != findSet(e.dest)) {
            total += e.weight;
            unionSet(e.src, e.dest);
            count++;  // mst grows by one edge
        }
    }

    return total;
}

int main() {
    srand(time(NULL));

    int V = 10;
    int E = 20;

    printf("Minimum Spanning Tree\n");

    // generate random connected graph
    generateGraph(V, E);

    clock_t start, end;

    // measure prim's time
    start = clock();
    for (int i = 0; i < ITERATIONS; i++)
        primMST(V);
    end = clock();

    double primTime = ((double)(end - start) * 1000000) / (CLOCKS_PER_SEC * ITERATIONS);
    int primWeight = primMST(V);

    // measure kruskal's time
    start = clock();
    for (int i = 0; i < ITERATIONS; i++)
        kruskalMST(V);
    end = clock();

    double kruskalTime = ((double)(end - start) * 1000000) / (CLOCKS_PER_SEC * ITERATIONS);
    int kruskalWeight = kruskalMST(V);

    printf("\nPrim's MST Weight: %d", primWeight);
    printf("\nPrim's Time: %.2f microseconds", primTime);

    printf("\n\nKruskal's MST Weight: %d", kruskalWeight);
    printf("\nKruskal's Time: %.2f microseconds\n", kruskalTime);

    clearGraph(V);
    return 0;
}
