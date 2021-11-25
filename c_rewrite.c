#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <complex.h>
#include <gsl/linalg_complex_LU_decomp>
#include <gsl/linalg_complex_LU_solve>

#define _USE_MATH_DEFINES





double incident(double x);
double green_function(double r1, double r2);

int main()
{
	int i, j, k, n = 10;
	double x, y, z;
	double scatterers[n][3];

	srand((unsigned)time(NULL));
	for (i = 0; i < n; i++)
	{
		x = 20*(double)rand()/RAND_MAX;
		y = 50*(double)rand()/RAND_MAX;
		z = 30*(double)rand()/RAND_MAX;
		
		scatterers[i][0] = x;
		scatterers[i][1] = y;
		scatterers[i][2] = z;

		printf("%lf %lf %lf \n", scatterers[i][0], scatterers[i][1], scatterers[i][2]);
	}

	double field_scatterer = incident(scatterers[i][0]);

	printf("%lf\n field scatterer: ", field_scatterer);

	double field_decomp = gsl_linalg_LU_decomp(green_function)
}

double incident(double x)
{
	double E_0 = 1.0;

	return E_0*exp(1*I*2*M_PI*x);
}

double green_function(double r1, double r2)
{
	double r, g;
	r = r1 - r2;

	if (r == 0.0)
	{
		g = 1.0;
	}
	else
	{
		g = exp(1*I*2*M_PI*r)/(4*M_PI*r)
	}

}
