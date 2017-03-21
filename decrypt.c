/*HPP Mini Project by Jonas Melander */

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "file_utils.h"
#include "utils.h"
#include "funcs_opt.h"
#include "timings.h"

int main(int argc, char** argv) {
  
	
	if(argc != 4) {
    printf("Please give 3 arguments: input_file_name output_file_name n_threads\n");
    return -1;
  }

  const char* input_file_name = argv[1];
  const char* output_file_name = argv[2];
  int n_threads = atoi(argv[3]);
  if (n_threads < 1)
  {
  	printf("You need to have at least 1 thread.");
  	return -1;
  }
  
  printf("input_file_name = '%s'\n", input_file_name);
  printf("output_file_name = '%s'\n", output_file_name);
  printf("n_threads = %d\n", n_threads);

  // Get size of input file
  int fileSize = get_file_size(input_file_name);
  if(fileSize <= 0) {
    printf("Error: (fileSize <= 0)\n");
    return -1;
  }
  
  //Allocating memory for vector of chars.
  double *func11rep;
  func11rep = (double *)malloc(256*sizeof(double));
  
  // Allocate buffer for input data
  unsigned char* buf0 = (unsigned char*)malloc(fileSize*sizeof(unsigned char));
  
  // Read input file
  if(read_file_into_buffer(input_file_name, buf0, fileSize) != 0) {
    printf("Error in read_file_into_buffer for input_file_name = '%s'.\n", input_file_name);
    return -1;
  }
  printf("Input file read OK, now starting computation...\n");
  

  // Computation of "characteristic number" and measuring time.
  double computationStartTime = get_wall_seconds();
  double chnum = get_wall_seconds();
  long double characteristicNumber= ComputeNumber1(buf0, fileSize, func11rep, n_threads);
  double timechnum = get_wall_seconds() - chnum;
  printf("timechnum = %lf\n",  timechnum);
  printf("filesize = %d, mod 4 = %d\n", fileSize, fileSize%4);
  
  // ****  To check errors. ****
  /* long double relative_err1, relative_err2, relative_err3, relative_errM, relative_errt;
  long double characteristic_text = 0.1076053277114157;
  long double characteristic_img1 = 26336.6123770279;
  long double characteristic_img2 = 52548.6367708101;
  long double characteristic_img3 = 169029.7682397679;
  long double characteristic_Musi = 2371800.421340139;
  relative_err1 = (characteristicNumber - characteristic_img1) / characteristic_img1;
  relative_err2 = (characteristicNumber - characteristic_img2) / characteristic_img2;
  relative_err3 = (characteristicNumber - characteristic_img3) / characteristic_img3;
  relative_errM = (characteristicNumber - characteristic_Musi) / characteristic_Musi;
  relative_errt = (characteristicNumber - characteristic_text) / characteristic_text;*/
  long double characteristic_Musi = 2371800.421340139;
  long double relative_errM = (characteristicNumber - characteristic_Musi) / characteristic_Musi;
  int i;
  //Parallelising loop with n_threads number of threads using openmp
  #pragma omp parallel for num_threads(n_threads) 
  for (i = 0; i < fileSize; i+=1)
  {
   	  //Calling ShuffleBitsB with result of ShuffleBitsA as an argument.
	  buf0[i] 	= ShuffleBitsB(ShuffleBitsA(buf0[i])); 
  }

  unsigned char* buf1 = (unsigned char*)malloc(fileSize*sizeof(unsigned char));

  for (i = 0; i < fileSize-1; i += 2)   //Swaping bytes pairwise in buffer
  {
	buf1[i] = buf0[i+1];
	buf1[i+1] = buf0[i];
  }

  unsigned char* buf2 = (unsigned char*)malloc(fileSize*sizeof(unsigned char));
  //Parallelising loop with n_threads number of threads using openmp
  #pragma omp parallel for num_threads(n_threads)
  for (i = 0; i < fileSize; i++)
  {
  	buf2[i] = ShuffleBitsC(buf1[i]); // Shuffling bits around
  }

  unsigned char* buf3 = (unsigned char*)malloc(fileSize*sizeof(unsigned char));  
  int cntr;
  cntr = fileSize-1;
  for (i = 0; i < fileSize; i++) //  Reversing Array
  {
	buf3[i] = buf2[cntr];
	cntr -=1;
  }

  double computationTimeTaken = get_wall_seconds() - computationStartTime;
  printf("Computation took %f wall seconds.\n", computationTimeTaken);

  // Write output file
  if(write_buffer_to_file(output_file_name, buf3, fileSize) != 0) {
    printf("Error in write_buffer_to_file for output_file_name = '%s'.\n", output_file_name);
    return -1;
  }
  
  printf("Done. Output file '%s' written OK, %d bytes. characteristicNumber = %10.16Lf \nRelative error music = %8.16Le\n", output_file_name, fileSize, characteristicNumber, relative_errM);

  free(buf0);
  free(buf1);
  free(buf2);
  free(buf3);
  free(func11rep);
  return 0;
}
