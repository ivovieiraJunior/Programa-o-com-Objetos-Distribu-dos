#include <windows.h>
#include <winsock.h>
#include <stdio.h>
#include <string.h>

#define REMOTE_SERVER_PORT 2018 //2022
#define LOCAL_SERVER_PORT 2019  
#define MAX_MSG 100
#define SERVIDOR "127.0.0.1"
#define LENGTH 100

int enviar(char *file_nome){
	FILE *arquivo;
	double vetor[50];
	char *palavra;
	char ch;
	
	if ((arquivo = fopen("arquivo1.txt","rb")) == NULL)
		{ printf("Erro ao abrir arquivo"); }
	else{
	}
	int sd, rc,i;
	struct sockaddr_in cliAddr, remoteServAddr;
	WSADATA wsaData;
	LPHOSTENT lpHostEntry;
	char mensagem[] = "";
	
	WSAStartup(MAKEWORD(2,1),&wsaData);
	lpHostEntry = gethostbyname(SERVIDOR);
	
	sd = socket(AF_INET,SOCK_DGRAM,0);// criando um socket
	if(sd<0){  //varifica se foi criado
		printf(" socket nao foi possivel ser criado com servidor %s: \n", SERVIDOR);
		exit(1);
	} 
	// bind
		cliAddr.sin_family = AF_INET; // 
			cliAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	cliAddr.sin_port = htons(0);

	remoteServAddr.sin_family = AF_INET;
	remoteServAddr.sin_addr = *((LPIN_ADDR)*lpHostEntry->h_addr_list);

	remoteServAddr.sin_port = htons(REMOTE_SERVER_PORT);
	rc = sendto(sd, "__remove", strlen("__remove")+1, 0 , (LPSOCKADDR) &remoteServAddr, sizeof(struct sockaddr));
	memset(mensagem, 0, LENGTH);
	
	while(!feof(arquivo)){
		fscanf(arquivo, "%s", mensagem);
		printf(" %s \n", mensagem);
		i++;
	}
	
}

int main(int argc, char *argv[]) {
	FILE * arquivo;
	enviar("arquivo1.txt");
}

