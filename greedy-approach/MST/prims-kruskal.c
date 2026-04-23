#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#define MAXV 25
#define MAXE 100
#define ITERATIONS 10000

// edge structure for kruskal
typedef struct {
    int src, dest, weight;
} Edge;

// adjacency list node for prim
typedef struct Node {
    int dest, weight;
    struct Node* next;
} Node;

Node* adj[MAXV];      // adjacency list
Edge edges[MAXE];     // edge list
int edgeCount = 0;

// add edge to both representations
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

// free adjacency list
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

// sample graph
void createGraph(int V) {
    clearGraph(V);

    addEdge(0, 1, 4);
    addEdge(0, 2, 8);
    addEdge(1, 2, 11);
    addEdge(1, 3, 8);
    addEdge(2, 4, 7);
    addEdge(2, 5, 1);
    addEdge(3, 4, 2);
    addEdge(3, 6, 7);
    addEdge(4, 5, 6);
}

// prim's algorithm
int primMST(int V) {
    int key[MAXV];
    int visited[MAXV] = {0};
    int total = 0;

    for (int i = 0; i < V; i++)
        key[i] = INT_MAX;

    key[0] = 0;

    for (int count = 0; count < V; count++) {
        int u = -1;

        // pick minimum key vertex not yet included
        for (int i = 0; i < V; i++)
            if (!visited[i] && (u == -1 || key[i] < key[u]))
                u = i;

        visited[u] = 1;
        total += key[u];

        // update adjacent vertices
        Node* temp = adj[u];
        while (temp) {
            int v = temp->dest;
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

// comparator for sorting edges
int cmp(const void* a, const void* b) {
    return ((Edge*)a)->weight - ((Edge*)b)->weight;
}

// kruskal's algorithm
int kruskalMST(int V) {
    qsort(edges, edgeCount, sizeof(Edge), cmp);

    for (int i = 0; i < V; i++)
        makeSet(i);

    int total = 0;
    int count = 0;

    for (int i = 0; i < edgeCount && count < V - 1; i++) {
        Edge e = edges[i];

        // include edge if it does not form a cycle
        if (findSet(e.src) != findSet(e.dest)) {
            total += e.weight;
            unionSet(e.src, e.dest);
            count++;
        }
    }

    return total;
}

int main() {
    int V = 7;

    printf("Minimum Spanning Tree\n");

    createGraph(V);

    clock_t start, end;

    // prim timing
    start = clock();
    for (int i = 0; i < ITERATIONS; i++)
        primMST(V);
    end = clock();

    double primTime = ((double)(end - start) * 1000000) / (CLOCKS_PER_SEC * ITERATIONS);
    int primWeight = primMST(V);

    // kruskal timing
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
