#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "especies.h"

void crearLista(lista *ptrEspecies) {
    // Inicializa la estructura que contendra los datos de las especies.
    ptrEspecies->longitud = 0;
}

int esVacia(const lista *list) {
    return list->longitud == 0;
}

void insertar(lista *ptrLista, int posicion, especie *dato) {
    // Inserta una especie en la pokedex.
    if (posicion <= ptrLista->longitud && posicion >= 0 && ptrLista->longitud + 1 <= NUM_ESPECIES) {
        if (posicion < ptrLista->longitud) {
            for (int i = ptrLista->longitud - 1; i >= posicion; i--) {
                ptrLista->arrEspecies[i + 1] = ptrLista->arrEspecies[i];
            }
        }
        ptrLista->arrEspecies[posicion] = *dato;
        ptrLista->longitud++;
    }
}

const especie* consultar(const lista *ptrLista, int posicion) {
    // Retorna la especie a consultar de la pokedex.
    if (posicion < ptrLista->longitud && posicion >= 0) {
        return &ptrLista->arrEspecies[posicion];
    } else {
        return NULL;
    }
}

int longitud(const lista *ptrLista) {
    return ptrLista->longitud;
}

void eliminar(lista *ptrLista, int posicion) {
    // Elimina un elemento de la pokedex
    // pre: posSelec >= 0 && posSelec < longitud(list)
    if (posicion >= 0 && posicion < ptrLista->longitud) {
        for (int i = posicion; i < ptrLista->longitud - 1; i++) {
            ptrLista->arrEspecies[i] = ptrLista->arrEspecies[i + 1];
        }
        ptrLista->longitud--;
    }
}

void eliminarLista(lista *ptrLista) {
    ptrLista->longitud = 0;
}