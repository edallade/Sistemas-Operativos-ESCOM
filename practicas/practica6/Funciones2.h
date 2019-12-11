 #include<unistd.h>
#include <sys/types.h>
#include <sys/stat.h>  
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#define TAM 10
void generaMatriz(int matriz[TAM][TAM],int matriz2[TAM][TAM])
{
    int i, j;
    srand(time(NULL));
    for (i=0; i<TAM; i++)
    {
        for (j=0; j<TAM; j++)
        {
            matriz[i][j]=rand()%10;
            matriz2[i][j]=rand()%9;
        }
    }
}



void sumaMatrices(int m1 [TAM][TAM],int m2[TAM][TAM],int mResult[TAM][TAM])
{
	 int i, j;
	for ( i = 0; i < TAM; i++)
    {
		for (j = 0; j < TAM; j++)
        {
			mResult[i][j] = m1[i][j] + m2[i][j];
        }
    }
}

void multiplicaMatrices(int m1 [][TAM],int m2[][TAM],int mResult[TAM][TAM])
{
int i, j,temporal,k;
for (i = 0 ; i < 10 ; i++ ) //i para las filas de la matriz resultante
{
    for (k = 0 ; k < 10 ; k++ ) // k para las columnas de la matriz resultante
    {
        temporal = 0 ;
        for (j = 0 ; j < 10 ; j++ ) //j para realizar la multiplicacion de 
                {                                   //los elementos   de la matriz
            temporal += m1[i][j] * m2[j][k];
            mResult[i][k] = temporal ;
       		 }
        }
	}
}

void imprimeMatriz(int matriz[TAM][TAM])
{
    int i, j;
	for (i = 0; i < TAM; i++)
	{
		for (j = 0; j < TAM; j++)
		{
			printf("%d ",matriz[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void crearArchivo(char inversa[700] ,char nombre[512])
{
int ref,nue,m,o;
int i =0;
char  num [3],ruta[256];
char *ptrrut,*ptrcad,*ptrnum,*ward,matriz[700];


ptrnum=num;
ward=num;

ptrrut=ruta;
for(ptrrut;*ptrrut!='\0';ptrrut++);
for(ptrcad=nombre;*ptrcad!='\0';ptrcad++,ptrrut++)
	*ptrrut=*ptrcad;
	
*ptrrut='\0';

ptrcad=matriz;
ward=inversa;
for(ward;*ward!='\0';ward++,ptrcad++)
{
        *ptrcad=*ward;
        i=i+1;
}
*ptrcad++='\0';
	m = creat(ruta,0777);
	m = chmod(ruta,0777);
	nue=open(ruta,O_RDWR);
	o = write(nue,&matriz,i);
	close(nue);


	printf("Se creó correctamente el archivo en la ruta:\t%s\n", nombre);
}

double Determinante (double m1[10][10],int n)
{
  double s = 1, det = 0;
  int i, j, k, m, x;
  double m2[10][10];
  if (n == 1)
  {
    return m1[0][0];
  }
  else
  {
    for (k = 0; k < n; k++)
    {
      m = 0;
      x = 0;
      for (i = 0; i < n; i++)
      {
        for (j = 0; j < n; j++)
        {
          m2[i][j] = 0;
          if (i != 0 && j != k)
          {
            m2[m][x] = m1[i][j];
            if (x < (n - 2))
            {
              x++;
            }
			else
            {
              x = 0;
              m++;
            }
          }
        }
      }
      det = det + s * (m1[0][k] * Determinante(m2, n-1));
      s *= -1;
    }
  }
  return det;
}

void matrizCofactores (double m1[10][10], int n, double determinante)
{
  char resultado[700];
  char buffer[8]={};
  int q, m, i, j, k, l;
  double m2[10][10], matrizFactores[10][10], aux[10][10], inversa[10][10];
  for (l = 0; l < n; l++)
  {
    for (k = 0; k < n; k++)
    {
      m = 0; q = 0;
      for (i = 0; i < n; i++)
      {
        for (j = 0; j < n; j++)
        {
          if ( i != l && j != k)
          {
            m2[m][q] = m1[i][j];
            if (q < (n-2))
            {
              q++;
            }
			else 
            {
				q = 0; m++;
            }
          }
        }
      }
      matrizFactores[l][k] = (pow(-1, l + k)* Determinante (m2, n-1));
    }
  }
  for (i = 0; i < 10; i++)
  {
    for (j = 0; j < 10; j++)
    {
      aux[i][j] = matrizFactores[j][i];
    }
  }
  for (i = 0; i < 10; i++)
  {
    for (j = 0; j < 10; j++)
    {
      inversa[i][j] = aux[i][j] / determinante;
    }
  }
  /*****************IMPRESION DE LA INVERSA*************/
  strcpy(resultado,"MATRIZ INVERSA 1:\r\n ");
  for (i=0; i<10; i++)
  {
    for (j=0; j<10; j++)
    {
	  sprintf(buffer,"%.3lf\t",inversa[i][j]);
	  strcat(resultado,buffer);
	  memset(buffer,0,8);
    }
	strcat(resultado,"\r\n");
  }

  crearArchivo(resultado,"inversaSuma.txt");
}

void matrizCofactores2 (double m1[10][10], int n, double determinante)

{
	
	
	
  char resultado[700];
  char buffer[8]={};
  int q, m, i, j, k, l;
  double m2[10][10], matrizFactores[10][10], aux[10][10], inversa[10][10];
  for (l = 0; l < n; l++)
  {
    for (k = 0; k < n; k++)
    {
      m = 0; q = 0;
      for (i = 0; i < n; i++)
      {
        for (j = 0; j < n; j++)
        {
          if ( i != l && j != k)
          {
            m2[m][q] = m1[i][j];
            if (q < (n-2))
            {
              q++;
            }
			else 
            {
				q = 0; m++;
            }
          }
        }
      }
      matrizFactores[l][k] = (pow(-1, l + k)* Determinante (m2, n-1));
    }
  }
  for (i = 0; i < 10; i++)
  {
    for (j = 0; j < 10; j++)
    {
      aux[i][j] = matrizFactores[j][i];
    }
  }
  for (i = 0; i < 10; i++)
  {
    for (j = 0; j < 10; j++)
    {
      inversa[i][j] = aux[i][j] / determinante;
    }
  }
  
  /*****************IMPRESION DE LA INVERSA*************/
  strcpy(resultado,"MATRIZ INVERSA 2\r\n");
  for (i = 0; i < 10; i++)
  {
    for (j = 0; j < 10; j++)
    {
	  sprintf(buffer,"%.3lf\t",inversa[i][j]);
	  strcat(resultado,buffer);
	  memset(buffer,0,8);
    }
	  strcat(resultado,"\r\n");
  }

  crearArchivo(resultado,"inversaMultiplicacion.txt");
}




