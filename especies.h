#ifndef ESPECIES_H
#define ESPECIES_H
#define NUM_ESPECIES 150
#define MAX_NOMBRE 50
#define MAX_NOMBRE_TIPO 50

typedef struct especie{
    char nombre[MAX_NOMBRE], primerTipo[MAX_NOMBRE_TIPO], segundoTipo[MAX_NOMBRE_TIPO];
    int numero, hpBase, ataqueBase, defensaBase, velocidadBase;
} especie;

typedef struct lista {
    especie arrEspecies[NUM_ESPECIES];
    int longitud;
} lista;

void crearLista(lista*);
int esVacia(const lista*);
void insertar(lista*, int, especie*);
const especie* consultar(const lista*, int);
int longitud(const lista*);
void eliminar(lista*, int);
void eliminarLista(lista*);
#endif