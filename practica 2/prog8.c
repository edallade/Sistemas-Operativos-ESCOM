  #include<unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>  
#include <fcntl.h>
#include<stdlib.h>
#include<string.h>


void mi_itoa(char *ca,int numero); 
int main (){

int ref,nue,m,o;
int i = 1;
char  num [3],ruta[100],cad[]= {'a','r','c',' ',' ','.','t','x','t','\0'};
char mens[]={'h','o','l','a',' ','m','u','n','d','o',' ',' ','\0'};
char *ptrrut,*ptrcad,*ptrnum,*ward;


ptrnum=num;
ward=num;

printf ("introdusca la ruta donde crear los archivos\n");
scanf("%s",ruta);
m = mkdir(ruta,0777);
m = chmod (ruta,0777);

ref=rand()%15;
ptrrut=ruta;
for(ptrrut;*ptrrut!='\0';ptrrut++);
for(ptrcad=cad;*ptrcad!='\0';ptrcad++,ptrrut++)
	*ptrrut=*ptrcad;
	
*ptrrut='\0';

for(i;i<=ref;i++){
	
	 for(ptrrut=ruta;*ptrrut!='\0';ptrrut++){

		if(*ptrrut=='.'){
			ptrnum=ward;
			mi_itoa(ptrnum,i);
			ptrrut=ptrrut-2;
			for(ptrnum=ward;*ptrnum!='\0';ptrnum++,ptrrut++){
														
				*ptrrut=*ptrnum;			
			}
			
		}		
	}
	m = creat(ruta,0777);
	m = chmod(ruta,0777);
	nue=open(ruta,O_RDWR);
	o = write(nue,&mens,sizeof(mens));
	close(nue);

}


return 0;

}


void mi_itoa (char *ca, int numero){

*ca='0'+(numero/10);
ca=ca+1;
*ca='0'+(numero % 10);
ca=ca+1;
*ca='\0';

}


 //    ruta de prueba -> /home/alexis/Escritorio/a/home/alexis/Escritorio/a

