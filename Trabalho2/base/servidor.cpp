

// fazer o servidor receber os dados e mostrar na tela
// se mostrar na tela mandar escrever no asquivo 



#include <windows.h>
#include <winsock.h>

#include <stdio.h>

#define LOCAL_SERVER_PORT 2022
#define MAX_MSG 100
// mesma struct do cliente

int main(int argc, char *argv[]) {
	// so servidor arquivo no cliente nao 
	//
	
	
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
  ///
//  sockaddr_in client;
//  int clientLength = sizeof(client);
//  ZeroMemory(&client, clientLength);
//  
//  char buf[1024];
//  
//
//  printf("\n Iniciando o Servidor: \n %s \n", argv[0]   );
//
//  printf("\nAguardando dados na porta UDP: %u\n", LOCAL_SERVER_PORT);
//
//	while(true){// depois comentar eke 
//		ZeroMemory(buf, 1024);
//		int bytesIn = recvfrom(pnt_sck, buf, 1024, 0, (sockaddr*)&client, &clientLength);
//		if (bytesIn == SOCKET_ERROR){
//			printf("\n Nao foi possivel receber dados \n");
//			continue;
//		}
//		char clientIp[256];
//		ZeroMemory(clientIp, 256);
//		
//		inet_ntop(AF_INET, &client.sin_addr, clientIp, 256);
//	}

  while(1) { 
    memset(msg,0x0,MAX_MSG);// aqui nao vai mais precisar 
    tam_msg = sizeof(cliAddr);//
    	//msg e a variavel que o servidor ta recebendo msg tenho que declarar que ela e uma strct de pessoa EX: msg.nome e msg.email
    	//MAX_Msg vai virar um sizeof(MSG) que é o tamnho da minha struct 
    num_bytes = recvfrom(pnt_sck, msg, MAX_MSG, 0, (struct sockaddr *) &cliAddr, &tam_msg);
    //mostrar os dados recebidos printf("msg.nome + msg.email");
    
    //num_bytes = sendto(pnt_sck, msg, MAX_MSG, 0, (struct sockaddr *) &cliAddr, &tam_msg); // por enquanto deixar pra depois 
    if(num_bytes<0) {
      printf("\n Nao foi possivel receber dados \n");
      continue;
    }
    printf("\n Recebido de %s: (UDP) Porta: %u a msg: %s \n", inet_ntoa(cliAddr.sin_addr), ntohs(cliAddr.sin_port),msg);
    
  }

 closesocket(pnt_sck);
 WSACleanup();
return 0;
}


