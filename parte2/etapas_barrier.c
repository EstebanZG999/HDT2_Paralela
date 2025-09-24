// Parte 2 — Identificar etapas con MPI_Barrier
// Compilar: mpicc -o etapas_barrier etapas_barrier.c
// Ejecutar: mpirun --oversubscribe --bind-to none -np 8 ./etapas_barrier

#include <mpi.h>
#include <stdio.h>
#include <unistd.h>  // usleep

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    double t0 = MPI_Wtime();

    // --- Etapa 1: trabajo asíncrono (simulado con delays distintos)
    usleep(100000 * (rank % 5)); // hasta 0.5 s
    printf("[Etapa 1] Rank %d completó trabajo (t=%.3fs)\n",
           rank, MPI_Wtime() - t0);
    fflush(stdout);

    // --- Barrera: todos deben llegar aquí antes de continuar
    MPI_Barrier(MPI_COMM_WORLD);

    // --- Etapa 2: imprime en orden 0..size-1 usando "token passing"
    int token = 0;
    if (rank == 0) {
        printf("[Etapa 2] Rank 0 inicia (pasaron barrera)\n");
        fflush(stdout);
        if (size > 1) MPI_Send(&token, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
    } else {
        MPI_Recv(&token, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("[Etapa 2] Rank %d inicia (pasaron barrera)\n", rank);
        fflush(stdout);
        if (rank < size - 1) MPI_Send(&token, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}
