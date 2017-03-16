#include "timings.h"
#include <sys/time.h>
#include <stdlib.h>

/* Here we define a routine called get_wall_seconds() the gets number
   of seconds and microseconds since the Epoch (1970-01-01 00:00:00
   +0000 (UTC)). The seconds and microseconds values are combined in a
   double number giving the number of seconds since the Epoch. */
double get_wall_seconds() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  double seconds = tv.tv_sec + (double)tv.tv_usec / 1000000;
  return seconds;
}
