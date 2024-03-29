#include <stdio.h>
#include <pthread.h>

void * HelloThread(void * argumento){ //função que retorna um ponteiro "genérico" e recebe argumentos "genéricos"
    pthread_t NumThread; //declara NumThread como um thread
    NumThread = pthread_self(); //NumThread recebe o id do thread onde esta função está rodando
    
    printf("\nOlá Mundo! Eu sou a thread # %d. \n", (int)NumThread);
    pthread_exit(NumThread); //termina o thread antes do fim da função HelloThread
    printf("Não chamei ptread_exit.\n");
    return NumThread; //equivalente a chamar pthread_exit(NumThread);
}

int main(){
    pthread_t thread; //declara o identificador do thread a ser criado
    int flag;
    printf("Iniciando o programa de Threads...");
    flag = pthread_create(&thread, NULL, HelloThread, NULL); //cria o thread com identificador thread que vai executar a função HelloThread
    printf("\nLinha logo após a chamada de pthread_create, aparece antes ou depois do Olá Mundo do thread?");
    if (flag != 0) //se retornou um valor diferente de 0 é porque deu erro na criação do thread
        printf("Erro na criação da thread\n");
    pthread_join(thread, NULL); //termina o thread atual apenas depois que a thread criada aqui dentro terminar
    return 0;
}