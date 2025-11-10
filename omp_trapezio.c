/*
    Para compilar e excutar: 
        export OMP_NUM_THREADS=4
        gcc omp_trapezio.c -fopenmp -o omp_trapezio
        ./omp_trapezio

*/

#include <stdio.h>
#include <math.h>
#include <omp.h>

double f(double x) {
double valor;
    valor = x*x;
    return(valor);
}

int main(int argc, char *argv[]) { 
double integral;    
double a, b;        
long n;             
double h;           
double tempo_sequencial = 32.788024; 
a = 0.0;
b = 1.0;
n = 8000000000;
    
h = (b-a)/n;
integral = (f(a) + f(b))/2.0;
double t_inicio = omp_get_wtime();

#pragma omp parallel for default(none) firstprivate(n,a,h) reduction(+:integral) schedule(static)
    for (long i = 1; i < n-1; i++) {
         integral += f(a + i*h);
    }
    integral *= h ;

    double t_fim = omp_get_wtime();

    double tempo_paralelo = t_fim - t_inicio;
    int num_threads = omp_get_max_threads();
    double speedup = tempo_sequencial / tempo_paralelo;
    double eficiencia = speedup / num_threads;

    printf("Com n = %ld trapezoides, a estimativa \n", n);
    printf("da integral de %f ate %f = %lf \n", a, b, integral);
    
    printf("--------------------------------------------------\n");
    printf("Tempo Sequencial (Base): \t %f s\n", tempo_sequencial);
    printf("Tempo Paralelo: \t\t %f s\n", tempo_paralelo);
    printf("Numero de Threads: \t %d\n", num_threads);
    printf("Speedup: \t\t\t %f\n", speedup);
    printf("Eficiencia: \t\t %f\n", eficiencia);
    printf("--------------------------------------------------\n");

    return(0);
}