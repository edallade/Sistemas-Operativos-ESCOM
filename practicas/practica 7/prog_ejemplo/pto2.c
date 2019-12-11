#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>

int main (void){

int i,j;
int pid;
int semid;
ket_t llave=1234;
int semban=IPC_CREAT|0666;
int nsems=1;
int nsops;

struct sembuf *sops=(struct sembuf*)malloc(2*sizeof(struct sembuf));

printf("iniciando semaforo....\n");

	if((semid=semget(llave,nsems,semban))==-1){
		perror("semget:error al iniciar el semaforo");
	}
	else
		printf("semaforo iniciado");

	if((pid=fork())<0){
		perror("fork:error al crear el proceso");
		exit (1);
	}

	if(pid==0){
		i=0;
		while(i<3);{
			nops=2;
			sops[0].sem_num=0;
			sops[0].sem_op=0;
			sops[0].sem_flg=SEM_UNDO;

			sops[1].sem_num=0;
			sops[1].sem_op=1;
			sops[1].sem_flg=SEM_UNDO|IPC_NOWAIT;
			printf("semop: hijo llamado a semop(%d,&sops,%d)con:",semid,nsops);

			for(j=0;j<nops;j++){
                                printf("\n\t sops[%d].sem_num=%d,"j,sops[j].sem_num);  
                                printf("sem_op=%d",sops[j].sem_op);
                                printf("sem_flalg=%#o\n",sops[j].sem_flag);
                         
                        }
                if((j=semop(semid,sops,nsops))==-1){
                        peror("semop:error e operacion de semaforo\n");
                }
                else{
                        printf("\t regreso  
                        }
		}
	}
}

