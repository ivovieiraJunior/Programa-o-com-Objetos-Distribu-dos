#include <windows.h>
#include <winsock.h>
#include <stdio.h>
#include <string.h>

#define REMOTE_SERVER_PORT 2022
#define MAX_MSG 100
#define SERVIDOR "127.0.0.1"

struct pessoa({
	// char menu() // mandar pro servidor e la sera tratado 
	
	char nome[50];
	char email[50];
	
};typedef struct pessoa;// arrumar depois 

int main() {
	//fazer um scanf no registro.nome .email
	pessoa registro;
	registro.nome
	
  int sd, pnt_bind, i;
  struct sockaddr_in cliAddr, remoteServAddr;
  WSADATA wsaData;
  LPHOSTENT lpHostEntry;
  char mensagem[20];

  WSAStartup(MAKEWORD(2,1),&wsaData);

  lpHostEntry = gethostbyname(SERVIDOR);

  /* cira??o do socket */
  // renomiar sd como socket 
  // pode crair varios sockts 
  sd = socket(AF_INET,SOCK_DGRAM,0);// e um canol de comunicação 

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
	
	printf("\n digite a opçao ===== \n ");
	printf("\n digite a opçao ===== \n ");
	printf("\n digite a opçao ===== \n ");
   sprintf(mensagem, "aluno email");
   printf("\nEnviando: %s", mensagem);
   getchar();
				//mensagen e a variavel que estou enviando 
				//fazer uma struct e enviar 
				//sd e o sockt como se fosse uma porta
				//mensagem aque e a varaiavel que eu estou enviar no caso vai ser registro
				//strlen(mensagem) e o tamanho da string mudar para sizeof(registro);
   pnt_bind = sendto(sd, mensagem, strlen(mensagem)+1, 0,(LPSOCKADDR) &remoteServAddr, sizeof(struct sockaddr));
   //
//   pnt_bind = recvfrom(sd, mensagem, strlen(mensagem)+1, 0,(LPSOCKADDR) &remoteServAddr, sizeof(struct sockaddr));
   
   //fazer um sendto para todas as acoes ex cadastro envio o nome e email recebo um ok oi falho;
   //na pesquisa eu vou enviar o nome a servidor vai me mandar email
   
  
  	if(pnt_bind<=0) {
	  	printf("ERRO: Nao foi possivel enviar valor %d \n",i-1);
      	exit(1);
    }
  }
  closesocket(sd);
  return 1;

}

