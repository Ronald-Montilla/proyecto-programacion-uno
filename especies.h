#ifndef ESPECIES_H
#define ESPECIES_H
#define NUM_ESPECIES 150
#define MAX_NOMBRE 50
#include "tabla.h"

typedef struct {
    char nombre[MAX_NOMBRE];
    int numero, hpBase, ataqueBase, defensaBase, velocidadBase;
    tipoPokemon primerTipo, segundoTipo;
} especie;

typedef struct {
    especie arrEspecies[NUM_ESPECIES];
    int longitud;
} lista;

void crearLista(lista*);
int esVacia(const lista*);
void insertar(lista*, int, especie*);
const especie* consultar(const lista*, int);
int longitud(const lista*);
int numMaxEspecies(void);
void eliminar(lista*, int);
void eliminarLista(lista*);
#endif