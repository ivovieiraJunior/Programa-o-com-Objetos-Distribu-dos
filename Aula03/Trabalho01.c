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

int main(int argc, char *argv[]) {
	clock_t begin = clock();
	char linha[1024];
	char * palavra;
	char * pala;
    int contaPalindromo =0;
	int comparar =0;
	int i=0;
	
	FILE *livro =fopen("livro.txt","r");
		if(livro==NULL){
			printf("Erro na criação do arquivo.");
		}
	else{
			while(!feof(livro))
			{
           		fgets(linha,1024, livro);
					palavra=strtok(linha," ");
					pala=strtok(linha," ");
				while (palavra!=NULL)
				{	
					//comparar de nao tem caracter como ###
					comparar = strcmp(palavra,"##");
					if(comparar != 0){
						str_reverse(pala);//envia a palavra para ser invertida e ja muda no seu Endereço sem retorno 

						comparar = strcmp(palavra,pala);// compara para ver se e igual 
														
						if(comparar == 0){// se igual vai dar zero, 
							contaPalindromo++;
						}
					}
					
					pala=strtok(NULL, " ");//pega a proxima palavra da frase como se fosse um i++;
					palavra=strtok(NULL, " ");

				}
			}	
			
		}

	clock_t end = clock();// tempo de 0.004891 ou 00.3999

    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC ;
    printf("\nTempo percorrido foi de: %fs \n" , time_spent);

	printf("\n Contem %d palindromos \n", contaPalindromo);
	fclose(livro);

	return 0;
}

