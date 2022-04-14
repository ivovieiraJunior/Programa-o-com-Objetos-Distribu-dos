//
//  Exercicio-09-02.c
//
//  Created by Bruno on 13/06/19.
//  Copyright © 2019 Bruno. All rights reserved.
//
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 100
 
struct aluno{
    int matricula;
    char nome[81];
    char email[42];
    struct aluno * proximo;
};
typedef struct aluno Aluno;
 
typedef Aluno* Hash[N];
 
int hash(int matricula){
    return (matricula % N);
}
 
Aluno * hsh_busca_l(Hash tabela, int matricula){
    int h = hash(matricula);
    Aluno * aluno = tabela[h];
    while(aluno != NULL){
        if(aluno->matricula == matricula)
            return aluno;
        aluno = aluno->proximo;
    }
    return NULL;
}
 
void hsh_insere_l(Hash tabela, int matricula, char * nome, char * email){
    int h = hash(matricula);
    Aluno * aluno = tabela[h];
    while(aluno != NULL){
        if(aluno->matricula == matricula)
            break;
        aluno = aluno->proximo;
    }
    if(aluno == NULL){
        aluno = (Aluno *) malloc(sizeof(Aluno));
        aluno->matricula = matricula;
        aluno->proximo = tabela[h];
        tabela[h] = aluno;
    }
    strcpy(aluno->nome, nome);
    strcpy(aluno->email, email);
}
 
void hsh_remove_l(Hash tabela, int matricula){
    int h = hash(matricula);
    Aluno * aluno = tabela[h];
    if(aluno->matricula == matricula){
        tabela[h] = aluno->proximo;
        free(aluno);
    }
    Aluno * next;
    while(aluno != NULL){
        next = aluno->proximo;
        if(next && next->matricula == matricula){
            aluno->proximo = next->proximo;
            free(next);
        }
        aluno = aluno->proximo;
    }
}
 
int main(){
    Hash tabela = {};
     
    hsh_insere_l(tabela,12345,"Aluno 1", "aluno1@ads.com");
    hsh_insere_l(tabela,12445,"Aluno 2", "aluno2@ads.com");
    hsh_insere_l(tabela,12545,"Aluno 3", "aluno3@ads.com");
     
    hsh_remove_l(tabela, 12345);
     
    Aluno * res = hsh_busca_l(tabela, 12545);
     
    if(res)
        printf("%s",res->nome);
    else
        printf("Aluno não encontrado.");
    printf("\n");
}
