// mpicc -o mpi_wtime mpi_wtime.c
// mpirun -n 1 mpi_wtime

#include "mpi.h"
#include <stdio.h>

int main(int argc, char *argv[]) { /* mpi_wtime.c */
  // ...
    double tempo_inicial, tempo_final, a;
    /* MPI_Wtime() --> Wtime = Wall Clock Time */
    tempo_inicial = MPI_Wtime();
    /* Realiza um trabalho qualquer */
        for (long int i = 0; i < 1000; i++) {
            a = (double) i;
        } 
    // ...
    tempo_final = MPI_Wtime();
    printf("Foram gastos %3.6f segundos para calcular a = %3.0f com precisão de  %3.3e segundos\n",tempo_final-tempo_inicial, a, MPI_Wtick ());
    
    return(0);
}
