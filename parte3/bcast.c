// Parte 3 — Broadcast de un valor con MPI_Bcast (MPI_INT)
// Compilar: mpicc -o bcast bcast.c
// Ejecutar: mpirun --oversubscribe --bind-to none -np 8 ./bcast 42

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int valor = 0;
    int root = 0; // coordinador

    if (rank == root) {
        // Si viene argumento, úsalo; si no, usa 7 como default
        valor = (argc > 1) ? atoi(argv[1]) : 7;
        printf("[Root %d] Valor inicial = %d; lo enviaré a todos con MPI_Bcast\n", rank, valor);
        fflush(stdout);
    }

    // Difundir el valor desde 'root' a TODOS los procesos del comunicador
    MPI_Bcast(&valor, 1, MPI_INT, root, MPI_COMM_WORLD);

    // En este punto, 'valor' es el mismo en todos los ranks
    printf("Rank %d recibió valor = %d (size=%d)\n", rank, valor, size);
    fflush(stdout);

    MPI_Finalize();
    return 0;
}
