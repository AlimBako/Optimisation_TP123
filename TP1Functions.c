#include "TP1Functions.h"
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/time.h>
#include<stdio.h>

int read_TP1_instance(FILE*fin,dataSet* dsptr)
{
	int rval = 0;

	//capacite b
	int b;
	//Nombre d'objets
	int n;
	rval = fscanf(fin,"%d,%d\n",&n,&b);
	dsptr->b = b;
	dsptr->n = n;
	dsptr->c = (int*)malloc(sizeof(int)*n);
	dsptr->a = (int*)malloc(sizeof(int)*n);


	int i;
	for( i = 0 ; i < n ; i++)
		rval = fscanf(fin,"%d,%d\n",&(dsptr->c[i]),&(dsptr->a[i]));

	fprintf(stderr,"\nInstance file read, we have capacity %d and there is %d items of values/weights:\n",
			b,n);
	for( i = 0 ; i < n ; i++)
		fprintf(stderr,"%d,%d\n",dsptr->c[i],dsptr->a[i]);
	fprintf(stderr,"\n");


	return rval;
}

int* TP1_solve_exact(dataSet* dsptr)
{

	/******Put dynamic programming code here******/
	int* a = dsptr->a;
	int b = dsptr->b;
	int* c = dsptr->c;
	int n = dsptr->n;
	int* z = (int*)malloc(sizeof(int)*b);
	int* zp = (int*)malloc(sizeof(int)*b);
	int* D = (int*)malloc(sizeof(int)*b);
	int* x_opt = (int*)malloc(sizeof(int)*n);
	int y, k, j;

	for (y=0; y<=b; y++) {
		*(z + y) = 0;
		*(D + y) = 0;
	}

	for (k=0; k<=n-1; k++) {
		for (y=0; y<=b; y++) {
		*(zp + y) = *(z + y);
	}

		for (y= *(a + k+1); y<=b; y++) {
			if (zp[y - a[k+1]] + c[k+1] > zp[y]) {
				D[y] = k +1;
				z[y] = max(zp[y], c[k+1] + zp[y - a[k+1]]);
			}
		}
	}


	for (j=0; j<n; j++) {
		x_opt[j] = 0;
	} 

	y = b;

	while(y>0) {
		while (z[y] == z[y-1]) y = y-1;
		x_opt[D[y]] = 1;
		y = y - a[D[y]];
	}

	return x_opt;
}

int max(int x, int y)
{
	if (x > y) return x;
	return y;
}

void afficher(int* tableau, int n) {
   printf("Le tableau d'entiers est : \n");
   
   // Boucle for pour parcourir et afficher le tableau
   for(int i=0; i<n; i++) {
      printf("%d ", *(tableau+i));
   }
   
   printf("\n");
}

/******************  TP2  ************************/

float* LinearRelaxation(dataSet* dsptr, int*p)
{

	int* a = dsptr->a;
	float b = dsptr->b;
	int* c = dsptr->c;
	int n = dsptr->n;
	float* rapport = (float*)malloc(sizeof(float)*n);
	int* index = (int*)malloc(sizeof(int)*n);
	float* _x = (float*)malloc(sizeof(float)*n);
	float _b = b;
	int i, j;

	for (i=0; i<n; i++) {
		rapport[i] = c[i]/a[i];
		index[i] = i;

		_x[i] = 0;
	}

    selection_sort(rapport, index, n);

	for(j=0; j<n; j++){
		_x[index[j]] = min((_b/a[index[j]]),1);
		_b = _b - _x[index[j]]*a[index[j]];
		if(_b == 0) 
		{
			*p=j;
			return _x;
		}
	}

	return _x;
}

void afficherf(float* tableau, int n) {
   printf("Le tableau de flottants est : \n");
   
   // Boucle for pour parcourir et afficher le tableau
   for(int i=0; i<n; i++) {
      printf("%4.2f ", *(tableau+i));
   }
   
   printf("\n");
}

float min(float x, float y)
{
	if (x > y) return y;
	return x;
}


void fswap(float* a, float* b) {
    float temp = *a;
    *a = *b;
    *b = temp;
}

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void selection_sort(float* arr, int* index_arr, int n) {
    int i, j, max_index;

    for (i = 0; i < n - 1; i++) {
        max_index = i;
        for (j = i + 1; j < n; j++) {
            if (arr[j] > arr[max_index]) {
                max_index = j;
            }
        }
        if (max_index != i) {
            fswap(&arr[i], &arr[max_index]);
			swap(&index_arr[i], &index_arr[max_index]);
        }
    }
}