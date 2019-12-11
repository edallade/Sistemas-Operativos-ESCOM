void escribe(int matriz[10][10]){
	z=shm;
	for(i=0;i<10;i++)
		for(j=0;j<10;j++)
			*z++=matriz[i][j];
	*z='\0';
}
 
void lee(int matriz[10][10]){
	int colum=0,fila=0,valor;				
	for(z=shm;fila<10;z++)
	{
		valor = *z;
		matriz[fila][colum]=valor;
		if(colum ==9)
		{
		fila++;
		colum=0;
		}
		else colum++;
	}
}
 
void llenarMatriz(int matriz[10][10]){
	int i,j;
	for(i=0;i<10;i++){
		for(j=0;j<10;j++){
			matriz[i][j] = 1+(rand()%9);
		}
	}
 
}
 
void imprimeMatriz(int matriz[10][10]){
	int i,j;
	for(i=0;i<10;i++){
		for(j=0;j<10;j++){
			printf("%d\t",matriz[i][j]);
		}printf("\n");
	}
 
}
 
void multiMatrices(int matrizMulti[10][10], int matriz1[10][10], int matriz2[10][10]){	
	int i=0,j=0;
	for(i=0;i<10;i++){
		for(j=0;j<10;j++){
			matrizMulti[i][j] = matriz1[i][j] * matriz2[i][j];
		}
	}
}
 
void sumaMatrices(int matrizSuma[10][10], int matriz1[10][10], int matriz2[10][10]){
	int i=0,j=0;
	for(i=0;i<10;i++){
		for(j=0;j<10;j++){
			matrizSuma[i][j] = matriz1[i][j] + matriz2[i][j];
		}
	}
}
 
void matrizInversa(int matriz[10][10],char nombre[100])
{
k=10;//tamano
	for (i=0;i<k;i++)
		{
			for (j=0;j<k;j++)
			{
				inversa[i][j] =(float)matriz[i][j];
			}
		}
	for (i=0;i<k;i++)
		for(j=k;j<2*k;j++)
		{
			if(i==(j-k))
				inversa[i][j]=1;
			else
				inversa[i][j]=0;
		}
	
		for (s=0;s<k;s++)
		{
			elemento=inversa[s][s];
			for (j=0;j<2*k;j++)
				inversa[s][j]=inversa[s][j]/elemento;
 
			for(i=0;i<k;i++)
			{
				if (i==s)
					;
				else 
				{
					coef= inversa[i][s];
					for (j=0;j<2*k;j++)
						aux[j]=inversa[s][j]*(coef*-1);
					for (j=0;j<2*k;j++)
						inversa[i][j]=inversa[i][j]+aux[j];
				}
			}
		}
		
		 FILE *f;
   		 f = fopen(nombre,"w+");
		for (i=0;i<k;i++)
		{
			for (j=k;j<2*k;j++)
			{
				printf("%.2f",inversa[i][j]);
				fprintf(f,"%.2f",inversa[i][j]);
			}
			printf("\n");
			fprintf(f,"\n");
		}fclose(f);
}	 

