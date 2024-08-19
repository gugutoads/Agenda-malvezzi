#define MAX 3
#include <stdio.h>
#include <string.h>
#include <conio.h>


struct contato {  //criando uma struct para os contatos

	char nome [50];
	int telefone;
	char email [50];
};


struct Lista {//criando a lista
    int qntd;
	struct contato dados [MAX];	
};
   
void inicializarLista(Lista *li);

