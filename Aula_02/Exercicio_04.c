#include <stdio.h>
#include <time.h>
#include <pthread.h>

void pares_de_01_a_5000000(){
    FILE * pares_de_01_a_5000000 = fopen("pares_de_01_a_5000000.txt" , "w");
    int i = 0;
   for (i = 1; i < 5000000; i++){
       if (i%2==0){
       fprintf(pares_de_01_a_5000000, "\n%d", i );
       }

   }
    fclose(pares_de_01_a_5000000);
}

void impares_de_5000000_a_9000000(){
    FILE * impares_de_5000000_a_9000000 = fopen("impares_de_5000000_a_9000000.txt" , "w");
    int i = 0;
   for (i = 1; i < 5000000; i++){
       if (i%3==0){
            fprintf(impares_de_5000000_a_9000000, "\n%d", i );
       }

   }
    fclose(impares_de_5000000_a_9000000);
}

void multiplos_de_7_e_9_01_a_9000000(){
    FILE * multiplos_de_7_e_9_01_a_9000000 = fopen("multiplos_de_7_e_9_01_a_9000000.txt" , "w");
    int i = 0;
   for (i = 1; i < 5000000; i++){
       if (i%7==0 && i%9==0){
       fprintf(multiplos_de_7_e_9_01_a_9000000, "\n%d", i );
       }

   }
    fclose(multiplos_de_7_e_9_01_a_9000000);
}

int main(){
    clock_t begin = clock();

    pares_de_01_a_5000000();
    impares_de_5000000_a_9000000();
    multiplos_de_7_e_9_01_a_9000000();

    clock_t end = clock();

    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Tempo percorrido foi de: %fs.\n" , time_spent);
    
    return 0;
}