#include <stdio.h>
#include <omp.h>

int main() {
    int M, N;

    printf("Ingrese el número de vectores (M): ");
    scanf("%d", &M);

    printf("Ingrese el número de términos (N): ");
    scanf("%d", &N);

    int series[M][N];

    #pragma omp parallel
    {
        int i, j;
        int num_threads = omp_get_num_threads();
        int chunk = N / num_threads;
        
        #pragma omp for private(i, j) schedule(static, chunk)
        for (i = 0; i < M; i++) {
            int start_value = (i * N + 1) * 2;

            for (j = 0; j < N; j++) {
                series[i][j] = start_value + j * 2;
            }
        }
    }

    printf("Serie generada:\n");
    for (int i = 0; i < M; i++) {
        printf("Vector %d: ", i + 1);
        for (int j = 0; j < N; j++) {
            printf("%d ", series[i][j]);
        }
        printf("\n");
    }

    return 0;
}
