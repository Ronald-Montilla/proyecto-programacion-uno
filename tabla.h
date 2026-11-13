#ifndef TABLA_H
#define TABLA_H

#define NUM_TIPOS 18
#define MAX_NOMBRE_TIPO 50
#define TIPO_VACIO "Ninguno"

/* Multiplicadores oficiales de efectividad */
#define EFECTO_NULO         0.0f
#define EFECTO_POCO         0.5f
#define EFECTO_NORMAL       1.0f
#define EFECTO_MUY_EFECTIVO 2.0f

typedef enum tipoPokemon {
    TIPO_INVALIDO  = -2,
    TIPO_NINGUNO   = -1,
    TIPO_NORMAL    = 0,
    TIPO_FUEGO     = 1,
    TIPO_AGUA      = 2,
    TIPO_PLANTA    = 3,
    TIPO_ELECTRICO = 4,
    TIPO_HIELO     = 5,
    TIPO_LUCHA     = 6,
    TIPO_VENENO    = 7,
    TIPO_TIERRA    = 8,
    TIPO_VOLADOR   = 9,
    TIPO_PSIQUICO  = 10,
    TIPO_BICHO     = 11,
    TIPO_ROCA      = 12,
    TIPO_FANTASMA  = 13,
    TIPO_DRAGON    = 14,
    TIPO_SINIESTRO = 15,
    TIPO_ACERO     = 16,
    TIPO_HADA      = 17
} tipoPokemon;

tipoPokemon descifrarTipo(const char*);
const char* tipoAString(const tipoPokemon);
tipoPokemon tipoInvalido();
tipoPokemon tipoVacio();

float obtenerEfectividad(tipoPokemon atacante, tipoPokemon defPrimario, tipoPokemon defSecundario);

#endif