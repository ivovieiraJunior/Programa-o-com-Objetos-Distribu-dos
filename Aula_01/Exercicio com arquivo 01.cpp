#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/* 1 EmpresaA Bedecs Anna Proprietario pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	
	char empresa [150];
	char nome  [40];
	char primeiroNome [40];
	char cargo [40];
	int numero;
	int i=0;
	
	FILE * arquivo;
	
	//arquivo = fopen("arquivo1.txt","r+");
	if ((arquivo = fopen("arquivo1.txt","r")) == NULL)
		{ printf("Erro ao abrir arquivo"); }
	else
	{
		while(!feof(arquivo)){
			fscanf(arquivo, " %d %s %s %s %s", &numero, empresa, nome, primeiroNome, cargo );
			printf(" \n %d %s %s %s %s", numero, empresa, nome, primeiroNome, cargo);
			i++;
		}
	}
	fclose(arquivo);
	return 0;
}
