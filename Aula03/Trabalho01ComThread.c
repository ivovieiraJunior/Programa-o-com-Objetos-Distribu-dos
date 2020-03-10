#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

/*			Executar um programa (código C) para identificar os palídromos do arquivo TXT.ZIP.

O programa deverá gerar uma saída com a quantidade de palíndromos e o tempo necessário para a identificação dos palíndromos.

Executar em sequencial e em paralelo (mostrar comparação de desempenho).

Trabalho Individual. Vou verificar os programas em software detector de plágio.

Além de entregue por aqui, o trabalho deve ser apresentado na aula do dia 16/03/2020, onde vamos analisar o desempenho dos programas. */

char linha[1024];  // deixando em como ums variavel global para evitar erros
	char * palavra;
	char * pala;
    int contaPalindromo =0;
	int comparar =0;
	int i=0;

void str_reverse(char* str)
{
  char caracter;
  int a, b;

  for(a = 0, b = strlen(str) - 1;  a < b;  ++a, b--)
  {
    caracter = str[a];
    str[a] = str[b];
    str[b] = caracter;
  }
}

void * HelloThread(void * argumento){ //função que retorna um ponteiro "genérico" e recebe argumentos "genéricos"
    pthread_t NumThread; //declara NumThread como um thread
    NumThread = pthread_self(); //NumThread recebe o id do thread onde esta função está rodando

    FILE *livro =fopen("livro.txt","r");//abrir arquivo em modo leitura
		if(livro==NULL){//certificar se ele nao esteja vazio
			printf("Erro na criação do arquivo.");
		}
	else{
			while(!feof(livro))//feof significa fim de de arquivo 
			{
           		fgets(linha,1024, livro);
					palavra=strtok(linha," ");
					pala=strtok(linha," ");
				while (palavra!=NULL)
				{	
					//comparar de nao tem caracter como ###
					comparar = strcmp(palavra,"##");
					if(comparar != 0){
						char palavras[30];
						str_reverse(pala); 

						comparar = strcmp(palavra,pala);

						if(comparar == 0){
							contaPalindromo++;
						}
					}
					
					pala=strtok(NULL, " ");
					palavra=strtok(NULL, " ");

				}
			}	
			
		}

    fclose(livro);//fechamento de arquivo nao esquecer

    return NumThread; //equivalente a chamar pthread_exit(NumThread);
}

int main(int argc, char *argv[]) {
	clock_t begin = clock();
	

    pthread_t thread1;
    int flag1 =0;
    int n1=1;


    flag1 = pthread_create(&thread1, NULL, HelloThread, &n1); //cria o thread com identificador thread que vai executar a função HelloThread
        printf("\nLinha logo após a primeira chamada de pthread_create.");
    if (flag1 != 0) //se retornou um valor diferente de 0 é porque deu erro na criação do thread
        printf("Erro na criação da thread 1!\n");
	
	
    pthread_join(thread1, NULL);

	clock_t end = clock();// tempo foi de 0.009228

    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC ;
    printf("\nTempo percorrido foi de: %fs \n" , time_spent);

	printf("\n Contem %d palindromos \n", contaPalindromo);//empresao dos numero de palindromo

	

	return 0;
}

