#include <stdio.h>
#include <omp.h>

int main() {
    int a, b, aux;
    int multi = 0;
    int div = 0;
    printf("Introduce dos numeros: \n");
    scanf("%d", &a);
    scanf("%d", &b);

    // Multiplicación por suma
    #pragma omp parallel for reduction(+:multi)
    for (int i = 0; i < b; i++) {
        multi = multi + a;
    }

    // División por resta
    aux = a;
    #pragma omp parallel for reduction(+:div)
    for (int i = 0; i < a ; i+=b) {
        div = div + 1;
    }

    printf("Multiplicación por suma: %d\n", multi);
    printf("División por resta: %d\n", div);

    return 0;
}