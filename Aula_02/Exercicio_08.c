#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

/* 1)Tendo um array de inteiros (valores) com 20000 posi��es (inicializado automaticamente onde a
		posi��o corresponde a valor), pretende-se calcular resultado[i] = valores[i] * 5 + 55. 
		
		Altere o c�lculo do exerc�cio anterior para  resultado[i] = valores[i] * rand() ate 5 + rand() 
		at� 1000. */


int resultados1[10000];
//int resultados2[10000];

void * HelloThread1(void * argumento){ //função que retorna um ponteiro "genérico" e recebe argumentos "genéricos"
    pthread_t NumThread; //declara NumThread como um thread
    NumThread = pthread_self(); //NumThread recebe o id do thread onde esta função está rodando
    int i = 0;
    for (i = 0; i < 5; i++){
    	int num = (rand() % 5);
       resultados1[i] = i * num + 55;
       //printf("rand(): %d \n" , num);
    }
    return NumThread; //equivalente a chamar pthread_exit(NumThread);
}

void * HelloThread2(void * argumento){ //função que retorna um ponteiro "genérico" e recebe argumentos "genéricos"
    pthread_t NumThread; //declara NumThread como um thread
    NumThread = pthread_self(); //NumThread recebe o id do thread onde esta função está rodando
    int i = 0;
    for (i = 5000; i < 10000; i++){
       resultados1[i] = i *5 + 55;
    }
    return NumThread; //equivalente a chamar pthread_exit(NumThread);
}

void * HelloThread3(void * argumento){ //função que retorna um ponteiro "genérico" e recebe argumentos "genéricos"
    pthread_t NumThread; //declara NumThread como um thread
    NumThread = pthread_self(); //NumThread recebe o id do thread onde esta função está rodando
    int i = 0;
    for (i = 10000; i < 15000; i++){
       resultados1[i] = i *5 + 55;
       
    }
    return NumThread; //equivalente a chamar pthread_exit(NumThread);
}

void * HelloThread4(void * argumento){ //função que retorna um ponteiro "genérico" e recebe argumentos "genéricos"
    pthread_t NumThread; //declara NumThread como um thread
    NumThread = pthread_self(); //NumThread recebe o id do thread onde esta função está rodando
    int i = 0;
    for (i = 15000; i < 20000; i++){
       resultados1[i] = i *5 + 55;
    }
    return NumThread; //equivalente a chamar pthread_exit(NumThread);
}
int main(int argc, char *argv[]) {
	clock_t begin = clock();
	
    pthread_t thread1 , thread2 ,thread3 ,thread4 ;
    int flag1 = 1 ,flag2= 0;
    int n1 = 1;



    flag1 = pthread_create(&thread1, NULL, HelloThread1, &n1); //cria o thread com identificador thread que vai executar a função HelloThread
        printf("\nLinha logo após a primeira chamada de pthread_create.");
    if (flag1 != 0) //se retornou um valor diferente de 0 é porque deu erro na criação do thread
        printf("Erro na criação da thread 1!\n");
	
    flag2 = pthread_create(&thread2, NULL, HelloThread2, &n1); //cria o thread com identificador thread que vai executar a função HelloThread
        printf("\nLinha logo após a segunda chamada de pthread_create.");
    if (flag2 != 0) //se retornou um valor diferente de 0 é porque deu erro na criação do thread
        printf("Erro na criação da thread 2!\n");
    /*flag1 = pthread_create(&thread3, NULL, HelloThread3, &n1); //cria o thread com identificador thread que vai executar a função HelloThread
        printf("\nLinha logo após a terceira chamada de pthread_create.");
    if (flag1 != 0) //se retornou um valor diferente de 0 é porque deu erro na criação do thread
        printf("Erro na criação da thread 3!\n");
    flag1 = pthread_create(&thread4, NULL, HelloThread4, &n1); //cria o thread com identificador thread que vai executar a função HelloThread
        printf("\nLinha logo após a quarta chamada de pthread_create.");
    if (flag1 != 0) //se retornou um valor diferente de 0 é porque deu erro na criação do thread
        printf("Erro na criação da thread 4!\n");
	*/

    pthread_join(thread1, NULL);
    //pthread_join(thread2, NULL);
    //pthread_join(thread3, NULL);
    //pthread_join(thread4, NULL);
 	
    clock_t end = clock();


    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC ;
     printf("\nTempo percorrido foi de: %fs  -  %fs\n" , (double)end , (double)begin);
    printf("\nTempo percorrido foi de: %fs \n" , time_spent);
    
    int i;
    
    for (i = 0; i < 3; i++)
    {
        printf("Elemento [%d]: %d .\n", i ,resultados1[i]);

    }
    
    if(pthread_join(thread1, NULL)){
    		return 0;
	}
	
}
