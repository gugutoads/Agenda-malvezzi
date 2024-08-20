#define MAX 3 // Tamanho máximo da lista de contatos
#include <stdio.h>
#include <string.h>
#include <conio.h>

typedef struct {
    char nome[50];
    char numero[15];
    char email[50];
} Contato;

typedef struct {
    Contato contatos[MAX];
    int tamanho; // Número atual de contatos
} Agenda;

// Funções para manipulação da agenda
void inicializarAgenda(Agenda *agenda);
int inserirContato(Agenda *agenda, const char *nome, const char *numero, const char *email);
int removerContato(Agenda *agenda, const char *nome);
void procurarContato(Agenda *agenda, const char *nome);
void listarContatos(Agenda *agenda);
