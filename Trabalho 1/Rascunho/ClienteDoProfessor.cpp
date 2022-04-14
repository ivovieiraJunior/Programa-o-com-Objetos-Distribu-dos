#include <windows.h>
#include <winsock.h>
#include <stdio.h>
#include <string.h>

#define REMOTE_SERVER_PORT 2022
#define MAX_MSG 100
#define SERVIDOR "127.0.0.1"


struct sRegistro{
	char nome[40]; 
	char email[40]; 
	} typedef sregistro;

int main() {

	sregistro dado; 	
	
  int sd, pnt_bind, i;
  struct sockaddr_in cliAddr, remoteServAddr;
  WSADATA wsaData;
  LPHOSTENT lpHostEntry;
  char mensagem[20];

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

   printf ("\nDigite o nome: ");
   fflush(stdin);
   scanf ("%[ A-Za-z]s", dado.nome); 
   printf ("\nDigite o email: ");
   fflush(stdin);
   scanf ("%[ @A-Za-z]s", dado.email); 
   
   printf ("\nVoce ira enviar: %s e %s  " , dado.nome, dado.email);
   sprintf(mensagem,"%s | %s", dado.nome, dado.email);
  
   
   pnt_bind = sendto(sd,mensagem, strlen(mensagem)+1, 0,(LPSOCKADDR) &remoteServAddr, sizeof(struct sockaddr));
   printf ("\nEnviado : %s " , mensagem);
 
  	if(pnt_bind<=0) {
	  	printf("ERRO: Nao foi possivel enviar valor %d \n",i-1);
      	exit(1);
    }
  }
  closesocket(sd);
  return 1;

}
