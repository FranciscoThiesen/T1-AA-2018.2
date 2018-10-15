#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#pragma warning(disable : 4996)


void FreeMATRIX(int **M, int ROW) {
	for (int i = 0; i < ROW; i++)
		free(M[i]);
	free(M);
}

int** MakeMATRIX(int ROW, int COL, int tipo)
{
	int j = 0;
	int k = 0;
	int **MATRIX = (int **)malloc(ROW * sizeof(int*));

	//printf("Rows %d, Columns%d\n", ROW, COL);

	for (int i = 0; i < ROW; i++)
	{
		MATRIX[i] = (int *)malloc(COL * sizeof(int));
	}





	if (tipo == 0)
	{
		for (int j = 0; j < ROW; j++)
		{
			//printf("Linha %d\n", j);
			for (int k = 0; k < COL; k++)
			{
				MATRIX[j][k] = 0;
				//printf("%d %d \n", j, k);
				//printf("%d \t", MATRIX[j][k]);
			}//printf("\n");
		}
	}
	else
	{
		for (int j = 0; j < ROW; j++)
		{
			//printf("Linha %d\n", j);
			for (int k = 0; k < COL; k++)
			{
				MATRIX[j][k] = rand() % 10;
				//printf("%d \t", j, k);
				//printf("%d \t", MATRIX[j][k]);

			}//printf("\n");
		}
	}



	return MATRIX;
}

void matrixMultiplication()
{
	double total_time;
	clock_t startMM, endMM;
	int SIZE[] = { 100,200,300,400,500,600,700,800,900,1000 };
	int n = 10;
	FILE * fp = fopen("mmult.csv", " w ");
	int ** M1;
	int ** M2;
	int ** M3;

	int l1, c1, l2, a;


	for (int s = 0; s < n; s++)
	{
		//printf("Tamanho da matriz %d \n", SIZE[s]);
		//printf("Matriz 1:\n");
		M1 = MakeMATRIX(SIZE[s], SIZE[s], 1);
		//printf("Matriz 2\n");
		M2 = MakeMATRIX(SIZE[s], SIZE[s], 1);
		//printf("Matriz 3\n");
		M3 = MakeMATRIX(SIZE[s], SIZE[s], 0);

		//printf("Matriz de Multiplicação:\n");

		startMM = clock();

		/* Aqui começa o For aninhado que seleciona cada linha da M1, cada coluna da M2 e o terceiro vem de fato para percorrer e multiplicar.*/

		for (l1 = 0; l1 < SIZE[s]; l1++)
		{
			for (c1 = 0; c1 < SIZE[s]; c1++)
			{
				for (l2 = 0; l2 < SIZE[s]; l2++)
				{
					M3[l1][c1] += M1[l1][l2] * M2[l2][c1];
				}
				//printf("%d \t", M3[l1][c1]);
			}//printf("\n");
		}//printf("\n\n\n");

		endMM = clock();//time count stops 
		total_time = ((double)(endMM - startMM)) / CLOCKS_PER_SEC;//calulate total time

		printf("Tamanho da matriz %d \n", SIZE[s]);
		printf("Time taken to multiply Matrix  is: %f\n\n\n", total_time);
		fprintf(fp, "Tamanho da matriz %d e tempo de multiplicacao %lf", SIZE[s], total_time);
	}
}


void matrixMultiplication2(int **M1, int **M2, int **M3, int SIZE)
{
	int l1, c1, l2, a;


	/* Aqui começa o For aninhado que seleciona cada linha da M1, cada coluna da M2 e o terceiro vem de fato para percorrer e multiplicar.*/

	for (l1 = 0; l1 < SIZE; l1++)
	{
		for (c1 = 0; c1 < SIZE; c1++)
		{
			for (l2 = 0; l2 < SIZE; l2++)
			{
				M3[l1][c1] += M1[l1][l2] * M2[l2][c1];
			}
			//printf("%d \t", M3[l1][c1]);
		}//printf("\n");
	}//printf("\n\n\n");


	//fprintf(fp, "Tamanho da matriz %d e tempo de multiplicacao %lf", SIZE, total_time);


}


int ** particionaMatriz(int **M1, int SIZE, int linIni, int colIni)
{
	int ** NovaMatriz = MakeMATRIX(SIZE / 2, SIZE / 2, 0);

	for (int l = linIni; l < linIni + SIZE / 2; l++)
	{
		for (int c = colIni; c < colIni + SIZE / 2; c++)
		{
			NovaMatriz[l - linIni][c - colIni] = M1[l][c];
		}
	}
	return NovaMatriz;
}

void juntaMatriz(int **M1, int **M2, int SIZE, int linIni, int colIni)
{

	for (int l = linIni; l < linIni + SIZE / 2; l++)
	{
		for (int c = colIni; c < colIni + SIZE / 2; c++)
		{
			M1[l][c] = M2[l - linIni][c - colIni];
		}
	}

}



int ** SomaSub(int **M1, int **M2, int SIZE, int sinal)
{
	int ** NovaMatriz = MakeMATRIX(SIZE, SIZE, 0);

	for (int l = 0; l < SIZE; l++)
	{
		for (int c = 0; c < SIZE; c++)
		{
			NovaMatriz[l][c] = M1[l][c] + M2[l][c] * sinal;
		}
	}
	return NovaMatriz;
}


int ** SomaSubInplace(int **M1, int **M2, int SIZE, int sinal)
{
	for (int l = 0; l < SIZE; l++)
	{
		for (int c = 0; c < SIZE; c++)
		{
			M1[l][c] = M1[l][c] + M2[l][c] * sinal;
		}
	}
	return M1;
}

int ** SetInPlace(int **M1, int **M2, int SIZE, int sinal) {
	int l, c;
	for (l = 0; l < SIZE; l++)
		for (c = 0; c < SIZE; c++)
			M1[l][c] = sinal * M2[l][c];
	return M1;
}

void strassenMultiplication(int **M1, int **M2, int **M3, int SIZE)
{


	int **p1, **p2, **p3, **p4, **p5, **p6, **p7, **a, **b, **c, **d, **e, **f, **g, **h, **x, **y, **w, **z;

	int half = SIZE / 2;

	if (SIZE == 1)
	{
		M3[0][0] = M1[0][0] * M2[0][0];
		return;
	}

	p1 = MakeMATRIX(half, half, 0); p2 = MakeMATRIX(half, half, 0); p3 = MakeMATRIX(half, half, 0); p4 = MakeMATRIX(half, half, 0);
	p5 = MakeMATRIX(half, half, 0); p6 = MakeMATRIX(half, half, 0); p7 = MakeMATRIX(half, half, 0);

	w = MakeMATRIX(half, half, 0); x = MakeMATRIX(half, half, 0); y = MakeMATRIX(half, half, 0); z = MakeMATRIX(half, half, 0);

	a = particionaMatriz(M1, SIZE, 0, 0);
	b = particionaMatriz(M1, SIZE, 0, half);
	c = particionaMatriz(M1, SIZE, half, 0);
	d = particionaMatriz(M1, SIZE, half, half);
	e = particionaMatriz(M2, SIZE, 0, 0);
	f = particionaMatriz(M2, SIZE, 0, half);
	g = particionaMatriz(M2, SIZE, half, 0);
	h = particionaMatriz(M2, SIZE, half, half);

	//(MODIFICACAO) Eliminei memory leak usando Mp1 (e Mp2)
	//p1
	int ** Mp1 = SomaSub(f, h, half, -1);
	strassenMultiplication(a, Mp1, p1, half);
	//p2
	SetInPlace(Mp1, a, half, 1); SomaSubInplace(Mp1, b, half, 1); //Mp1 = a+b
	strassenMultiplication(Mp1, h, p2, half);
	//p3
	SetInPlace(Mp1, c, half, 1); SomaSubInplace(Mp1, d, half, 1); //Mp1 = c+d
	strassenMultiplication(Mp1, e, p3, half);
	//p4
	SetInPlace(Mp1, g, half, 1); SomaSubInplace(Mp1, e, half, -1); //Mp1 = g-e
	strassenMultiplication(d, SomaSub(g, e, half, -1), p4, half);
	//p5 (aqui vamos passar a precisar de Mp2)
	SetInPlace(Mp1, a, half, 1); SomaSubInplace(Mp1, d, half, 1); //Mp1 = a+d
	int **Mp2 = SomaSub(e, h, half, 1);
	strassenMultiplication(Mp1, Mp2, p5, half);
	//p6
	SetInPlace(Mp1, b, half, 1); SomaSubInplace(Mp1, d, half, -1); //Mp1 = b-d
	SetInPlace(Mp2, g, half, 1); SomaSubInplace(Mp2, h, half, 1); //Mp2 = g+h
	strassenMultiplication(Mp1, Mp2, p6, half);
	//p7
	SetInPlace(Mp1, a, half, 1); SomaSubInplace(Mp1, c, half, -1); //Mp1 = a-c
	SetInPlace(Mp2, e, half, 1); SomaSubInplace(Mp2, f, half, 1); //Mp2 = e+f
	strassenMultiplication(Mp1, Mp2, p7, half);

	SomaSubInplace(w, p5, half, 1); SomaSubInplace(w, p4, half, 1); SomaSubInplace(w, p2, half, -1); SomaSubInplace(w, p6, half, 1);
	SomaSubInplace(x, p1, half, 1); SomaSubInplace(x, p2, half, 1);
	SomaSubInplace(y, p3, half, 1); SomaSubInplace(y, p4, half, 1);
	SomaSubInplace(z, p1, half, 1); SomaSubInplace(z, p5, half, 1); SomaSubInplace(z, p3, half, -1); SomaSubInplace(z, p7, half, -1);

	juntaMatriz(M3, w, SIZE, 0, 0);
	juntaMatriz(M3, x, SIZE, 0, half);
	juntaMatriz(M3, y, SIZE, half, 0);
	juntaMatriz(M3, z, SIZE, half, half);

	//(MODIFICACAO) LIBERANDO MEMORIA ALOCADA
	FreeMATRIX(Mp1, half); FreeMATRIX(Mp2, half);
	FreeMATRIX(a, half); FreeMATRIX(c, half); FreeMATRIX(e, half); FreeMATRIX(f, half);
	FreeMATRIX(w, half); FreeMATRIX(x, half); FreeMATRIX(y, half); FreeMATRIX(z, half);
	FreeMATRIX(b, half); FreeMATRIX(d, half); FreeMATRIX(g, half); FreeMATRIX(h, half);
	FreeMATRIX(p1, half); FreeMATRIX(p2, half); FreeMATRIX(p3, half); FreeMATRIX(p4, half);
	FreeMATRIX(p5, half); FreeMATRIX(p6, half); FreeMATRIX(p7, half);
}

void sumInside(int **M1, int **M2, int SIZE, int linIni, int colIni, int sinal)
{
	int l, c;
	for (l = linIni; l < linIni + SIZE / 2; l++)
		for (c = colIni; c < colIni + SIZE / 2; c++)
			M1[l][c] += sinal * M2[l - linIni][c - colIni];

}

void strassenMultiplication2(int **M1, int **M2, int **M3, int SIZE)
{
	/*input:
		a b		e f
		c d 	g h
	 output:
		w x
		y z
	*/
	/*Proccess:
		p1 = a(f-h); p2 = (a+b)h; p3 = (c+d)e; p4 = d(g-e);
		p5 = (a+d)(e+h); p6 = (b-d)(g+h); p7 = (a-c)(e+f);
	 Result:
		w = p5 + p4 - p2 + p6
		x = p1 + p2
		y = p3 + p4
		z = p1 + p5 - p3 - p7
	 */

	

	int **a, **b, **c, **d, **e, **f, **g, **h; //declara as matrizes particionadas 
	int **w;

	int half = SIZE / 2;

	if (SIZE <= 64) { // O caso base foi selecionado como 64 após tentativa e erro. A recursao ate um elemento estava gerando um problema 
		matrixMultiplication2(M1, M2, M3, SIZE);
		return;
	}

	a = particionaMatriz(M1, SIZE, 0, 0);
	b = particionaMatriz(M1, SIZE, 0, half);
	c = particionaMatriz(M1, SIZE, half, 0);
	d = particionaMatriz(M1, SIZE, half, half);
	e = particionaMatriz(M2, SIZE, 0, 0);
	f = particionaMatriz(M2, SIZE, 0, half);
	g = particionaMatriz(M2, SIZE, half, 0);
	h = particionaMatriz(M2, SIZE, half, half);

	//P1 starting p's proccess
	w = MakeMATRIX(half, half, 0);
	int ** Mp1 = SomaSub(f, h, half, -1); //f-h
	strassenMultiplication2(a, Mp1, w, half);
	sumInside(M3, w, SIZE, half, 0, 1); 	//p1 in x
	sumInside(M3, w, SIZE, half, half, 1);	//p1 in z
	//P2
	SetInPlace(Mp1, a, half, 1); SomaSubInplace(Mp1, b, half, 1); //a+b
	strassenMultiplication2(Mp1, h, w, half);
	sumInside(M3, w, SIZE, 0, 0, -1); 	//-p2 in w
	sumInside(M3, w, SIZE, half, 0, 1);	//p2 in x
	//P3
	SetInPlace(Mp1, c, half, 1); SomaSubInplace(Mp1, d, half, 1); //c+d
	strassenMultiplication2(Mp1, e, w, half);
	sumInside(M3, w, SIZE, 0, half, 1); 	//p3 in y
	sumInside(M3, w, SIZE, half, half, -1);	//-p3 in z
	//P4
	SetInPlace(Mp1, g, half, 1); SomaSubInplace(Mp1, e, half, -1); //g-e
	strassenMultiplication2(d, Mp1, w, half);
	sumInside(M3, w, SIZE, 0, 0, 1); 	//p4 in w
	sumInside(M3, w, SIZE, 0, half, 1);	//p4 in y
	//P5
	SetInPlace(Mp1, a, half, 1); SomaSubInplace(Mp1, d, half, 1); //a+d
	int **Mp2 = SomaSub(e, h, half, 1);
	strassenMultiplication2(Mp1, Mp2, w, half);
	sumInside(M3, w, SIZE, 0, 0, 1); 	//p5 in w
	sumInside(M3, w, SIZE, half, half, 1);	//p5 in z
	//P6
	SetInPlace(Mp1, b, half, 1); SomaSubInplace(Mp1, d, half, -1); //b-d
	SetInPlace(Mp2, g, half, 1); SomaSubInplace(Mp2, h, half, 1); //g+h
	strassenMultiplication2(Mp1, Mp2, w, half);
	sumInside(M3, w, SIZE, 0, 0, 1); 	//p6 in w
	//FREEING
	FreeMATRIX(b, half); FreeMATRIX(d, half); FreeMATRIX(g, half); FreeMATRIX(h, half);
	//P7
	SetInPlace(Mp1, a, half, 1); SomaSubInplace(Mp1, c, half, -1); //a-c
	SetInPlace(Mp2, e, half, 1); SomaSubInplace(Mp2, f, half, 1); //e+f
	strassenMultiplication2(Mp1, Mp2, w, half);
	sumInside(M3, w, SIZE, half, half, 1); 	//-p7 in z

	FreeMATRIX(Mp1, half); FreeMATRIX(Mp2, half);
	FreeMATRIX(a, half); FreeMATRIX(c, half); FreeMATRIX(e, half); FreeMATRIX(f, half);
	FreeMATRIX(w, half);
}

void imprimeMatriz(int **M, int SIZE) {
	int l, c;
	printf("Exibindo matriz:\n");
	for (l = 0; l < SIZE; l++)
	{

		for (c = 0; c < SIZE; c++)
		{
			printf("%d\t", M[l][c]);
		}
		printf("\n");
	}
}






int main(void)
{
	FILE * fp = fopen("mmult.csv", " w ");
	//FILE * fp2 = fopen("strassen.csv", " w ");
	int ** M1;
	int ** M2;
	int ** M3;
	int SIZE[] = { 16,32,64,128,256,512,1024,2048} ;

	double total_time;
	clock_t startMM, endMM;




	//Criando as matrizes

	/*
	M1 = MakeMATRIX(SIZE, SIZE, 1);
	M2 = MakeMATRIX(SIZE, SIZE, 1);
	M3 = MakeMATRIX(SIZE, SIZE, 0);
	*/

	//Comecando a multiplicacao pedestre


	for (int t = 0; t < 8; t++)
	{
		for (int p = 0; p < 10; p++)
		{
			M1 = MakeMATRIX(SIZE[t], SIZE[t], 1);
			M2 = MakeMATRIX(SIZE[t], SIZE[t], 1);
			M3 = MakeMATRIX(SIZE[t], SIZE[t], 0);
			startMM = clock();
			matrixMultiplication2(M1, M2, M3, SIZE[t]);
			endMM = clock();//time count stops 
			total_time = ((double)(endMM - startMM)) / CLOCKS_PER_SEC;//calulate total time
			printf("Tempo para multiplicar a matriz com %d de forma pedestre: %f\n\n\n", SIZE[t], total_time);
			fprintf(fp, "Tamanho da matriz %d e tempo de multiplicacao %lf \n", SIZE[t], total_time);
		}
		
	}
	
	
	
	//Comecando a multiplicacao STRASSEN

	/*
	for (int t = 0; t < 8; t++)
	{
		for (int p = 0; p < 10; p++)
		{
			M1 = MakeMATRIX(SIZE[t], SIZE[t], 1);
			M2 = MakeMATRIX(SIZE[t], SIZE[t], 1);
			M3 = MakeMATRIX(SIZE[t], SIZE[t], 0);
			startMM = clock();
			strassenMultiplication2(M1, M2, M3, SIZE[t]);
			endMM = clock();//time count stops 
			total_time = ((double)(endMM - startMM)) / CLOCKS_PER_SEC;//calulate total time
			printf("Tempo para multiplicar a matriz com %d pelo strassen: %f\n\n\n", SIZE[t], total_time);
			fprintf(fp2, "Tamanho da matriz %d e tempo de multiplicacao pelo strassen %lf \n", SIZE[t], total_time);
		}

	}

	*/


	//imprimeMatriz(M1, SIZE);
	//imprimeMatriz(M2, SIZE);
	//imprimeMatriz(M3, SIZE);

}

