
/*
 * Problem 12 - Highly Divisible Triangular Number
 *
 * What is the value of the first triangle number to have over five hundred divisors?
 *
 * Method two: count the divisors of each triangular number by repetitively dividing
 * out by each prime factor to get the prime decomposition; then multiply the prime
 * exponents, each increased by one.
 *
 * Output:
 *
 * 2016-02-06 17:51:33 - CPU time used: 0 hrs 00 mins 00.050 secs
 *        76576500 is the first triangular number with over 500 divisors (it has 576)
 */

#include "eulersubs.h"

int main()
   {
   int start_tics, limit=15000;        /* highest triangle index to try    */
   int i, idx, tr, divs, max=0, maxtr, factors, val, found;
   extern int *primes;
   char msg[250];


   found = 0;
   start_tics = clock();               /* get start time                   */
   buildprimes(limit+1);               /* construct list of needed primes  */

   max = 0;                            /* reinitialize                     */
   for (i=1; i<limit; i++)
      {
      tr = (i*(i+1))/2;                /* calculate ith triangular number  */
      val = tr;                        /* working copy of triangular nbr   */
      divs=1;                          /* initialize number of divisors    */
      idx = 0;                         /* initialize index into primes     */
      while(val > 1)                   /* look for any primes              */
         {                             /*  that divide val                 */
         if (val % primes[idx] == 0)   /* for each such prime              */
            {
            factors=0;                 /* count the times prime goes in    */
            while(val%primes[idx] == 0)
               {
               val /= primes[idx];     /* reducing the value by one more   */
               factors++;              /*  factor of the prime each time   */
               }
            divs *= (factors+1);       /* that prime's contributions       */
            }                          /*  to the divisors                 */
         idx++;                        /* advance to the next prime        */
         }                             /* val will be one when we're done  */
      if (divs > max)
         {
         max = divs;
         maxtr = tr;
         if (max > 500)
            {
            sprintf(msg, "%d is the first triangular number with over 500 divisors (it has %d)",
                        tr, max);
            logcputime(start_tics, msg);
            found = 1;                 /* show we found the answer         */
            break;
            }
         }
      }

   if (found == 0)
      {
      sprintf(msg, "Max of %d divisors found for triangular number %d of index %d\n",
         max, maxtr, i);
      logcputime(start_tics, msg);
      }
   exit(0);
   }
