#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

int **graph;
int V;
int *node_types;

void setGraph(int **g, int n) {
    graph = g;
    V = n;
}

void setNodeTypes(int *types) {
    node_types = types;
}

int **findMST() {
    // create arrays to keep track of MST and visited nodes
    int **mst = (int **)malloc((V-1) * sizeof(int *));
    bool *visited = (bool *)calloc(V, sizeof(bool));
    int *distances = (int *)calloc(V, sizeof(int));
    int *parents = (int *)calloc(V, sizeof(int));
    
    // initialize arrays
    for (int i = 0; i < V-1; i++) {
        mst[i] = (int *)malloc(2 * sizeof(int));
        visited[i] = false;
        distances[i] = INT_MAX;
        parents[i] = -1;
    }
    
    // set the root node to the first outer node in the list
    int root = -1;
    for (int i = 0; i < V; i++) {
        if (node_types[i] == 1) {
            root = i;
            break;
        }
    }
    
    // set the distance to the root to 0
    distances[root] = 0;
    
    // loop through all nodes
    for (int i = 0; i < V-1; i++) {
        // find the closest node to the MST
        int closest = -1;
        for (int j = 0; j < V; j++) {
            if (!visited[j] && (closest == -1 || distances[j] < distances[closest])) {
                closest = j;
            }
        }
        
        // mark the closest node as visited
        visited[closest] = true;
        
        // add the closest edge to the MST
        if (parents[closest] != -1) {
            mst[i-1][0] = parents[closest];
            mst[i-1][1] = closest;
        }
        
        // update distances and parents for adjacent nodes
        for (int j = 0; j < V; j++) {
            if (graph[closest][j] > 0 && !visited[j] && graph[closest][j] < distances[j]) {
                distances[j] = graph[closest][j];
                parents[j] = closest;
            }
        }
    }
    
    // free memory and return MST
    free(visited);
    free(distances);
    free(parents);
    return mst;
}

void printPath(int **mst, int start, int end) {
    // find the index of the edge that connects the two outer nodes
    int index = -1;
    for (int i = 0; i < V-1; i++) {
        if ((mst[i][0] == start && mst[i][1] == end) || (mst[i][1] == start && mst[i][0] == end)) {
            index = i;
            break;
        }
    }
    
    if (index == -1) {
        printf("No path found between vertices %d and %d\n", start, end);
        return;
    }
    
    // print the path
    printf("Path between vertices %d and %d: %d", start, end, start);
    int node =
