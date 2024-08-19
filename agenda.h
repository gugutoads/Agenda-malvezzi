#define MAX_CONTATOS 3 // Tamanho m�ximo da lista de contatos
#include <stdio.h>
#include <string.h>
#include <conio.h>

typedef struct {
    char nome[50];
    char numero[15];
    char email[50];
} Contato;

typedef struct {
    Contato contatos[MAX_CONTATOS];
    int tamanho; // N�mero atual de contatos
} Agenda;

// Fun��es para manipula��o da agenda
void inicializarAgenda(Agenda *agenda);
int inserirContato(Agenda *agenda, const char *nome, const char *numero, const char *email);
int removerContato(Agenda *agenda, const char *nome);
Contato* procurarContato(Agenda *agenda, const char *nome);
void listarContatos(Agenda *agenda);
