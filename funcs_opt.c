/*HPP Mini Project by Jonas Melander */
#include "funcs_opt.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>


double Func11(unsigned char a) {
  double x = a*0.001;
  double y = sqrt(x) + 0.12;
  double z = pow(x, 1.3);
  double w = z / y + 0.4;
  return w*w*0.04;
}

double Func21(unsigned char a, unsigned char b, double * f1rp) {
  int mid = (a + b)*0.5;
  int step = 1;
  int k;
  double sum = 0;
  if(b < a)
 {
   step = -1;
   for (k = a; k > mid; k += step)
   {
     sum += f1rp[k];	
   }
  }
  else
  {
    for (k = a; k < mid; k += step)
	{
	  sum += f1rp[k];
	}
  }
  return sum / 300;
}

// This function expects the input array a to consist of 4 numbers.
double Func31(unsigned char* a) {
  double w[4];

  w[0] = a[0]*0.001 - 0.0006*a[1] + 0.0004*a[2];
  w[1] = a[1]*0.001 - 0.0005*a[2] + 0.0009*a[3];
  w[2] = a[0]*0.001 - 0.0004*a[2] + 0.0001*a[3];
  w[3] = a[0]*0.001 - 0.0002*a[1] + 0.0003*a[2];
  double sum = 0;
  sum = w[0]*w[0]*w[0] + w[1]*w[1]*w[1] + w[2]*w[2]*w[2] + w[3]*w[3]*w[3];
  return sum / 3;
}

double ComputeNumber1(unsigned char* buf, int nBytes, double * f1rp, int nThrds) {
  double * f2rp = malloc(256*256*sizeof(double));
  int i;
  //Parallelising loop with n_threads number of threads using openmp
  #pragma omp parallel for num_threads(nThrds)
  for (i = 0; i < 256; i++)
	  f1rp[i] = Func11(i); //Calculating all possible values from Func11.
  #pragma omp parallel for num_threads(nThrds)
  for (i = 0; i < 256; i++)
  {
  	for (int j = 0; j < 256; j++)
  	{
  	  f2rp[i*256 + j] = Func21(i, j, f1rp);
  	}
  }
  double sum = 0;
  //Parallelising loop with n_threads number of threads using openmp
  #pragma omp parallel for num_threads(nThrds) reduction(+:sum)
  for(i = 0; i < nBytes-3; i+=4) 
  {
    /*Using values from vector of possible Func11 vals instead of calculating them again.*/
    sum += f1rp[buf[i]]+ f1rp[buf[i+1]]+ f1rp[buf[i+2]] + f1rp[buf[i+3]] \
    + f2rp[buf[i]*256 + buf[i+1]] + f2rp[buf[i+2]*256 + buf[i+3]] \
	+ Func31(&buf[i]);
  }
  /*If the number of bytes is not divisible by 4,
  add the last (nBytes - nBytes%4 -1) to the sum here*/
  if (nBytes % 4 != 0)
  {	
    double strt;
    strt = (nBytes- nBytes % 4);
    for(i = strt; i < nBytes; i++)
      sum += f1rp[buf[i]];

    for(i = strt; i < nBytes-1; i+=2)
      sum += Func21(buf[i], buf[i+1], f1rp);

    for(i = strt; i < nBytes-3; i+=4)
      sum += Func31(&buf[i]);
  }	
  free(f2rp);
  return sum;
}
