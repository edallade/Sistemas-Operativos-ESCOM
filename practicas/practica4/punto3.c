#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main (void){

int id_proc;

id_proc=fork();

if(id_proc==0)
{
printf("soy el oriceso hijo\n");
exit(0);
}
else{
printf("soy el proceso padre\n");
exit(0);
}



}
