#include <windows.h>
#include <winsock.h>
#include <stdio.h>
#include <string.h>

#define REMOTE_SERVER_PORT 2022
#define MAX_MSG 100
#define SERVIDOR "127.0.0.1"

//definindo a aminha struct no cliente;
typedef struct Pessoa{
	char menu[5];
	char nome[50];
	char email[100];
	
} Pessoa;

void Mensagens_Do_pnt_bind (int pnt_bind){
	if(pnt_bind<=0) {
      		printf("ERRO pnt_bind: Nao foi possivel enviar a mensagen \n");
		exit(1);					
	}
}

int main() {
	
	//primeiro declarar a minha struct de pessoa EX registro
	Pessoa registro;

  int sd, pnt_bind, num_bytes, tam_msg, i;
  struct sockaddr_in cliAddr, remoteServAddr;
  WSADATA wsaData;
  LPHOSTENT lpHostEntry;
  char mensagem[1024];

  WSAStartup(MAKEWORD(2,1),&wsaData);

  lpHostEntry = gethostbyname(SERVIDOR);

  /* cira??o do socket */
  sd = socket(AF_INET,SOCK_DGRAM,0);

  if(sd<0) {
    printf("\n Nao foi possivel criar o socket com o servidor %s:\n",SERVIDOR);
    exit(1);
  }

  /* bind */
  cliAddr.sin_family = AF_INET;
  cliAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  cliAddr.sin_port = htons(0);

  remoteServAddr.sin_family = AF_INET;
  remoteServAddr.sin_addr = *((LPIN_ADDR)*lpHostEntry->h_addr_list);

  remoteServAddr.sin_port = htons(REMOTE_SERVER_PORT);
	

  int fim = 10000000;
	
	tam_msg = sizeof(cliAddr);
	
  for(i=1;i<fim;i++) {
		//primeiro declarar a minha struct de pessoa EX registro
//		Pessoa registro;
		int MENU =0;

		//fazer depois menu // construição
	
		printf("\n ====== Menu de Opcoes ======== \n");
		printf("\n ====== 1 ) Cadastrar usuario  DIGITE 1 ======== \n");
		printf("\n ====== 2 ) ver todos cadastrados  DIGITE 2 ======== \n");
		printf("\n ====== 3 ) Pesquisa aluno cadastrado  DIGITE 3 ======== \n");
		printf("\n ====== 4 ) Deletar usuario Digite 4 ======== \n");
		printf("\n ====== 5 ) Alterar usuario Digite 5 ======== \n");
		printf("\n ====== 6 ) Sair do Cliente   DIGITE 6 ======== \n");


		scanf("%d", &MENU);
 			 	if(MENU == 1){
				  
   				 	// setar atuomaticamento o regristo.menu == "add" para o servidor reconhecer essa opção.
   				 	sprintf(registro.menu,"add");
//   				 registro.menu == "add";
   				 	// printf("\n ==> menu : %s ==", registro.menu ); // um teste 
   				 	printf("\n ==> CADASTRAR NOVO REGISTRO ==");
   				 	printf("\n ==> Nome: ==");
   				 		fflush(stdin);
   				 			scanf("%[ A-Za-z]s", registro.nome);
   				 	printf("\n ==> Email ==");
   				 		fflush(stdin);
   				 			scanf("%[ @A-Za-z]s", registro.email);
   				 			
   				 	// fazer o sendto; com o seu par revcfrom();
   				 	// ...(sd, (const char*) esta transformando a struct em uma seguincia de byts 
   				 	
   				 	pnt_bind = sendto(sd, (const char*)&registro, sizeof(registro), 0,(LPSOCKADDR) &remoteServAddr, sizeof(struct sockaddr));
   				 		Mensagens_Do_pnt_bind(pnt_bind); //apenas faz o if (pnt_bind <=0)
   				 	
						if((recvfrom(sd, mensagem, 1024, 0, (struct sockaddr *) &cliAddr, &tam_msg)) <0) {
      						printf("\n num_bytes:: Nao foi possivel receber dados \n");	
							continue;				
						}	else{
								printf("\n %s \n\n", mensagem);
							}
							
				continue;
   				}
   				 
  				if(MENU == 2){// setar atuomaticamento o regristo.menu == "psq" para o servidor reconhecer essa opção.
  					printf("\n ==> BUSCANDO TODOS CADASTRADOS:");
  					fflush(stdin);
  					sprintf(registro.menu,"psq");
//  					registro.menu == "psq";
  					registro.nome == " ";
  					registro.email == " ";
  					
  					tam_msg = sizeof(cliAddr);
					// enviando a minha struct com a opção de pesquisa registro.menu == psq
					// ...(sd, (const char*) esta transformando a struct em uma seguincia de byts 
					pnt_bind = sendto(sd, (const char*)&registro, sizeof(registro), 0,(LPSOCKADDR) &remoteServAddr, sizeof(struct sockaddr));
					// fazer o retorn o par desse sendto 
    				while(1){
    					
    					if((recvfrom(sd, mensagem, 1024, 0, (struct sockaddr *) &cliAddr, &tam_msg)) <0) {
      						printf("\n num_bytes:: Nao foi possivel receber dados \n");	
							break;				
						}

						if(strcmp(mensagem, "break")== 0){
    							break;
						}
    					else {	
    						printf("\n %s ", mensagem);
						}
						
					}	
    			}
    			if(MENU == 3){
    					// fazer a pesaqusa por aluno
					 	// setar atuomaticamento o regristo.menu == "bsc" para o servidor reconhecer essa opção.
    				sprintf(registro.menu,"bsc");
					sprintf(registro.email," "); // nao precisar ter mais pra evitar bug
    				
    				printf("\n ==> BUSCAR por Nome: ==");
   				 		fflush(stdin);
   				 			scanf("%[ A-Za-z]s", registro.nome);
   				 			
					pnt_bind = sendto(sd, (const char*)&registro, sizeof(registro), 0,(LPSOCKADDR) &remoteServAddr, sizeof(struct sockaddr));
						Mensagens_Do_pnt_bind(pnt_bind);
					
						
					while(1){// se tiver mais de um fazer uma copia do while dentro do if anterior 
						if((recvfrom(sd, mensagem, 1024, 0, (struct sockaddr *) &cliAddr, &tam_msg)) <0) {
      							printf("\n num_bytes:: Nao foi possivel receber dados \n");	
								break;				
						}	
							if(strcmp(mensagem, "break")== 0){
    							break;
							}
								if(strcmp(mensagem,"NAO ENCONTRADO") ==0){
									printf("\n NAO ENCONTRADO ");
									break;
								}	else{
										printf("\n BUSCAR ENCONTRADA %s \n\n", mensagem);
									}
					}
				}
				if(MENU == 4){
						sprintf(registro.menu,"rem");
						sprintf(registro.email, " ");
//   					registro.menu == "add";
//   				 	printf("\n ==> menu : %s ==", registro.menu ); // um teste 
   				 		printf("\n ==> REMOVER ANTIGO REGISTRO ==");
   				 		printf("\n ==> REMOVER Nome: ==");
   				 		fflush(stdin);
   				 		scanf("%[ A-Za-z]s", registro.nome);
						//mandar a mensagem de remover 
						pnt_bind = sendto(sd, (const char*)&registro, sizeof(registro), 0,(LPSOCKADDR) &remoteServAddr, sizeof(struct sockaddr));
						Mensagens_Do_pnt_bind(pnt_bind);
						// o par do sendto
						
						if((recvfrom(sd, mensagem, 1024, 0, (struct sockaddr *)&cliAddr, &tam_msg)) < 0) {
      						printf("\n num_bytes:: Nao foi possivel receber dados \n");	
							continue;				
						}else{
							printf("\n %s",mensagem);
						}	
						
				}
				if(MENU == 5){
						sprintf(registro.menu,"nov");
//   					registro.menu == "add";
//   				 	printf("\n ==> menu : %s ==", registro.menu ); // um teste 
   				 		printf("\n ==> ALTERAR ANTIGO REGISTRO ==");
   				 		printf("\n ==> ALTERAR Nome: ==");
   				 		fflush(stdin);
   				 		scanf("%[ A-Za-z]s", registro.nome);
						//mandar a mensagem de altera 
						pnt_bind = sendto(sd, (const char*)&registro, sizeof(registro), 0,(LPSOCKADDR) &remoteServAddr, sizeof(struct sockaddr));
						Mensagens_Do_pnt_bind(pnt_bind);
						// o par do sendto
						//recebendo a mendagem com o nome para alterar 
						if((recvfrom(sd, mensagem, 1024, 0, (struct sockaddr *) &cliAddr, &tam_msg)) <0) {
      						printf("\n num_bytes:: Nao foi possivel receber dados \n");	
							continue;				
						}else{     	
							printf("\n %s", mensagem);
									//mandar o novo nome 
								printf("\n ==> NOVO Nome: ==");
   				 				fflush(stdin);
   				 				scanf("%[ A-Za-z]s", registro.nome);
   				 				printf("\n ==> NOVO Email: ==");
   				 				fflush(stdin);
   				 				scanf("%[ @A-Za-z]s", registro.email);
   				 				
									pnt_bind = sendto(sd, (const char*)&registro, sizeof(registro), 0,(LPSOCKADDR) &remoteServAddr, sizeof(struct sockaddr));
							
										if((recvfrom(sd, mensagem, 1024, 0, (struct sockaddr *) &cliAddr, &tam_msg)) <0) {
      									printf("\n num_bytes:: Nao foi possivel receber dados \n");	
											continue;				
										}			
											else{
												printf("\n %s",mensagem);
											}
						}	
				}
				
				if(MENU == 6){
					printf("\n SAINDO DO CLIENTE:");
					return 1;
				}
				if(MENU >= 7 ){
					printf("\n ERROR: OPCAO: %d INVALIDA", MENU);
					continue;
				}
    }
    
  closesocket(sd);
  return 1;
}


