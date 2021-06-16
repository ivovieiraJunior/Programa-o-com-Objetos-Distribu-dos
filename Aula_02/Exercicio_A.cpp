#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* a) Crie uma programa que que leia o arquivo (Dicionario) e: 
		1-Conte as palavras (únicas).
		2-Crie uma lista ordenada de palavras procedural.
		
	b) Após a implementação do programa alterar de modo que execute cada função paralelamente.
	
	c) Você deverá medir o tempo de execução do programa procedural comparando com a versão paralela e verificar
	qual foi o ganho (ou perda) de desempenho.  */

int main(int argc, char** argv) {
	
	FILE * arquivo = fopen("dicionario.txt", "r");
	char frase[5][15];
	char palavras[] = "";
	int i =0;
	
	while(feof(arquivo)){
		int contaVezes = 0;
		fscanf(arquivo, "%s" , frase);
			int i =0;
			for(i =0; i< frase[i][15].lngth-1 ; i++){
				if(strcmp(palavra,frase[i]) ==0){
					contaVezes++;
				}
			}
				
			if(contaVezes==0){
				strcmp(frase.length+1, palavra);
			}
	}

	return 0;
}
