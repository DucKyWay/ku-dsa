/*
0 -> 1, 3
1 -> 4
2 -> 0, 3
3 -> 4
4 -> NULL

crateGraph(n)
addEdge(G, u, v)
printGraph(G)
deleteGraph(G)
*/

#include <stdio.h>
#include <stdlib.h>

int** createGraph(const int n) {

    int** matrix = (int **)malloc(n * sizeof(int*));
    for(int i = 0; i < n; i++) {

        matrix[i] = (int *)malloc(sizeof(int) * n);
        for(int j = 0; j < n; j++) {
            matrix[i][j] = 0;
        }
    }
    return matrix;
}

void addEdge(int** matrix, int i, int j) {
    matrix[i][j] = 1;
}

void printGraph(int** matrix, int n) {
    printf("%5s ", "0");
    for(int i = 1; i < n; i++) {
        printf("%d ", i);
    }

    for(int i = 0; i < n; i++) {
        printf("\n%d | ", i);
        for(int j = 0; j < n; j++) {
            printf("%d ", matrix[i][j]);
        }
    }
}

int main() {

    int n = 5;
    int** matrix = createGraph(n);

    addEdge(matrix, 0, 1);
    addEdge(matrix, 0, 3);
    addEdge(matrix, 1, 4);
    addEdge(matrix, 2, 3);
    addEdge(matrix, 3, 4);

    printGraph(matrix, n);
    
    return 0;
}