/*
  Para compilar e executar:
    mpicc -o mpi_ms mpi_ms.c
    mpirun -n 4 mpi_ms
*/

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char** argv) {

    const int N = 10;
    int meu_ranque, num_procs, *vet = NULL;
    double start_time, end_time, tempo_paralelo = 0.0, tempo_sequencial = 0.0, speedup = 0.0, eficiencia = 0.0;

    /* Chamada inicial para o MPI */
    MPI_Init(&argc, &argv);
    /* Determina o ranque do processo */
    MPI_Comm_rank(MPI_COMM_WORLD, &meu_ranque);
    /* Determina o número de processos em execução */
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

    /* Processo Mestre */
    if (meu_ranque == 0) {
        /* Execução Sequencial do Programa */
        vet = malloc(N * sizeof(int));
        for (int i = 0; i < N; i++) vet[i] = i + 1;

        double seq_start = MPI_Wtime();
        int soma_seq = 0, sub_seq = 0;
        long long mult_seq = 1;
        for (int i = 0; i < N; i++) {
            soma_seq += vet[i];
            sub_seq -= vet[i];
            mult_seq *= vet[i];
        }
        double seq_end = MPI_Wtime();
        tempo_sequencial = seq_end - seq_start;
    }

    /* Balanceamento de Carga entre os Processos */
    int chunk_size = N / num_procs;
    int resto = N % num_procs;
    int local_n; /* Número de elementos que um processo irá receber */
    int *tam = NULL, *inicio = NULL;

    if (meu_ranque == 0) {
        tam = malloc(num_procs * sizeof(int));
        inicio = malloc(num_procs * sizeof(int));
        /* Calcula quantos elementos cada processo recebe e onde eles começam */
        for (int i = 0; i < num_procs; i++) {
            /* Se i < resto, recebe a quantidade máxima que os vetores terão em comum mais um elemento do resto*/
            /* c.c. recebe apenas a quantidade máxima que os vetores terão em comum, pois não há mais resto */
            tam[i] = (i < resto) ? chunk_size + 1 : chunk_size;
            /* Se i == 0, irá começar suas operações no início do vetor */
            /* c.c. começa um elemento depois do último elemento do processo anterior */
            inicio[i] = (i == 0) ? 0 : inicio[i-1] + tam[i-1];
        }
    }
    
    /* Sincroniza todos os processos */
    MPI_Barrier(MPI_COMM_WORLD);
    
    if (meu_ranque == 0) {
        start_time = MPI_Wtime();
    }

    /* O mestre envia para cada processo quantos elementos ele irá receber. */
    MPI_Scatter(tam, 1, MPI_INT, &local_n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    
    /* Aloca o buffer local para receber sua parte do vetor */
    int *local_vet = malloc(local_n * sizeof(int));
    
    /* Utiliza a versão vetorial do MPI_Scatter para distribuir os elementos do vetor (como vetores) para todos os processos */
    MPI_Scatterv(vet, tam, inicio, MPI_INT, local_vet, local_n, MPI_INT, 0, MPI_COMM_WORLD);
    
    int soma_local = 0, sub_local = 0; 
    long long mult_local = 1;

    /* Realiza as operações */
    for (int i = 0; i < local_n; i++) {
        soma_local += local_vet[i];
        sub_local -= local_vet[i];
        mult_local *= local_vet[i];
    }

    int soma_global, sub_global;
    long long mult_global;

    /* Combina todos os 'soma_local' e armazena em 'soma_global' */
    MPI_Reduce(&soma_local, &soma_global, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    /* Combina todos os 'sub_local' e armazena em 'sub_global' */
    MPI_Reduce(&sub_local, &sub_global, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    /* Combina todos os 'mult_local' e armazena em 'mult_global' */
    MPI_Reduce(&mult_local, &mult_global, 1, MPI_LONG_LONG, MPI_PROD, 0, MPI_COMM_WORLD);

    /* Finaliza Medidas de Desempenho e Imprime Resultado no Console*/
    if (meu_ranque == 0) {
        end_time = MPI_Wtime();
        tempo_paralelo = end_time - start_time;
        if (tempo_paralelo > 0) {
            speedup = tempo_sequencial / tempo_paralelo;
            eficiencia = speedup / num_procs;
        }

        printf("--- Calculadora Master/Slave (N processos) ---\n");
        printf("Soma = %d\n", soma_global);
        printf("Subtracao = %d\n", sub_global);
        printf("Multiplicacao = %lld\n\n", mult_global);

        printf("--- Análise de Desempenho ---\n");
        printf("Tempo de execução sequencial: %f segundos\n", tempo_sequencial);
        printf("Tempo de execução paralelo:   %f segundos\n", tempo_paralelo);
        printf("Speedup: %.4f\n", speedup);
        printf("Eficiência: %.2f %%\n", eficiencia * 100);
    }

    /* Libera memória utilizada pelo processo 0*/
    if (meu_ranque == 0) {
        free(vet);
        free(tam);
        free(inicio);
    }

    /* Libera memória que todos os processos alocaram*/
    free(local_vet);
    
    /* Finaliza o ambiente MPI*/
    MPI_Finalize();

    return 0;
}