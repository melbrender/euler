
/*
 * Problem 12 - Highly Divisible Triangular Number
 *
 * What is the value of the first triangle number to have over five hundred divisors?
 *
 * Method three: we have tr = i*(i+1)/2 which is either (i/2)*(i+1)
 *                                                or       i*((i+2)/2)
 *
 * depending on whether i is even or not. In either case, the two numbers
 * being multiplied are relatively prime, so we can get the number of divisors
 * of the triangular number by multiplying the number of divisors the two
 * numbers separately have.
 *
 * Output:
 *
 * 2016-02-11 15:30:29 - CPU time used: 0 hrs 00 mins 00.000 secs
 *       76576500 is the first triangular number with over 500 divisors (it has 576)
 */

#include "eulersubs.h"

int main()
   {
   int start_tics, limit=15000;        /* highest triangle index to try    */
   int i, tr, divs, max=0, maxtr, found;
   extern int *divcnts;
   char msg[250];


   found = 0;
   start_tics = clock();               /* get start time                   */

   buildprimesdivs(limit+1);           /* compile primes, divisor counts   */
   for (i=1; i<limit; i++)
      {
      tr = (i*(i+1))/2;                /* calculate ith triangular number  */
      if (i%2 == 0)
         divs = divcnts[i/2]*divcnts[i+1];
      else
         divs = divcnts[i]*divcnts[(i+1)/2];

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
