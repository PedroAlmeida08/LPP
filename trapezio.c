/*
  Para compilar e executar:
  gcc trapezio.c -o trapezio -lm
  time ./trapezio
*/

#include <stdio.h>
#include <math.h>

float f(float x) {
    return pow(x, 2);
}

int main(void) {

    float integral;
    float a, b;
    int n;
    float h;
    int i;

    printf("Entre os limites de integração [a, b] e o número de trapezoides (n):\n");
    scanf("%f %f %d", &a, &b, &n);

    h = (b - a) / n;

    integral = (f(a) + f(b)) / 2.0;

    for (i = 1; i < n; i++) {
        float x = a + i * h;
        integral += f(x);
    }

    integral *= h;

    printf("\nCom n = %d trapezoides, a estimativa da integral é:\n", n);
    printf("Integral de %f até %f = %f\n", a, b, integral);

    return 0;
}