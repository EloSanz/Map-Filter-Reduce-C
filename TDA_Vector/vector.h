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
    vec->vec = malloc(cant * tam);

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
    
    crearVector(mapeado, vec->capacidad, vec->tam);

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

/*Filter-AutoFilter*/
typedef int(tFilter)(const void*);
void filter(tVector* vec, tVector* vecFiltrado, tFilter filtro)
{
    void* ini = vec->vec;

    if(vec->cant_elem == 0)
        return ; //no hay nada que filtrar, puede ser opcional este if.

    if(vecFiltrado->cant_elem > 0) //tiene que devolver un vector filtrado nuevo
        destruirVector(vecFiltrado);

    crearVector(vecFiltrado, vec->capacidad, vec->tam);
    
    for(int i = 0 ; i < vec->cant_elem; i++, ini+= vec->tam)
        //{
            if(filtro(ini))
                insertarAlFinal(vecFiltrado, ini);
            //ini += vec->tam; // lo hago junto con el incremento de i++
        //}
    destruirVector(vec);
}
void autoFilter(tVector* vec, tFilter filtro)
/*
    La estrategia que elegí fue No usar int sacarDelVector(vec...);
    sino usar un vector :auxiliar: y copiar los datos al vec del parámetro
*/
{
    void* ini = vec->vec;
    tVector aux;
    if(vec->cant_elem == 0)
        return;
    crearVector(&aux, vec->capacidad, vec->tam);
    for(int i = 0; i < vec->cant_elem; i++, ini += vec->tam)
            if(filtro(ini))
                insertarAlFinal(&aux, ini);
        
    memcpy(vec->vec, aux.vec, vec->capacidad * vec->tam); //copio los datos
    vec->cant_elem = aux.cant_elem;//actualizo la cantidad de elementos que fueron filtrados

    destruirVector(&aux);//libero memoria

}

/*Reduce-AutoReduce*/
typedef void(*tReduce)(void* destino, const void* dato);
void reduce(tVector* vec, tReduce accion, void* destino)
{
    void* ini;
    if(vec->cant_elem == 0)
        return; //nada que hacer
    //Lo voy a hacer con aritmetica de punteros
                        // este casteo (void*) lo agrego para sacar el warning, aunque no debería influir
    for (ini = vec->vec ; ini < (void*) (vec->vec + vec->cant_elem * vec->tam); ini+= vec->tam)
        accion(destino, ini);

    destruirVector(vec);
}
void autoReduce(tVector* vec, tReduce accion, void* destino)
{
    void* ini = vec->vec;
    if(vec->cant_elem == 0)
        return;
    while (ini < (void*) vec->vec + vec->cant_elem * vec->tam)
    {
        accion(destino, ini);
        ini += vec->tam;
    }
    //no destruyo al vector
}