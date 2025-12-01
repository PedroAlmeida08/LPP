
/*
    Para compilar e executar:
        gcc -O3 matriz_seq.c -o matriz_seq -fopenmp
        ./matriz_seq
*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 1000

void inicializa_matriz(double *M, double value) {
    for (int i = 0; i < N * N; i++) {
        M[i] = value;
    }
}

int main() {
    double *A = (double *)malloc(N * N * sizeof(double));
    double *B = (double *)malloc(N * N * sizeof(double));
    double *C = (double *)malloc(N * N * sizeof(double)); // Matriz de Resultados

    if (!A || !B || !C) {
        printf("Erro de alocação de memória!\n");
        return 1;
    }

    inicializa_matriz(A, 1.0);
    inicializa_matriz(B, 1.0);

    printf("Iniciando multiplicacao sequencial (Matrizes %dx%d)...\n", N, N);

    double start_time, end_time, total_time = 0.0;
    int num_runs = 10;

    for (int run = 0; run < num_runs; run++) {
        
        inicializa_matriz(C, 0.0);

        start_time = omp_get_wtime();

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                double sum = 0.0;
                for (int k = 0; k < N; k++) {
                    sum += A[i * N + k] * B[k * N + j];
                }
                C[i * N + j] = sum;
            }
        }

        end_time = omp_get_wtime();
        double run_time = end_time - start_time;
        total_time += run_time;
        
        printf("Execucao %d: %.4f segundos\n", run + 1, run_time);
    }

    double avg_time = total_time / num_runs;
    printf("\nTempo Medio (Sequencial): %.6f segundos\n", avg_time);

    printf("Debug: C[0][0] = %.1f (Esperado: 1000.0)\n", C[0]);

    free(A);
    free(B);
    free(C);

    return 0;
}