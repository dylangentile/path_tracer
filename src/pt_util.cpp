#include "pt_util.h"

#include <cstdlib>
#include <cstdio>


void 
seed_random()
{
	unsigned the_seed = 420;
	FILE* fp = fopen("/dev/random", "r");
	
	if(fp != nullptr)
	{
		fread(&the_seed, 1, sizeof(the_seed), fp);
		fclose(fp);
	}

	srand(the_seed);
}


double
random_double()
{
	return (double)rand() / ((double)RAND_MAX + 1.0); // [0,1)
}

double
random_double(double min, double max)
{
	return min + ((max-min)*random_double());
}

double
clamp(double x, double min, double max)
{
	if(x < min)
		return min;
	if(x > max)
		return max;
	return x;
}

double 
deg_to_rad(double x)
{
	return x * ((2*M_PI)/360);
}
