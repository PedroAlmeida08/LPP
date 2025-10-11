/*
  Para compilar e executar:
    mpicc -o mpi_calc mpi_calc.c
    mpirun -n 4 mpi_calc
*/  

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char** argv) {

    const int N = 10;
    int meu_ranque, num_procs, vet[N];
    double start_time, end_time, tempo_paralelo = 0.0, tempo_sequencial = 0.0, speedup = 0.0, eficiencia = 0.0;

    /* Chamada inicial para o MPI */
    MPI_Init(&argc, &argv);
    /* Determina o ranque do processo */
    MPI_Comm_rank(MPI_COMM_WORLD, &meu_ranque);
    /* Determina o número de processos em execução */
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

    /* Esta versão requer exatamente 4 processos para funcionar corretamente. */
    if (num_procs != 4) {
        if (meu_ranque == 0) {
            fprintf(stderr, "Erro: Este programa deve ser executado com exatamente 4 processos.\n");
        }
        MPI_Finalize();
        exit(1);
    }

    /* Todos os processos preenchem o vetor */
    for (int i = 0; i < N; i++) {
        vet[i] = i + 1;
    }

    /* Execução Sequencial do Programa */
    if (meu_ranque == 0) {
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

    /* Início Real da Execução Paralela do Programa */
    /* Sincroniza todos os processos e inicia a contagem de tempo no processo 0 */
    MPI_Barrier(MPI_COMM_WORLD);
    if (meu_ranque == 0) {
        start_time = MPI_Wtime();
    }

    if (meu_ranque == 0) {
        int soma_total, sub_total;
        long long mult_total;
        
        /* Recebe o resultado da soma do processo 1 */
        MPI_Recv(&soma_total, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        
        /* Recebe o resultado da subtração do processo 2 */
        MPI_Recv(&sub_total, 1, MPI_INT, 2, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        /* Recebe o resultado da multiplicação do processo 3 */
        MPI_Recv(&mult_total, 1, MPI_LONG_LONG, 3, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        
        end_time = MPI_Wtime();
        tempo_paralelo = end_time - start_time;
        
        /* Cálculo do Speedup e da Eficiência */
        if (tempo_paralelo > 0) {
            speedup = tempo_sequencial / tempo_paralelo;
            eficiencia = speedup / num_procs;
        }

        printf("--- Calculadora (4 processos) ---\n");
        printf("Soma = %d\n", soma_total);
        printf("Subtracao = %d\n", sub_total);
        printf("Multiplicacao = %lld\n\n", mult_total);

        printf("--- Análise de Desempenho ---\n");
        printf("Tempo de execução sequencial: %f segundos\n", tempo_sequencial);
        printf("Tempo de execução paralelo:   %f segundos\n", tempo_paralelo);
        printf("Speedup: %.4f\n", speedup);
        printf("Eficiência: %.2f %%\n", eficiencia * 100);

    } 
    /* Processo 1: Soma */
    else if (meu_ranque == 1) {
        int soma_parcial = 0;
        for (int i = 0; i < N; i++) {
            soma_parcial += vet[i];
        }
        /* Envia o resultado para o processo de rank 0 */
        MPI_Send(&soma_parcial, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);

    } 
    /* Processo 2: Subtração */
    else if (meu_ranque == 2) {
        int sub_parcial = 0;
        for (int i = 0; i < N; i++) {
            sub_parcial -= vet[i];
        }
        /* Envia o resultado para o processo de rank 0 */
        MPI_Send(&sub_parcial, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);

    } 
    /* Processo 3: Multiplicação */
    else if (meu_ranque == 3) {
        long long mult_parcial = 1;
        for (int i = 0; i < N; i++) {
            mult_parcial *= vet[i];
        }
        /* Envia o resultado para o processo de rank 0 */
        MPI_Send(&mult_parcial, 1, MPI_LONG_LONG, 0, 0, MPI_COMM_WORLD);
    }
    
    /* Finaliza o ambiente MPI */
    MPI_Finalize();

    return 0;
}