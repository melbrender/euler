
/*
 * Euler problem 3: What is the largest prime factor of 600851475143?
 *
 * Output:
 *
 * 2016-03-20 12:01:06 - CPU time used: 0 hrs 00 mins 00.028 secs
 *                         to build the list of primes up to 775146 containing 62113 primes
 * 2016-03-20 12:01:06 - CPU time used: 0 hrs 00 mins 00.030 secs
 *                         to determine that the largest prime factor of 600851475143 is 6857
 */

#include "eulersubs.h"

#define VALUE 600851475143

int main(void)
   {
   long long int limit=VALUE;
   int i, sq, largest=0, start_tics;
   extern int primecnt, *primes;
   char msg[150];

   start_tics = clock();
   sq = sqrt(limit);                   /* highest prime we need to worry about      */

   buildprimes(sq);                    /* build primes up to square root of value   */

   for(i=0; i<primecnt; i++)           /* for all primes up to the square root      */
      {
      if (limit%primes[i] == 0)        /* if one of them is a factor then           */
         {
         largest = primes[i];          /* we have a new largest prime factor        */
         while (limit%primes[i] == 0)  /* divide out all factors of this prime      */
            limit /= primes[i];
         if (limit == 1)               /* if we reach one, we're all done           */
            break;
         }
      }

   if (largest == 0)
      sprintf(msg, "to determine that the value %I64d is a prime", VALUE);
   else
      sprintf(msg, "to determine that the largest prime factor of %I64d is %d", VALUE, largest);
   logcputime(start_tics, msg);
   exit(0);
   }




