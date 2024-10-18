#include "vector.h"


void mostrarInt(void* dato)
{
    printf("%d ", *(int*)dato);
}
// acciones
void duplicar(void* dato)
{
    int* aux = (int*)dato;
    *aux = (*aux) * 2 ;
    dato = aux;
}
// filtros
int filtrar_mayores_10(const void* dato)
{
    int* aux = (int*)dato;
    if(*aux > 10)//si es mayor a 10
        return 1;
    //else 
    return 0;
    // o se pudo hacer:
    //return (*(int*)dato) > 10;
}
// acciones de reduce
void acumularEnteros(void* destino, const void* dato)
{
    int* auxDestino = (int*) destino;
    int* auxDato = (int*) dato;
    *auxDestino += *auxDato;
}
// tests
void testMap()
{
    printf("\n******Test Map:******\n");

    tVector vecEnteros;
    tVector vecx2;
    int n = 10;
    crearVector(&vecEnteros, n, sizeof(int));

    for(int i = 0; i < n; i++)
        insertarAlFinal(&vecEnteros, &i);

    autoMap(&vecEnteros, mostrarInt);

    map(&vecEnteros, &vecx2, duplicar); //destruye a vecEnteros y deja el nuevo en vecx2

    puts("");
    autoMap(&vecx2, mostrarInt);

}
void testFilter()
{
    printf("\n******Test Filter:******\n");

    tVector enteros, mayores_10;
    crearVector(&enteros, 100, sizeof(int));
    for(int i = 1; i <= 100; i++)
        insertarAlFinal(&enteros, &i);

    filter(&enteros, &mayores_10, filtrar_mayores_10);
    autoMap(&mayores_10, mostrarInt);
}
void testAutoFilter()
{
printf("\n******Test autoFilter:******\n");
    tVector enteros;
    crearVector(&enteros, 100, sizeof(int));
    for(int i = 1; i <= 100; i++)
        insertarAlFinal(&enteros, &i);
    autoFilter(&enteros, filtrar_mayores_10);
    autoMap(&enteros, mostrarInt);//ahora solo debería mostrar pares mayores a 10
}
void testReduce()
{
    int suma = 0;
    tVector enteros;
    crearVector(&enteros, 100, sizeof(int));
    
    for(int i = 1; i <= 100; i++)
        insertarAlFinal(&enteros, &i);
    
    reduce(&enteros, acumularEnteros, &suma);
    //autoReduce(&enteros, acumularEnteros, &suma);

    printf("La suma total es: %d\n", suma);
    autoMap(&enteros, mostrarInt); // si se usa autoReduce sí se debería ver el vector
}


int main()
{
    //testMap();
    //testFilter();
    //testAutoFilter();
    testReduce();
    
    return 1;
}
