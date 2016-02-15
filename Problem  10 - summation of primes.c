
/*
 * Euler problem 10: Find the sum of all the primes below two million.
 *
 * Output:
 *
 * 2016-02-11 15:36:47 - CPU time used: 0 hrs 00 mins 00.260 secs
 *       The sum was: 142913828922
 */

#include "eulersubs.h"

int main(void)
   {
   extern int *primes;
   extern int primecnt;
   char msg[150];
   int limit = 2000000, sum=0, billions=0, start_tics, k;

   start_tics = clock();                  /* record starting time       */
   buildprimes(limit);                    /* build the table of primes  */

   for (k=0; k<primecnt; k++)
      {
      sum += primes[k];
      while (sum >= 1000000000)           /* we're working with 32-bit  */
         {                                /*  arithmetic, so handle     */
         billions++;                      /*   the carry                */
         sum -= 1000000000;
         }
      }
   sprintf(msg, "The sum was: %d%09d\n", billions, sum);
   logcputime(start_tics, msg);
   exit(0);
   }

