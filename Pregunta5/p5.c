#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char* argv[]) {
    int N;
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        printf("Ingrese la dimensión N para la matriz y el vector: ");
        scanf("%d", &N);
    }

    // Compartir el valor de N entre todos los procesos
    MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);

    int local_N = N / size; // Tamaño local de la matriz y el vector
    int matriz[local_N][N];
    int vector[N];
    int local_resultado[local_N];

    // Inicializar el vector y la matriz (similar a tu código original)
    printf("Matriz:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matriz[i][j] = i * N + j + 1;
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }

    printf("\nVector:\n");
    for (int i = 0; i < N; i++) {
        vector[i] = i + 1;
        printf("%d ", vector[i]);
    }
    printf("\n\n");

    MPI_Bcast(vector, N, MPI_INT, 0, MPI_COMM_WORLD);

 for (int i = rank; i < N; i += size) {
  for (int j = 0; j < N; j++) {
   local_resultado[i] += matriz[i][j] * vector[j];
  }
 }

 MPI_Reduce(local_resultado, vector, N, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

 if (rank == 0) {
     printf("Vector resultante:\n");
            for (int i = 0; i < N; i++) {
              printf("%d ", local_resultado[i]);
            }
            printf("\n");
 }

 MPI_Finalize();
 return 0;
}