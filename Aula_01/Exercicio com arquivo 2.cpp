#include <iostream>
#include <stdio.h>  
#include <pthread.h>  
#include <unistd.h> 
#include <stdlib.h>
#include <time.h>

FILE * arquivoMultDe3;
FILE * arquivoMultDe5;
FILE * arquivoMultDe7;
FILE * arquivoMultDe9;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
void * HellouThread02(void *numeroThread){
		int b ;
	
		arquivoMultDe5 = fopen("arquivoMultDe5Comthread.txt", "a+");
		printf(">> Executando o Thread Nro %d \n", numeroThread);
		for (b = 0; b <= 9000000; b++){	
			if(b % 5 == 0){
				
				srand((unsigned) time(NULL)); 
				float c = rand() % 100000;
				fprintf(arquivoMultDe5, "%d", b);	
			}		
		}	fclose(arquivoMultDe5);
			printf("\n arquivo escrito 1 \n");
	pthread_exit(NULL);
	}
void * HellouThread03(void *numerothread){
	int b;
	
	arquivoMultDe7 = fopen("arquivoMultDe7Comthread.txt", "a+");
	printf(">> Executando o Thread Nro %d \n", numerothread);
		for (b = 0; b <= 9000000; b++){	
			if(b % 7 == 0){	
				srand((unsigned) time(NULL)); 
				float c = rand() % 100000;
				fprintf(arquivoMultDe7, "%d", b);
				//printf("\n %d \n", b);
			}		
		}	fclose(arquivoMultDe7);
			printf("\n arquivo escrito 1 \n");
		pthread_exit(NULL);
	}
	


void * HellouThread04(void *numerothread){
		int b;
		
		arquivoMultDe9 = fopen("arquivoMultDe9Comthread.txt", "a+");
		
		printf(">> Executando o Thread Nro %d \n", numerothread);
		for (b = 0; b <= 9000000; b++){	
			if(b % 9 == 0){
				srand((unsigned) time(NULL)); 
				float c = rand() % 100000;
				fprintf(arquivoMultDe9, "%d", b);
			}		
		}fclose(arquivoMultDe9);
		printf("\n arquivo escrito 4 \n");
 	pthread_exit(NULL);
}
void * HellouThread01(void *numeroThread){
		arquivoMultDe3 = fopen("arquivoMultDekkk3Comthread.txt", "a+");
		int b ;
		
		printf(">> Executando o Thread Nro %d \n", numeroThread);
	
		
		for (b = 0; b <= 9000000; b++){	
			if(b % 3 == 0){
				srand((unsigned) time(NULL)); 
				float c = rand() % 100000;
				fprintf(arquivoMultDe3, "%d", b);
			}		
		}	fclose(arquivoMultDe3);
			printf("\n arquivo escrito 1 \n");
	}
	

int main(int argc, char** argv) {
	int i, t1=1, t2=2, t3=3, t4=4;
	
	pthread_t todasThreads[5];
	

		printf("\n criando todas as thread numero: %d \n", i );
	 	for( i =0; i <1 ; i++ ){
	 		printf("entrou no for \n");
			pthread_create(&todasThreads[1],NULL, HellouThread01, (void *)t1);
			pthread_create(&todasThreads[2],NULL, HellouThread02, (void *)t2 );
			pthread_create(&todasThreads[3],NULL, HellouThread03, (void *)t3 );
			pthread_create(&todasThreads[4],NULL, HellouThread04, (void *)t4 );
			printf("terminou o for");
		}
	
	return 0;
}










