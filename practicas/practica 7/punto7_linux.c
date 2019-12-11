#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define TAM 10
#define TAM_MEM 100
/**declaracion de funciones**/
void imprimeMatriz(int matriz[10][10]);
void llenarMatriz(int matriz[10][10]);
void sumaMatrices(int matrizSuma[10][10], int matriz1[10][10], int matriz2[10][10]);
void multiMatrices(int matrizMulti[10][10], int matriz1[10][10], int matriz2[10][10]);
void matrizInversa(int matriz[10][10], char nombre[100]);
void escribe(int matriz[10][10]);
void lee(int matriz[10][10]);
float inversa[1000][1000], coef, aux[1000], elemento;
int i,j, k, s;
int *shm, *z,c,d;
int main(void)
{
	srand(time(NULL));
	int pid,n,m;
	int semid;
	int matriz1[10][10];
	int matriz2[10][10];
	int matrizM[10][10];
	int matrizS[10][10];
	int shmid;
	key_t llave=1234,llaveMem;
	int semban = IPC_CREAT|0666;
	int nsems = 1;
	int nsops;
 
	llaveMem= 5678;
 
	if((shmid=shmget(llaveMem,TAM_MEM,IPC_CREAT|0666))<0)
	{
		perror("Error al obtener la memoria compartida: shmget");
		exit(-1);
	}
	if((shm=shmat(shmid,NULL,0))==(int *)-1)
	{
		perror("Error al enlazar la memoria compartida: shmat");
		exit(-1);
	}
	struct sembuf*sops=(struct sembuf*)malloc(2*sizeof(struct sembuf));
	printf("Iniciando semaforo...\n");
	if((semid=semget(llave,nsems,semban))==-1)
	{
		perror("semget:error al iniciar semaforo");
		exit(1);		
	}
	else
		printf("Semaforo Iniciado...\n");
	/*creacion por el proceso abuelo al proceso padre*/
	if((pid=fork())==0)
	{
		if((pid=fork())==0)
		{
			n=0;
			while(n<2)
			{
				nsops=2;
				sops[0].sem_num=0;
				sops[0].sem_op=0;
				sops[0].sem_flg = SEM_UNDO;
		
				sops[1].sem_num=0;
				sops[1].sem_op=1;
				sops[1].sem_flg= SEM_UNDO|IPC_NOWAIT;
				/*printf("semop:hijo llamado a semop(%d.&sops,%d)con:",semid,nsops);
				for(j=0;j<nsops;j++)
				{
					printf("\n\tsops[%d],sem_num=%d,",j,sops[j].sem_num);
					printf("sem_op = %d,",sops[j].sem_op);
					printf("sem_flg = %#o\n",sops[j].sem_flg);	
				}*/
				if((m=semop(semid,sops,nsops))==-1)
				{
					perror("semop:error en operacion del semaforo\n");
				}
				else
				{
					//printf("\tsemop:regreso de semop()%d\n",j);
					printf("\n\nProceso nieto toma el control del semaforo: %d/2 veces \n",n+1);
					if(n==0)
					{
						printf("El nieto lee de la memoria la matriz 1 \n");
						lee(matriz1);
						imprimeMatriz(matriz1);
					}
					if(n==1)
					{
						printf("El nieto lee de la memoria la matriz 2 \n");
						lee(matriz2);	
						imprimeMatriz(matriz2);	
						sumaMatrices(matrizS,matriz1,matriz2);
						printf("El nieto escribe la SUMA en la memoria  \n");
						imprimeMatriz(matrizS);						
						escribe(matrizS);
 
					}					
					sleep(5);
					nsops=1;
					sops[0].sem_num=0;
					sops[0].sem_op=-1;
					sops[0].sem_flg= SEM_UNDO|IPC_NOWAIT;
					if((j=semop(semid,sops,nsops))==-1)
					{
						perror("semop : error en operacion del semaforo\n");
					}
					else
						printf("Proceso nieto regresa el control del semaforo\n");
					sleep(5);
				}
				n++;
			}
		}
		else
		{
			n=0;
			while(n<3)
			{
				nsops=2;
				sops[0].sem_num=0;
				sops[0].sem_op =0;
				sops[0].sem_flg=SEM_UNDO;
			
				sops[1].sem_num =0;
				sops[1].sem_op=1;
				sops[1].sem_flg=SEM_UNDO|IPC_NOWAIT;
				/*printf("\nsmop : Padre llamado por semop(%d,&sops,%d)con: ",semid,nsops);
				for(j=0;j<nsops;j++)
				{
					printf("\n\tsops[%d],sem_num=%d,",j,sops[j].sem_num);
					printf("sem_op = %d,",sops[j].sem_op);
					printf("sem_flg = %#o\n",sops[j].sem_flg);	
				}*/
				if((m=semop(semid,sops,nsops))==-1)
				{
					perror("semop:error en operacion del semaforo\n");	
				}
				else
				{
					//printf("semop:regreso de semop()%d\n",j);
					printf("\n\nProceso hijo toma el control del semaforo: %d/3 veces \n",n+1);
					if(n==0)
					{
						printf("El hijo lee de la memoria la matriz 1 \n");
						lee(matriz1);
						imprimeMatriz(matriz1);
					}
					if(n==1)
					{
						printf("El hijo lee de la memoria la matriz 2 \n");
						lee(matriz2);	
						imprimeMatriz(matriz2);
					}
					if(n==2)
					{
						multiMatrices(matrizM,matriz1,matriz2);
						printf("El hijo escribe la MULTIPLICACION en la memoria  \n");
						imprimeMatriz(matrizM);
						escribe(matrizM);
					}
 
					sleep(5);
					nsops=1;
					sops[0].sem_num=0;
					sops[0].sem_op=-1;
					sops[0].sem_flg= SEM_UNDO|IPC_NOWAIT;
					if((j=semop(semid,sops,nsops))==-1)
					{
						perror("semop : error en semop()\n");
					}
					else
						printf("Proceso hijo regresa el control del semaforo\n");
					sleep(5);
				}
				n++;
			}
		}
	}
	else
	{
		n=0;
		while(n<4)
		{
			nsops=2;
			sops[0].sem_num=0;
			sops[0].sem_op =0;
			sops[0].sem_flg=SEM_UNDO;
			
			sops[1].sem_num =0;
			sops[1].sem_op=1;
			sops[1].sem_flg=SEM_UNDO|IPC_NOWAIT;
			//printf("\nsmop : Abuelo llamado por semop(%d,&sops,%d)con: ",semid,nsops);
			/*for(j=0;j<nsops;j++)
			{
				printf("\n\tsops[%d],sem_num=%d,",j,sops[j].sem_num);
				printf("sem_op = %d,",sops[j].sem_op);
				printf("sem_flg = %#o\n",sops[j].sem_flg);	
			}*/
			if((m=semop(semid,sops,nsops))==-1)
			{
				perror("semop:error en operacion del semaforo\n");	
			}
			else
			{	
				printf("\n\nProceso padre toma el control del semaforo: %d/4 veces \n",n+1);
				//printf("semop:regreso de semop()%d\n",j);
				if(n==0)
				{	
					llenarMatriz(matriz1);
					printf("Llenada Matriz 1 en el padre\n");
					imprimeMatriz(matriz1);
					printf("El padre escribe la matriz 1 en la memoria  \n");
					escribe(matriz1);
				}
				if(n==1)
				{	
					llenarMatriz(matriz2);
					printf("Llenada Matriz 2 en el padre\n");
					imprimeMatriz(matriz2);
					printf("El padre escribe la matriz 2 en la memoria  \n");
					escribe(matriz2);
				}
				if(n==2)
				{
					printf("El padre lee de la memoria la SUMA \n");
					lee(matrizS);
					imprimeMatriz(matrizS);
				}
				if(n==3)
				{
					printf("El padre lee de la memoria la Multiplicacion \n");
					lee(matrizM);
					imprimeMatriz(matrizM);
					printf("El padre calcula las inversas recibidas \n");		
					matrizInversa(matrizM,"InversaMultiplicacion.txt");
					printf("\n");
					matrizInversa(matrizS,"InversaSuma.txt");
                                        printf("He terminado, los resultados se han guardado en su archivo correspondiente.\n");
				}
				nsops=1;
				sops[0].sem_num=0;
				sops[0].sem_op=-1;
				sops[0].sem_flg= SEM_UNDO|IPC_NOWAIT;
				if((j=semop(semid,sops,nsops))==-1)
				{
					perror("semop : error en semop()\n");
				}
				else
					printf("el padre regresa el control del semaforo\n");
				sleep(5);
			}
			n++;
		}
	}
}
 
/////Funciones2.h/////////////////
void escribe(int matriz[10][10]){
	z=shm;
	for(i=0;i<10;i++)
		for(j=0;j<10;j++)
			*z++=matriz[i][j];
	*z='\0';
}
 
void lee(int matriz[10][10]){
	int colum=0,fila=0,valor;				
	for(z=shm;fila<10;z++)
	{
		valor = *z;
		matriz[fila][colum]=valor;
		if(colum ==9)
		{
		fila++;
		colum=0;
		}
		else colum++;
	}
}
 
void llenarMatriz(int matriz[10][10]){
	int i,j;
	for(i=0;i<10;i++){
		for(j=0;j<10;j++){
			matriz[i][j] = 1+(rand()%9);
		}
	}
 
}
 
void imprimeMatriz(int matriz[10][10]){
    int i, j;
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j++)
		{
			printf("%d ",matriz[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}
 
void multiMatrices(int matrizMulti[10][10], int matriz1[10][10], int matriz2[10][10]){	
	int i=0,j=0;
	for(i=0;i<10;i++){
		for(j=0;j<10;j++){
			matrizMulti[i][j] = matriz1[i][j] * matriz2[i][j];
		}
	}
}
 
void sumaMatrices(int matrizSuma[10][10], int matriz1[10][10], int matriz2[10][10]){
	int i=0,j=0;
	for(i=0;i<10;i++){
		for(j=0;j<10;j++){
			matrizSuma[i][j] = matriz1[i][j] + matriz2[i][j];
		}
	}
}
 
void matrizInversa(int matriz[10][10],char nombre[100])
{
k=10;//tamano
	for (i=0;i<k;i++)
		{
			for (j=0;j<k;j++)
			{
				inversa[i][j] =(float)matriz[i][j];
			}
		}
	for (i=0;i<k;i++)
		for(j=k;j<2*k;j++)
		{
			if(i==(j-k))
				inversa[i][j]=1;
			else
				inversa[i][j]=0;
		}
	
		for (s=0;s<k;s++)
		{
			elemento=inversa[s][s];
			for (j=0;j<2*k;j++)
				inversa[s][j]=inversa[s][j]/elemento;
 
			for(i=0;i<k;i++)
			{
				if (i==s)
					;
				else 
				{
					coef= inversa[i][s];
					for (j=0;j<2*k;j++)
						aux[j]=inversa[s][j]*(coef*-1);
					for (j=0;j<2*k;j++)
						inversa[i][j]=inversa[i][j]+aux[j];
				}
			}
		}
		
		 FILE *f;
   		 f = fopen(nombre,"w+");
		for (i=0;i<k;i++)
		{
			for (j=k;j<2*k;j++)
			{
				printf("%.2f",inversa[i][j]);
				fprintf(f,"%.2f",inversa[i][j]);
			}
			printf("\n");
			fprintf(f,"\n");
		}fclose(f);
}	 



