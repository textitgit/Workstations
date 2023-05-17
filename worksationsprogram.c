// Online C compiler to run C program online
#include <stdio.h>
#include <stdlib.h>

#define MAX_WORKSTATIONS 100005

typedef struct {
    int parent;
    int rank;
} DisjointSet;

void makeSet(DisjointSet sets[], int n) {
    for (int i = 0; i < n; i++) {
        sets[i].parent = i;
        sets[i].rank = 0;
    }
}

int findSet(DisjointSet sets[], int x) {
    if (sets[x].parent != x)
        sets[x].parent = findSet(sets, sets[x].parent);
    return sets[x].parent;
}

void unionSets(DisjointSet sets[], int x, int y) {
    int xRoot = findSet(sets, x);
    int yRoot = findSet(sets, y);

    if (sets[xRoot].rank < sets[yRoot].rank)
        sets[xRoot].parent = yRoot;
    else if (sets[xRoot].rank > sets[yRoot].rank)
        sets[yRoot].parent = xRoot;
    else {
        sets[yRoot].parent = xRoot;
        sets[xRoot].rank++;
    }
}

int makeConnected(int n, int connections[][2], int numConnections) {
    if (numConnections < n - 1)
        return -1;

    DisjointSet sets[MAX_WORKSTATIONS];
    makeSet(sets, n);

    int components = n;
    for (int i = 0; i < numConnections; i++) {
        int workstationA = connections[i][0];
        int workstationB = connections[i][1];

        int parentA = findSet(sets, workstationA);
        int parentB = findSet(sets, workstationB);

        if (parentA != parentB) {
            unionSets(sets, parentA, parentB);
            components--;
        }
    }

    int cablesRequired = components - 1;
    return cablesRequired;
}

int main() {
    int n = 4;
    int connections[][2] = {{0, 1}, {0, 2}, {1, 2}};
    int numConnections = sizeof(connections) / sizeof(connections[0]);

    int result = makeConnected(n, connections, numConnections);

    printf("Minimum cables required: %d\n", result);

    return 0;
}