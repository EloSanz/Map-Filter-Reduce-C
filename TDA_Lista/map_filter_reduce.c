#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

void mostrarInt(void* entero)
{
    printf("%d ", *((int*) entero));
}
int filtrarPares(const void* dato)
{
    return *((int*)dato) % 2 == 0;
}
void cuadrado(void* dato)
{
    int* aux = (int*) dato;
    *aux = (*aux) * (*aux);
    dato = aux;
}
void sumarEnteros(void* destino, const void* dato)
{
    int* aux = (int*)destino;
    int* aux2 = (int*)dato;
    *aux += *aux2;
    destino = aux;
}
void testFilter()
{
    tLista lista, pares;
    crearLista(&lista);
    crearLista(&pares);

    for(int i = 1; i <=10; i++)
        ponerEnListaAlFinal(&lista, &i, sizeof(int));
    
    filter(&pares, &lista, filtrarPares);
    recorrerLista(&pares, mostrarInt);
}
void testMap()
{
    tLista lista, listaAlCuadrado;
    crearLista(&lista);
    crearLista(&listaAlCuadrado);

    for(int i = 1; i <=10; i++)
        ponerEnListaAlFinal(&lista, &i, sizeof(int));
    
    map(&listaAlCuadrado, &lista, cuadrado);
    autoMap(&listaAlCuadrado, mostrarInt);
    
}
void testReduce()
{
    int suma = 0;
    tLista lista;
    crearLista(&lista);
    for(int i = 1; i <=100; i++)
        ponerEnListaAlFinal(&lista, &i, sizeof(int));
    //reduce(&lista, sumarEnteros, &suma);      //destruye la lista
    autoReduce(&lista, sumarEnteros, &suma);    //no destruye la lista
    
    recorrerLista(&lista, mostrarInt);
    printf("\nSuma total: %d\n", suma);
}
int main()
{
    //testFilter();   
    //testMap();
    testReduce();
    return 0;
}
