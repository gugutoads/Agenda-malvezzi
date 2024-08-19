#include "agenda.h"

// Função para inicializar a lista

void cria_lista(Lista *li) {
    li->qntd = 0; // Define o tamanho inicial como 0
}

int tamanho_lista(Lista* li) {
	if(li == NULL)
	    return -1;
    else
        return li->qntd;
} 

