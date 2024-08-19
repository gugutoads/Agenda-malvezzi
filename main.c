#include <stdio.h>
#include <stdlib.h>
#include "agenda.h"

void exibirMenu() {
    printf("\n===MENU:===\n");
    printf("\n1. Inserir Contato\n");
    printf("2. Remover Contato\n");
    printf("3. Procurar Contato\n");
    printf("4. Listar Contatos\n");
    printf("5. Sair\n");
    printf("\nEscolha uma opção: ");
}

int main() {
    Agenda minhaAgenda;
    inicializarAgenda(&minhaAgenda);
    int opcao;
    
    do {
    	system("cls"); //limpar a tela
        exibirMenu();
        scanf("%d", &opcao);
        getchar(); // Limpa o buffer do teclado

        switch (opcao) {
            case 1: {
                char nome[50], numero[15], email[50];
                printf("Digite o nome: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = 0; // Remove a nova linha
                printf("Digite o número: ");
                fgets(numero, sizeof(numero), stdin);
                numero[strcspn(numero, "\n")] = 0; // Remove a nova linha
                printf("Digite o email: ");
                fgets(email, sizeof(email), stdin);
                email[strcspn(email, "\n")] = 0; // Remove a nova linha

                if (inserirContato(&minhaAgenda, nome, numero, email)) {
                    printf("Contato inserido com sucesso!\n");
                    system("pause");
                } else {
                    printf("Agenda cheia! Não foi possível inserir o contato.\n");
                    system("pause");
                }
                break;
            }
            case 2: {
                char nome[50];
                printf("Digite o nome do contato a ser removido: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = 0; // Remove a nova linha

                if (removerContato(&minhaAgenda, nome)) {
                    printf("Contato removido com sucesso!\n");
                    system("pause");
                } else {
                    printf("Contato não encontrado!\n");
                    system("pause");
                }
                break;
            }
            case 3: {
                char nome[50];
                printf("Digite o nome do contato a ser procurado: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = 0; // Remove a nova linha

                Contato *contato = procurarContato(&minhaAgenda, nome);
                if (contato) {
                    printf("Contato encontrado: Nome: %s, Número: %s, Email: %s\n", 
                           contato->nome, contato->numero, contato->email);
                           system("pause");
                } 
				else {
                    printf("Contato não encontrado!\n");
                    system("pause");
                }
                break;
            }
            case 4:
                listarContatos(&minhaAgenda);
                system("pause");
                break;
            case 5:
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 5);

    return 0;
}


