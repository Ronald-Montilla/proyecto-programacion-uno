#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "pokedex.h"
#include "especies.h"
#include "tabla.h"

#define MAX_LINEA 200 // Tamanio maximo de linea a leer de un archivo.
#define MAX_NOMBRE_TIPO 50

void crearPokedex(pokedex *ptrPokedex) {
    // Crea una pokedex vacia.
    crearLista(&ptrPokedex->especies);
}

bool cargarPokedex(pokedex *ptrPokedex, const char *directorio) {
    // Carga los datos provinientes de la direccion(directorio) en la pokedex
    if (ptrPokedex == NULL || directorio == NULL) {
        return false;
    }
    eliminarPokedex(ptrPokedex); // Para evitar escribir sobre una pokedex que tenia datos basura.
    FILE *in = fopen(directorio, "r");
    if (in != NULL) {
        char linea[MAX_LINEA];
        especie pokemon;
        bool bandera = true;
        while (bandera && longitud(&ptrPokedex->especies) < numMaxEspecies() && fgets(linea, sizeof(linea), in) != NULL) {
            char primerTipo[MAX_NOMBRE_TIPO], segundoTipo[MAX_NOMBRE_TIPO];
            if (sscanf(linea, "%d%49s%49s%49s%d%d%d%d", &pokemon.numero, pokemon.nombre, primerTipo, segundoTipo, &pokemon.hpBase, &pokemon.ataqueBase, &pokemon.defensaBase, &pokemon.velocidadBase) != 8) {
                bandera = false;
            } else {
                // Obtencion de los tipos(de string a tipoPokemon):
                pokemon.primerTipo = descifrarTipo(primerTipo);
                pokemon.segundoTipo = descifrarTipo(segundoTipo);
                if (esEspecieValida(&pokemon)) { // Validacion de la especie
                    insertar(&ptrPokedex->especies, longitud(&ptrPokedex->especies), &pokemon);
                } else {
                    bandera = false;
                }
            }
        }
        fclose(in);
        if (bandera && longitud(&ptrPokedex->especies) == numMaxEspecies()) {
            // El retorno true indica que se cargaron las 150 especies correctamente.
            return true;
        }
        eliminarPokedex(ptrPokedex);
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

bool esEspecieValida(const especie *ptrEspecie) {
    if (ptrEspecie == NULL) {
        return false;
    }
    // Validacion de nombre:
    if (isspace(ptrEspecie->nombre[0])) {
        return false;
    }
    // Validacion de los tipos:
    if (ptrEspecie->primerTipo == tipoInvalido() || ptrEspecie->segundoTipo == tipoInvalido() || ptrEspecie->primerTipo == tipoVacio() || ptrEspecie->primerTipo == ptrEspecie->segundoTipo) {
        return false;
    }
    // Validacion de los numeros:
    if (ptrEspecie->numero < 1 || ptrEspecie->numero > numMaxEspecies()) {
        return false;
    }
    // Validacion de las estadisticas bases:
    if (ptrEspecie->hpBase < 1 || ptrEspecie->ataqueBase < 1 || ptrEspecie->defensaBase < 1 || ptrEspecie->velocidadBase < 1) {
        return false;
    }
    return true;
}

void consultarEspecie(const especie *pokemon) {
    // Consulta los datos completos de una especie.
    if (pokemon != NULL) {
        printf("Numero de la pokedex: %d\n", pokemon->numero);
        printf("Nombre del pokemon: %s\n", pokemon->nombre);
        printf("Tipo primario: %s\n", tipoAString(pokemon->primerTipo));
        printf("Tipo secundario: %s\n", tipoAString(pokemon->segundoTipo));
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