#include <stdio.h>
#include "pokedex.h"
#include "tabla.h"

int main() {
    pokedex miPokedex;
    crearPokedex(&miPokedex);
    if (cargarPokedex(&miPokedex, "especies.txt")) {
        //mostrarPokedex(&miPokedex);
        //consultarEspecie(buscarPorNumero(&miPokedex, 25));
    }
    eliminarPokedex(&miPokedex);
    return 0;
}