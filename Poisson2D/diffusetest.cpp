#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <cstdlib>

using namespace std;

//Macros
#define PI 3.14159
#define IX(i,j) ((n+2)*(i)+(j))
#define SWAP(x0,x) {double * tmp=x0;x0=x;x=tmp;}

//global variables

double *dens, *dens_prev, *s;
double dt, diff;
int size;
double a, c;


int main(int argc, char** argv)
{


	int i, j, k, n, K;
	double h;

	n = atoi(argv[1]);
	K = atoi(argv[2]);
	h = 1/((double)n+1);

	dt = 0.1; diff = -0.1;
	a = dt*diff*n*n;
	c = 1/(1-4*a);

	size = (n+2)*(n+2);

	dens		= (double *) malloc ( size*sizeof(double) );	
	dens_prev	= (double *) malloc ( size*sizeof(double) );
	s		= (double *) malloc ( size*sizeof(double) );



	//initialize b and x
	double *x;
	x		= (double *) malloc ( (n+2)*sizeof(double) );
	
	for (i=0; i<n+2; i++){
		x[i] = i*h;	
	}


	for (i=0; i<n+2; i++){
		for (j=0; j<n+2; j++){
			dens_prev[IX(i,j)] = 0.0;//2*PI*PI*sin(PI*x[i])*sin(PI*x[j]);
			dens[IX(i,j)] = 0.0;
			s[IX(i,j)] = 0.0;//2*PI*PI*sin(PI*x[i])*sin(PI*x[j]);
		}
	}

	s[IX(1,1)]=10;

	for (i=0; i<n+2; i++){
		s[IX(i,0)] = 0;
		s[IX(0,i)] = 0;
		s[IX(i,n+1)] = 0;
		s[IX(n+1,i)] = 0;
	}






	for ( k=0 ; k<K ; k++ ) {
		for ( i=1 ; i<n+1 ; i++ ) {
			for ( j=1 ; j<n+1 ; j++ ) {

	dens[IX(i,j)] = (c*(dens_prev[IX(i,j)] + dt*s[IX(i,j)] - a*(dens[IX(i-1,j)]+dens_prev[IX(i+1,j)]+dens[IX(i,j-1)]+dens_prev[IX(i,j+1)])));


			}
		}

	printf("dens = \n");
	for (i=0; i<n+2; i++){
		for (j=0; j<n+2; j++){
			printf("|%f",dens[IX(i,j)]);
		}
		printf("|\n");
	}

	SWAP(dens, dens_prev);
	}

/*
	printf("x = \n");
	for (j=0; j<n+2; j++){
		printf("|%f",x[j]);
	}
	printf("|\n");

	printf("b = \n");
	for (i=0; i<n+2; i++){
		for (j=0; j<n+2; j++){
			printf("|%f",dens[IX(i,j)]);
		}
		printf("|\n");
	}
*/

	
    	return 0;
}
