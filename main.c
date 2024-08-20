#include <stdio.h>
#include <stdlib.h>
#include "agenda.h"

void exibirMenu() { //função para exibir o menu
    printf("\n===MENU:===\n");
    printf("\n1. Inserir Contato\n");
    printf("2. Remover Contato\n");
    printf("3. Procurar Contato\n");
    printf("4. Listar Contatos\n");
    printf("5. Sair\n");
    printf("\nEscolha uma opcao: ");
}

int main() {
    Agenda minhaAgenda; //criando uma variavel do tipo agenda para manipular a lista
    inicializarAgenda(&minhaAgenda); //iniciando a agenda
    char nome[50], numero[15], email[50]; //variaveis para armazenar os dados
    int opcao;
    
    do {
    	system("cls"); //limpar a tela
        exibirMenu(); //exibindo o menu
        scanf("%d", &opcao); // le a opção do usuário
        getchar(); // Limpa o buffer do teclado

        switch (opcao) {
            case 1: {
                printf("Digite o nome: ");
                fgets(nome, sizeof(nome), stdin); //le o nome
                nome[strcspn(nome, "\n")] = 0; // Remove a nova linha
                printf("Digite o número: ");
                fgets(numero, sizeof(numero), stdin); //le o numero
                numero[strcspn(numero, "\n")] = 0; // Remove a nova linha
                printf("Digite o email: ");
                fgets(email, sizeof(email), stdin);//le o email
                email[strcspn(email, "\n")] = 0; // Remove a nova linha

                if (inserirContato(&minhaAgenda, nome, numero, email)) { //se a inserção retornar valor positivo
                    printf("Contato inserido com sucesso!\n");
                    system("pause");
                } 
				else {// se a função retornar valor negativo
                    printf("Não foi possível inserir o contato.\n");
                    system("pause");
                 }
                break;
            }
            case 2: 
                printf("Digite o nome do contato a ser removido: ");
                fgets(nome, sizeof(nome), stdin); // le a opcao do usuario
                nome[strcspn(nome, "\n")] = 0; // Remove a nova linha

                if (removerContato(&minhaAgenda, nome)) { //se a função retornar valor positivo
                    printf("Contato removido com sucesso!\n");
                    system("pause");
                } 
				else {//se a função retornar valor negativo
                    printf("Contato não encontrado!\n");
                    system("pause");
                }
                break;
            
            case 3: {                
                printf("Digite o nome do contato a ser procurado: ");
                fgets(nome, sizeof(nome), stdin);//le a opcao do usuario
                nome[strcspn(nome, "\n")] = 0; // Remove a nova linha

                procurarContato(&minhaAgenda, nome); // função para procurar contato

                system("pause");
                
                break;
               }
            case 4:
                listarContatos(&minhaAgenda); //função para listar os contatos
                system("pause");
                break;

                
            default:;
        }
    } 
	while (opcao != 5);

    return 0;
}


