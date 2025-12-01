/*
    Para compilar e executar:
        gcc -O3 matriz_par_guided.c -o matriz_par_guided -fopenmp
        export OMP_NUM_THREADS=2
        ./matriz_par_guided
*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 1000
#define TEMPO_SEQUENCIAL 0.360449 

void inicializa_matriz(double *M, double value) {
    for (int i = 0; i < N * N; i++) {
        M[i] = value;
    }
}

int main() {
    double *A = (double *)malloc(N * N * sizeof(double));
    double *B = (double *)malloc(N * N * sizeof(double));
    double *C = (double *)malloc(N * N * sizeof(double));

    if (!A || !B || !C) {
        printf("Erro de alocacao!\n");
        return 1;
    }

    inicializa_matriz(A, 1.0);
    inicializa_matriz(B, 1.0);

    int n_threads = 0;
    #pragma omp parallel
    {
        #pragma omp single
        n_threads = omp_get_num_threads();
    }

    printf("\n--- Execucao Paralela (Guided) com %d Threads ---\n", n_threads);
    printf("Base de comparacao (Sequencial): %.6f s\n", TEMPO_SEQUENCIAL);

    double start_time, end_time, total_time = 0.0;
    int num_runs = 10;

    for (int run = 0; run < num_runs; run++) {
        inicializa_matriz(C, 0.0);

        start_time = omp_get_wtime();

        #pragma omp parallel for schedule(guided) shared(A,B,C)
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
        total_time += (end_time - start_time);
    }

    double t_par = total_time / num_runs;
    printf("Tempo Medio Paralelo: %.6f s\n", t_par);

    double speedup = TEMPO_SEQUENCIAL / t_par;
    double eficiencia = speedup / n_threads;

    printf("Speedup: %.4f\n", speedup);
    printf("Eficiencia: %.4f (%.2f%%)\n", eficiencia, eficiencia * 100);

    free(A);
    free(B);
    free(C);

    return 0;
}