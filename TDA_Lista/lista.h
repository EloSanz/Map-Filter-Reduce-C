#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN(X,Y) (X<Y)? X : Y;
typedef struct snodito
{
    void* info;
    unsigned tam;
    struct snodito* sig;
}tNodo;

typedef tNodo* tLista;
/*Lista Simplemente enlazada*/
void crearLista(tLista* pl)
{
    *pl = NULL;
}
int ponerEnListaAlPrincipio(tLista* pl, const void* dato, unsigned tam)
{
    tNodo* nue = malloc(sizeof(tNodo));
    if(!nue || !(nue->info = malloc(tam)))
    {
        free(nue);
        return 0;
    }
    
    memcpy(nue->info, dato, tam);
    nue->tam = tam;
    nue->sig = *pl;
    *pl = nue;

    return 1;
} 
int ponerEnListaAlFinal(tLista* pl, const void* dato, unsigned tam)
{
    tNodo* nue = malloc(sizeof(tNodo));
    if(!nue || !(nue->info = malloc(tam)))
    {
        free(nue);
        return 0;
    }
    
    memcpy(nue->info, dato, tam);
    nue->tam = tam;

    while (*pl)
        pl = &(*pl)->sig;
    
    nue->sig = *pl;
    *pl = nue;

    return 1;
} 
void recorrerLista(tLista* pl, void accion(void*))
{
    while (*pl)
    {
        accion((*pl)->info);
        pl = &(*pl)->sig;
    }   
}
void vaciarLista(tLista* pl)
{
    while (*pl)
    {
        tNodo* aux = *pl;
        *pl = aux->sig;
        free(aux);
    }
}

typedef int(*tFiltro)(const void*);
/*Filter - AutoFilter*/
void filter(tLista* nueva, const tLista* pl, tFiltro filtro)
{
    void* aux;
    if(!filtro)
        return ;
    if(*nueva)
        vaciarLista(nueva);
 
    while (*pl){
        if(filtro( (*pl)->info) == 1 )
            {
                aux = malloc((*pl)->tam);
                if(!aux)
                    {
                        vaciarLista(nueva);
                        return ;
                    }
                memcpy(aux, (*pl)->info, (*pl)->tam);
                if (!ponerEnListaAlFinal(nueva, aux, (*pl)->tam))
                    {
                        vaciarLista(nueva);
                        free(aux);
                        return ;
                    }
            }
        pl = &(*pl)->sig;
    }
    free(aux);
}
void autoFilter(tLista* pl, tFiltro filtro)
{
    if(!filtro)
        return;

    while (*pl)
    {
        if(filtro((*pl)->info) == 0)
            {
                tNodo* elim = *pl;
                (*pl) = elim->sig;
                free(elim->info);
                free(elim);
            }
        else
            pl = &(*pl)->sig;
    }
}

typedef void(*tAccionMap)(void*);
/*Map - AutoMap*/
int map(tLista* nueva, const tLista* pl, tAccionMap accion){
    
    if(!accion)
        return 0;
    void* aux = NULL; 
    if(*nueva) vaciarLista(nueva);

    while (*pl)
    {
        aux = malloc((*pl)->tam);
        if(!aux){
                vaciarLista(nueva);
                return 0;
            }
        memcpy(aux, (*pl)->info, (*pl)->tam);
        accion(aux);
        if (!ponerEnListaAlFinal(nueva, aux, (*pl)->tam) )
            {
                vaciarLista(nueva);
                free(aux);
                return 0;
            }
        pl = &(*pl)->sig;
    }
    if(aux)
        free(aux);
    return 1;
}
void autoMap(tLista* pl, tAccionMap accion){
    while (*pl)
    {
        accion((*pl)->info);
        pl = &(*pl)->sig;
    }
}

typedef void(*tAcumular)(void*, const void*);
/*Reduce - AutoReduce*/
void reduce/*!const*/(tLista* pl, tAcumular acumular, void* destino){
    while (*pl)
    {
        tNodo* elim = *pl;
        acumular(destino, elim->info);
        *pl = elim->sig;
        free(elim->info);
        free(elim);
    }
    //*pl = NULL;
}
void autoReduce(const tLista* pl, tAcumular acumular, void* destino)//no destruye la lista
{
    while (*pl)
    {
        acumular(destino, (*pl)->info);
        pl = &(*pl)->sig;
    }
}