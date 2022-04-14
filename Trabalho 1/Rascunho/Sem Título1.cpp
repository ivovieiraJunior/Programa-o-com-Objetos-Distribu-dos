
#include <windows.h>
#include <winsock.h>
#include <stdio.h>

#define LOCAL_SERVER_PORT 2018
#define MAX_MSG 4096

int main(int argc, char *argv[]) {
  
	int sd, cliLen;
	struct sockaddr_in cliAddr, servAddr;
	char msg[MAX_MSG];

	WSADATA wsaData;
	WSAStartup(MAKEWORD(2,1),&wsaData);
  
	sd=socket(AF_INET, SOCK_DGRAM, 0);
 
	if(sd < 0) {
		printf("%s: Nao foi possivel abrir o socket \n",argv[0]);
		exit(1);
	}

	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(LOCAL_SERVER_PORT);
  
	if(bind (sd, (struct sockaddr *) &servAddr,sizeof(servAddr)) < 0) {
		printf("%s: nao foi possivel associar a porta %d \n", argv[0], LOCAL_SERVER_PORT);
		exit(1);
	}

	printf("%s: Aguardando dados na porta UDP %u\n", argv[0],LOCAL_SERVER_PORT);

	char bufferMaiusculo[MAX_MSG];
	while(1) {
		memset(msg, 0x0, MAX_MSG);
		cliLen = sizeof(cliAddr);
		if(recvfrom(sd, msg, MAX_MSG, 0, (struct sockaddr *) &cliAddr, &cliLen) < 0) {
			printf("Nao foi possivel receber dados \n");
			continue;
		}else{
			printf("%s:Recebido de %s:UDP Porta: %u a msg: %s \n", argv[0],inet_ntoa(cliAddr.sin_addr), ntohs(cliAddr.sin_port),msg);
			for(int i=0; i<strlen(msg); i++){
				msg[i] = toupper(msg[i]);
			}

			if(sendto(sd, msg, strlen(msg)+1, 0,(LPSOCKADDR) &cliAddr, sizeof(struct sockaddr)) < 0) {
				printf("Nao foi possivel enviar a mensagem \n");
				closesocket(sd);
				exit(1);
			}
		}
	}

closesocket(sd);
WSACleanup();
return 0;
}

