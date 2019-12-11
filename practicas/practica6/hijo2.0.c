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

int main (int argc , char * argv[]){
        pid_t pid;
        char *argv2[2];
	argv2[0] = "/home/alexis/Documentos/programas_sistemas_operativos/practica6/Nieto";
        argv2[1]=NULL;
	int j,i,m1[TAM][TAM];
	int m2[TAM][TAM],mult[TAM][TAM],m3[TAM][TAM],m4[TAM][TAM];
        int shm_id,shm_id2,shm_id3,shm_id4;
        int *shm,*shm2,*shm3,*shm4,*apT;
        key_t llave=123,llave2=456,llave3=789,llave4=666;
	////////////////////acceder a los espacios de memoria del pade /////////////////////////
	if((shm_id=shmget(llave,TAM_MEM,0666)) < 0)
	{
		perror("1-Error al obtener memoria compartida: shmget");
		exit(-1);
	}
	
	if((shm=shmat(shm_id,NULL,0))==(int*)-1)
	{
		perror("Error al enlazar la memoria compartida: shmat");
		exit(-1);
	}
	
        if((shm_id2=shmget(llave2,TAM_MEM,0666)) < 0)
	{
		perror("1-Error al obtener memoria compartida: shmget");
		exit(-1);
	}
	
	if((shm2=shmat(shm_id2,NULL,0))==(int*)-1)
	{
		perror("Error al enlazar la memoria compartida: shmat");
		exit(-1);
	}
//////////////////////////////////////////////////////////////////////////////////////////////////	
///////////////////////////////reservar espacios de memoria para el nieto////////////////////
	if((shm_id3=shmget(llave3,TAM_MEM,IPC_CREAT | 0666)) < 0)
	{
		perror("1-Error al obtener memoria compartida: shmget");
		exit(-1);
	}
	
	if((shm3=shmat(shm_id3,NULL,0))==(int*)-1)
	{
		perror("Error al enlazar la memoria compartida: shmat");
		exit(-1);
	}
	
        if((shm_id4=shmget(llave4,TAM_MEM,IPC_CREAT | 0666)) < 0)
	{
		perror("1-Error al obtener memoria compartida: shmget");
		exit(-1);
	}
	
	if((shm4=shmat(shm_id4,NULL,0))==(int*)-1)
	{
		perror("Error al enlazar la memoria compartida: shmat");
		exit(-1);
	}
////////////////////////////////////////////////////////////////////////////////////////////////////	
	 generaMatriz(m3,m4);
		apT=shm+1;
		
 	for ( i=0; i<TAM; i++)
    {
        for ( j=0; j<TAM; j++)
        {
            m1[i][j]=*apT;
           apT=apT+1;
        }
    }
    
   	printf("\nmatriz1 recibida en el hijo\n  ");
   imprimeMatriz(m1);
	printf("\nse multiplicara con la matriz 2 \n  ");
	////////////////////////////////////////
	apT=shm2+1;
		
 	for ( i=0; i<TAM; i++)
    {
        for ( j=0; j<TAM; j++)
        {
            m2[i][j]=*apT;
           apT=apT+1;
        }
    }
    
   imprimeMatriz(m2);
	
	multiplicaMatrices(m1,m2,mult);
	
	apT=shm+1;
	 for ( i=0; i<TAM; i++)
    {
        for ( j=0; j<TAM; j++)
        {
            *apT++=mult[i][j];
           
        }
    }

*shm=-1;

	
   	apT=shm3+1;
    for ( i=0; i<TAM; i++)
    {
        for ( j=0; j<TAM; j++)
        {
            *apT++=m3[i][j];
           
        }
    }
    printf("\n matriz 3 enviada al nieto\n");
    	imprimeMatriz(m3);
    	
    	apT=shm4;
	
   
    for ( i=0; i<TAM; i++)
    {
        for ( j=0; j<TAM; j++)
        {
            *apT++=m4[i][j];
           
        }
    }
    printf("\n matriz 4 enviada al nieto\n");
    	imprimeMatriz(m4);
    	
 if((pid = fork()) == 0)
		execv(argv2[0],argv2);
	wait(0);
while (*shm3!=-1)//espera señal del nieto para 
    	sleep(1);

*shm2=-1;//enviar señal de continuar al padre




        shmdt ((char *)shm);
	shmdt ((char *)shm2);
        shmdt ((char *)shm3);
	shmdt ((char *)shm4);
	shmctl(shm_id, IPC_RMID, NULL);
	shmctl(shm_id2, IPC_RMID, NULL);
        shmctl(shm_id3, IPC_RMID, NULL);
	shmctl(shm_id4, IPC_RMID, NULL);
	exit(0);
}
	
	
	
