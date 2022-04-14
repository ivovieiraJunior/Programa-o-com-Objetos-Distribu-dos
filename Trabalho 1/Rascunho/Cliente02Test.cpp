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


int main() {
	
	//primeiro declarar a minha struct de pessoa EX registro
	Pessoa registro;
	
//	// fazer o a pergunta
//	printf("\n digite o nome: ");
//	scanf("%s", registro.nome);
//	printf("\n nome e: %s ", registro.nome);
//	printf("\n digite o email: ");
//	scanf("%s", registro.email);
//	printf("\n nome e: %s ", registro.email);
	//fazer depois menu 
	
	

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
	
  for(i=1;i<fim;i++) {
	//primeiro declarar a minha struct de pessoa EX registro
	Pessoa registro;
	
	// fazer o a pergunta
	printf("\n digite o menu: ");
	fflush(stdin);
	scanf("%[ A-Za-z]s", registro.menu);
	printf("\n digite o nome: ");
	fflush(stdin);
	scanf("%[ A-Za-z]s", registro.nome);
//	printf("\n nome e: %s ", registro.nome);
	printf("\n digite o email: ");
	fflush(stdin);
	scanf("%[ @A-Za-z]s", registro.email);
	printf("\n nome e: %s ", registro.email);
	//fazer depois menu 

	pnt_bind = sendto(sd, (const char*)&registro, sizeof(registro), 0,(LPSOCKADDR) &remoteServAddr, sizeof(struct sockaddr));
	
	tam_msg = sizeof(cliAddr);
//	num_bytes = recvfrom(sd, mensagem, 1024, 0, (struct sockaddr *) &cliAddr, &tam_msg);
// receber a mensagem do servidor 	
//    	if(num_bytes<0) {
//      	printf("\n Nao foi possivel receber dados \n");
//    	}else{
    		while(1){
    			
    			num_bytes = recvfrom(sd, mensagem, 1024, 0, (struct sockaddr *) &cliAddr, &tam_msg);
    			if(num_bytes<0) {
      				printf("\n Nao foi possivel receber dados \n");
      				
				}
				if(strcmp(mensagem, "break")== 0){
    							break;
				}
    			else {	
    				printf("nome:   email:");
    				printf("\n %s\n ", mensagem);
				}
						
			}	
//    p	nt_bind = sendto(sd, mensagem, strlen(mensagem)+1, 0,(LPSOCKADDR) &remoteServAddr, sizeof(struct sockaddr));
  
  	if(pnt_bind<=0) {
	  	printf("ERRO: Nao foi possivel enviar valor %d \n",i-1);
      	exit(1);
    }
  }
  closesocket(sd);
  return 1;

}

