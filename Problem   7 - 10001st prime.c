
/*
 * Euler problem 7: Find the 10,001st prime.
 *
 * Output:
 *
 * 2016-02-07 18:42:14 - CPU time used: 0 hrs 00 mins 00.110 secs
 *        The 10,001st prime is: 104743
 */

#include "eulersubs.h"


int main(void)
   {
   int limit = 1000000;
   char msg[150];
   int start_tics;
   extern int *primes, primecnt;

   start_tics = clock();                  /* record starting time       */
   buildprimes(limit);                    /* build the table of primes  */

   if (primecnt < 10001)
      {
      printf("Limit of %d is too small; look further!\n", limit);
      exit(1);
      }

   sprintf(msg, "The 10,001st prime is: %d", primes[10000]);
   logcputime(start_tics, msg);
   exit(0);
   }


