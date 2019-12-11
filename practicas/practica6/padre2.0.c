#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>
#include <unistd.h>
 #include <sys/wait.h>
#include "Funciones2.h"
#define TAM_MEM 200 /*Tamaño de la memoria compartida en bytes*/ 
#define TAM 10

int main (void){
        pid_t pid;
        char *argv[2];
	argv[0] = "/home/alexis/Documentos/programas_sistemas_operativos/practica6/Hijo";
        argv[1]=NULL; 
	int j,i,m1[TAM][TAM];
	int m2[TAM][TAM];
	int shm_id,shm_id2;
        int *shm,*shm2,*apT;
        float inv[TAM][TAM];
        key_t llave=123,llave2=456;

	
	////////////////////////////////////reservar espacios de memoria para el hijo////////////////////
	if((shm_id=shmget(llave,TAM_MEM,IPC_CREAT | 0666)) < 0)
	{
		perror("1-Error al obtener memoria compartida: shmget");
		exit(-1);
	}
	
	if((shm=shmat(shm_id,NULL,0))==(int*)-1)
	{
		perror("Error al enlazar la memoria compartida: shmat");
		exit(-1);
	}
	
        if((shm_id2=shmget(llave2,TAM_MEM,IPC_CREAT | 0666)) < 0)
	{
		perror("1-Error al obtener memoria compartida: shmget");
		exit(-1);
	}
	
	if((shm2=shmat(shm_id2,NULL,0))==(int*)-1)
	{
		perror("Error al enlazar la memoria compartida: shmat");
		exit(-1);
	}
	 generaMatriz(m1,m2);
	////////////////////////envio de la matriz uno al hijo//////////////////////////////////////
	apT=shm+1;

	
    
    for ( i=0; i<TAM; i++)
    {
        for ( j=0; j<TAM; j++)
        {
            *apT++=m1[i][j];
           
        }
    }
  
    	printf("\n matriz uno enviada\n");
    imprimeMatriz(m1);
 /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 
    	
   
	
		apT=shm2+1;
	
   
    for ( i=0; i<TAM; i++)
    {
        for ( j=0; j<TAM; j++)
        {
            *apT++=m2[i][j];
           
        }
    }
    printf("\n matriz 2 enviada\n");
    	imprimeMatriz(m2);
    	
    if((pid = fork()) == 0)
		execv(argv[0],argv);
	wait(0);

     while (*shm!=-1)
    	sleep(1);
    
    	apT=shm+1;    //copiar el resultado de la multiplicacion
    //sobreescribiendo en m1
for ( i=0; i<TAM; i++)
    {
        for ( j=0; j<TAM; j++)
        {
            m1[i][j]=*apT++;
           
        }
    }
    
    
    	  printf("\n matriz multiplicada recibida desde el hijo\n");
    		imprimeMatriz(m1);
    		
 while (*shm2!=-1)
    	sleep(1);
    
    	 	apT=shm2+1;    
    for ( i=0; i<TAM; i++)
    {
        for ( j=0; j<TAM; j++)
        {
            m2[i][j]=*apT++;
           
        }
    }
    	  printf("\n matriz sumada recibida desde el nieto \n");
    		imprimeMatriz(m2);
   double determinante1;
   double determinante2;
   double inv1[10][10]; /* Matrices auxiliares para el calculo de la inversa */
   double inv2[10][10];
   
   for(i=0 ; i<10 ; i++ )
   {
	   for(j=0 ; j<10 ; j++ )
	   {
		   inv1[i][j]=m1[i][j];
		   inv2[i][j]=m2[i][j];
	   }   
   }
   determinante1=Determinante(inv1, 10);
	if (determinante1!=0)
	{
		matrizCofactores(inv1, 10, determinante1);
	}
	else
	{
		printf("La matriz 1 no tiene inversa\n");
	}
	determinante2=Determinante (inv2, 10);
	if (determinante2!=0)
	{
		matrizCofactores2(inv2, 10, determinante2);
	}
	else
	{
		printf("La matriz 2 no tiene inversa\n");
	}
   printf("He terminado, los resultados se han guardado en su archivo correspondiente.\n");
    	system("pause");
        shmdt ((char *)shm);
	shmdt ((char *)shm2);
	shmctl(shm_id, IPC_RMID, NULL);
	shmctl(shm_id2, IPC_RMID, NULL);
	exit(0);
	
	
}
