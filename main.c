#include <stdio.h>
#include "agenda.h"

// Outras operações podem ser implementadas aqui

int main() {
    Lista minhaLista;
    inicializarLista(&minhaLista);

    printf("Lista inicializada com tamanho: %d\n", minhaLista.tamanho);
    return 0;
}
