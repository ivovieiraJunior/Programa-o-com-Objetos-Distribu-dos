
void *contar(void *th){
   	int b=0;	 
	printf(">> Executando o Thread Nro %d \n", th);
			  for (b=0; b< 20000000; b++)
			{
				srand((unsigned) time(NULL));
				float c = rand() % 100000;
			}
	printf(">>>>> Thread %d Finalizou agora 20.000.000 de operacoes\n\n", th);
   	pthread_exit(NULL);
}


int main ( ) 
{   
	int a=0, b=0;
	
	//Controlador das Threads
	pthread_t programas[10];
	
	printf("Inciando do programa com Threads. Contanto 10 x ate 20.000.000 \n");

	for (a = 0; a<10; a++)
		{
			printf(">> Criando a thread Nro: %d \n", a+1);
			
			pthread_create(&programas[a],NULL,contar,(void *)a);
			
		}
		pthread_exit(NULL);
	return 0;   
}
