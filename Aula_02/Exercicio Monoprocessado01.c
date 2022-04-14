#include <stdio.h>  
#include <pthread.h>  
#include <unistd.h> 
#include <stdlib.h>
#include <time.h>

/* 
Programação usando Threads - medição de tempo: 

Faça um programa sequencial que:

a) conte de 1 até 9.000.000, mostrando somente os múltiplos de 3,

b) de 1 até 9.000.000, mostrando somente os múltiplos de 5, 

c) de  1 até 9.000.000 mostrando todos múltiplos de 7 e

d) de  1 até 9.000.000 mostrando todos múltiplos de 9

Todos os resultados deverão ser escritos em quatro arquivos diferentes.

Após criar o programa procedural, crie uma versão do mesmo programa usando 4 threads.

Envie os dois códigos fontes e responda, Qual foi o % ganho do tempo de execução?
 */

int main(int argc, char *argv[]) {
	
	int i;
	int mult;
	
	FILE * arquivoMultDe3;
	FILE * arquivoMultDe5;
	FILE * arquivoMultDe7;
	FILE * arquivoMultDe9;
	
	if((arquivoMultDe3 = fopen("arquivoMultDe3.txt", "a+")) == NULL)
		{ printf("Erro ao abrir arquivo 1");
	}	else{
			for(i=0 ; i <=9000000; i++){
				if(i % 3 == 0){
					fprintf(arquivoMultDe3, "%d", i);
				}
		
			}	printf("arquivo escrito 1");
		}
	if((arquivoMultDe5 = fopen("arquivoMultDe5.txt", "a+")) == NULL)
		{ printf("Erro ao abrir arquivo 2");
	}	else{
			for(i=0 ; i <=9000000; i++){
				if(i % 5 == 0){
					fprintf(arquivoMultDe5, "%d", i);
				}
		
			}	printf("\n arquivo 2 escrito ");
		}
	if((arquivoMultDe7 = fopen("arquivoMultDe7.txt", "a+")) == NULL)
		{ printf("Erro ao abrir arquivo 3");
	}	else{
			for(i=0 ; i <=9000000; i++){
				if(i % 7 == 0){
					fprintf(arquivoMultDe7, "%d", i);
				}
		
			}	printf("\n arquivo 3 escrito ");
		}
	if((arquivoMultDe9 = fopen("arquivoMultDe9.txt", "a+")) == NULL)
		{ printf("Erro ao abrir arquivo 4");
	}	else{
			for(i=0 ; i <=9000000; i++){
				if(i % 9 == 0){
					fprintf(arquivoMultDe9, "%d", i);
				}
		
			}	printf("\n arquivo 4 escrito ");
		}
	
	fclose(arquivoMultDe3);
	fclose(arquivoMultDe5);
	fclose(arquivoMultDe7);
	fclose(arquivoMultDe9);
	
	return 0;
}
