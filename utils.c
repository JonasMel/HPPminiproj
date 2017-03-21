/*HPP Mini Project by Jonas Melander */
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

//Shuffling bits. If shift is odd do or_eq on result.
unsigned char ShuffleBitsA(unsigned char c)
{
	unsigned char result = 0;
	if((c >> 1) & 1) result |= (1 << 0);
	if((c >> 0) & 1) result |= (1 << 1);
	if((c >> 3) & 1) result |= (1 << 2);
	if((c >> 2) & 1) result |= (1 << 3);
	if((c >> 5) & 1) result |= (1 << 4);
	if((c >> 4) & 1) result |= (1 << 5);	
	if((c >> 7) & 1) result |= (1 << 6);
	if((c >> 6) & 1) result |= (1 << 7);

	return result;
}

//Shuffling bits. If shift is odd do or_eq on result.
unsigned char ShuffleBitsB(unsigned char c)
{
	unsigned char result = 0;
	if ((c >> 7) & 1) result |= (1 << 0);
	if ((c >> 5) & 1) result |= (1 << 1);
	if ((c >> 6) & 1) result |= (1 << 2);
	if ((c >> 3) & 1) result |= (1 << 3);
	if ((c >> 4) & 1) result |= (1 << 4);
	if ((c >> 1) & 1) result |= (1 << 5);
	if ((c >> 2) & 1) result |= (1 << 6);
	if ((c >> 0) & 1) result |= (1 << 7);

	return result;
}


//Shuffling bits. If shift is odd do or_eq on result.
unsigned char ShuffleBitsC(unsigned char c) {
  unsigned char result = 0;
  if((c >> 0)&1) result |= (1 << 0);
  if((c >> 7)&1) result |= (1 << 1);
  if((c >> 2)&1) result |= (1 << 2);
  if((c >> 6)&1) result |= (1 << 3);
  if((c >> 4)&1) result |= (1 << 4);
  if((c >> 5)&1) result |= (1 << 5);
  if((c >> 3)&1) result |= (1 << 6);
  if((c >> 1)&1) result |= (1 << 7);
      
  return result;
}

//Print contents of buffer.
void PrintBufferContents(const unsigned char* buf, int n) {
  for(int i = 0; i < n; i++)
    printf(" %d", (int)buf[i]);
  printf("\n");
}
