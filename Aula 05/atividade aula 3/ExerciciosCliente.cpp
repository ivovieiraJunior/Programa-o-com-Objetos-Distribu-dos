#include <windows.h>
#include <winsock.h>
#include <stdio.h>
#include <string.h>

#define REMOTE_SERVER_PORT 2022
#define LOCAL_SERVER_PORT 2023
#define MAX_MSG 100
#define SERVIDOR "127.0.0.1"
#define LENGTH 100

char nomeArquivo[50];

int enviar(char *nomeArquivo){
	int sd, i, rc;
	char ch;
	
	FILE * arquivo_do_enviar;
	if((arquivo_do_enviar = fopen(nomeArquivo, "rb")) == NULL)
		printf("Erro no abrir arquivo do enviar no lado do CLIENTE");
		
  	struct sockaddr_in cliAddr, remoteServAddr;
  	WSADATA wsaData;
  	LPHOSTENT lpHostEntry;
  	char mensagem[MAX_MSG];

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
	rc = sendto(sd, "__remove", strlen("__remove")+1, 0,(LPSOCKADDR) &remoteServAddr, sizeof(struct sockaddr));
	if(rc<0) {
		printf("%s: Nao foi possivel enviar valor %d \n",i,i-1);
	}
	
	rc = sendto(sd, "__abrir", strlen("__abrir")+1, 0,(LPSOCKADDR) &remoteServAddr, sizeof(struct sockaddr));
	if(rc<0) {
		printf("%s: Nao foi possivel enviar valor %d \n",i,i-1);
	}
	memset(mensagem,0, LENGTH);
  	while((ch = getc(arquivo_do_enviar)) != EOF) {
//  		memset(mensagem,0,MAX_MSG);
//  		cliLen = sizeof(cliAddr);
//			printf("\n Digite sua mensagem:" );
//			scanf("%s", mensagem);// envia palavra por palavra
//   		getchar();
		fread(&mensagem, sizeof(char), 50, arquivo_do_enviar);
		
   		rc = sendto(sd, mensagem, strlen(mensagem)+1, 0,(LPSOCKADDR) &remoteServAddr, sizeof(struct sockaddr));// manda e recebe
  	
	  	if(rc<=0) {// confere se deu error 
	  		printf("ERRO: Nao foi possivel enviar valor %d \n",i-1);
			closesocket(sd);			
			exit(1);
   		}
  	}
  	rc = sendto(sd, "__fechar", strlen("__fechar")+1, 0,(LPSOCKADDR) &remoteServAddr, sizeof(struct sockaddr));
  	if(rc<0) 
		printf("%s: Nao foi possivel enviar valor %d \n",i,i-1);

	fclose(arquivo_do_enviar);
  	closesocket(sd);
  	return 1;
};

int main(int argc, char *argv[]) {
	pontoInicial:
	printf("\nDigite nome do aquivo a ser enviado incluindo o Tipo ex(.txt): ");
	gets(nomeArquivo);// pega o nome do arquivo
	enviar(nomeArquivo);
	
	FILE *arquivo_do_main;
//	if((arquivo_do_main = fopen(nomeArquivo , "w+b")) == NULL){
//		printf("\nErro ao abri o arquivo do main");
//	}
//	else*/{
		goto pontoInicial; // volta para o pontoInicial para poder escrever de novo e sempre esta escrevendo sem trancar 
//	} 
	
	
	
	int pnt_sck, pnt_bind, num_bytes, tam_msg;
  	struct sockaddr_in cliAddr, servAddr;
  	char msg[MAX_MSG];
  	WSADATA wsaData;
  	WSAStartup(MAKEWORD(2,1),&wsaData);// funcao que inicializa os winsocks
  									

  	pnt_sck=socket(AF_INET, SOCK_DGRAM, 0);// criando um socket do servidor precisa criar do cliente 


  	if(pnt_sck<0) {
    	printf("\n %s: Nao foi possivel abrir o socket \n",argv[0]);
    	exit(1);
  	}

  	servAddr.sin_family = AF_INET;// define o protocolo de tranporte, como UDP
  	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);// o endereco IP
  	servAddr.sin_port = htons(LOCAL_SERVER_PORT);// O numero da porta a ser Utilizada nessa processo
  
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
    	num_bytes = recvfrom(pnt_sck, msg, MAX_MSG, 0, (struct sockaddr *) &cliAddr, &tam_msg); //pnt_bind = sendto(pnt_sck, msg, MAX_MSG, 0, (struct sockaddr *) &cliAddr, &tam_msg);
   		if(num_bytes<0) {
      		printf("\n Nao foi possivel receber dados \n");
      		continue;
    	}
    	if(strcmp(msg, "__remove") == 0) {
			fclose(arquivo_do_main);
		//	remove("arquivotextconvetido.txt");
			continue;
		} else if (strcmp(msg, "__fechar") == 0) {
		//	fclose(arquivo_do_main);
			printf("\n Processo concluido =) \n");
			continue;
		} else if (strcmp(msg, "__abrir") == 0) {
		//	arquivo_do_main = fopen("arquivotextconvetido.txt", "w+");
			continue;
		}
		fwrite(&msg, sizeof(char), 50, arquivo_do_main);
    }

 	closesocket(pnt_sck);
 	WSACleanup();//a funcao finalisa o uso do winsocks
 // 	return 1;
}

