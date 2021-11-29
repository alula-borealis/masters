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
	

	double field_scatterer = incident(scatterers[i][0]);

	printf("Incident field at scatterer %d: %lf\n", i, field_scatterer);
	
	}
	double green = green_function(scatterers, scatterers);
	//double field_decomp = gsl_linalg_LU_decomp(green_function)
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
