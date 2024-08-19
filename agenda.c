<<<<<<< HEAD

=======
#include"agendaESTATICA_H.h"

//aqui estou inicializando a agenda
void inicializar_Agenda(Agenda *agenda){
	agenda -> total_contatos = 0; //zero contatos
	
}

//função para adicionar um contato
int adicionar_Contato(Agenda *agenda, Contatos contatos){
	if(agenda -> total_contatos <MAX){
		 agenda -> contatos [agenda -> total_contatos] = contatos; 
		 	
			// aqui esta adicionando um contato 
		   agenda -> total_contatos++;
	}  return 1; // se de certo
	
		return 0; // caso de errado
}	 

int remover_Contato(Agenda *agenda, const char *nome){
		for(i=0; i < agenda -> total_contatos; i++){
			if (strcmp(agenda->contatos[i].nome, nome) == 0) {	  
		} // Move os contatos para preencher o espaço deixado
		
			 for(int k=i; k <agenda -> total_contatos -1; k++){
			 	agenda -> total_contatos [k] = agenda -> contatos [k-1]; 
					
					//aqui estou diminuindo 1 contato
					agenda -> total_contatos--; 
					
			 } return 1;
			 
			 	return 0;
	} 
	
}
Contato* buscar_Contato(Agenda *agenda, const char *nome){
}
void listar_Contatos(Agenda *agenda){
}
>>>>>>> 01bcedcb8c97c6e264fc7555479a518ca3c41a5a
