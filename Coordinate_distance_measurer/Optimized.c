//compilation instructions/examples:
//gcc -fopenmp point_epsilon_starter.c -o point_epsilon_starter
//sometimes you need to link against the math library with -lm:
//gcc -fopenmp point_epsilon_starter.c -lm -o point_epsilon_starter

//math library needed for the square root

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "omp.h"

//N is 100000 for the submission. However, you may use a smaller value of testing/debugging.
#define N 10000
//Do not change the seed, or your answer will not be correct
#define SEED 72


struct pointData{
double x;
double y;
};



void generateDataset(struct pointData * data);
double euclid_dist(struct pointData p1, struct pointData p2);
int compare_func(const void* first, const void* second);

int main(int argc, char *argv[])
{


	//Read epsilon distance from command line
	if (argc!=2)
	{
	printf("\nIncorrect number of input parameters. Please input an epsilon distance.\n");
	return 0;
	}


	char inputEpsilon[20];
	strcpy(inputEpsilon, argv[1]);
	double epsilon=atof(inputEpsilon);

	//generate dataset:
	struct pointData * data;
	data=(struct pointData*)malloc(sizeof(struct pointData)*N);
	printf("\nSize of dataset (MiB): %f\n",(2.0*sizeof(double)*N*1.0)/(1024.0*1024.0));
	printf("ε = %s\n", argv[1]);
	generateDataset(data);

	////////////////////////////////////////////////
	/////////////////// MY CODE ////////////////////
	////////////////////////////////////////////////

	//change OpenMP settings:
	omp_set_num_threads(1);
	int distances_within_epsilon = 0;

	struct pointData p1, p2;
	int i,j;
	double epsilon_square = pow(epsilon, 2);

	double tstart=omp_get_wtime();

	double sort_start=omp_get_wtime();
	qsort(data, N, sizeof(struct pointData), compare_func);
	double sort_end=omp_get_wtime();

	#pragma omp parallel for private(i, j, p1, p2) shared(data, epsilon, epsilon_square, distances_within_epsilon) schedule(dynamic)
	for (i=0; i<N; i++) {
		p1 = data[i];

		for (j=i+1; j<N; j++) {
			p2 = data[j];

			if (p2.x - p1.x > epsilon) {
				break;
			} else if (euclid_dist(p1, p2) < epsilon_square) {
				#pragma omp atomic
				distances_within_epsilon += 2;
			}
		}
	}

	double tend=omp_get_wtime();

	printf("\nTime to sort (s): %f\n", sort_end-sort_start);
	printf("Total time (s): %f\n", tend-tstart);

	//we add the N distances that are the distance between the point and itself (0)
	distances_within_epsilon += N;
	printf("total number of distances within ε: %d\n", distances_within_epsilon);

	free(data);
	printf("\n");
	return 0;
}


double euclid_dist(struct pointData p1, struct pointData p2) {

	return (pow((p1.x - p2.x), 2) + pow((p1.y - p2.y), 2));

}

int compare_func(const void* first, const void* second) {
	struct pointData *p1 = (struct pointData *)first;
	struct pointData *p2 = (struct pointData *)second;

	if (p1->x > p2->x) {
		return 1;
	} else if (p1->x < p2->x) {
		return -1;
	} else {
		return 0;
	}
}

/* //Slowass sorting algorithm, ended up not needing this
void sort_array_by_x(struct pointData * data) {

	int did_swap;
	for (int i=0; i<N-1; i++) {
		did_swap = 0;
		for (int j=0; j<N-i-1; j++) {
			if (data[j].x>data[j+1].x) {
				did_swap = 1;
				struct pointData temp_datapoint = data[j];
				data[j] = data[j+1];
				data[j+1] = temp_datapoint;
			}
		}

		if (did_swap == 0) {
			break;
		}
	}
} */

////////////////////////////////////////////////
//////////////// END OF MY CODE ////////////////
////////////////////////////////////////////////

//Do not modify the dataset generator or you will get the wrong answer
void generateDataset(struct pointData * data)
{

	//seed RNG
	srand(SEED);


	for (unsigned int i=0; i<N; i++){
		data[i].x=1000.0*((double)(rand()) / RAND_MAX);
		data[i].y=1000.0*((double)(rand()) / RAND_MAX);
	}


}
