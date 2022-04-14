
#include <windows.h>
#include <winsock.h>

#include <stdio.h>
#define REMOTE_SERVER_PORT 2023
#define LOCAL_SERVER_PORT 2022
#define SERVIDOR "127.0.0.1"
#define MAX_MSG 100
#define LENGTH 100
char msg[50];

int enviar(){
	//fazer depois 
	FILE *arquivo; //arquvio a ser enviado
	double vet[50]; //vetor
	char *palavras;
 	char  ch;
 	 
	arquivo = fopen("arquivo_do_main_ServidorConvertido.txt", "rb");
	if(arquivo == NULL){
		printf("Erro ao abrir o arquivo do enviar no lado do SERVIDOR.");
	}

	int sd,rc, i;
	struct sockaddr_in cliAddr, remoteServAddr;
	WSADATA wsaData;
	LPHOSTENT lpHostEntry;
	char mensagem[100];

	WSAStartup(MAKEWORD(2,1),&wsaData);

	lpHostEntry = gethostbyname(SERVIDOR);

  /* cira??o do socket */
	sd = socket(AF_INET,SOCK_DGRAM,0);

  	if(sd<0) {
    	printf("\n Nao foi possivel criar o socket com o servidor %s:\n",SERVIDOR);
    	exit(1);
  	}

  	/* bind */// e o ip e a porta 
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
  	memset(mensagem,0,MAX_MSG);
	while((ch = getc(arquivo)) != EOF){//
	
  		fread(&mensagem, sizeof(char), 50, arquivo);
		rc = sendto(sd, mensagem, strlen(mensagem)+1, 0,(LPSOCKADDR) &remoteServAddr, sizeof(struct sockaddr));
   		
		   if(rc<0) {
			printf("%s: Nao foi possivel enviar valor %d \n",i,i-1);
			closesocket(sd);
			exit(1);
		}
	}	
  	if(rc<=0) {
	  	printf("ERRO: Nao foi possivel enviar valor %d \n",i-1);
      	exit(1);
    }

  	rc = sendto(sd, "__fechar", strlen("__fechar")+1, 0,(LPSOCKADDR) &remoteServAddr, sizeof(struct sockaddr));
	if(rc<0) {
		printf("%s: Nao foi possivel enviar valor %d \n",i,i-1);
	}

	fclose(arquivo);
	closesocket(sd);
	printf("\n Processo concluido =) \n");
	return 1;
};
int main(int argc, char *argv[]) {
	int receber =1;
	while(receber =! 0){
		
		FILE *arquivo_do_main_Servidor;
		if((arquivo_do_main_Servidor = fopen("arquivo_do_main_ServidorConvertido.txt", "W+b"))=NULL)
			printf("Erro ao abrir o arquivo_do_main_Servido.");
	
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
//    		enviar(msg);
//			if(num_bytes<0) {
//      			printf("\n Nao foi possivel receber dados \n");
//      			continue;
//    		}
//    		printf("\n Recebido de %s: (UDP) Porta: %u a msg: %s \n", inet_ntoa(cliAddr.sin_addr), ntohs(cliAddr.sin_port),msg);
    		if(num_bytes<0) {
				printf("%s: nao foi possivel receber dados \n",argv[0]);
				continue;
			}
			if(strcmp(msg, "__remove") == 0) {
				fclose(arquivo_do_main_Servidor);
				remove("convertido.txt");
				continue;
			} else if (strcmp(msg, "__fechar") == 0) {
				fclose(arquivo_do_main_Servidor);
				printf("\n Pronto!, enviando para cliente \n");
				enviar();
				continue;
			} else if (strcmp(msg, "__abrir") == 0) {
				arquivo_do_main_Servidor = fopen("arquivo_do_main_ServidorConvertido.txt", "w+");
				continue;
			}
			strupr(msg);
			fwrite(&msg, sizeof(char), 50, arquivo_do_main_Servidor);
  		}
		fclose(arquivo_do_main_Servidor);
 		closesocket(pnt_sck);
 		WSACleanup();//a funcao finalisa o uso do winsocks
 		receber = 0;
	}	
}


// socket service 
