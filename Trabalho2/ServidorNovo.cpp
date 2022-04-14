
#include <windows.h>
#include <winsock.h>

#include <stdio.h>

#define LOCAL_SERVER_PORT 2022
#define MAX_MSG 1024
typedef struct Pessoa{
	char menu[5];
	char nome[50];
	char email[100];
}Pessoa;

FILE *arquivo;


int main(int argc, char *argv[]) {
	
	//declarando a struturar
	Pessoa registro;
	

  int pnt_sck, pnt_bind, num_bytes, tam_msg;
  struct sockaddr_in cliAddr, servAddr;
  char msg[MAX_MSG];

  WSADATA wsaData;
  WSAStartup(MAKEWORD(2,1),&wsaData);

  pnt_sck=socket(AF_INET, SOCK_DGRAM, 0);


  if(pnt_sck<0) {
    printf("\n %s: Nao foi possivel abrir o socket \n",argv[0]);
    exit(1);
  }

  servAddr.sin_family = AF_INET;
  servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servAddr.sin_port = htons(LOCAL_SERVER_PORT);
  
  pnt_bind = bind (pnt_sck, (struct sockaddr *) &servAddr,sizeof(servAddr));

  if(pnt_bind<0) {
    printf("\n Nao foi possivel associar a porta %d \n", LOCAL_SERVER_PORT);
    exit(1);
  }

  printf("\n Iniciando o Servidor: \n %s \n", argv[0]   );

  printf("\nAguardando dados na porta UDP: %u\n", LOCAL_SERVER_PORT);

  while(1) {
  	
  		memset(msg,0x0,MAX_MSG);
    	tam_msg = sizeof(cliAddr);
    	num_bytes = recvfrom(pnt_sck, (char*)&registro, sizeof(registro), 0, (struct sockaddr *) &cliAddr, &tam_msg);
    	if(num_bytes<0) {
      	printf("\n Nao foi possivel receber dados \n");
    	  continue;
    	}
    	/// ======== ADICIONAR =========
    	if(strcmp(registro.menu, "add") == 0){
    		memset(msg,0x0,MAX_MSG);
    		printf("\n entrou no if add\n");
    		
			if((arquivo = fopen("arquivo.txt", "a+b")) == NULL){
				printf("\n Erro ao abrir o arquivo_do_main_Servidor.");
					
			}else{
				fprintf(arquivo, "\n%s %s", &registro.nome, &registro.email);
				printf("\n escrito com sucesso!!!");
				fclose(arquivo);
				//mensagen para o cliente dizedo uqe foi sucesso
				sprintf(msg,"\n escrito com sucesso!!!");
				pnt_bind = sendto(pnt_sck, msg, strlen(msg)+1, 0,(LPSOCKADDR) &cliAddr, sizeof(struct sockaddr));
			}			
//    		fazer ele add no arquivo
 			continue;
		}
		/// ======== PESQUISA ===========
		if(strcmp(registro.menu, "psq")==0){
			memset(msg,0x0,MAX_MSG);
				if((arquivo = fopen("arquivo.txt", "a+b")) == NULL){
				printf("Erro ao abrir o arquivo_do_main_Servidor.");
					
			}else{
				char nome[50] = " ";
				char email[100] = " ";
				int i = 0;
				while(!feof(arquivo)){
					nome == " ";
					email == " ";
					fscanf(arquivo, "%s %s", nome, email );
						printf("\n nome: %s   email: %s", nome, email);
						sprintf(msg,"%s | %s", nome, email);
						pnt_bind = sendto(pnt_sck, msg, strlen(msg)+1, 0,(LPSOCKADDR) &cliAddr, sizeof(struct sockaddr));
//						sendto pro cliente ehehheheheh
		
						if(!feof(arquivo)==NULL){
							pnt_bind = sendto(pnt_sck, "break", 20, 0,(LPSOCKADDR) &cliAddr, sizeof(struct sockaddr));
					}
					i++;
				}
				
			}
						
//    		fazer ele pessquisar no arquivo
			fclose(arquivo);
 			continue;
		}
		/// ========== BUSCAR ==========
		if(strcmp(registro.menu, "bsc")==0){
			memset(msg,0x0,MAX_MSG);
				if((arquivo = fopen("arquivo.txt", "a+b")) == NULL){
				printf("Erro ao abrir o arquivo_do_main_Servidor.");
					
			}else{
				char nome[50];
				char email[100];
				int i = 0;
				int encontrados = 0;
				while(!feof(arquivo)){
					fscanf(arquivo, "%s %s", nome, email );
					
					if(strcmp(registro.nome, nome)==0){
						encontrados++;
						printf("\n ENCONTRADO pelo nome: %s  email: %s", nome, email);
						
						memset(msg,0x0,MAX_MSG);
						sprintf(msg,"nome: %s  email: %s", nome, email);
						
						pnt_bind = sendto(pnt_sck, msg, strlen(msg)+1, 0,(LPSOCKADDR) &cliAddr, sizeof(struct sockaddr));
//							sendto pro cliente ehehheheheh	
						memset(msg,0x0,MAX_MSG);			
					}
					if(!feof(arquivo) == NULL){
						pnt_bind = sendto(pnt_sck, "break", 20, 0,(LPSOCKADDR) &cliAddr, sizeof(struct sockaddr));
					}
					i++;
				}	
					if(encontrados == 0){
						printf("\n NAO ENCONTRADO");
						sprintf(msg,"NAO ENCONTRADO");
						pnt_bind = sendto(pnt_sck, msg, strlen(msg)+1, 0,(LPSOCKADDR) &cliAddr, sizeof(struct sockaddr));
					}			
				
			}
						
//    		fazer ele pessquisar no arquivo
			fclose(arquivo);
 			continue;
		}
		/// ========== ESCLUIR ===========
		if(strcmp(registro.menu,"rem") == 0){ // Sao duas atapas primeiro abre o arquivo le todos que nao sao igual e fecha 
											 // segunda abre o arquivo de modo que nao ira add no fim e sim sobre escrever tudo 
			//remover usando lista encadeada 
				//  variaveis do while
					char nome[50];
					char email[100];
					int i = 0;
					int finalDeVetor = 0;
					
			if((arquivo = fopen("arquivo.txt", "a+b")) == NULL){
				printf("Erro ao abrir o arquivo_do_main_Servidor.");
					
				}	else{
						while(!feof(arquivo)){
							fscanf(arquivo, "%s %s", nome, email );
							finalDeVetor++;
							i++;
						}
					fclose(arquivo);
				}
				printf("\n tamanho de cadastros: %d", finalDeVetor);
				printf("\n tamanho de linha no arquivo: %d", i);
			Pessoa cadastrados[finalDeVetor];
			i=0;
//			 while(i<= 30){ // testa pra ver se esta cheio
//			 	printf("\n %s",cadastrados[i]);
//			 	i++;
//			 }
				
				// primeira Parte
				if((arquivo = fopen("arquivo.txt", "a+b")) == NULL){
				printf("Erro ao abrir o arquivo_do_main_Servidor.");
					
				}	else{
						sprintf(nome,"nada");
						sprintf(email, "nada");
						// ler o arquivo e e registrar no vetor pra depois registrar de novo no arquivo 
						i = 0;
						while(!feof(arquivo)){
							fscanf(arquivo, "%s %s", nome, email );
							if(strcmp(nome, registro.nome) == 0){
								printf("\n Nome encontrado: %s", registro.nome);
								i--;
							}else{						
								sprintf(cadastrados[i].nome, "%s", nome); //salvar todo nome que nao é igual
								printf("\n vetor:%d , nome: %s ",i ,cadastrados[i].nome, cadastrados[i].email);
								sprintf(cadastrados[i].email, "%s", email); //salvar todo email que nao é igual
								printf("email: %s ", cadastrados[i].email);
							}
							i++;
//							finalDeVetor++;	
						}
						fclose(arquivo);
				}
				// segunga parte
				i = 0;
				if((arquivo = fopen("arquivo.txt", "w")) == NULL){
				printf("Erro ao abrir o arquivo_do_main_Servidor.");
					
				}	else{
						fprintf(arquivo,"%s %s",cadastrados[i].nome, cadastrados[i].email);
						i++;
						while(i < finalDeVetor-1){
							fprintf(arquivo, "\n%s %s",cadastrados[i].nome, cadastrados[i].email);
							i++;
						}
						fclose(arquivo);
					}
			memset(msg,0x0,MAX_MSG);
			sprintf(msg, "REMOVIDO TODO OS ENCONTRADOS COM NOME OFERICIDO");
			pnt_bind = sendto(pnt_sck, msg, strlen(msg)+1, 0,(LPSOCKADDR) &cliAddr, sizeof(struct sockaddr));
//			remove((const char*)&cadastrados);	
			continue;
		}
			/// ========== alterar ===========
		if(strcmp(registro.menu,"nov") == 0){ // receber dois parametros 
		
											 // Sao duas atapas primeiro abre o arquivo le todos que nao sao igual e fecha 
			memset(msg,0x0,MAX_MSG);						 // segunda abre o arquivo de modo que nao ira add no fim e sim sobre escrever tudo 
			//remover usando lista encadeada 
				//  variaveis do while
					char nome[50];
					char email[100];
					int i = 0;
				
			int finalDeVetor = 0;
			
			Pessoa cadastrados01[1000];
				
				// primeira Parte
				if((arquivo = fopen("arquivo.txt", "a+b")) == NULL){
				printf("Erro ao abrir o arquivo_do_main_Servidor.");
					
				}	else{
					sprintf(nome,"nada");
						sprintf(email, "nada");
						// ler o arquivo e e registrar no vetor pra depois registrar de novo no arquivo 
						while(!feof(arquivo)){
							fscanf(arquivo, "%s %s", nome, email );
							if(strcmp(nome, registro.nome) == 0){
								fflush(stdin);
								printf("\n Nome encontrado: %s",nome);
								// aqui vai receber e alterar com recvfrom
								fflush(stdin);
									printf("\n Esperado novo Nome: ");
								sprintf(msg,"NOME encontrado: %s  %s",nome, email);
								//mandar o nome e pedir pra alterar
								pnt_bind = sendto(pnt_sck, msg, strlen(msg)+1, 0,(LPSOCKADDR) &cliAddr, sizeof(struct sockaddr)); // mandao a mensagem dizendo pra nandar o nome
								//receber a nova struct ja alterada 
								num_bytes = recvfrom(pnt_sck, (char*)&registro, sizeof(registro), 0, (struct sockaddr *) &cliAddr, &tam_msg);	
									printf("\nrecebido novo nome: %s %s",registro.nome, registro.email);	
    								if(num_bytes<0) {
      								printf("\n Nao foi possivel receber dados \n");
    								  continue;
    								}	
										else{
											fflush(stdin);
    										sprintf(cadastrados01[i].nome, "%s", registro.nome); //copiando o novo nome para dentro 
    										sprintf(cadastrados01[i].email, "%s", registro.email); //copiando o novo email para dentro
    										fflush(stdin);
    										memset(msg,0x0,MAX_MSG);
    										sprintf(msg,"altedado com sucesso!!");
    										// tratar o recebimento de sucesso
											pnt_bind = sendto(pnt_sck, msg, strlen(msg)+1, 0,(LPSOCKADDR) &cliAddr, sizeof(struct sockaddr));
										}
							}else{						
								sprintf(cadastrados01[i].nome, "%s", nome); //salvar todo nome que nao é igual
								sprintf(cadastrados01[i].email, "%s", email); //salvar todo email que nao é igual
							}
							i++;
							finalDeVetor++;	
						}
						fclose(arquivo);
				}
				// segunga parte
				printf("\nfinal do vetor: %d",finalDeVetor);
				printf("\nfinal do arquivo: %d",i);
				i = 0;
				if((arquivo = fopen("arquivo.txt", "w")) == NULL){
				printf("Erro ao abrir o arquivo_do_main_Servidor.");
					
				}	else{
					//arrumar o enprimeir na tela 
						fprintf(arquivo, "%s %s",cadastrados01[i].nome, cadastrados01[i].email);
						i++;
						while(i < finalDeVetor){
							fprintf(arquivo, "\n%s %s",cadastrados01[i].nome, cadastrados01[i].email);
							i++;
						}
						fclose(arquivo);
					}
			memset(msg,0x0,MAX_MSG);
			sprintf(msg, "ALTERADO TODOS OS ENCONTRADOS COM NOME OFERICIDO");
			pnt_bind = sendto(pnt_sck, msg, strlen(msg)+1, 0,(LPSOCKADDR) &cliAddr, sizeof(struct sockaddr));
			remove((const char*)&cadastrados01);	
			continue;
		}
		//// ======= sair NAO IMPLEMNTADO ======== SOMENTE NO CLIENTE
		if(strcmp(registro.menu, "sai")== 0){
//    		fazer ele sai no arquivo
		}
    	printf("\n Recebido de %s: (UDP) Porta: %u a msg:menu:%s  %s e %s \n", inet_ntoa(cliAddr.sin_addr), ntohs(cliAddr.sin_port),registro.menu,registro.nome, registro.email);
    
 	}

 closesocket(pnt_sck);
 WSACleanup();
return 0;
}


