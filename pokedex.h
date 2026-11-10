#ifndef POKEDEX_H
#define POKEDEX_H
#include "especies.h"

typedef struct pokedex {
    lista especies;
} pokedex;

void crearPokedex(pokedex*);
int cargarPokedex(pokedex*, const char*);
const especie* buscarPorNumero(const pokedex*, int);
const especie* buscarPorNombre(const pokedex*, const char*);
void mostrarPokedex(const pokedex*);
void consultarEspecie(const especie*);
void eliminarPokedex(pokedex*);

#endif