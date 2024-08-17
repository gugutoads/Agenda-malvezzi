#ifndef agendaESTATICA_H
#define agendaESTATICA_H

#include <stdio.h>
#include <string.h>
#include <conio.h>

#define MAX[100]

typedef struct contatos{   //criando uma struct para os contatos
	char nome[50];
	char email[50];
	char numero[11];
	
}contatos;

typedef struct{            //criando uma struct para agenda
	Contatos contatos [MAX];
	int total_contatos;
}agenda;

void inicializar_Agenda(Agenda *agenda);
int adicionar_Contato(Agenda *agenda, Contato contato);
int remover_Contato(Agenda *agenda, const char *nome);
Contato* buscar_Contato(Agenda *agenda, const char *nome);
void listar_Contatos(Agenda *agenda);

#endif
