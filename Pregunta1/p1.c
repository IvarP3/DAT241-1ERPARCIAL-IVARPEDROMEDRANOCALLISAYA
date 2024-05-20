#include "stdio.h"
int suma(int *a, int *b)
{
  return *a+*b;
}
int resta(int *a, int *b)
{
  return *a-*b;
}
int multi(int *a, int *b)
{
  int i,s, resu;
  s=*b;
  resu=*b;
  for(i=0; i<*a-1; i++){
    resu=resu+s;
  }
  return resu;
}
int div(int *a, int *b)
{
    int i,c;
    c=0;
    while(*a>=*b){
      *a=*a-*b;
      c=c+1;
    }
    return c;
}
void main ()
{
  int a,b;
  printf("Introduce dos numeros: \n");
  scanf("%d", &a);
  scanf("%d", &b);
  printf("La suma es: %d \n",suma(&a,&b));
  printf("La resta es: %d \n",resta(&a,&b));
  printf("La multiplicacion es: %d \n",multi(&a,&b));
  if (b != 0)
    printf("La division es: %d \n",div(&a,&b));
  else
    printf("No existe division entre cero \n");
}
