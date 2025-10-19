#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

typedef float(*function)(float);

float f1(float x) 
{    
	return (0.6*x + 3); 
}

float f2(float x) 
{    
	return pow((x-2),3)-1; 
}

float f3(float x) 
{    
	return 3/x;
}

float calcIntegralSimpson(float xl, float xr, size_t n, function f) 
{    
	float sum = 0;    
	float h = (xr-xl)/n;    
	for(float x=xl+h; x<xr-h; x+=h) 
	{        
		sum += h/6.0*(f(x) + 4.0*f(0.5*(x+x+h)) + f(x+h));    
	}    
	return sum; 
}

float rootFindLineSearch(float xl, float xr, float eps, function f2, function f1, int *stepcount) 
{ 
	int minstep = 0;
	float x, minx = xl, nextstep;    
	nextstep = fabs(xr-xl)/(1/eps);     
	for(x=xl; x<xr; x += nextstep, *stepcount = *stepcount + 1) 
	{        
		if( fabs(f2(x) - f1(x)) < fabs(f2(minx) - f1(minx)) )
		{
			minstep = *stepcount;
			minx = x;
		}               
	}
	*stepcount = minstep;   
	return minx; 
}

int signF_1(float x, function f)
{
 return f(x) == 0 ? 0 : (f(x) < 0 ? -1:+1);
}

int signF_2(float x, function f2, function f1)
{
 return (f2(x)-f1(x))==0 ? 0 : ((f2(x)-f1(x)) < 0 ? -1:+1);
}

float rootFindDiv1(float xl, float xr, float eps, function f) 
{
	int stepcount=0;
	float xm;
	while(fabs(xr-xl)>eps) 
	{
 		stepcount++;
 		xm=(xl+xr)/2;
 		if(f(xr)==0) 
		{ 
 			return xr;
 		}
		if(f(xl)==0) 
		{
 			return xl;
 		}
 		if(signF_1(xl, f) != signF_1(xm, f))
 		xr=xm;
 		else
 		xl=xm;
 	}
 	return (xl+xr)/2;
}

float rootFindDiv2(float xl, float xr, float eps, function f2, function f1, int *stepcount) 
{
	float xm;
	while(fabs(xr-xl)>eps) 
	{
 		*stepcount = *stepcount + 1;
 		xm=(xl+xr)/2;		
 		if((f2(xr)-f1(xr))==0) 
		{ 
			return xr;
 		}
		if((f2(xl)-f1(xl))==0) 
		{
			return xl;
 		}
 		if(signF_2(xl,f2,f1) != signF_2(xm,f2,f1))	xr=xm;
 		else	xl=xm;
 	}
 	return (xl+xr)/2;
}

int main(int argc, char *argv[])
{
	float xl, xr;
	float x1, x2, x3;
	float s1, s2, s3;
	int step_1 = 0, step_2 = 0, step_3 = 0;
	
// -------------------- обработка параметров командной строки -------------------- начало
	int result = 0;

	if (argc == 1)
	{
		printf("\n");
		printf("-------------------------------------------------------\n");
		printf("no parameters, for more information write parameter -h\n");
		printf("-------------------------------------------------------\n");
		printf("\n");
		return 0;
	}
	
	while ((result = getopt(argc,argv,"hx:s:a:t:")) != -1)
	{
		if (result == 'h')
		{
			printf("\n");
			printf("-------------------------------------------------------\n");
			printf("App to find area between thee functions:\nf1(x) = 0.6*x+3\nf2(x) = (x-2)^3-1\nf3(x) = 3/x\n");
			printf("'-h' for help\n");
			printf("'-x' Intersection poin of f1-f2 f1-f3 and f2-f3 in the given range of x ( for example: -x 0:5 )\n");
			printf("'-s' Intersection poin of f1-f2 f1-f3 and f2-f3 in the given range of x whith statistic ( for example: -s 0:5 )\n");
			printf("'-a' Area between f1 f2 f3 in the given range of x ( for example: -a 0:5 )\n");
			printf("-------------------------------------------------------\n");
			printf("\n");
			if (argc == 2) return 0;
			else continue;
		}
		if (result == 'x')
		{
			sscanf(optarg, "%f:%f", &xl, &xr);
			
			x1 = rootFindDiv2(xl,xr,0.01, f2, f1, &step_1);
			x2 = rootFindDiv2(xl,xr,0.01, f3, f1, &step_2);
			x3 = rootFindDiv2(xl,xr,0.01, f3, f2, &step_3);
			
			printf("\n");
			printf("-------------------------------------------------------\n");
			printf("Root of equation (f2-f1) = 0 is x1 = %f\n", x1);    
			printf("Root of equation (f3-f1) = 0 is x2 = %f\n", x2);    
			printf("Root of equation (f3-f2) = 0 is x3 = %f\n", x3);
			printf("-------------------------------------------------------\n");
			printf("\n");
			continue;
		}
		if (result == 's')
		{
			sscanf(optarg, "%f:%f", &xl, &xr);

			x1 = rootFindDiv2(xl,xr,0.01, f2, f1, &step_1);
			x2 = rootFindDiv2(xl,xr,0.01, f3, f1, &step_2);
			x3 = rootFindDiv2(xl,xr,0.01, f3, f2, &step_3);

			printf("\n");
			printf("-------------------------------------------------------\n");
			printf("Root of equation (f2-f1) = 0 is x1 = %f [number of solver iteration = %d]\n",x1, step_1);    
			printf("Root of equation (f3-f1) = 0 is x2 = %f [number of solver iteration = %d]\n",x2, step_2);    
			printf("Root of equation (f3-f2) = 0 is x3 = %f [number of solver iteration = %d]\n",x3, step_3);
			printf("-------------------------------------------------------\n");
			printf("\n");
			continue;
		}
		if (result == 'a')
		{	
			sscanf(optarg, "%f:%f", &xl, &xr);

			x1 = rootFindDiv2(xl,xr,0.01, f2, f1, &step_1);
			x2 = rootFindDiv2(xl,xr,0.01, f3, f1, &step_2);
			x3 = rootFindDiv2(xl,xr,0.01, f3, f2, &step_3);

			s1 = calcIntegralSimpson(x2, x1, 100, f1);
			s2 = calcIntegralSimpson(x3, x1, 100, f2);
			s3 = calcIntegralSimpson(x2, x3, 100, f3);

			printf("\n");
			printf("-------------------------------------------------------\n");
			printf("Area of f1(x) beetween x2 = %f and x1 = %f is S1 = %f\n", x2, x1, s1);    
			printf("Area of f2(x) beetween x3 = %f and x1 = %f is S2 = %f\n", x3, x1, s2);
			printf("Area of f3(x) beetween x2 = %f and x3 = %f is S3 = %f\n", x2, x3, s3);
			printf("-------------------------------------------------------\n");
			printf("Area between f1 f2 f3 = %f\n",(s1-s2-s3));
			printf("-------------------------------------------------------\n");
			printf("\n");
			continue;
		}
	};
// -------------------- обработка параметров командной строки -------------------- конец
	return 0;
}