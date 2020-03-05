#include <stdio.h>
#include <time.h>
#include <pthread.h>

void * HelloThread(void * argumento){ //função que retorna um ponteiro "genérico" e recebe argumentos "genéricos"
    pthread_t NumThread; //declara NumThread como um thread
    NumThread = pthread_self(); //NumThread recebe o id do thread onde esta função está rodando
    for (int i = 0; i < 10; i++){
        printf("\nOlá Mundo! Eu sou a thread %d #%d.\r", *(int*)argumento,(int)NumThread);
    }
    return NumThread; //equivalente a chamar pthread_exit(NumThread);
}

int main(){
    pthread_t thread1, thread2; //declara o identificador do thread a ser criado
    int flag1, flag2;
    int n1 = 1;
    int n2 = 2;
    printf("Iniciando o programa de Threads...");
    
    flag1 = pthread_create(&thread1, NULL, HelloThread, &n1); //cria o thread com identificador thread que vai executar a função HelloThread
    printf("\nLinha logo após a primeira chamada de pthread_create.");
    if (flag1 != 0) //se retornou um valor diferente de 0 é porque deu erro na criação do thread
        printf("Erro na criação da thread 1!\n");
    
    flag2 = pthread_create(&thread2, NULL, HelloThread, &n2); //cria o thread com identificador thread que vai executar a função HelloThread
    printf("\nLinha logo após a segunda chamada de pthread_create.");
    if (flag2 != 0) //se retornou um valor diferente de 0 é porque deu erro na criação do thread
        printf("Erro na criação da thread 2!\n");
    
    pthread_join(thread1, NULL); //termina o thread atual apenas depois que a thread criada aqui dentro terminar //o thread atual (main) espera o thread (thread) terminar
    pthread_join(thread2, NULL);
    
    return 0;
}