#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main (void){
int id_proc;

id_proc=fork();

if (id_proc==0){
printf("soy el proceso hijo\n");
}
else{
printf("soy el proceso padre\n");

}

printf("mensaje en ambos procesos\n");
exit(0);
}
