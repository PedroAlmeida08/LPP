/*
    Para compilar e excutar: 
        export OMP_NUM_THREADS=4
        gcc omp_sections.c -fopenmp -o omp_sections
        ./omp_sections

*/

#include <omp.h>
#include <stdio.h>

int main(int argc, char *argv[]) { /* omp_sections.c */
int conta_secao = 0;
#pragma omp parallel sections num_threads(4)
{
    #pragma omp section
	{
    		int tid = omp_get_thread_num();
 		conta_secao++;
 		/* deve imprimir o número um ou dois */ 
 		printf( "Ordem de execução da sessão %d, thread %d \n", conta_secao, tid);
 	}
    #pragma omp section
 	{
    		int tid = omp_get_thread_num();
 		conta_secao++;
		/* deve imprimir o número um ou dois */ 
 		printf( "Ordem de execução da sessão %d, thread %d \n", conta_secao, tid );
 	}
}
    return(0);
}