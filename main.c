#include <stdio.h>
#include "agenda.h"

// Outras opera��es podem ser implementadas aqui

int main() {
    Lista minhaLista;
    inicializarLista(&minhaLista);

    printf("Lista inicializada com tamanho: %d\n", minhaLista.tamanho);
    return 0;
}
