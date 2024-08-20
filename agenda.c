#include <stdio.h>
#include <string.h>
#include "agenda.h"

// Fun��o para inicializar a agenda
void inicializarAgenda(Agenda *agenda) {
    agenda->tamanho = 0; // Define o tamanho inicial como 0
}

// Fun��o para inserir um contato
int inserirContato(Agenda *agenda, const char *nome, const char *numero, const char *email) {
    if (agenda->tamanho >= MAX_CONTATOS) {
        return 0; // Agenda cheia
    }
    strcpy(agenda->contatos[agenda->tamanho].nome, nome);
    strcpy(agenda->contatos[agenda->tamanho].numero, numero);
    strcpy(agenda->contatos[agenda->tamanho].email, email);
    agenda->tamanho++;
    return 1; // Inser��o bem-sucedida
}

// Fun��o para remover um contato
int removerContato(Agenda *agenda, const char *nome) {
    for (int i = 0; i < agenda->tamanho; i++) {
        if (strcmp(agenda->contatos[i].nome, nome) == 0) {
            // Move os contatos para preencher o espa�o
            for (int j = i; j < agenda->tamanho - 1; j++) {
                agenda->contatos[j] = agenda->contatos[j + 1];
            }
            agenda->tamanho--;
            return 1; // Remo��o bem-sucedida
        }
    }
    return 0; // Contato n�o encontrado
}

// Fun��o para procurar um contato
void procurarContato(Agenda *agenda, const char *nome) {
    int encontrado = 0; // Flag para verificar se o contato foi encontrado
    for (int i = 0; i < agenda->tamanho; i++) {
        if (strcmp(agenda->contatos[i].nome, nome) == 0) {
            printf("Contato encontrado: Nome: %s, N�mero: %s, Email: %s\n", 
                   agenda->contatos[i].nome, 
                   agenda->contatos[i].numero, 
                   agenda->contatos[i].email);
            encontrado = 1; // Define a flag como encontrada
            break; // Sai do loop ap�s encontrar
        }
    }
    if (!encontrado) { // Se n�o foi encontrado
        printf("Contato n�o encontrado!\n");
    }
}
// Fun��o para listar todos os contatos
void listarContatos(Agenda *agenda) {
    if (agenda->tamanho == 0) {
        printf("Agenda vazia.\n");
        return;
    }
    printf("Contatos:\n");
    for (int i = 0; i < agenda->tamanho; i++) {
        printf("Nome: %s, N�mero: %s, Email: %s\n", 
               agenda->contatos[i].nome, 
               agenda->contatos[i].numero, 
               agenda->contatos[i].email);
    }
}
