#define MAX 3 // Tamanho m�ximo da lista
#include <stdio.h>
#include <string.h>
#include <conio.h>

struct Lista{
    int elementos[MAX]; // Array para armazenar os elementos
    int tamanho;             // N�mero atual de elementos na lista
} 

// Fun��o para inicializar a lista
void inicializarLista(Lista *lista);

