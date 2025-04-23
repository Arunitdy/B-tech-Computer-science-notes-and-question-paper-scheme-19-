#include <stdio.h>
#include <limits.h>
#define MAX_NODES 10
#define INF INT_MAX
void dijkstra(int graph[MAX_NODES][MAX_NODES], int n, int startNode) {
    int distance[MAX_NODES], visited[MAX_NODES] = {0}, count = 0, minDistance, nextNode;
    for (int i = 0; i < n; i++) {
        distance[i] = graph[startNode][i];
    }
    distance[startNode] = 0;
    visited[startNode] = 1;
    count = 1;
    while (count < n) {
        minDistance = INF;
        for (int i = 0; i < n; i++) {
            if (distance[i] < minDistance && !visited[i]) {
                minDistance = distance[i];
                nextNode = i;
            }
        }
        visited[nextNode] = 1;
        for (int i = 0; i < n; i++) {
            if (!visited[i] && (minDistance + graph[nextNode][i] < distance[i]) && graph[nextNode][i] !=
            INF) {
                distance[i] = minDistance + graph[nextNode][i];
            }
        }
        count++;
    }
    printf("Shortest paths from node %d (Link State):\n", startNode + 1);
    for (int i = 0; i < n; i++) {
        printf("To node %d: %d\n", i + 1, distance[i]);
    }
}
int main() {
    int graph[MAX_NODES][MAX_NODES], n;
    printf("Enter the number of nodes: ");
    scanf("%d", &n);
    printf("Enter the adjacency matrix (use 999 for no connection):\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &graph[i][j]);
            if (graph[i][j] == 999) graph[i][j] = INF;
        }
    }
    printf("Calculating shortest paths from all nodes using Link State Routing (Dijkstra)\n\n");
    for (int i = 0; i < n; i++) {
        dijkstra(graph, n, i);
        printf("\n");
    }
    return 0;
}
