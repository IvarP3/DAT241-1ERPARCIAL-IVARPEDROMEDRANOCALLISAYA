#include <stdio.h>
#include <omp.h>

int main() {
    int N;

    printf("Ingrese la dimension N para la matriz y el vector: ");
    scanf("%d", &N);

    int matriz[N][N];
    int vector[N];
    int resultado[N];

    for (int i = 0; i < N; i++) {
        vector[i] = i + 1;
        for (int j = 0; j < N; j++) {
            matriz[i][j] = i * N + j + 1;
        }
    }

    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            resultado[i] += matriz[i][j] * vector[j];
        }
    }

    printf("Vector resultante:\n");
    for (int i = 0; i < N; i++) {
        printf("%d ", resultado[i]);
    }
    printf("\n");

    return 0;
}