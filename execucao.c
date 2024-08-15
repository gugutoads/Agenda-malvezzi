#include <stdlib.h>
#include "biblioteca.h"
#include <stdio.h>
#include <conio.h>
#include <string.h>


void remove_conta(FILE *arquivo, int numero_conta)
 { 
   char tipo_conta;
   fun funcionario;
   cp conta_poupanca; // declara uma variavel para armazenar as contas lidas do arquivo
   cc conta_corrente; 
   int encontrado = 0; // Variável para indicar se a conta foi encontrada

   if(arquivo != NULL)
   {
    // Procura em contas poupança
    fseek(arquivo, 0L, SEEK_SET); // Move o ponteiro do arquivo para o início  
    while (fread(&tipo_conta, sizeof(char), 1, arquivo)) // Lê o tipo da conta até atingir o final do arquivo
        {
           if (tipo_conta == 'P') // Conta Poupança
              { 
                  if (fread(&conta_poupanca, sizeof(conta_poupanca), 1, arquivo)) // Lê cada conta poupança do arquivo enquanto fread não tiver problema ou chegar no fim do arquivo
      	            { 
                       if (conta_poupanca.numero_conta == numero_conta && conta_poupanca.excluido == 0) // Verifica se o número da conta é o mesmo e se a conta ainda não foi excluida
	    	              {  	
                            conta_poupanca.excluido = 1; // Marca a conta como excluída
            
		                    fseek(arquivo, -sizeof(conta_poupanca), SEEK_CUR); // Move o ponteiro do arquivo de volta para a posição da conta lida
                            fwrite(&conta_poupanca, sizeof(conta_poupanca), 1, arquivo); // Escreve a conta marcada como excluida no arquivo           
			   
			                encontrado = 1; // Indica que a conta foi encontrada
            
			                printf("\n\nA conta foi excluida com sucesso\n"); // se a conta foi excluida mostra a mensagem
            
		                    break; // Sai do loop se a conta foi excluida
                          }
                   }       
             } 
            // Procura em contas correntes    
           else if (tipo_conta == 'C') // Conta Corrente
             {
                if (fread(&conta_corrente, sizeof(conta_corrente), 1, arquivo)) // Lê cada conta corrente do arquivo enquanto fread retornar 1
	              {				   
                     if (conta_corrente.numero_conta == numero_conta && conta_corrente.excluido == 0) // Verifica se o número da conta é o mesmo e se a conta ainda não foi excluida
		                {      
			               conta_corrente.excluido = 1; // Marca a conta como excluída
              
			               fseek(arquivo, -sizeof(conta_corrente), SEEK_CUR); // Move o ponteiro do arquivo de volta para a posição da conta lida
                           fwrite(&conta_corrente, sizeof(conta_corrente), 1, arquivo); // Escreve a conta marcada como excluida no arquivo
             
			               encontrado = 1; // Indica que a conta foi encontrada
           
		                   printf("\n\nA conta foi excluida com sucesso\n"); // se a conta foi excluida mostra a mensagem
            
			               break; // Sai do loop se a conta foi excluida
                        }
                  } 
             }
             
           else if (tipo_conta == 'F')
            {
              if (fread(&funcionario, sizeof(funcionario), 1, arquivo)) // Lê a estrutura da conta corrente
                {                   	                                                    
				   encontrado = 0;
			    }	      
		    }
        }
        
        if(encontrado == 0) // Se a conta não foi encontrada	       
        printf("\n\nConta nao encontrada\n"); 
   }
   else
   printf("Erro ao abrir o arquivo");
}






int insere_funcionario(FILE *arquivo, fun funcionario)
{
    char tipo_conta = 'F';
	
	   if (arquivo != NULL) // verifica se o arquivo existe e executa a função
	     {
	        fseek(arquivo, 0L, SEEK_END); // Move o ponteiro do arquivo para o início.
            funcionario.excluido = 0;	  		  
		   
		    if (fwrite(&tipo_conta, sizeof(tipo_conta), 1, arquivo) && fwrite(&funcionario, sizeof(funcionario), 1, arquivo))
		    return 1;
	     }
	     return 0;
}




int Insere_cp(FILE *arquivo, cp conta) 
{
    char tipo_conta = 'P'; // Identificador do tipo de conta

    if (arquivo != NULL) 
    {
        fseek(arquivo, 0L, SEEK_END); // Move o ponteiro do arquivo para o final
        conta.excluido = 0; // Define a conta como não excluida

        if (fwrite(&tipo_conta, sizeof(tipo_conta), 1, arquivo) && fwrite(&conta, sizeof(conta), 1, arquivo)) // Escreve o tipo da conta e a conta no arquivo     
        return 1; // Retorna 1 se a escrita foi bem-sucedida
    
    }
    return 0; // Retorna 0 se houve algum problema
}




int Insere_cc(FILE *arquivo, cc conta) 
{
    char tipo_conta = 'C'; // Identificador do tipo de conta

    if (arquivo != NULL) 
    {
        fseek(arquivo, 0L, SEEK_END); // Move o ponteiro do arquivo para o final
        conta.excluido = 0; // Define a conta como não excluida

        if (fwrite(&tipo_conta, sizeof(tipo_conta), 1, arquivo) &&  fwrite(&conta, sizeof(conta), 1, arquivo)) // Escreve o tipo da conta e a conta no arquivo     
        return 1; // Retorna 1 se a escrita foi bem-sucedida
        
    }
    return 0; // Retorna 0 se houve algum problema
}



void altera_funcionario(FILE *arquivo, int codigo)
{
   char tipo_conta;
   fun funcionario;
   int encontrado = 0;
   
if(arquivo != NULL)
   { 
        fseek(arquivo, 0L, SEEK_SET); // move o ponteiro do arquivo para o inicio	
    
        while (fread(&tipo_conta, sizeof(char), 1, arquivo)) // Lê o tipo da conta até atingir o final do arquivo
		  { 
            if (tipo_conta == 'F') 
			   { // Tipo Funcionário
                  long pos = ftell(arquivo); // Salva a posição atual do ponteiro
                  if (fread(&funcionario, sizeof(fun), 1, arquivo)) // Lê a estrutura do funcionário
				     { 
                        if (funcionario.codigo == codigo)
						   {
                              system("cls");
                              printf("\nFuncionario encontrado.");
                              printf("\nDIGITE OS NOVOS DADOS DO FUNCIONARIO");					 	

                              printf("\n\nNovo codigo: ");
                              scanf("%d", &funcionario.codigo);
                              while (getchar() != '\n');
                        
                              printf("Novo cargo: ");
                              fgets(funcionario.cargo, sizeof(funcionario.cargo), stdin);
                              funcionario.cargo[strcspn(funcionario.cargo, "\n")] = '\0';
                        
                              printf("Novo telefone: ");
                              fgets(funcionario.telefone, sizeof(funcionario.telefone), stdin);
                              funcionario.telefone[strcspn(funcionario.telefone, "\n")] = '\0';
                        
                              printf("Novo endereco: ");
                              fgets(funcionario.endereco, sizeof(funcionario.endereco), stdin);
                              funcionario.endereco[strcspn(funcionario.endereco, "\n")] = '\0';
                        
                              printf("Novo numero da casa: ");
                              scanf("%d", &funcionario.numero_casa);
                              while (getchar() != '\n');
                        
                              printf("Novo cep: ");
                              scanf("%d", &funcionario.cep);
                              while (getchar() != '\n');
                        
                              printf("Novo bairro: ");
                              fgets(funcionario.bairro, sizeof(funcionario.bairro), stdin);
                              funcionario.bairro[strcspn(funcionario.bairro, "\n")] = '\0';
                        
                              printf("Nova cidade: ");
                              fgets(funcionario.cidade, sizeof(funcionario.cidade), stdin);
                              funcionario.cidade[strcspn(funcionario.cidade, "\n")] = '\0';
                        
                              printf("Novo estado: ");
                              fgets(funcionario.estado, sizeof(funcionario.estado), stdin);
                              funcionario.estado[strcspn(funcionario.estado, "\n")] = '\0';	

                               // Move o ponteiro do arquivo de volta para a posição da conta lida
                              fseek(arquivo, pos, SEEK_SET);
                              fwrite(&funcionario, sizeof(fun), 1, arquivo); // Escreve a conta com os dados alterados                            

                              encontrado = 1; 
                              printf("\n\nO funcionario foi alterado com sucesso!\n");

                              break;      	  	
                         }    
                    }
               }
            }

        if (encontrado == 0) // Se a conta não foi encontrada
		   { 	       
            printf("\nFuncionario nao encontrado\n");
           }   
   } 
	else 
    printf("Erro ao abrir o arquivo");			
    
}



void altera_cliente(FILE *arquivo, int numero_conta)
{
	char tipo_conta;
	fun funcionario;
	cp conta_poupanca;
	cc conta_corrente;
	int encontrado = 0;
	
	if(arquivo != NULL)
     {
	  //procura em conta poupança
	  fseek(arquivo, 0L, SEEK_SET); // Move o ponteiro do arquivo para o início  
      
	   while (fread(&tipo_conta, sizeof(char), 1, arquivo)) // Lê o tipo da conta até atingir o final do arquivo
        {
            if (tipo_conta == 'P') // Conta Poupança
            {
	           if (fread(&conta_poupanca, sizeof(conta_poupanca), 1, arquivo)) // Lê cada conta poupança do arquivo enquanto fread não tiver problema ou chegar no fim do arquivo
             	{ 
                    if (conta_poupanca.numero_conta == numero_conta && conta_poupanca.excluido == 0) // Verifica se o número da conta é o mesmo e se a conta ainda não foi excluida
	    	           {  	
                          system("cls");
                          printf("\nconta encontrada.");
			              printf("\nDIGITE OS NOVOS DADOS DA CONTA");
                          printf("\n\nNovo telefone: ");
			              fgets(conta_poupanca.telefone, sizeof(conta_poupanca.telefone), stdin);
			              conta_poupanca.telefone[strcspn(conta_poupanca.telefone, "\n")] = '\0';
			   
			              printf("Novo endereco: ");
			              fgets(conta_poupanca.endereco, sizeof(conta_poupanca.endereco), stdin);
			              conta_poupanca.endereco[strcspn(conta_poupanca.endereco, "\n")] = '\0';
			   
			              printf("Novo numero da casa: ");
			              scanf("%d", &conta_poupanca.numero_casa);
			              while (getchar() != '\n');
			   
			              printf("Novo cep: ");
			              scanf("%d", &conta_poupanca.cep);
			              while (getchar() != '\n');
			   
			              printf("Novo bairro: ");
			              fgets(conta_poupanca.bairro, sizeof(conta_poupanca.bairro), stdin);
			              conta_poupanca.bairro[strcspn(conta_poupanca.bairro, "\n")] = '\0';
			   
			              printf("Nova cidade: ");
			              fgets(conta_poupanca.cidade, sizeof(conta_poupanca.cidade), stdin);
			              conta_poupanca.cidade[strcspn(conta_poupanca.cidade, "\n")] = '\0';
			   
			              printf("Novo estado: ");
			              fgets(conta_poupanca.estado, sizeof(conta_poupanca.estado), stdin);
			              conta_poupanca.estado[strcspn(conta_poupanca.estado, "\n")] = '\0';
               
		                  fseek(arquivo, -sizeof(conta_poupanca), SEEK_CUR); // Move o ponteiro do arquivo de volta para a posição da conta lida
                          fwrite(&conta_poupanca, sizeof(conta_poupanca), 1, arquivo); // Escreve a conta com os dados alterados         
			   
			              encontrado = 1; // Indica que a conta foi encontrada
            
			              printf("\n\nA conta foi alterada com sucesso\n"); // se a conta foi excluida mostra a mensagem           
		                  break; // Sai do loop se a conta foi 
                       }          
                } 
           }
       
        //procura em conta corrente
	   else if (tipo_conta == 'C') // Conta Corrente
           {
              if (fread(&conta_corrente, sizeof(conta_corrente), 1, arquivo)) // Lê cada conta poupança do arquivo enquanto fread não tiver problema ou chegar no fim do arquivo
	            { 
                    if (conta_corrente.numero_conta == numero_conta && conta_corrente.excluido == 0) // Verifica se o número da conta é o mesmo e se a conta ainda não foi excluida
	    	           {  	
                          system("cls");
                          printf("\nconta encontrada.");
			              printf("\nDIGITE OS NOVOS DADOS DA CONTA");
                          printf("\n\nNovo telefone: ");
			              fgets(conta_corrente.telefone, sizeof(conta_corrente.telefone), stdin);
			              conta_corrente.telefone[strcspn(conta_corrente.telefone, "\n")] = '\0';
			   
			              printf("Novo endereco: ");
			              fgets(conta_corrente.endereco, sizeof(conta_corrente.endereco), stdin);
			              conta_corrente.endereco[strcspn(conta_corrente.endereco, "\n")] = '\0';
			   
			              printf("Novo numero da casa: ");
			              scanf("%d", &conta_corrente.numero_casa);
			              while (getchar() != '\n');
			   
			              printf("Novo cep: ");
			              scanf("%d", &conta_corrente.cep);
			              while (getchar() != '\n');
			   
			              printf("Novo bairro: ");
			              fgets(conta_corrente.bairro, sizeof(conta_corrente.bairro), stdin);
			              conta_corrente.bairro[strcspn(conta_corrente.bairro, "\n")] = '\0';
			   
			              printf("Nova cidade: ");
			              fgets(conta_corrente.cidade, sizeof(conta_corrente.cidade), stdin);
			              conta_corrente.cidade[strcspn(conta_corrente.cidade, "\n")] = '\0';
			   
			              printf("Novo estado: ");
			              fgets(conta_corrente.estado, sizeof(conta_corrente.estado), stdin);
			              conta_corrente.estado[strcspn(conta_corrente.estado, "\n")] = '\0';
               
		                  fseek(arquivo, -sizeof(conta_corrente), SEEK_CUR); // Move o ponteiro do arquivo de volta para a posição da conta lida
                          fwrite(&conta_corrente, sizeof(conta_corrente), 1, arquivo); // Escreve a conta com os dados alterados         
			   
			              encontrado = 1; // Indica que a conta foi encontrada
            
			              printf("\n\nA conta foi alterada com sucesso\n"); // se a conta foi excluida mostra a mensagem          
		                  break; // Sai do loop se a conta foi 
                       }		
                }
           }
           
        else if (tipo_conta == 'F')
            {
              if (fread(&funcionario, sizeof(funcionario), 1, arquivo)) // Lê a estrutura da conta corrente
                {                   	                                                    
				   encontrado = 0;
			    }
		      
		    }
       }	    

       if(encontrado == 0) // Se a conta não foi encontrada	       
       printf("\n\nConta nao encontrada\n");        
    }   
    else
    printf("Erro ao abrir o arquivo");		
} 




void altera_conta(FILE *arquivo, int numero_conta)
{
	char tipo_conta;
    fun funcionario;
	cp conta_poupanca;
	cc conta_corrente;
	int encontrado = 0;
	
   if(arquivo != NULL)
     {
    // Procura em contas poupança
    fseek(arquivo, 0L, SEEK_SET); // Move o ponteiro do arquivo para o início  
     
	while (fread(&tipo_conta, sizeof(char), 1, arquivo)) // Lê o tipo da conta até atingir o final do arquivo
        {
           if (tipo_conta == 'P') // Conta Poupança
             {
                if(fread(&conta_poupanca, sizeof(conta_poupanca), 1, arquivo)) // Lê cada conta poupança do arquivo enquanto fread não tiver problema ou chegar no fim do arquivo
	              { 
                     if (conta_poupanca.numero_conta == numero_conta && conta_poupanca.excluido == 0) // Verifica se o número da conta é o mesmo e se a conta ainda não foi excluida
	    	           {  	
                          system("cls");
                          printf("\nconta encontrada.");
			              printf("\nDIGITE OS NOVOS DADOS DA CONTA");
                          printf("\n\nNovo tipo: ");
			              fgets(conta_poupanca.tipo, sizeof(conta_poupanca.tipo), stdin);
			              conta_poupanca.tipo[strcspn(conta_poupanca.tipo, "\n")] = '\0';
			   
			              printf("Novo limite: ");
			              fgets(conta_poupanca.limite, sizeof(conta_poupanca.limite), stdin);
			              conta_poupanca.limite[strcspn(conta_poupanca.limite, "\n")] = '\0';
			   
			              printf("Nova data de vencimento: ");
			              fgets(conta_poupanca.vencimento, sizeof(conta_poupanca.vencimento), stdin);
			              conta_poupanca.vencimento[strcspn(conta_poupanca.vencimento, "\n")] = '\0';
               
		                  fseek(arquivo, -sizeof(conta_poupanca), SEEK_CUR); // Move o ponteiro do arquivo de volta para a posição da conta lida
                          fwrite(&conta_poupanca, sizeof(conta_poupanca), 1, arquivo); // Escreve a conta com os dados alterados         
			   
			              encontrado = 1; // Indica que a conta foi encontrada
            
			              printf("\n\nA conta foi alterada com sucesso\n"); // se a conta foi excluida mostra a mensagem        
		                  break; // Sai do loop se a conta foi 
                       }
				  }
			}
       
          else if (tipo_conta == 'C') // Conta Corrente
            {
               if(fread(&conta_corrente, sizeof(conta_corrente), 1, arquivo)) // Lê cada conta poupança do arquivo enquanto fread não tiver problema ou chegar no fim do arquivo
               	  { 
                    if (conta_corrente.numero_conta == numero_conta && conta_corrente.excluido == 0) // Verifica se o número da conta é o mesmo e se a conta ainda não foi excluida
	              	  {  	
                        system("cls");
                        printf("\nconta encontrada.");
			            printf("\nDIGITE OS NOVOS DADOS DA CONTA");
                        printf("\n\nNovo tipo: ");
			            fgets(conta_corrente.tipo, sizeof(conta_corrente.tipo), stdin);
			            conta_corrente.tipo[strcspn(conta_corrente.tipo, "\n")] = '\0';
			   
			            printf("Novo limite: ");
			            scanf("%f", &conta_corrente.limite);
			            while (getchar() != '\n');
			   
			            printf("Nova data de vencimento: ");
			            fgets(conta_corrente.vencimento, sizeof(conta_corrente.vencimento), stdin);
			            conta_corrente.vencimento[strcspn(conta_corrente.vencimento, "\n")] = '\0';
               
		                fseek(arquivo, -sizeof(conta_corrente), SEEK_CUR); // Move o ponteiro do arquivo de volta para a posição da conta lida
                        fwrite(&conta_corrente, sizeof(conta_corrente), 1, arquivo); // Escreve a conta com os dados alterados         
			   
			            encontrado = 1; // Indica que a conta foi encontrada
            
			            printf("\n\nA conta foi alterada com sucesso\n"); // se a conta foi excluida mostra a mensagem           
		                break; // Sai do loop se a conta foi 
                      }          
                  } 
            }
            
          else if (tipo_conta == 'F')
            {
              if (fread(&funcionario, sizeof(funcionario), 1, arquivo)) // Lê a estrutura da conta corrente
                {                   	                                                    
				   encontrado = 0;
			    }
		      
		    }
        }    
      
	   if(encontrado == 0) // Se a conta não foi encontrada	       
       printf("\n\nConta nao encontrada\n"); 
   }  
   else
   printf("Erro ao abrir o arquivo");	
		
}



void consulta_conta(FILE *arquivo, int numero_conta)
{
    char tipo_conta;
    fun funcionario;
	cp conta_poupanca;
    cc conta_corrente;
    int encontrado = 0;

    if (arquivo != NULL)
    {
        fseek(arquivo, 0L, SEEK_SET); // Move o ponteiro do arquivo para o início
        
		// Loop para ler todo o arquivo
        while (fread(&tipo_conta, sizeof(char), 1, arquivo)) // Lê o tipo da conta até atingir o final do arquivo
        {
            if (tipo_conta == 'P') // Conta Poupança
            {
                if (fread(&conta_poupanca, sizeof(conta_poupanca), 1, arquivo)) // Lê a estrutura da conta poupança
                {
                    if (conta_poupanca.numero_conta == numero_conta && conta_poupanca.excluido == 0)
                    {
                        printf("\nTipo de conta: %s", conta_poupanca.tipo);
                        printf("\nNome do cliente: %s", conta_poupanca.nome);
                        printf("\nCpf: %s", conta_poupanca.cpf);
                        printf("\nSaldo: R$%.2f", conta_poupanca.saldo);
                        printf("\nLimite disponivel: %s", conta_poupanca.limite);
                        printf("\nData de vencimento: %s\n", conta_poupanca.vencimento);

                        encontrado = 1;
                        break;
                    }
                }
            }
            
			else if (tipo_conta == 'C') // Conta Corrente
            {
                if (fread(&conta_corrente, sizeof(conta_corrente), 1, arquivo)) // Lê a estrutura da conta corrente
                {
                    if (conta_corrente.numero_conta == numero_conta && conta_corrente.excluido == 0)
                    {
                        printf("\nTipo de conta: %s", conta_corrente.tipo);
                        printf("\nNome do cliente: %s", conta_corrente.nome);
                        printf("\nCpf: %s", conta_corrente.cpf);
                        printf("\nSaldo: R$%.2f", conta_corrente.saldo);
                        printf("\nLimite disponivel: %.2f", conta_corrente.limite);
                        printf("\nData de vencimento: %s\n", conta_corrente.vencimento);

                        encontrado = 1;
                        break;
                    }
                }
            }
            
			else if (tipo_conta == 'F')
            {
              if (fread(&funcionario, sizeof(funcionario), 1, arquivo)) // Lê a estrutura da conta corrente
                {                   	                                                    
				   encontrado = 0;
			    }
		      
		    }

        }

        if (encontrado == 0) // Se a conta não foi encontrada
            printf("\nConta nao encontrada\n");
            system("pause");
    }
    else
      {
        printf("Erro ao abrir o arquivo");
      }
}





void consulta_funcionario(FILE *arquivo, int numero_conta)
{
   char tipo_conta;
   fun funcionario;
   int encontrado = 0;
   
if(arquivo != NULL)
   { 
        fseek(arquivo, 0L, SEEK_SET); // move o ponteiro do arquivo para o inicio	
        while (fread(&tipo_conta, sizeof(char), 1, arquivo)) // Lê o tipo da conta até atingir o final do arquivo
		  {
             if (tipo_conta == 'F')
			    { 
                     if (fread(&funcionario, sizeof(fun), 1, arquivo)) // Lê a estrutura do funcionário
					     { 
                             if (funcionario.codigo == numero_conta && funcionario.excluido == 0) 
							   {
                                 printf("\nCODIGO: %d", funcionario.codigo);
                                 printf("\nCARGO: %s", funcionario.cargo);
                                 printf("\nNOME: %s", funcionario.nome);
                                 printf("\nCPF: %s", funcionario.cpf);
                                 printf("\nDATA DE NASCIMENTO: %s", funcionario.nascimento);
                                 printf("\nTELEFONE: %s", funcionario.telefone);
                                 printf("\nENDERECO: %s", funcionario.endereco);
                                 printf("\nCEP: %d", funcionario.cep);
                                 printf("\nLOCAL: %s", funcionario.local);
                                 printf("\nNUMERO DA CASA: %d", funcionario.numero_casa);
                                 printf("\nBAIRRO: %s", funcionario.bairro);
                                 printf("\nCIDADE: %s", funcionario.cidade);
                                 printf("\nESTADO: %s", funcionario.estado);
                                 printf("\nSENHA DO FUNCIONARIO: %d \n", funcionario.senha);
                        
                                 encontrado = 1;    	  	
                                 break;      	  	
                               }
                         }
                }
          }

        if (encontrado == 0)  // Se a conta não foi encontrada
         printf("\nFuncionario nao encontrado\n");
        
        system("pause");
    } 
	else 
    printf("Erro ao abrir o arquivo");
}




void consulta_cliente(FILE *arquivo, int numero_conta)
{
  char tipo_conta;
  fun funcionario;
  cp conta_poupanca;
  cc conta_corrente;
  int encontrado = 0;
   
  if(arquivo != NULL)
   { 
  //procura em contas poupança
  fseek(arquivo, 0L, SEEK_SET); // move o ponteiro do arquivo para o inicio	
  
  while (fread(&tipo_conta, sizeof(char), 1, arquivo)) // Lê o tipo da conta até atingir o final do arquivo
     {
  
       if (tipo_conta == 'P') // Conta Poupança
         {
            if (fread(&conta_poupanca, sizeof(conta_poupanca), 1, arquivo)) // le as contas do arquivo até chegar ao final ou acontecer algum erro
               {
  	              if (conta_poupanca.numero_conta == numero_conta && conta_poupanca.excluido == 0)
		            {
		  	           printf("\nNome do cliente: %s", conta_poupanca.nome);
		  	           printf("\nCpf: %s", conta_poupanca.cpf);
		               printf("\nData de nascimento: %s", conta_poupanca.nascimento);
		  	           printf("\nTelefone: %s", conta_poupanca.telefone);
		  	           printf("\nEndereco: %s ", conta_poupanca.endereco);
		   	           printf("\nNumero da casa: %d", conta_poupanca.numero_casa);
		  	           printf("\nCep: %d", conta_poupanca.cep);
		  	           printf("\nBairro: %s", conta_poupanca.bairro);
		  	           printf("\nCidade: %s", conta_poupanca.cidade);
		  	           printf("\nEstado: %s \n", conta_poupanca.estado);
		  	
		  	           encontrado = 1;
		  	           break;		  	
		            } 		
		  
                }	
         }
  
      //procura em conta corrente
        else if (tipo_conta == 'C') // Conta Corrente
          {	
             if (fread(&conta_corrente, sizeof(conta_corrente), 1, arquivo)) // le as contas do arquivo até chegar ao final ou acontecer algum erro
              {
  	              if (conta_corrente.numero_conta == numero_conta && conta_corrente.excluido == 0)
		            {
		  	           printf("\nNome do cliente: %s", conta_corrente.nome);
		  	           printf("\nCpf: %s", conta_corrente.cpf);
		           	   printf("\nData de nascimento: %s", conta_corrente.nascimento);
		  	           printf("\nTelefone: %s", conta_corrente.telefone);
		  	           printf("\nEndereco: %s ", conta_corrente.endereco);
		  	           printf("\nNumero da casa: %d", conta_corrente.numero_casa);
		  	           printf("\nCep: %d", conta_corrente.cep);
		  	           printf("\nBairro: %s", conta_corrente.bairro);
		  	           printf("\nCidade: %s", conta_corrente.cidade);
		  	           printf("\nEstado: %s \n", conta_corrente.estado);
		  	
		  	           encontrado = 1;
		  	           break;		  	
		            } 
			  }
		 
          }
       
	    else if (tipo_conta == 'F')
          {
              if (fread(&funcionario, sizeof(funcionario), 1, arquivo)) // Lê a estrutura da conta corrente
                {                   	                                                    
				    encontrado = 0;
			    };
		      
		  }
	 }

      if(encontrado == 0) // Se a conta não foi encontrada	       
      printf("\nConta nao encontrada\n");   
	  
	  system("pause");	
  }
   else
   printf("Erro ao abrir o arquivo");
}





void mostrar_saldo(FILE *arquivo, int senha)
{
   char tipo_conta;
   fun funcionario;
   cp conta_poupanca;
   cc conta_corrente;
   int encontrado = 0;	
   
   if(arquivo != NULL)
     { 
        fseek(arquivo, 0L, SEEK_SET);
        
		while (fread(&tipo_conta, sizeof(char), 1, arquivo)) // Lê o tipo da conta até atingir o final do arquivo
          {
              if (tipo_conta == 'P') // Conta Poupança
                 {
                     if (fread(&conta_poupanca, sizeof(conta_poupanca), 1, arquivo)) // le as contas do arquivo até chegar ao final ou acontecer algum erro
                        {
  	                       if (conta_poupanca.senha == senha && conta_poupanca.excluido == 0)
		                      {
							   printf("\nSALDO DA CONTA: R$%.2f\n", conta_poupanca.saldo);
							   
							   encontrado = 1;
		  	                   break; 
		                      }
		                }
		         }
		         
		    else if (tipo_conta == 'C') // Conta Corrente
               {	
                   if (fread(&conta_corrente, sizeof(conta_corrente), 1, arquivo)) // le as contas do arquivo até chegar ao final ou acontecer algum erro
                      {
  	                      if (conta_corrente.senha == senha && conta_corrente.excluido == 0)
		                    {
		                     printf("\nSALDO DA CONTA: R$%.2f\n", conta_corrente.saldo);
							 	
		                     encontrado = 1;
		  	                 break;
		                    }		            
					  }
				}
				
		   else if (tipo_conta == 'F')
               {
                    if (fread(&funcionario, sizeof(funcionario), 1, arquivo)) // Lê a estrutura da conta corrente
                      {                   	                                                    
				         encontrado = 0;
			          }	      
		        } 						 
		  } 
		    
		if(encontrado == 0) // Se a conta não foi encontrada	       
        printf("\nConta nao encontrada\n");   
	    
    }
    else
    printf("Erro ao abrir o arquivo");			
	
}





void deposita_conta(FILE *arquivo, FILE *extrato, int numero_conta)
{
   char tipo_conta, sinal = '+';
   fun funcionario;
   cp conta_poupanca;
   cc conta_corrente;
   int encontrado = 0;
   float deposito;	
   
   if(arquivo != NULL)
     {  
	    fseek(arquivo, 0L, SEEK_SET);    
		while (fread(&tipo_conta, sizeof(char), 1, arquivo)) // Lê o tipo da conta até atingir o final do arquivo
          {
              if (tipo_conta == 'P') // Conta Poupança
                 {
                    if (fread(&conta_poupanca, sizeof(conta_poupanca), 1, arquivo)) // le as contas do arquivo até chegar ao final ou acontecer algum erro
                        {
  	                       if (conta_poupanca.numero_conta == numero_conta && conta_poupanca.excluido == 0)
		                      {				     
							    printf("\nDigite o valor do deposito: R$");
					            scanf("%f", &deposito);
					            
								conta_poupanca.saldo += deposito; 
							   
							    fseek(arquivo, -sizeof(conta_poupanca), SEEK_CUR); // Move o ponteiro do arquivo de volta para a posição da conta lida
                                fwrite(&conta_poupanca, sizeof(conta_poupanca), 1, arquivo);
							   
							    encontrado = 1;
							    
							    
							    fseek(extrato, 0L, SEEK_END); // move o ponteiro para o final do arquivo extrato
							    fwrite(&sinal, sizeof(sinal), 1, extrato) && fwrite(&deposito, sizeof(deposito), 1, extrato) && fwrite(&conta_poupanca.saldo, sizeof(conta_poupanca.saldo), 1, extrato);//escrevendo a operação no extrato 
							    						    
							    printf("\nDeposito feito com sucesso!\n");
		  	                    break; 
		                      }
		                }
		         }
		         
		    else if (tipo_conta == 'C') // Conta Corrente
               {	
                   if (fread(&conta_corrente, sizeof(conta_corrente), 1, arquivo)) // le as contas do arquivo até chegar ao final ou acontecer algum erro
                      {
  	                      if (conta_corrente.numero_conta == numero_conta && conta_corrente.excluido == 0)
		                    {	                      
		                      printf("\nDigite o valor do deposito: R$");
					          scanf("%f", &deposito);
		                     
							  conta_corrente.saldo += deposito;
							 	
							  fseek(arquivo, -sizeof(conta_corrente), SEEK_CUR); // Move o ponteiro do arquivo de volta para a posição da conta lida
                              fwrite(&conta_corrente, sizeof(conta_corrente), 1, arquivo);	
							 	
		                      encontrado = 1;
		                      
		                      printf("\n\nDeposito feito com sucesso!\n");
		  	                  break;
		                    }		            
					  }
				}
				
		   else if (tipo_conta == 'F')
               {
                    if (fread(&funcionario, sizeof(funcionario), 1, arquivo)) // Lê a estrutura da conta corrente
                      {                   	                                                    
				         encontrado = 0;
			          }	      
		        } 						 
		  } 
		    
		if(encontrado == 0) // Se a conta não foi encontrada	       
        printf("\nConta nao encontrada\n");    
	  	
	 }
    else
    printf("Erro ao abrir o arquivo");			
}




void saque(FILE *arquivo, FILE *extrato, int senha)
{
   char tipo_conta, sinal = '-';
   fun funcionario;
   cp conta_poupanca;
   cc conta_corrente;
   int encontrado = 0;
   float saque;	
   
   if(arquivo != NULL)
     { 
        fseek(arquivo, 0L, SEEK_SET);
        
		while (fread(&tipo_conta, sizeof(char), 1, arquivo)) // Lê o tipo da conta até atingir o final do arquivo
          {
              if (tipo_conta == 'P') // Conta Poupança
                 {
                     if (fread(&conta_poupanca, sizeof(conta_poupanca), 1, arquivo)) // le as contas do arquivo até chegar ao final ou acontecer algum erro
                        {
  	                       if (conta_poupanca.senha == senha && conta_poupanca.excluido == 0)
		                      {
							   printf("\nInforme o valor do saque: R$");
							   scanf("%f", &saque);
							   
							        if(saque>conta_poupanca.saldo)
							          {  
							             printf("\nSaldo insuficiente\n");
							             encontrado =1;
									     break;							        
							          }
							      
							         else
								      {
								 	    conta_poupanca.saldo -= saque;
								 	   		
										fseek(arquivo, -sizeof(conta_poupanca), SEEK_CUR); // Move o ponteiro do arquivo de volta para a posição da conta lida
                                        fwrite(&conta_poupanca, sizeof(conta_poupanca), 1, arquivo);
                                        
                                        
                                        fseek(extrato, 0L, SEEK_END); // move o ponteiro para o final do arquivo extrato
							            fwrite(&sinal, sizeof(sinal), 1, extrato) && fwrite(&saque, sizeof(saque), 1, extrato) && fwrite(&conta_corrente.saldo, sizeof(conta_corrente.saldo), 1, extrato);//escrevendo a operação no extrato 
										
										printf("\nSaque realizado com sucesso!\n");							 	   	
									    encontrado = 1;
		  	                            break; 									 
							          } 					          							   
		                      }
		                }
		         }
		         
		    else if (tipo_conta == 'C') // Conta Corrente
               {	
                   if (fread(&conta_corrente, sizeof(conta_corrente), 1, arquivo)) // le as contas do arquivo até chegar ao final ou acontecer algum erro
                      {
  	                      if (conta_corrente.senha == senha && conta_corrente.excluido == 0)
		                    {
		                      printf("\nInforme o valor do saque: R$");
							  scanf("%f", &saque);
							   
							        if(saque>conta_corrente.saldo)
							          {  
							             printf("\nSaldo insuficiente\n");
							             encontrado =1;
									     break;							        
							          }
							      
							         else
								      {
								 	    conta_corrente.saldo -= saque;
								 	   		
										fseek(arquivo, -sizeof(conta_corrente), SEEK_CUR); // Move o ponteiro do arquivo de volta para a posição da conta lida
                                        fwrite(&conta_corrente, sizeof(conta_corrente), 1, arquivo);
										
										printf("\nSaque realizado com sucesso!\n");							 	   	
									    encontrado = 1;
		  	                            break; 									 
							          } 					  
							 	
		                     encontrado = 1;
		  	                 break;
		                    }		            
					  }
				}
				
		   else if (tipo_conta == 'F')
               {
                    if (fread(&funcionario, sizeof(funcionario), 1, arquivo)) // Lê a estrutura da conta corrente
                      {                   	                                                    
				         encontrado = 0;
			          }	      
		        } 						 
		  } 
		    
		if(encontrado == 0) // Se a conta não foi encontrada	       
        printf("\nConta nao encontrada\n");   
	    
    }
    else
    printf("Erro ao abrir o arquivo");			
}



void ver_limite(FILE *arquivo, int senha)
{
   char tipo_conta;
   fun funcionario;
   cp conta_poupanca;
   cc conta_corrente;
   int encontrado = 0;	
   
   if(arquivo != NULL)
     { 
        fseek(arquivo, 0L, SEEK_SET);
        
		while (fread(&tipo_conta, sizeof(char), 1, arquivo)) // Lê o tipo da conta até atingir o final do arquivo
          {
              if (tipo_conta == 'P') // Conta Poupança
                 {
                     if (fread(&conta_poupanca, sizeof(conta_poupanca), 1, arquivo)) // le as contas do arquivo até chegar ao final ou acontecer algum erro
                        {
  	                       if (conta_poupanca.senha == senha && conta_poupanca.excluido == 0)
		                      {
		                        if(conta_poupanca.limite == "Conta sem limite")
		                          {							      	
							        printf("\nLIMITE INDISPONIVEL\n");
							    
							        encontrado = 1;
		  	                        break; 
		  	                      }
		  	                      
		  	                      else
		  	                       {								
						             printf("\nLIMITE DISPONIVEL\n");
						             encontrado =1;
						             break; 
						           }
		                     }
		                }
		         }
		         
		    else if (tipo_conta == 'C') // Conta Corrente
               {	
                   if (fread(&conta_corrente, sizeof(conta_corrente), 1, arquivo)) // le as contas do arquivo até chegar ao final ou acontecer algum erro
                      {
  	                      if (conta_corrente.senha == senha && conta_corrente.excluido == 0 && conta_corrente.limite > 0.0)
		                    {
		                     printf("\nLIMITE DISPONIVEL\n");
							 	
		                     encontrado = 1;
		  	                 break;
		                    }	
		                    
						  else
						    { 						  
						      printf("\nLIMITE INDISPONIVEL\n");
						      encontrado =1;
						      break;	  
					        }
					  }
				}
				
		   else if (tipo_conta == 'F')
               {
                    if (fread(&funcionario, sizeof(funcionario), 1, arquivo)) // Lê a estrutura da conta corrente
                      {                   	                                                    
				         encontrado = 0;
			          }	      
		        } 						 
		  } 
		    
		if(encontrado == 0) // Se a conta não foi encontrada	       
        printf("\nConta nao encontrada\n");   
	    
    }
    else
    printf("Erro ao abrir o arquivo");		
	
	
	
}



void ver_extrato(FILE *arquivo, FILE *extrato, int senha)
{
   char tipo_conta;
   fun funcionario;
   cp conta_poupanca;
   cc conta_corrente;
   int encontrado = 0;	
   
   if(arquivo != NULL)
     { 
        fseek(arquivo, 0L, SEEK_SET);
        
		while (fread(&tipo_conta, sizeof(char), 1, arquivo)) // Lê o tipo da conta até atingir o final do arquivo
          {
              if (tipo_conta == 'P') // Conta Poupança
                 {
                     if (fread(&conta_poupanca, sizeof(conta_poupanca), 1, arquivo)) // le as contas do arquivo até chegar ao final ou acontecer algum erro
                        {
  	                       if (conta_poupanca.senha == senha && conta_poupanca.excluido == 0)
		                      {
							   system("cls");
							   
							   fclose(extrato);
							   printf("\n\nEXTRATO SENDO ENCAMINHADO PARA EXCEL\n");
       	                	                   
						       system("extrato.xlsx");
							   extrato = fopen("extrato.txt", "w+b");
							   
							   
							   encontrado = 1;
		  	                   break; 
		                      }
		                }
		         }
		         
		    else if (tipo_conta == 'C') // Conta Corrente
               {	
                   if (fread(&conta_corrente, sizeof(conta_corrente), 1, arquivo)) // le as contas do arquivo até chegar ao final ou acontecer algum erro
                      {
  	                      if (conta_corrente.senha == senha && conta_corrente.excluido == 0)
		                    {
		                     system("cls");	
		                     printf("EXTRATO SENDO ENCAMINHADO PARA EXCEL");
							 	
		                     encontrado = 1;
		  	                 break;
		                    }		            
					  }
				}
				
		   else if (tipo_conta == 'F')
               {
                    if (fread(&funcionario, sizeof(funcionario), 1, arquivo)) // Lê a estrutura da conta corrente
                      {                   	                                                    
				         encontrado = 0;
			          }	      
		        } 						 
		  } 
		    
		if(encontrado == 0) // Se a conta não foi encontrada	       
        printf("\nConta nao encontrada\n");   
	    
    }
    else
    printf("Erro ao abrir o arquivo");			
	
}
	
	
	


void MenuInicial (int x)
{
FILE *Arquivo; //declarando o arquivo
FILE *extrato;
cp conta; // declarando variavel do tipo registro conta p
cc contac; // declarando variavel do tipo registro conta c
fun funcionario; //declarando uma variavel do tipo registro fun
char opcao, ola; 
int senha, numero_conta;
float deposito = 0;

Arquivo = fopen("banco.txt", "w+b"); // Abre o arquivo
extrato = fopen("extrato.txt", "w+b");//Abrindo o arquivo para extrato
 
  if(Arquivo == NULL) // tenta criar outro arquivo se não existir um
  { 
   	 Arquivo = fopen("banco.txt", "w+"); 
  }


  if(extrato == NULL) // tenta criar outro arquivo se não existir um
  { 
   	 printf("ola");
   	 system("pause");
  }



   if(Arquivo != NULL) // Se o arquivo foi aberto ou criado
  { 
    do //realiza o programa enquanto o usuario não quiser sair
    {
      system("cls");//limpa a tela
      
	  printf("\n");
        printf("\n                   d8888 8888888b.   .d8888b.  ");
		printf("\n                  d88888 888   Y88b d88P  Y88b ");
		printf("\n                 d88P888 888    888 Y88b.      ");
		printf("\n                d88P 888 888    888   Y888b.   ");
		printf("\n               d88P  888 888    888      Y88b. ");
		printf("\n              d88P   888 888    888        888 ");
		printf("\n             d8888888888 888  .d88P Y88b  d88P ");
		printf("\n            d88P     888 8888888P     Y8888P   ");
        printf("\n\n");
     	printf("\n            888888b.          d8888 888b    888 888    d8P  ");
		printf("\n            888   88b        d88888 8888b   888 888   d8P   ");
		printf("\n            888  .88P       d88P888 88888b  888 888  d8P    ");
		printf("\n            8888888K.      d88P 888 888Y88b 888 888d88K     ");
		printf("\n            888   Y88b    d88P  888 888 Y88b888 8888888b    ");
		printf("\n            888    888   d88P   888 888  Y88888 888  Y88b   ");
		printf("\n            888   d88P  d8888888888 888   Y8888 888   Y88b  ");
		printf("\n            8888888P   d88P     888 888    Y888 888    Y88b ");  
		
				           printf("\n");                                                                      
		printf("\n                           ++############++              ");            
		printf("\n                      ############################           ");          
		printf("\n                  ########        ####        @@######       ");          
		printf("\n               @@####        ##  ####            ######         ");      
		printf("\n                ####              ####              ####         ");      
		printf("\n              ####                ####                ####       ");      
		printf("\n              ####                ####                ####       ");      
		printf("\n              ##::                ####                  ##          ");   
		printf("\n            ::##                  ####                  ####      ");     
		printf("\n            ####                  ####              MM@@####        ");   
		printf("\n            ####                  ####            ..########        ");   
		printf("\n            ####                  ####                  ####        ");   
		printf("\n            ##################..  ####    ##################         ");  
		printf("\n            ####MM          ################@@        ######          "); 
		printf("\n            ####  ##########MM  ..######  MM##########  ..##          "); 
		printf("\n          mm##  ##################..  ##################  ####        "); 
		printf("\n          ####  ####          ############::        ####  ####       ");  
		printf("\n          ####  ####          ####    ####          ####  ####        "); 
		printf("\n          ##mm  ######      ##########  ####      ######    ##        "); 
		printf("\n        ####    ################  ####..################    ####      "); 
		printf("\n        ####  ####    mm@@mm    ##++  ##    mmmmmm    ####  ####      "); 
		printf("\n        ####  ####            @@##::  ####            ####  ::##      "); 
		printf("\n      ####    ##############  ############  MM############    ##@@    "); 
		printf("\n      ####  ::####################  MM######################  ####    "); 
		printf("\n      ##::  ##    ######  ..######  MMMM####--  @@####    ##  ..##    "); 
		printf("\n    ####            ####  ########  MM@@######  ####            ####  "); 
		printf("\n    ##########################  ##  mm@@  ##########################  "); 
		printf("\n  ####################  ####@@  ##  MM@@  ######  ####################"); 
		printf("\n                      ######----##  @@##--  ######--                  "); 
		printf("\n                    ##--##########################mm##                "); 
		printf("\n                    ##@@##########################mm##                ");
		
      printf("\n\n\nFUNCIONARIO [1]\n");
      printf("\nCLIENTE [2]\n");
      printf("\nSAIR [3]\n");
      
      opcao = getch(); //le a opção do usuario
      switch(opcao)
       {
       	   case '1':
       	   	system("cls"); //limpa a tela
       	   	printf("\nDigite a senha de Administrador: "); //pede a senha do adm
       	   	scanf("%d", &senha);
       	   	while (getchar() != '\n');
				     
       	   	     if(senha == 1234) //se a senha for correta entra no menu do funcionario
       	   	       {           
       	   	   	       do // realiza enquanto não apertar 7 para sair do programa
                       {
						system("cls"); // limpa a tela e mostra as opções do funcionario
				        printf("ABERTURA DE CONTA [1]"); 
				        printf("\n\nENCERRAMENTO DE CONTA [2]"); 
				        printf("\n\nCONSULTAR DADOS[3]"); 
				        printf("\n\nALTERAR DADOS [4]"); 
				        printf("\n\nCADASTRO DE FUNCIONARIOS [5]"); 
				        printf("\n\nGERAR RELATORIOS [6]"); 
				        printf("\n\nSAIR [7]"); 
						
                     
					 	
						ola = getch(); // le a opcao do usuario						
						switch(ola)
						  {
						   	case '1': //case abertura de conta
						   	system ("cls"); // limpa a tela e mostra o menu de acertura de conta
							printf("\nCONTA POUPANCA - CP [1]");
							printf("\n\nCONTA CORRENTE - CC [2]");
							printf("\n\nVOLTAR [3]");	
						   	
						   	  do // realiza enquanto não aperta 3 para voltar
							   {				   	
							      ola = getch();// le a opcao do usuario de qual tipo de conta ele quer abrir    							
							      switch(ola)
							        {
							     	  case '1':
							     	  system("cls");	
							       	  printf("\n===== ABERTURA CONTA POUPANCA =====");							       	             
							       	  
							       	  printf("\n\nAGENCIA: "); // mostrando o dado para ser inserido
									  scanf("%d", &conta.agencia); // lendo as informações do usuario e armazenando na structure da conta poupança
									  while (getchar() != '\n'); // Limpando o Buffer para a proxima leitura
									   
									  printf("NUMERO DA CONTA: ");
									  scanf("%d", &conta.numero_conta);
									  while (getchar() != '\n');
									   
									  printf("NOME: ");
									  fgets(conta.nome, sizeof(conta.nome), stdin); // usando fgets para ler um vetor do tipo char
									  conta.nome[strcspn(conta.nome, "\n")] = '\0'; // Remove o caractere de nova linha
									  
									  printf("CPF: ");
									  fgets(conta.cpf, sizeof(conta.cpf), stdin); 
									  conta.cpf[strcspn(conta.cpf, "\n")] = '\0';
									  
									  printf("DATA DE NASCIMENTO: ");
									  fgets(conta.nascimento, sizeof(conta.nascimento), stdin);
									  conta.nascimento[strcspn(conta.nascimento, "\n")] = '\0';
									  
								      printf("TELEFONE: ");
									  fgets(conta.telefone, sizeof(conta.telefone), stdin);
									  conta.telefone[strcspn(conta.telefone, "\n")] = '\0';
									  
									  printf("ENDERECO: ");
									  fgets(conta.endereco, sizeof(conta.endereco), stdin);
									  conta.endereco[strcspn(conta.endereco, "\n")] = '\0';
									  
									  printf("CEP: ");
									  scanf("%d", &conta.cep);
									  while (getchar() != '\n');
									   
									  printf("LOCAL: "); 
									  fgets(conta.local, sizeof(conta.local), stdin);
									  conta.local[strcspn(conta.local, "\n")] = '\0';
									  
									  printf("NUMERO DA CASA: ");
									  scanf("%d", &conta.numero_casa);
									  while (getchar() != '\n');									  
									  
									  printf("BAIRRO: ");
									  fgets(conta.bairro, sizeof(conta.bairro), stdin);
									  conta.bairro[strcspn(conta.bairro, "\n")] = '\0'; 
									  
									  printf("CIDADE: ");
									  fgets(conta.cidade, sizeof(conta.cidade), stdin);
									  conta.cidade[strcspn(conta.cidade, "\n")] = '\0'; 
									  
									  printf("ESTADO: ");
									  fgets(conta.estado, sizeof(conta.estado), stdin);
									  conta.estado[strcspn(conta.estado, "\n")] = '\0';
									  
									  printf("SENHA: ");
									  scanf("%d", &conta.senha);
							  	      while (getchar() != '\n');
							  	      
							  	      strcpy(conta.tipo, "Conta poupanca"); //grava no regisro o tipo da conta
							  	      strcpy(conta.limite, "Conta sem limite"); //grava no regisro o tipo da conta
							  	      strcpy(conta.vencimento, "Conta sem data de vencimento"); //grava no regisro o tipo da conta
							  	      
							  	      conta.saldo = 0.0; // inicializa o saldo da conta em 0
     										  
											if (Insere_cp(Arquivo, conta))// chama a função para gravar a conta poupança no arquivo
                                            printf("\nConta poupanca aberta com sucesso\n");// mostra a mensagem se a conta foi inserida                                      
										    
											else
                                            printf("Erro ao abrir a conta\n");
											
											system("pause"); // Pausa para que o usuário veja a mensagem
                                           	
											     ola = '3';	// força a saido do loop								   
										         break;																	  	       
	
							        
							          case '2':
									  system("cls");	
							       	  printf("\n===== ABERTURA CONTA CORRENTE =====");
							       	  
									  printf("\n\nAGENCIA: "); // mostrando o dado para ser inserido
									  scanf("%d", &contac.agencia); // lendo as informações do usuario e armazenando na structure da conta poupança
									  while (getchar() != '\n'); // Limpando o Buffer para a proxima leitura
									  
									  printf("NUMERO DA CONTA: ");
									  scanf("%d", &contac.numero_conta);
									  while (getchar() != '\n');	
									
									  printf("LIMITE: R$");
									  scanf("%f", &contac.limite);
									  while (getchar() != '\n');
									  
									  printf("DATA DE VENCIMENTO: "); 
									  fgets(contac.vencimento, sizeof(contac.vencimento), stdin);
									  contac.vencimento[strcspn(contac.vencimento, "\n")] = '\0';
									  
									  printf("NOME: ");
									  fgets(contac.nome, sizeof(contac.nome), stdin);
									  contac.nome[strcspn(contac.nome, "\n")] = '\0';
									  
									  printf("CPF: ");
									  fgets(contac.cpf, sizeof(contac.cpf), stdin); 
									  contac.cpf[strcspn(contac.cpf, "\n")] = '\0';
									  
									  printf("DATA DE NASCIMENTO: ");
									  fgets(contac.nascimento, sizeof(contac.nascimento), stdin);
									  contac.nascimento[strcspn(contac.nascimento, "\n")] = '\0';
									  
								      printf("TELEFONE: ");
									  fgets(contac.telefone, sizeof(contac.telefone), stdin);
									  contac.telefone[strcspn(contac.telefone, "\n")] = '\0';
									  
									  printf("ENDERECO: ");
									  fgets(contac.endereco, sizeof(contac.endereco), stdin);
									  contac.endereco[strcspn(contac.endereco, "\n")] = '\0';
									  
									  printf("CEP: ");
									  scanf("%d", &contac.cep);
									  while (getchar() != '\n');
									   
									  printf("LOCAL: "); 
									  fgets(contac.local, sizeof(contac.local), stdin);
									  contac.local[strcspn(contac.local, "\n")] = '\0';
									  
									  printf("NUMERO DA CASA: ");
									  scanf("%d", &contac.numero_casa);
									  while (getchar() != '\n');									  
									  
									  printf("BAIRRO: ");
									  fgets(contac.bairro, sizeof(contac.bairro), stdin);
									  contac.bairro[strcspn(contac.bairro, "\n")] = '\0'; 
									  
									  printf("CIDADE: ");
									  fgets(contac.cidade, sizeof(contac.cidade), stdin);
									  contac.cidade[strcspn(contac.cidade, "\n")] = '\0'; 
									  
									  printf("ESTADO: ");
									  fgets(contac.estado, sizeof(contac.estado), stdin);
									  contac.estado[strcspn(contac.estado, "\n")] = '\0';
									  
									  printf("SENHA: ");
									  scanf("%d", &contac.senha);
							  	      while (getchar() != '\n');
									  									      
									  strcpy(contac.tipo, "Conta corrente");  //grava no regisro o tipo da conta
									  
									  contac.saldo = 0.0; // inicializa o saldo da conta em 0
									  							  
										  if (Insere_cc(Arquivo, contac))// chama a função para gravar a conta corrente no arquivo
                                          printf("\nConta corrente aberta com sucesso.\n");// mostra a mensagem se a conta foi inserida                                      
										  
										  
										  else
                                          printf("Erro ao abrir a conta.\n");    
									  
									      system("pause"); // Pausa para que o usuário veja a mensagem
									      
                                              ola = '3';	// força a saido do loop								   
									          break;
									  
									 }							   

							    }
							   while(ola != '3');
							
							break;
							
							
							case '2': // caso o usuario escolha encerrar a conta							
							system("cls"); // limpa a tela
							printf("\nDigite a senha de admnistrador: ");
							scanf("%d", &senha); // le a senha que o usuario digitar
       	                	while (getchar() != '\n'); //limpa o buffer
       	                	
       	                	       if(senha == 1234)
       	                	         {
       	                	  	           system("cls");
										   printf("\nDigite o numero da conta para encerramento: ");
       	                	  	         
									       scanf("%d", &numero_conta);// le o numero da conta do usuario
                                           while (getchar() != '\n');
                                           
                                           remove_conta(Arquivo, numero_conta);                                      

                                           system("pause");
       	                	   	
							         }
							     
							       else
							         {
							           printf("\nSenha incorreta!\n");
							           system("pause");									   							           
								     }
							
							break;


							
							case '3':
							system("cls");
							printf("\nCONSULTAR CONTA [1]");
							printf("\n\nCONSULTAR FUNCIONARIO [2]");
							printf("\n\nCONSULTAR CLIENTE [3]");
							printf("\n\nVOLTAR [4]");	
							
							    do
							      {						    	
							    	  ola = getch();
							    	  
							    	   switch(ola)
							    	     {
									         case '1':
										        system("cls");
												printf("\n\nDigite o numero da conta a ser consultada: ");
										        scanf("%d", &numero_conta);
										        while (getchar() != '\n');
										        
										        
										        consulta_conta(Arquivo, numero_conta);// chama função para consultar a conta
										        
										        system("cls");
												printf("\nCONSULTAR CONTA [1]");
							                    printf("\n\nCONSULTAR FUNCIONARIO [2]");
							                    printf("\n\nCONSULTAR CLIENTE [3]");
						                     	printf("\n\nVOLTAR [4]");	
												 									    								        								     
											 break;
										     
										     
										     case '2':
										     	 system("cls"); 
												 printf("\n\nDigite o codigo do funcionario a ser consultado: ");
												 scanf("%d", &numero_conta);
												 while (getchar() != '\n');
												 
												 consulta_funcionario(Arquivo, numero_conta); // chama função consultar funcionario
												 
												system("cls");
												printf("\nCONSULTAR CONTA [1]");
							                    printf("\n\nCONSULTAR FUNCIONARIO [2]");
							                    printf("\n\nCONSULTAR CLIENTE [3]");
						                     	printf("\n\nVOLTAR [4]");
										     	
										      break;
										      
										      
										     case '3':
										      	 system("cls"); 
											     printf("\n\nDigite o numero da conta do cliente a ser consultada: ");
											     scanf("%d", &numero_conta);
											     while (getchar() != '\n');
											     
											     consulta_cliente(Arquivo, numero_conta); // chama função para consultar o cliente
											     
											     system("cls");
											     printf("\nCONSULTAR CONTA [1]");
							                     printf("\n\nCONSULTAR FUNCIONARIO [2]");
							                     printf("\n\nCONSULTAR CLIENTE [3]");
						                     	 printf("\n\nVOLTAR [4]");
										      
											  break;  							 
										 }
							    	
							    	
							      }
								while(ola != '4');										
							
							break;
							
	
							
							case '4':
                            system("cls");
                            printf("\nALTERAR CONTA [1]");
                            printf("\n\nALTERAR FUNCIONARIO [2]");
                            printf("\n\nALTERAR CLIENTE [3]");
                            printf("\n\nVOLTAR [4]");                  
                            
							    do
								  {								  	
									ola = getch();
									
									switch(ola)
									    {
									    	case '1':	// caso o usuario escolha alterar conta								    	  
   										       system("cls");
											   printf("\n\nDigite a senha do administrador: ");
											   scanf("%d", &senha);
											   while (getchar() != '\n');
											     
											       if(senha == 1234)
							                          { 
											   			  system("cls");
														  printf("\nDigite o numero da conta que voce deseja alterar: ");
														  scanf("%d", &numero_conta);
														  while (getchar() != '\n');
														  
														  altera_conta(Arquivo, numero_conta);														  
														  system("pause");
														  
														  system("cls");
														  printf("\nALTERAR CONTA [1]");
                                                          printf("\n\nALTERAR FUNCIONARIO [2]");
                                                          printf("\n\nALTERAR CLIENTE [3]");
                                                          printf("\n\nVOLTAR [4]");   														  										    	
									             	  }
													   
												   else
											         {
											          printf("\n\nSenha incorreta! \n");
													  system("pause");
													  
													  system("cls");
                                                      printf("\nALTERAR CONTA [1]");
                                                      printf("\n\nALTERAR FUNCIONARIO [2]");
                                                      printf("\n\nALTERAR CLIENTE [3]");
                                                      printf("\n\nVOLTAR [4]");  	
													 }
													   
											   break;
											   
											   
											   case '2':	// caso o usuario escolha alterar conta								    	  
   										       system("cls");
											   printf("\n\nDigite a senha do administrador: ");
											   scanf("%d", &senha);
											   while (getchar() != '\n');
											     
											       if(senha == 1234)
							                          { 
											   		     system("cls");
														 printf("\nDigite o codigo do funcionario que deseja alterar: ");
														 scanf("%d", &numero_conta);
														 while (getchar() != '\n');     
													   
													     altera_funcionario(Arquivo, numero_conta);	
														 system("pause");
														  
														 system("cls");
														 printf("\nALTERAR CONTA [1]");
                                                         printf("\n\nALTERAR FUNCIONARIO [2]");
                                                         printf("\n\nALTERAR CLIENTE [3]");
                                                         printf("\n\nVOLTAR [4]");   														 		    	
									    	
									             	  }
													   
												   else
											         {
											          printf("\n\nSenha incorreta! \n");
													  system("pause");
													  
													  system("cls");
                                                      printf("\nALTERAR CONTA [1]");
                                                      printf("\n\nALTERAR FUNCIONARIO [2]");
                                                      printf("\n\nALTERAR CLIENTE [3]");
                                                      printf("\n\nVOLTAR [4]");  		
													 }
													   
											   break;	
											   
											   
											   case '3':	// caso o usuario escolha alterar conta								    	  
   										       system("cls");
											   printf("\n\nDigite a senha do administrador: ");
											   scanf("%d", &senha);
											   while (getchar() != '\n');
											     
											       if(senha == 1234)
							                          { 											   					    										    	          
											   			 system("cls");
														 printf("\nDigite o numero da conta que voce deseja alterar: ");
														 scanf("%d", &numero_conta);
														 while (getchar() != '\n');
														 
													     altera_cliente(Arquivo, numero_conta);
													     system("pause");
													     
													      system("cls");
														  printf("\nALTERAR CONTA [1]");
                                                          printf("\n\nALTERAR FUNCIONARIO [2]");
                                                          printf("\n\nALTERAR CLIENTE [3]");
                                                          printf("\n\nVOLTAR [4]"); 
									    	          
									             	  }
													   
												   
												   else
											         {
											          printf("\n\nSenha incorreta! \n");
													  system("pause");
													 
													  system("cls");
                                                      printf("\nALTERAR CONTA [1]");
                                                      printf("\n\nALTERAR FUNCIONARIO [2]");
                                                      printf("\n\nALTERAR CLIENTE [3]");
                                                      printf("\n\nVOLTAR [4]");  		
													 }
													   
											   break;								  								  									  	
								  	
								         }

								    }
								    while (ola != '4');
							
							break;
									
							
							
							case '5':
							system("cls");
							printf("\n\nDigite a senha de admnistrador: ");
							scanf("%d", &senha);
       	                	while (getchar() != '\n'); 
       	                	
       	                	       if(senha == 1234)
       	                	          {
       	                	  	        system("cls");
										printf("===== CADASTRO DE FUNCIONARIO =====");
       	                	  	        
       	                	  	        printf("\n\nCODIGO DO FUNCIONARIO: ");
       	                	  	        scanf("%d", &funcionario.codigo);
       	                	  	        while (getchar() != '\n');
       	                	  	        
       	                	  	        printf("CARGO: ");
       	                	  	        fgets(funcionario.cargo, sizeof(funcionario.cargo), stdin);
									    funcionario.cargo[strcspn(funcionario.cargo, "\n")] = '\0';
       	                	  	        
       	                	  	        printf("NOME DO FUNCIONARIO: ");
       	                	  	        fgets(funcionario.nome, sizeof(funcionario.nome), stdin);
									    funcionario.nome[strcspn(funcionario.nome, "\n")] = '\0';
       	                	  	        
       	                	  	        printf("CPF: ");
       	                	  	        fgets(funcionario.cpf, sizeof(funcionario.cpf), stdin);
									    funcionario.cpf[strcspn(funcionario.cpf, "\n")] = '\0';
       	                	  	        
       	                	  	        printf("DATA DE NASCIMENTO: ");
       	                	  	        fgets(funcionario.nascimento, sizeof(funcionario.nascimento), stdin);
									    funcionario.nascimento[strcspn(funcionario.nascimento, "\n")] = '\0';
       	                	  	        
       	                	  	        printf("TELEFONE: ");
       	                	  	        fgets(funcionario.telefone, sizeof(funcionario.telefone), stdin);
									    funcionario.telefone[strcspn(funcionario.telefone, "\n")] = '\0';
       	                	  	        
       	                	  	        printf("ENDERECO: ");
       	                	  	        fgets(funcionario.endereco, sizeof(funcionario.endereco), stdin);
									    funcionario.endereco[strcspn(funcionario.endereco, "\n")] = '\0';
       	                	  	        
       	                	  	        printf("CEP: ");
       	                	  	        scanf("%d", &funcionario.cep);
       	                	  	        while (getchar() != '\n');
       	                	  	        
       	                	  	        printf("LOCAL: ");
       	                	  	        fgets(funcionario.local, sizeof(funcionario.local), stdin);
									    funcionario.local[strcspn(funcionario.local, "\n")] = '\0';
       	                	  	        
       	                	  	        printf("NUMERO DA CASA: ");
       	                	  	        scanf("%d", &funcionario.numero_casa);
       	                	  	        while (getchar() != '\n');
       	                	  	        
       	                	  	        printf("BAIRRO: ");
       	                	  	        fgets(funcionario.bairro, sizeof(funcionario.bairro), stdin);
									    funcionario.bairro[strcspn(funcionario.bairro, "\n")] = '\0';
       	                	  	        
       	                	  	        printf("CIDADE: ");
       	                	  	        fgets(funcionario.cidade, sizeof(funcionario.cidade), stdin);
									    funcionario.cidade[strcspn(funcionario.cidade, "\n")] = '\0';
       	                	  	        
       	                	  	        printf("ESTADO: ");
       	                	  	        fgets(funcionario.estado, sizeof(funcionario.estado), stdin);
									    funcionario.estado[strcspn(funcionario.estado, "\n")] = '\0';
       	                	  	        
       	                	  	        printf("SENHA DO FUNCIONARIO: ");
       	                	  	        scanf("%d", &funcionario.senha);
       	                	  	        while (getchar() != '\n');     	                	  	         	                	  	        
       	                	  	        
									     	if (insere_funcionario(Arquivo, funcionario))
										    printf("\nFuncionario inserido com sucesso\n");
										
										      else
										      printf("\nErro ao inserir funcionario"); 
										      
										      system("pause");
											  break;          	   	
							         
									  }					      
							       else
							         {
							           printf("\nSenha incorreta!\n");
							           system("pause");
									   							           
								     }	
									 
						    break;
							
							
							
							
							case '6':
							system("cls");
							printf("\nRELATORIO GERAL [1]: ");
							
							ola = getch();
							switch(ola)
							   {
							   	  case '1':
							   	    system("cls");
							      	printf("\n\nDigite a senha de admnistrador: ");
							        scanf("%d", &senha);
       	                	        while (getchar() != '\n'); 
							      
								         if(senha == 1234)
       	                	                  {	 
       	                	                   fclose(Arquivo);
       	                	                   system("cls");
       	                	                   printf("\n\nRELATORIO DE MOVIMENTACAO SENDO EXPORTADO PARA EXCEL.\n");
       	                	                   
											   system("dados.xlsx");
											   Arquivo = fopen("banco.txt", "r+b");
       	                	                   system("pause");
       	                	                   break;   
       	                	                   
       	                	                  }							 			   	  
							   	            else
							                  {
							                    printf("\nSenha incorreta!\n");
							                    system("pause");									   							           
								              }
							  
							   }								
												   							   	
						  } 
						 
       	   	   	       }
		   	          while(ola != '7');
				
					} 
			    	else
					{
       	   	        printf("\nSenha incorreta!\n"); //se a senha for incorreta, mostra uma mensagem e o usuario pode tentar novamente
                    system("pause");
				    }
			break; 
			
					
		
			
			case '2':
				
			do //realiza o programa enquanto o usuario não quiser sair
            {
			   system("cls"); //limpa a tela
		       printf("SALDO [1]");
		  	   printf("\n\nDEPOSITO [2]");
			   printf("\n\nSAQUE [3]");
			   printf("\n\nEXTRATO [4]");
			   printf("\n\nCONSULTAR LIMITE [5]");
			   printf("\n\nSAIR [6]");
			
			      ola = getch();
			      switch(ola)
			        {
			    	   case '1':
			    	   system("cls");	
			    	   printf("\nDigite a senha da conta do cliente: ");
					   scanf("%d", &senha);
					   
					   mostrar_saldo(Arquivo, senha); // chama a função para mostrar o saldo do cliente	
			    	   		    	
                       system("pause");
					   break;	
					   
					   
					   
					   
					   case '2':
					   system("cls");
					   printf("\nDigite o numero da conta que deseja fazer o deposito: ");
					   scanf("%d", &numero_conta);
					   
					   
					   deposita_conta(Arquivo, extrato, numero_conta);
					   system("pause");
					   
					   break;
					   
					   
					   
					   
					   case '3':
					   system("cls");	
					   printf("\nDigite a senha da conta do cliente: ");
					   scanf("%d", &senha);
					   
					   saque(Arquivo, extrato, senha);
					   system("pause");				   
					   
					   break;
					   
					   
					   
					   case '4':
					   system("cls");
					   printf("\nDigite a senha da conta do cliente: ");
					   scanf("%d", &senha);
					   
					   if(senha == 12)// se a senha for igual a 12 mostra o extrato, se não não mostra
					     {
					        ver_extrato(Arquivo, extrato, senha);
				         }
				         
					   else
					   printf("\nconta indisponivel para ver o extrato\n");
					   system("pause");
					   
					   
					   break;
					   
					   
					   
					   case '5':
					   system("cls");
					   printf("\nDigite a senha da conta do cliente: ");
					   scanf("%d", &senha);
					   
					   ver_limite(Arquivo, senha);
					   system("pause");
					   
					   break;
					   				   		    	 
				    } 
				    
				    
		     }while(ola != '6');
			
			break;            	
	   }
   
    }while(opcao != '3');
    
  fclose(extrato);
  fclose(Arquivo);//fecha o arquivo
  }
else
printf("deu ruim");
}
