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

int main (int argc , char * argv2[]){
	int j,i,m3[TAM][TAM];
	int m4[TAM][TAM],sum[TAM][TAM];
	int shm_id2,shm_id3,shm_id4;
	 key_t llave2=456,llave3=789,llave4=666;
	int *shm2,*shm3,*shm4,*apT;
	////////////////////acceder a los espacios de memoria del hijo del padre /////////////////////////
	if((shm_id3=shmget(llave3,TAM_MEM,0666)) < 0)
	{
		perror("1-Error al obtener memoria compartida: shmget");
		exit(-1);
	}
	
	if((shm3=shmat(shm_id3,NULL,0))==(int*)-1)
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

         if((shm_id4=shmget(llave4,TAM_MEM,0666)) < 0)
	{
		perror("1-Error al obtener memoria compartida: shmget");
		exit(-1);
	}
	
	if((shm4=shmat(shm_id4,NULL,0))==(int*)-1)
	{
		perror("Error al enlazar la memoria compartida: shmat");
		exit(-1);
	}
///////////////////////////////////////////////////////////////////////////////
		apT=shm3+1;
		
 	for ( i=0; i<TAM; i++)
    {
        for ( j=0; j<TAM; j++)
        {
            m3[i][j]=*apT;
           apT=apT+1;
        }
    }
    printf("\n matriz 3 recivida del hijo del padre:\n  ");
   imprimeMatriz(m3);
	printf("\nse sumara con matriz 4 :\n  ");
	////////////////////////////////////////
	apT=shm4;
		
 	for ( i=0; i<TAM; i++)
    {
        for ( j=0; j<TAM; j++)
        {
            m4[i][j]=*apT;
           apT=apT+1;
        }
    }
    
   imprimeMatriz(m4);
	
	sumaMatrices(m3,m4,sum);
	
	apT=shm2+1;
	 for ( i=0; i<TAM; i++)
    {
        for ( j=0; j<TAM; j++)
        {
            *apT++=sum[i][j];
           
        }
    }

*shm3=-1;
//	system("pause");

	shmdt ((char *)shm2);
        shmdt ((char *)shm3);
	shmdt ((char *)shm4);
	shmctl(shm_id2, IPC_RMID, NULL);
        shmctl(shm_id3, IPC_RMID, NULL);
	shmctl(shm_id4, IPC_RMID, NULL);
	exit(0);

}
	
	
	
