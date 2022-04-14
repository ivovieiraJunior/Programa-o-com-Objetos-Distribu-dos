#include <windows.h>
#include <winsock.h>
#include <stdio.h>
#include <string.h>
#define REMOTE_SERVER_PORT 2019
#define LOCAL_SERVER_PORT 2018
#define MAX_MSG 100
#define CLIENTE "127.0.0.1"
#define LENGTH 100

// função que envia o arquivo
int enviar(){
	FILE *arquivos;
	double vet[50];
	char *palavras;
	char ch;
	
	//abre o arquivo
	arquivos = fopen("convertido.txt", "rb");
		if(arquivos == NULL){
		printf("Erro ao abrir o arquivo.");
	}


	int sd, rc, i;
	struct sockaddr_in cliAddr, remoteServAddr;
	WSADATA wsaData;
	LPHOSTENT lpHostEntry;
	char mensagem[100];

	WSAStartup(MAKEWORD(2,1),&wsaData);

	lpHostEntry = gethostbyname(CLIENTE);

	/* cira??o do socket */
	sd = socket(AF_INET,SOCK_DGRAM,0);

	if(sd<0) {
		printf("Nao foi possivel criar o socket com o servidor %s:\n",CLIENTE);
		exit(1);
	}

	/* bind */
	cliAddr.sin_family = AF_INET;
	cliAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	cliAddr.sin_port = htons(0);

	remoteServAddr.sin_family = AF_INET;
	remoteServAddr.sin_addr = *((LPIN_ADDR)*lpHostEntry->h_addr_list);

	remoteServAddr.sin_port = htons(REMOTE_SERVER_PORT);


	rc = sendto(sd, "__remove", strlen("__remove")+1, 0,(LPSOCKADDR) &remoteServAddr, sizeof(struct sockaddr));
	if(rc<0) {
		printf("%s: Nao foi possivel enviar valor %d \n",i,i-1);
	}
	
	rc = sendto(sd, "__abrir", strlen("__abrir")+1, 0,(LPSOCKADDR) &remoteServAddr, sizeof(struct sockaddr));
	if(rc<0) {
		printf("%s: Nao foi possivel enviar valor %d \n",i,i-1);
	}
	memset(mensagem, 0x0, LENGTH); //teste zerar mesangem
	while((ch = getc(arquivos)) != EOF) 
	{
		fread(&mensagem, sizeof(char), 50, arquivos);
		//printf("%s", mensagem); //teste
		
		rc = sendto(sd, mensagem, strlen(mensagem)+1, 0,(LPSOCKADDR) &remoteServAddr, sizeof(struct sockaddr));
		if(rc<0) {
			printf("%s: Nao foi possivel enviar valor %d \n",i,i-1);
			closesocket(sd);
			exit(1);
		}

	}

	rc = sendto(sd, "__fechar", strlen("__fechar")+1, 0,(LPSOCKADDR) &remoteServAddr, sizeof(struct sockaddr));
	if(rc<0) {
		printf("%s: Nao foi possivel enviar valor %d \n",i,i-1);
	}

	fclose(arquivos);
	closesocket(sd);
	printf("\n Processo concluido =) \n");
	return 1;
}

int main(int argc, char *argv[]) {
	int receber=1;
	while(receber =! 0){
		
	
	FILE *arquivo;
	char texto[50];
	char *palavra;
	arquivo = fopen("convertido.txt", "w+b");

	if(arquivo == NULL){
			printf("Erro ao abrir o arquivo.");
		}

	int sd, rc, n, cliLen;
	struct sockaddr_in cliAddr, servAddr;
	char msg[MAX_MSG];


	WSADATA wsaData;
	WSAStartup(MAKEWORD(2,1),&wsaData);

	sd=socket(AF_INET, SOCK_DGRAM, 0); //cria o socket

	if(sd<0) {
		printf("%s: Nao foi possivel abrir o socket \n",argv[0]);
		exit(1);
	}

	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(LOCAL_SERVER_PORT);
	
	rc = bind (sd, (struct sockaddr *) &servAddr,sizeof(servAddr)); //assicia a porta com o socket
	if(rc<0) {
		printf("%s: nao foi possivel associar a porta %d \n", argv[0], LOCAL_SERVER_PORT);
		exit(1);
	}

	printf("\n Aguardando dados na porta UDP %u\n", LOCAL_SERVER_PORT);

	while(1) {
		memset(msg,0x0,MAX_MSG); //seta na memoria, zera a variavel de recebimento
		cliLen = sizeof(cliAddr);
		n = recvfrom(sd, msg, MAX_MSG, 0, (struct sockaddr *) &cliAddr, &cliLen); //faz o recebimento
		if(n<0) {
			printf("%s: nao foi possivel receber dados \n",argv[0]);
			continue;
		}
		if(strcmp(msg, "__remove") == 0) {
			fclose(arquivo);
			remove("convertido.txt");
			continue;
		} else if (strcmp(msg, "__fechar") == 0) {
			fclose(arquivo);
			printf("\n Pronto!, enviando para cliente \n");
			enviar();
			continue;
		} else if (strcmp(msg, "__abrir") == 0) {
			arquivo = fopen("convertido.txt", "w+");
			continue;
		}
		strupr(msg);
		fwrite(&msg, sizeof(char), 50, arquivo);
	}
	fclose(arquivo);
	closesocket(sd); //fecha o socket
	WSACleanup(); //libera a api do windwos

	receber = 0;
 }
}

