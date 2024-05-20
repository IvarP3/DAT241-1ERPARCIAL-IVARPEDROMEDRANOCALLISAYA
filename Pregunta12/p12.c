#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <math.h>

int fibo_term(int n) {
    if (n == 2) {
        return 1; // Caso especial: tercer término de Fibonacci
    } else {
        double p1 = (1/sqrt(5))*pow((1+sqrt(5))/2, n);
        double p2 = (1/sqrt(5))*pow((1-sqrt(5))/2, n);
        return (int)(p1 - p2);
    }
}

int main(int argc, char **argv) {
    int rank, size;
    int result;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int N;
    if (rank == 0) { // Proceso maestro
        printf("Ingrese el número de términos de la secuencia de Fibonacci a generar: ");
        scanf("%d", &N);
    }

    MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);
    
    if (size < 2) {
        fprintf(stderr, "Se necesitan al menos dos procesos para este ejemplo.\n");
        MPI_Finalize();
        return EXIT_FAILURE;
    }

    if (rank == 0) { // Proceso maestro
        for (int i = 0; i < N; i++) {
            int term;
            MPI_Recv(&term, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
            printf("Término %d: %d\n", i + 1, term);
        }
    }
    else { // Procesos esclavos
        for (int i = 0; i < N; i++) {
            int term = fibo_term(i);
            MPI_Send(&term, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        }
    }

    MPI_Finalize();
    return EXIT_SUCCESS;
}
