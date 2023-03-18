#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <math.h>
#include <errno.h>
#include <time.h>
#include <assert.h>




typedef struct dataSet 
{
	//Attributes of the instance
	//Nombre d'objets
	int n;
	//Capacite b
	int b;
	//Tableau d'entiers de taille n contenant la valeur de chacun des objets
	int*c;
	//Tableau d'entiers de taille n contenant le poids de chacun des objets
	int*a;


} dataSet;

int read_TP1_instance(FILE*fin,dataSet* dsptr);
int* TP1_solve_exact(dataSet* dsptr);
int max(int x, int y);
void afficher(int* tableau, int n);

// ****************************************************************************
float* LinearRelaxation(dataSet* dsptr, int*p);
float* Greedy(dataSet* dsptr);
int max(int x, int y);
float min(float x, float y);
void fswap(float* a, float* b);
void swap(int* a, int* b);
void selection_sort(float* arr, int* index_arr, int n);
void afficherf(float* tableau, int n);

// ****************************************************************************
float* VariableProcessing(dataSet* dsptr);
float zfunc(dataSet* dsptr, float* _x);

