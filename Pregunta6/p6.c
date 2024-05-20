#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size;
    double pi = 0.0;
    int sign, denominator, n;
    double local_pi = 0.0;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    for (n = rank; n < 100000; n += size) {
        sign = (n % 2 == 0) ? 1 : -1;
        denominator = 2 * n + 1;
        local_pi += sign * 1.0 / denominator;
    }

    MPI_Reduce(&local_pi, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        pi *= 4; // Multiplicamos por 4 ya que la serie converge a pi/4
        printf("Valor aproximado de pi: %lf\n", pi);
    }

    MPI_Finalize();

    return 0;
}
