#include <stdio.h>
#include <string.h>
#include "tabla.h"

// Arreglo que contendra todos los tipos validos de tipos
static const char *tipos[NUM_TIPOS] = {"Normal", "Fuego", "Agua", "Planta", "Electrico", "Hielo", "Lucha",
"Veneno", "Tierra", "Volador", "Psiquico", "Bicho", "Roca", "Fantasma", "Dragon", "Siniestro",
"Acero", "Hada"};

static const char *ninguno = "Ninguno";
static const char *invalido = "Invalido";

/*
 * Matriz de efectividad NUM_TIPOS x NUM_TIPOS .
 * Filas: Tipo Atacante.
 * Columnas: Tipo Defensor.
 * Orden: Nor, Fue, Agu, Pla, Ele, Hie, Luc, Ven, Tie, Vol, Psi, Bic, Roc, Fan, Dra, Sin, Ace, Had
 */
static const float matrizEfectividad[NUM_TIPOS][NUM_TIPOS] = {
    /* 00 Normal    */ {1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.5f, 0.0f, 1.0f, 1.0f, 0.5f, 1.0f},
    /* 01 Fuego     */ {1.0f, 0.5f, 0.5f, 2.0f, 1.0f, 2.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 2.0f, 0.5f, 1.0f, 0.5f, 1.0f, 2.0f, 1.0f},
    /* 02 Agua      */ {1.0f, 2.0f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 2.0f, 1.0f, 1.0f, 1.0f, 2.0f, 1.0f, 0.5f, 1.0f, 1.0f, 1.0f},
    /* 03 Planta    */ {1.0f, 0.5f, 2.0f, 0.5f, 1.0f, 1.0f, 1.0f, 0.5f, 2.0f, 0.5f, 1.0f, 0.5f, 2.0f, 1.0f, 0.5f, 1.0f, 0.5f, 1.0f},
    /* 04 Electrico */ {1.0f, 1.0f, 2.0f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 2.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.5f, 1.0f, 1.0f, 1.0f},
    /* 05 Hielo     */ {1.0f, 0.5f, 0.5f, 2.0f, 1.0f, 0.5f, 1.0f, 1.0f, 2.0f, 2.0f, 1.0f, 1.0f, 1.0f, 1.0f, 2.0f, 1.0f, 0.5f, 1.0f},
    /* 06 Lucha     */ {2.0f, 1.0f, 1.0f, 1.0f, 1.0f, 2.0f, 1.0f, 0.5f, 1.0f, 0.5f, 0.5f, 0.5f, 2.0f, 0.0f, 1.0f, 2.0f, 2.0f, 0.5f},
    /* 07 Veneno    */ {1.0f, 1.0f, 1.0f, 2.0f, 1.0f, 1.0f, 1.0f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 0.5f, 0.5f, 1.0f, 1.0f, 0.0f, 2.0f},
    /* 08 Tierra    */ {1.0f, 2.0f, 1.0f, 0.5f, 2.0f, 1.0f, 1.0f, 2.0f, 1.0f, 0.0f, 1.0f, 0.5f, 2.0f, 1.0f, 1.0f, 1.0f, 2.0f, 1.0f},
    /* 09 Volador   */ {1.0f, 1.0f, 1.0f, 2.0f, 0.5f, 1.0f, 2.0f, 1.0f, 1.0f, 1.0f, 1.0f, 2.0f, 0.5f, 1.0f, 1.0f, 1.0f, 0.5f, 1.0f},
    /* 10 Psiquico  */ {1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 2.0f, 2.0f, 1.0f, 1.0f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.5f, 1.0f},
    /* 11 Bicho     */ {1.0f, 0.5f, 1.0f, 2.0f, 1.0f, 1.0f, 0.5f, 0.5f, 1.0f, 0.5f, 2.0f, 1.0f, 1.0f, 0.5f, 1.0f, 2.0f, 0.5f, 0.5f},
    /* 12 Roca      */ {1.0f, 2.0f, 1.0f, 1.0f, 1.0f, 2.0f, 0.5f, 1.0f, 0.5f, 2.0f, 1.0f, 2.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.5f, 1.0f},
    /* 13 Fantasma  */ {0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 2.0f, 1.0f, 1.0f, 2.0f, 1.0f, 0.5f, 1.0f, 1.0f},
    /* 14 Dragon    */ {1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 2.0f, 1.0f, 0.5f, 0.0f},
    /* 15 Siniestro */ {1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.5f, 1.0f, 1.0f, 1.0f, 2.0f, 1.0f, 1.0f, 2.0f, 1.0f, 0.5f, 1.0f, 0.5f},
    /* 16 Acero     */ {1.0f, 0.5f, 0.5f, 1.0f, 0.5f, 2.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 2.0f, 1.0f, 1.0f, 1.0f, 0.5f, 2.0f},
    /* 17 Hada      */ {1.0f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 2.0f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 2.0f, 2.0f, 0.5f, 1.0f}
};

tipoPokemon descifrarTipo(const char *tipoADescifrar) {
    if (tipoADescifrar != NULL) {
        for (int i = 0; i < NUM_TIPOS; i++) {
            if (!strcmp(tipoADescifrar, tipos[i])) {
                return i;
            }
        }
        if (!strcmp(TIPO_VACIO, tipoADescifrar)) {
            return TIPO_NINGUNO;
        } else {
            return TIPO_INVALIDO;
        }
    } else {
        return TIPO_INVALIDO;
    }
}

const char* tipoAString(const tipoPokemon tipo) {
    if (tipo >= 0 && tipo < NUM_TIPOS) {
        return tipos[tipo];
    } else if (tipo == TIPO_NINGUNO) {
        return ninguno;
    } else {
        return invalido;
    }
}

tipoPokemon tipoInvalido() {
    // Retorna el tipo invalido.
    return TIPO_INVALIDO;
}

tipoPokemon tipoVacio() {
    // Retorna el equivalente a 'ningun tipo' de la tabla de tipos.
    return TIPO_NINGUNO;
}

float obtenerEfectividad(tipoPokemon atacante, tipoPokemon defPrimario, tipoPokemon defSecundario) {
    // Calcula el multiplicador de efectividad total de un ataque considerando el tipo del atacante y los dos tipos del defensor.
    // Validación del tipo del atacante y el primer tipo del defensor.
    if (atacante < 0 || atacante >= NUM_TIPOS || defPrimario < 0 || defPrimario >= NUM_TIPOS) {
        return EFECTO_NULO;
    }

    // Validación del tipo segundo tipo del defensor: debe ser TIPO_NINGUNO o un índice válido distinto del primario
    if (defSecundario != TIPO_NINGUNO && (defSecundario < 0 || defSecundario >= NUM_TIPOS || defSecundario == defPrimario)) {
        return EFECTO_NULO;
    }

    float multiplicador = matrizEfectividad[atacante][defPrimario];

    // Si el Pokémon defensor posee un segundo tipo, se consideran ambos en el cálculo final
    if (defSecundario != TIPO_NINGUNO) {
        multiplicador *= matrizEfectividad[atacante][defSecundario];
    }

    return multiplicador;
}