
/*
 * Euler problem 187: How many composite integers, n < 10,000,000, have precisely two,
 * not necessarily distinct, prime factors?
 *
 * Output:
 *
 * 2016-03-20 16:56:45 - CPU time used: 0 hrs 00 mins 01.831 secs
 *                         to build the list of primes up to 50000000 containing 3001134 primes
 * 2016-03-20 16:56:45 - CPU time used: 0 hrs 00 mins 01.888 secs
 *                         to determine the answer is 17427258
 */

#include "eulersubs.h"



int main(void)
   {
   int limit=100000000;
   long long count=0;
   int i, j, start_tics;
   extern int primecnt, *primes;
   char msg[150];

   start_tics = clock();

   buildprimes(limit/2);                     /* build primes up to half the limit         */

   for(i=0; i<primecnt; i++)                 /* for all primes up to half the limit       */
      for (j=0; j<=i; j++)                   /*  see if the product is within the limit   */
         {
         if (primes[i]*primes[j] >= limit)   /* if product has reached the limit          */
            break;                           /*  we're done for this i                    */
         count++;                            /* else count another semi-prime             */
      }

   sprintf(msg, "to determine the answer is %I64d", count);
   logcputime(start_tics, msg);
   exit(0);
   }




