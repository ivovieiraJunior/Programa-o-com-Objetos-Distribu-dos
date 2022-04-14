
#include <windows.h>
#include <winsock.h>

#include <stdio.h>

#define LOCAL_SERVER_PORT 2022
#define MAX_MSG 100

int main(int argc, char *argv[]) {

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
    num_bytes = recvfrom(pnt_sck, msg, MAX_MSG, 0, (struct sockaddr *) &cliAddr, &tam_msg);
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


