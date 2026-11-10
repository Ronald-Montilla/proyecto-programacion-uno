#include <stdio.h>
#include "pokedex.h"

int main() {
    pokedex miPokedex;
    crearPokedex(&miPokedex);
    if (cargarPokedex(&miPokedex, "especies.txt")) {
        //mostrarPokedex(&miPokedex);
        consultarEspecie(buscarPorNumero(&miPokedex, 15));
    }
    eliminarPokedex(&miPokedex);
    return 0;
}