#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size, M, N;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        printf("Ingrese el número de vectores (M): ");
        scanf("%d", &M);

        printf("Ingrese el número de términos (N): ");
        scanf("%d", &N);
    }

    MPI_Bcast(&M, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);

    int series[M][N];

    int chunk = M / size;
    int start = rank * chunk;
    int end = (rank == size - 1) ? M : start + chunk;

    for (int i = start; i < end; i++) {
        int start_value = (i * N + 1) * 2;
        for (int j = 0; j < N; j++) {
            series[i][j] = start_value + j * 2;
        }
    }

    MPI_Barrier(MPI_COMM_WORLD);

    if (rank == 0 || rank == 1) {
        printf("Serie generada:\n");
        for (int i = 0; i < M; i++) {
            printf("Vector %d: ", i + 1);
            for (int j = 0; j < N; j++) {
                printf("%d ", series[i][j]);
            }
            printf("\n");
        }
    }

    MPI_Finalize();

    return 0;
}