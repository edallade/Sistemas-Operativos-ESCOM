#include<unistd.h>
#include<stdio.h>
#include<math.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<string.h>

long long octal (int oct);

int main(){

char nom[100];
int l,o;
int a;

printf("introduca nombre y ruta del archivo\n");
printf("al cual se le cambiaran los permisos\n");
scanf("%s",nom);

a = open(nom,O_RDWR);

	if (a!=-1){
		printf("ingrese el nuevo modo de permisos del archivo\n para  activar odesactivar las banderas : rwxrwxrwx\n  en formato de tres numeros base octal \n");
		scanf("%d",&l);
		o=octal(l);
		a=chmod(nom,o);
		if(a!=-1)
		printf("operacion exitosa");
		else
		printf("error al cambiar los permisos");
		close(a);
	}
	else
	printf("directorio o archivo invalido");

return 0;
}


long long octal (int oct){

int dec =0, i =0;

	while (oct !=0){
	dec+=(oct%10) * pow(8,i);
	i++;
	oct/=10;
	}
	i =1;
	return dec;
}




