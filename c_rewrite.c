#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <complex.h>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_matrix.h>

#define _USE_MATH_DEFINES

// global variables
int n = 10;

double incident(double x);
double green_function(double r1[n][3], double r2[n][3]);

int main()
{
	int i, j, k;
	double x, y, z;
	double scatterers[n][3];
	
	gsl_matrix * mmat = gsl_matrix_alloc (n,n);

	srand((unsigned)time(NULL));
	for (i = 1; i < n; i++)
	{
		x = 20*(double)rand()/RAND_MAX;
		y = 50*(double)rand()/RAND_MAX;
		z = 30*(double)rand()/RAND_MAX;
		
		scatterers[i][0] = x;
		scatterers[i][1] = y;
		scatterers[i][2] = z;

		printf("Scatterer %d position: %lf %lf %lf \n", i, scatterers[i][0], scatterers[i][1], scatterers[i][2]);
	

	//double field_scatterer = incident(scatterers[i][0]);

	//printf("Incident field at scatterer %d: %lf\n", i, field_scatterer);
	
	
		double field_scatterer = incident(scatterers[i][0]);	
	
	// solving the matrix equation
		
		gsl_matrix_set (mmat, i,i, field_scatterer);

	//	gsl_vector_view b
	//		= gsl_vector_view_array (field_scatterer, n);
	// gsl vector set instead
			
	//	gsl_vector *total_field = gsl_vector_alloc (n);
	}
	double green = green_function(scatterers, scatterers);
	int s;
	//gsl_permutation * p = gsl_permutation_alloc (n);
	//gsl_linalg_LU_decomp (&green.matrix, p, &s);
	//gsl_linalg_LU_solve (&green.matrix, p, &b.vector, total_field);
	
	//printf("Total field = \n");
	//gsl_vector_fprintf (stdout, total_field, "%g");

	//gsl_permutation_free (p);

	// defining surface of sphere
	double phi[150];
	double theta[150];
	int r = 500;

	for (i=(M_PI-2); i < (M_PI+2); i++)
	{
		phi[i] =(double)(i)/((M_PI-2) - (M_PI+2));

	}
	for (i=(M_PI/2 - 2); i < (M_PI/2 +2); i++)
	{
		theta[i] = (double)(i)/((M_PI/2 - 2) - (M_PI/2 +2));
	}

	return 0;	
}

double incident(double x)
{
	double E_0 = 1.0;

	return E_0*cexp(1*I*2*M_PI*x);
}

double green_function(double r1[n][3], double r2[n][3])
{
	int i, j;
	gsl_matrix * m = gsl_matrix_alloc (n,n);
	
	double r[n], g[n];
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{	
			r[n] = sqrt((r1[i][1]-r2[j][1])*(r1[i][1]-r2[j][1]) + (r1[i][2]-r2[j][2])*(r1[i][2]-r2[j][2]) + (r1[i][3] - r2[j][3])*(r1[i][3] - r2[j][3]));

			if (r[n] == 0.0)
			{
				g[n] = 1.0;
			}
			else
			{
				g[n] = exp(1*I*2*M_PI*r[n])/(4*M_PI*r[n]);
			}

			gsl_matrix_set (m, i, j, g[n]);
		}
	}
	
	for (i = 0; i < 100; i++)
	{
		for (j = 0; j < n; j++)
		{
			printf ("m(%d,%d) = %g\n", i, j,
					gsl_matrix_get (m, i, j));
		}
	}
	gsl_matrix_free (m);
}

