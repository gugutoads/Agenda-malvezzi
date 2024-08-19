#define MAX 3 // Tamanho máximo da lista
#include <stdio.h>
#include <string.h>
#include <conio.h>

struct Lista{
    int elementos[MAX]; // Array para armazenar os elementos
    int qntd;             // Número atual de elementos na lista
};

struct contato{
   char nome[50];
   int	telefone;
   char email[50];
};

// Função para inicializar a lista
void cria_lista(Lista *li);

int tamanho_lista(Lista* li);
