#include <ctype.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>
#include "TP1Functions.h"
#include <time.h>


int main(int argc, char **argv)
{
	int rval =0;	
	//File instance name
	//-F option
        char instance_file[1024];
        snprintf(       instance_file,
                        1024,
                        "%s",
                        "instance1.csv");

	char c;
        while ((c=getopt (argc, argv,"F:h")) != EOF)
	{
		switch(c)
		{
                        case 'F':
				snprintf(       instance_file,
						1024,
						"%s",
						optarg);
				break;

			case 'h':
				fprintf(stderr,"Usage: ./TP1 [options]\nOptions:\n\n");
				fprintf(stderr,"******** INSTANCE DATA ********\n");
				fprintf(stderr,"\t-F Instance file name to load............................(default %s).\n",instance_file);
				break;
			default:
				exit(0);
		}
	}

	dataSet data;

	//Open the instance file
	FILE* fin = fopen(instance_file,"r");
	read_TP1_instance(fin,&data);
	fclose(fin);

	// Calcul du temps d'execution
	clock_t start_t, end_t;
	// double tps_exec;

	//execute your solution methods on the instance you just read
	//Exact solution
	start_t = clock();
	int* sol = TP1_solve_exact(&data);
	end_t = clock();
	printf("La solution du programme dynamic est : \n");
	afficher(sol, data.n);
	printf("Le temps d'execution pour cette instance est: %fs \n", tempsexec(start_t, end_t));
	printf("\n");


	// Linear Relaxation
	int p = 0;
	start_t = clock();
	float* linear = LinearRelaxation(&data, &p);
	end_t = clock();
	printf("La solution de la relaxation linéaire est : \n");
	afficherf(linear, data.n);
	printf("Pour cette solution, on a z_linRel = ");
	printf("%.2f \n", zfunc(&data, linear));
	printf("Le temps d'execution pour cette instance est: %fs \n", tempsexec(start_t, end_t));
	printf("\n");


	// Greedy 
	start_t = clock();
	float* greed = Greedy(&data);
	end_t = clock();
	printf("La solution de l'algorithme glouton est : \n");
	afficherf(greed, data.n);
	printf("Pour cette solution, on a z_greedy = ");
	printf("%.2f \n", zfunc(&data, greed));
	printf("Le temps d'execution pour cette instance est: %fs \n", tempsexec(start_t, end_t));
	printf("\n");


	// Knapsack - Variable processing
	start_t = clock();
	float* varproc = VariableProcessing(&data);
	end_t = clock();
	printf("La solution du knapsack est : \n");
	afficherf(varproc, data.n);
	printf("Pour cette solution, on a z_knapsack = ");
	printf("%.2f \n", zfunc(&data, varproc));
	printf("Le temps d'execution pour cette instance est: %fs \n", tempsexec(start_t, end_t));
	printf("\n");

	return rval;
}

