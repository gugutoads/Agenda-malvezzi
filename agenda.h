<<<<<<< HEAD
#define MAX 3
#include <stdio.h>
#include <string.h>
#include <conio.h>
=======
#ifndef agendaESTATICA_H
#define agendaESTATICA_H
>>>>>>> 01bcedcb8c97c6e264fc7555479a518ca3c41a5a

#include <stdio.h>
#include <string.h>
#include <conio.h>

#define MAX[100]

<<<<<<< HEAD
=======
typedef struct contatos{   //criando uma struct para os contatos
	char nome[50];
	char email[50];
	char numero[11];
	
}contatos;

typedef struct{            //criando uma struct para agenda
	Contatos contatos [MAX];
	int total_contatos;
}agenda;
>>>>>>> 01bcedcb8c97c6e264fc7555479a518ca3c41a5a

void inicializar_Agenda(Agenda *agenda);
int adicionar_Contato(Agenda *agenda, Contato contato);
int remover_Contato(Agenda *agenda, const char *nome);
Contato* buscar_Contato(Agenda *agenda, const char *nome);
void listar_Contatos(Agenda *agenda);

#endif
