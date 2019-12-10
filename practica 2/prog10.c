  #include<unistd.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<dirent.h>
#include<fcntl.h>
#include<string.h>
#include<time.h>
int main(){


char ruta[200],dir[150];
int a,b,c;

DIR *ptrdir;
struct dirent *dirst;
struct stat sb;
ruta[1]='\0';
printf("ruta del directorio;\n\n");
scanf("%s",dir);
ptrdir=opendir(dir);
printf("\nnombre\t\ttamaño\tfecha y hora de creacion\n");
while ((dirst=readdir(ptrdir))!=NULL){
	if(!strcmp(dirst->d_name,".") || !strcmp(dirst->d_name,".."))
	{}
	else{
	strcpy(ruta,dir);
	strcat(ruta,dirst->d_name);
	b=stat(ruta,&sb);
	printf("\n%s\t\t%lld\t%s\t",dirst->d_name,(long long)sb.st_size,ctime(&sb.st_atime));
	}
    }
closedir(ptrdir);
return 0;
}
