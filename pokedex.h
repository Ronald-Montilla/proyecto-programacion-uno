#ifndef POKEDEX_H
#define POKEDEX_H
#include "especies.h"

typedef struct {
    lista especies;
} pokedex;

void crearPokedex(pokedex*);
bool cargarPokedex(pokedex*, const char*);
const especie* buscarPorNumero(const pokedex*, int);
const especie* buscarPorNombre(const pokedex*, const char*);
void mostrarPokedex(const pokedex*);
bool esEspecieValida(const especie*);
void consultarEspecie(const especie*);
void eliminarPokedex(pokedex*);

#endif