#include <stdio.h>
#include <string.h>
#include "agenda.h"

// Função para inicializar a agenda
void inicializarAgenda(Agenda *agenda) {
    agenda->tamanho = 0; // Define o tamanho inicial como 0
}

// Função para inserir um contato
int inserirContato(Agenda *agenda, const char *nome, const char *numero, const char *email) {
    if (agenda->tamanho >= MAX) {// se o tamanho da agenda for igual ou maior que o limite
        return 0; // Agenda cheia
    }
    //inserindo os dados do usuário na posição vaga da agenda/lista
    strcpy(agenda->contatos[agenda->tamanho].nome, nome);
    strcpy(agenda->contatos[agenda->tamanho].numero, numero);
    strcpy(agenda->contatos[agenda->tamanho].email, email);
    
    agenda->tamanho++;//aumenta o numero de contatos na agenda
    return 1; // Inserção bem-sucedida
}

// Função para remover um contato
int removerContato(Agenda *agenda, const char *nome) {
    for (int i = 0; i < agenda->tamanho; i++) {//percorre toda a agenda
        if (strcmp(agenda->contatos[i].nome, nome) == 0) {//compara o nome que o usuario digitou com os nomes da agenda
            // Move os contatos para preencher excluir o espaço vago
            for (int j = i; j < agenda->tamanho - 1; j++) {
                agenda->contatos[j] = agenda->contatos[j + 1];
            }
            agenda->tamanho--; // diminui o numero de contatos
            return 1; // Remoção bem-sucedida
        }
    }
    return 0; // Contato não encontrado
}

// Função para procurar um contato
void procurarContato(Agenda *agenda, const char *nome) {
    int encontrado = 0; // variavel para verificar se o contato foi encontrado
    for (int i = 0; i < agenda->tamanho; i++) {//percorre toda a agenda
        if (strcmp(agenda->contatos[i].nome, nome) == 0) {//compara o nome que o usuario digitou com os nomes da agenda
            printf("Contato encontrado: Nome: %s, Número: %s, Email: %s\n", 
                   agenda->contatos[i].nome, 
                   agenda->contatos[i].numero, 
                   agenda->contatos[i].email);
            encontrado = 1; // Define a variavel como encontrada
            break; // Sai do loop após encontrar
        }
    }
    if (!encontrado) { // Se não foi encontrado
        printf("Contato não encontrado!\n");
    }
}
// Função para listar todos os contatos
void listarContatos(Agenda *agenda) {
    if (agenda->tamanho == 0) {//verifica se a agenda está vazia
        printf("Agenda vazia.\n");
        return;
    }
    printf("Contatos:\n");
    for (int i = 0; i < agenda->tamanho; i++) {//percorre toda a agenda e imprime os contatos que encontrar
        printf("Nome: %s, Número: %s, Email: %s\n", 
               agenda->contatos[i].nome, 
               agenda->contatos[i].numero, 
               agenda->contatos[i].email);
    }
}
