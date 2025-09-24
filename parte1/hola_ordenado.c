// Parte 1 — Flujo de ranks en MPI (ordenado)
// Compilar: mpicc -o hola_ordenado hola_ordenado.c
// Ejecutar: mpirun -np 8 ./hola_ordenado

#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);  // rank: id único del proceso
    MPI_Comm_size(MPI_COMM_WORLD, &size);  // size: # total de procesos

    // Imprimir en orden 0..size-1 usando una barrera por iteración
    for (int i = 0; i < size; i++) {
        if (rank == i) {
            if (rank == 0) {
                printf("Rank 0 comunicador\n");
            } else {
                printf("Rank %d con size %d\n", rank, size);
            }
            fflush(stdout);
        }
        MPI_Barrier(MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}
