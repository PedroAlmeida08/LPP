/*
  Para compilar e executar:
    mpicc -o mpi_pipeline mpi_pipeline.c
    mpirun -n 4 mpi_pipeline
*/

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char** argv) {

    const int N = 10;
    int meu_ranque, num_procs, *vet = NULL;
    double start_time, end_time, tempo_paralelo = 0.0, tempo_sequencial = 0.0;
    
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
    int local_n; 
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
    
    /* Vetor de resultados: {soma, subtracao, multiplicacao} */
    long long resultados[3]; 
    if (meu_ranque == 0) {
        resultados[0] = 0;
        resultados[1] = 0;
        resultados[2] = 1;

        /* Realiza Operações */
        for (int i = 0; i < local_n; i++) {
            resultados[0] += local_vet[i];
            resultados[1] -= local_vet[i];
            resultados[2] *= local_vet[i];
        }

        /* Envia o resultado das operações para o próximo processo, se houver */
        if (num_procs > 1) {
            MPI_Send(resultados, 3, MPI_LONG_LONG, meu_ranque + 1, 0, MPI_COMM_WORLD);
        }

    } else { 
        /* Recebe o resultado das operações feitas pelo processo anterior */
        MPI_Recv(resultados, 3, MPI_LONG_LONG, meu_ranque - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        /* Realiza sua contribuição */
        for (int i = 0; i < local_n; i++) {
            resultados[0] += local_vet[i];
            resultados[1] -= local_vet[i];
            resultados[2] *= local_vet[i];
        }

        /* Envia o resultado das operações para o próximo processo, se houver */
        if (meu_ranque < num_procs - 1) {
            MPI_Send(resultados, 3, MPI_LONG_LONG, meu_ranque + 1, 0, MPI_COMM_WORLD);
        }
    }

    /* Coleta do Resultado Final */
    long long resultados_finais[3];
    if (meu_ranque == 0) {
        if (num_procs > 1) {
            /* Processo de ranque 0 espera pela mensagem do último processo, que contém os resultados finais */
            MPI_Recv(resultados_finais, 3, MPI_LONG_LONG, num_procs - 1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        } else {
            /* Se só há um processo, o resultado é imediato */
            resultados_finais[0] = resultados[0];
            resultados_finais[1] = resultados[1];
            resultados_finais[2] = resultados[2];
        }
        end_time = MPI_Wtime();
        tempo_paralelo = end_time - start_time;

        /* Calcula Métricas de Desempenho */
        double speedup = 0.0, eficiencia = 0.0;
        if (tempo_paralelo > 0) {
            speedup = tempo_sequencial / tempo_paralelo;
            eficiencia = speedup / num_procs;
        }

        /* Imprime Resultado no Console */
        printf("--- Calculadora Pipeline (N processos) ---\n");
        printf("Soma = %lld\n", resultados_finais[0]);
        printf("Subtracao = %lld\n", resultados_finais[1]);
        printf("Multiplicacao = %lld\n\n", resultados_finais[2]);

        printf("--- Análise de Desempenho ---\n");
        printf("Tempo de execução sequencial: %f segundos\n", tempo_sequencial);
        printf("Tempo de execução paralelo:   %f segundos\n", tempo_paralelo);
        printf("Speedup: %.4f\n", speedup);
        printf("Eficiência: %.2f %%\n", eficiencia * 100);

    } else if (meu_ranque == num_procs - 1) {
        /* O último processo envia o resultado final de volta para o processo de ranque 0 */
        /* É utilizada uma tag diferente (1) da tag utilizada para as mensagens de de comunicação relativas ao pipeline */
        MPI_Send(resultados, 3, MPI_LONG_LONG, 0, 1, MPI_COMM_WORLD);
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