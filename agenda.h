#define MAX 3 // Tamanho m�ximo da lista
#include <stdio.h>
#include <string.h>
#include <conio.h>

struct Lista{
    int elementos[MAX]; // Array para armazenar os elementos
    int qntd;             // N�mero atual de elementos na lista
};

struct contato{
   char nome[50];
   int	telefone;
   char email[50];
};

// Fun��o para inicializar a lista
void cria_lista(Lista *li);

int tamanho_lista(Lista* li);
