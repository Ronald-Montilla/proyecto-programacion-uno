#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "pokedex.h"
#include "especies.h"

void crearPokedex(pokedex *ptrPokedex) {
    // Crea una pokedex vacia.
    crearLista(&ptrPokedex->especies);
}

int cargarPokedex(pokedex *ptrPokedex, const char *directorio) {
    // Carga los datos provinientes de la direccion(directorio) en la pokedex
    FILE *in = fopen(directorio, "r");
    especie pokemon;
    if (in != NULL && ptrPokedex != NULL) {
        while (fscanf(in, "%d%s%s%s%d%d%d%d", &pokemon.numero, pokemon.nombre, pokemon.primerTipo, pokemon.segundoTipo, &pokemon.hpBase, &pokemon.ataqueBase, &pokemon.defensaBase, &pokemon.velocidadBase) == 8) {
           insertar(&ptrPokedex->especies, longitud(&ptrPokedex->especies), &pokemon);
        }
        fclose(in);
        if (longitud(&ptrPokedex->especies) == 150) {
            // El retorno true indica que se cargaron las 150 especies correctamente.
            return true;
        }
    }
    // El retorno false indica que no se cargaron las especies correctamente.
    return false;
}

const especie* buscarPorNumero(const pokedex *ptrPokedex, int numero) {
    // Busca en la pokedex la especie con el numero indicado en el parametro "numero".
    if (ptrPokedex != NULL && numero <= longitud(&ptrPokedex->especies) && numero >= 1) {
        const especie *actual = consultar(&ptrPokedex->especies, numero - 1);
        if (actual->numero == numero) {
            return actual;
        }
    }
    return NULL;
}

const especie* buscarPorNombre(const pokedex *ptrPokedex, const char *nombre) {
    // Busca en la pokedex la especie con el numero indicado en el parametro "nombre".
    if (nombre != NULL && ptrPokedex != NULL) {
        int actual = 0;
        while (actual < longitud(&ptrPokedex->especies)) {
            const especie *ptrEspecie = consultar(&ptrPokedex->especies, actual);
            if (strcmp(ptrEspecie->nombre, nombre) == 0) {
                return ptrEspecie;
            }
            actual++;
        }
    }
    return NULL;
}

void mostrarPokedex(const pokedex *ptrPokedex) {
    // Muestra los datos basicos de todas las especies que se encuentren en la pokedex.
    if (ptrPokedex == NULL) {
        return;
    }
    int indiceActual = 0, longuitudPokedex = longitud(&ptrPokedex->especies);
    while (indiceActual < longuitudPokedex) {
        const especie *actual = consultar(&ptrPokedex->especies, indiceActual);
        printf("Especie Numero: %d - %s\n", actual->numero, actual->nombre);
        indiceActual++;
    }
}

void consultarEspecie(const especie *pokemon) {
    // Consulta los datos completos de una especie.
    if (pokemon != NULL) {
        printf("Numero de la pokedex: %d\n", pokemon->numero);
        printf("Nombre del pokemon: %s\n", pokemon->nombre);
        printf("Tipo primario: %s\n", pokemon->primerTipo);
        printf("Tipo secundario: %s\n", pokemon->segundoTipo);
        printf("HP Base: %d\n", pokemon->hpBase);
        printf("Ataque Base: %d\n", pokemon->ataqueBase);
        printf("Defensa Base: %d\n", pokemon->defensaBase);
        printf("Velocidad Base: %d\n", pokemon->velocidadBase);
    }
}

void eliminarPokedex(pokedex *ptrPokedex) {
    // Elimina todas las especies de la pokedex.
    if (ptrPokedex == NULL) {
        return;
    }
    eliminarLista(&ptrPokedex->especies);
}