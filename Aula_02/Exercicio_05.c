#include <stdio.h>
#include <time.h>
#include <pthread.h>


void * HelloThread1(void * argumento){ //função que retorna um ponteiro "genérico" e recebe argumentos "genéricos"
    pthread_t NumThread; //declara NumThread como um thread
    NumThread = pthread_self(); //NumThread recebe o id do thread onde esta função está rodando
    FILE * pares_de_01_a_5000000 = fopen("pares_de_01_a_5000000_com_thread.txt" , "w");
    int i = 0;
   for (i = 1; i < 5000000; i++){
       if (i%2==0){
       fprintf(pares_de_01_a_5000000, "\n%d", i );
       }

   }
    fclose(pares_de_01_a_5000000);
    return NumThread; //equivalente a chamar pthread_exit(NumThread);
}

void * HelloThread2(void * argumento){ //função que retorna um ponteiro "genérico" e recebe argumentos "genéricos"
    pthread_t NumThread; //declara NumThread como um thread
    NumThread = pthread_self(); //NumThread recebe o id do thread onde esta função está rodando
    FILE * impares_de_5000000_a_9000000 = fopen("impares_de_5000000_a_9000000_com_thread.txt" , "w");
    int i = 0;
   for (i = 1; i < 5000000; i++){
       if (i%3==0){
            fprintf(impares_de_5000000_a_9000000, "\n%d", i );
       }

   }
    fclose(impares_de_5000000_a_9000000);
    return NumThread; //equivalente a chamar pthread_exit(NumThread);
}

void * HelloThread3(void * argumento){ //função que retorna um ponteiro "genérico" e recebe argumentos "genéricos"
    pthread_t NumThread; //declara NumThread como um thread
    NumThread = pthread_self(); //NumThread recebe o id do thread onde esta função está rodando
    FILE * multiplos_de_7_e_9_01_a_9000000 = fopen("multiplos_de_7_e_9_01_a_9000000_com_thread.txt" , "w");
    int i = 0;
   for (i = 1; i < 5000000; i++){
       if (i%7==0 && i%9==0){
       fprintf(multiplos_de_7_e_9_01_a_9000000, "\n%d", i );
       }

   }
    fclose(multiplos_de_7_e_9_01_a_9000000);
    return NumThread; //equivalente a chamar pthread_exit(NumThread);
}

int main(){
    clock_t begin = clock();

    pthread_t thread1, thread2, thread3;
    int flag1, flag2, flag3;
    int n1 = 1;
    int n2 = 2;
    int n3 = 3;

    flag1 = pthread_create(&thread1, NULL, HelloThread1, &n1); //cria o thread com identificador thread que vai executar a função HelloThread
        printf("\nLinha logo após a primeira chamada de pthread_create.");
    if (flag1 != 0) //se retornou um valor diferente de 0 é porque deu erro na criação do thread
        printf("Erro na criação da thread 1!\n");

    flag2 = pthread_create(&thread2, NULL, HelloThread2, &n2); //cria o thread com identificador thread que vai executar a função HelloThread
        printf("\nLinha logo após a segunda chamada de pthread_create.");
    if (flag2 != 0) //se retornou um valor diferente de 0 é porque deu erro na criação do thread
        printf("Erro na criação da thread 2!\n");

    flag3 = pthread_create(&thread3, NULL, HelloThread3, &n3); //cria o thread com identificador thread que vai executar a função HelloThread
        printf("\nLinha logo após a terceiro chamada de pthread_create.");
    if (flag3 != 0) //se retornou um valor diferente de 0 é porque deu erro na criação do thread
        printf("Erro na criação da thread 3!\n");


    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);
    clock_t end = clock();

    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Tempo percorrido foi de: %fs.\n" , time_spent);
    

    return 0;
}