#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#define TAM_MEM 27
int main (){

int shmid;
key_t llave;
 char *shm, *s;

llave=1234;

	if((shmid=shmget(llave,TAM_MEM,0666))<0){
		perror("error al obtener memoria compartida");
		exit(-1);


	}

	if((shm=shmat(shmid,NULL,0))==(char *)-1){

	perror("Error al enlazar la memoria compartida");
	exit(-1);

	}

	for( s = shm;*s!='\0';s++)
		putchar(*s);
	putchar('\n');

	*shm='*';

exit(0);

}
