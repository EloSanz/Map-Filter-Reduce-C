#include "vector.h"

void mostrarInt(void* dato)
{
    printf("%d ", *(int*)dato);
}
void duplicar(void* dato)
{
    int* aux = (int*)dato;
    *aux = (*aux) * 2 ;
    dato = aux;
}
void testMap()
{
    tVector vecEnteros;
    tVector vecx2;
    int n = 10;
    crearVector(&vecEnteros, n, sizeof(int));

    for(int i = 0; i < n; i++)
        insertarAlFinal(&vecEnteros, &i);
    autoMap(&vecEnteros, mostrarInt);

    map(&vecEnteros, &vecx2, duplicar);
    puts("");
    autoMap(&vecx2, mostrarInt);

}

int main()
{
    testMap();
    return 1;
}