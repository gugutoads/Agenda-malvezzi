#define MAX 3 // Tamanho máximo da lista
#include <stdio.h>
#include <string.h>
#include <conio.h>

struct Lista{
    int elementos[MAX]; // Array para armazenar os elementos
    int tamanho;             // Número atual de elementos na lista
} 

// Função para inicializar a lista
void inicializarLista(Lista *lista);

