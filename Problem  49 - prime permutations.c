/*
 * Problem 49: Prime Permutations
 *
 * The arithmetic sequence, 1487, 4817, 8147, in which each of the terms increases by 3330,
 * is unusual in two ways: (i) each of the three terms are prime, and, (ii) each of the 4-digit
 * numbers are permutations of one another.
 *
 * There are no arithmetic sequences made up of three 1-, 2-, or 3-digit primes, exhibiting this
 * property, but there is one other 4-digit increasing sequence.
 *
 * What 12-digit number do you form by concatenating the three terms in this sequence?
 *
 * We build the list of four-digit primes, and then at each starting point look at all possible
 * arithmetic sequences of threes. Check the second and third for primality and among sequences
 * meeting that condition, check for ones with same digits permuted.
 *
 * Output:
 *
 * 2016-02-20 14:29:48 - CPU time used: 0 hrs 00 mins 00.000 secs
 *                         to build the list of primes up to 10000 containing 1229 primes
 * 2016-02-20 14:29:48 - The first 4 digit prime is: 1009; the last is 9973
 * 2016-02-20 14:29:48 - The number of 4 digit primes is 1061
 * Found a sequence: 1487 4817 8147 with increment 3330
 * Found a sequence: 2969 6299 9629 with increment 3330
 * 2016-02-20 14:29:48 - CPU time used: 0 hrs 00 mins 00.060 secs
 *                         Found 2 such sequences
 */

#include "eulersubs.h"

extern int primecnt, *primes;

int main()
   {
   int i, j, k, first, last, seqcnt, start_tics;
   char msg[200];

   start_tics = clock();                     /* record start time                         */
   buildprimes(10000);                       /* build list containing all 4 digit primes  */

   for (i=0; i<primecnt; i++)
      if (primes[i] > 999)
         {
         first = i;                          /* save the index of the first 4 digit prime */
         break;
         }

   last = primecnt-1;                        /* save the index of the last 4 digit prime  */

   sprintf(msg, "The first 4 digit prime is: %d; the last is %d",
         primes[first], primes[last]);
   lognote(msg);
   sprintf(msg, "The number of 4 digit primes is %d",
         last-first+1);
   lognote(msg);

   seqcnt = 0;
   for (j=first; j<=last-2; j++)             /* for all possible starting points          */
      {                                      /*  and all possible increments (even only)  */
      for (k=2; k<=(primes[last]-primes[j])/2; k+=2)
         {
         if ( isprime(primes[j] + k) &&      /* okay, we have a sequence of three primes  */
              isprime(primes[j] + 2*k) )
            {
            if (arepermuted(3, primes[j],    /* if they are the same digits permuted      */
                               primes[j]+k,
                               primes[j]+2*k) == 1)

               {                             /* tell the world                            */
               printf("Found a sequence: %d %d %d with increment %d\n",
                         primes[j], primes[j]+k, primes[j]+2*k, k);
               seqcnt++;
               }
            }
         }
      }

   sprintf(msg, "Found %d such sequences\n", seqcnt);
   logcputime(start_tics, msg);
   exit(0);
   }
