#include <stdio.h>
#include <time.h>
#include <pthread.h>
int resultados[20000];
void calcular(){
   //int resultados[20000];
    int i = 0;
    for (i = 0; i < 20000; i++){
       resultados[i] = i *5 + 55;
    }
    

} 

int main(){
    clock_t begin = clock();

    calcular();

    clock_t end = clock();


    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Tempo percorrido foi de: %fs.\n" , time_spent);
    for (int i = 0; i < 3; i++)
    {
        printf("Elemento [%d]: %d .\n", i ,resultados[20000]);

    }
    

    return 0;
}