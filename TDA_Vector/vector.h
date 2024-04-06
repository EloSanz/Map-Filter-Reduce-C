#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct 
{
    char* vec;
    int cant_elem;
    int capacidad;
    unsigned tam;
}tVector;

int crearVector(tVector* vec, int cant, unsigned tam)
{
    if(cant <= 0)
        return 0;
    vec->vec = (char*)malloc(cant * tam);

    if(!vec->vec) //if(vec->info == NULL) //fallo al asignar memoria
        return 0;
    vec->cant_elem = 0;
    vec->capacidad = cant;
    vec->tam = tam;
    return 1;
}
int insertarAlFinal(tVector* vec, const void* dato)
{
    if(vec->cant_elem == vec->capacidad)
        return 0;

    memcpy(vec->vec + vec->cant_elem * vec->tam , dato, vec->tam); 
    vec->cant_elem++;
    return 1;
}
void destruirVector(tVector* vec)
{
    free(vec->vec);
    vec->cant_elem = 0;
}
/*Map-AutoMap*/
typedef void(tAccion)(void*);
void map(tVector* vec, tVector* mapeado, tAccion accion)
{
    void* ini = vec->vec;
    if(vec->cant_elem == 0) // no hay nada para mapear
        return;
    if(mapeado->cant_elem > 0)//si tiene algo, lo borro
        destruirVector(mapeado);
    
    crearVector(mapeado, vec->cant_elem, vec->tam);

    for(int i = 0; i < vec->cant_elem; i++, ini += vec->tam)
            {
                accion(ini);
                insertarAlFinal(mapeado, ini);
            }
    destruirVector(vec);
}

void autoMap(tVector* vec, tAccion accion)
{
    int i = 0;
    void* aux = vec->vec;
    if(vec->cant_elem == 0)
        return ;
    while (i < vec->cant_elem)
    {
        accion(aux);
        i++;
        aux += vec->tam;
    }
}