/*
 * Problem 179: Consecutive Positive Divisors
 *
 * Find the number of integers 1 < n < 10,000,000, for which n and n + 1 have the same number
 * of positive divisors. For example, 14 has the positive divisors 1, 2, 7, 14 while 15
 * has 1, 3, 5, 15.
 *
 * Output:
 *
 * 2016-02-14 16:33:09 - CPU time used: 0 hrs 00 mins 02.203 secs
 *                         to compile primes and divisor counts; found 664579 primes up to 10000000
 * 2016-02-14 16:33:09 - CPU time used: 0 hrs 00 mins 02.293 secs
 *                         There were 986262 cases where consecutive integers had the same number of divisors
 */

#include "eulersubs.h"

extern int *divcnts;

int main(void)
   {
   unsigned int i, count=0, start_tics, limit=10000000;
   char msg[200];

   start_tics = clock();
   buildprimesdivs(limit);                /* constuct table of numbers of divisors  */

   for (i=1; i<limit-1; i++)
      {
      if (divcnts[i] == divcnts[i+1])
         count++;
      }

   sprintf(msg, "There were %d cases where consecutive integers had the same number of divisors", count);
   logcputime(start_tics, msg);
   exit(0);
   }


