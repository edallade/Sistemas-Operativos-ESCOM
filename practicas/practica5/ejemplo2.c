#include <stdio.h>
#include <pthread.h>

void *hilo (void *arg);

int main(void){

        pthread_t id_hilo;
        char* mensaje="Hola a todos desde este hilo\n";
        int dev_hilo;
        pthread_create(%id_hilo,NULL,hilo,(void*)mensaje);
        pthread_join(id_hilo,(void*)&dev_hilo);
        printf("valor=%i\n",dev_hilo);
        return 0;
        

}


void *hilo(void *arg){

        char* men;
        int resultado_hilo=0;
        men 

}
