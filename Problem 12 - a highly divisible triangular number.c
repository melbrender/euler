
/*
 * Problem 12 - Highly Divisible Triangular Number
 *
 * What is the value of the first triangle number to have over five hundred divisors?
 *
 * Method one: straightforward counting of all divisors takes too long, so we count
 * divisors up to the square root and double, since each such divisor can be paired
 * with another divisor greater than the square root. Care must be taken to correctly
 * count the square root of a perfect square only once.
 *
 * Output:
 *
 * 2016-02-13 14:52:54 - CPU time used: 0 hrs 00 mins 01.231 secs
 *       76576500 is the first triangular number with over 500 divisors (it has 576)
 */

#include "eulersubs.h"

int main()
   {
   int start_tics, limit=15000;        /* highest triangle index to try    */
   int i, j, tr, sq, divs, max=0, maxtr, found;
   char msg[250];


   found = 0;
   start_tics = clock();               /* get start time                   */

   for (i=1; i<limit; i++)
      {
      tr = (i*(i+1))/2;                /* calculate ith triangular number  */
      sq = sqrt(tr);                   /* integer floor under square root  */
      divs = 0;                        /* initialize count                 */
      for (j=1; j<=sq; j++)
         if (tr%j == 0)
            divs +=2;
      if (sq*sq == tr)                 /* if tr was a perfect square       */
         divs--;                       /*  we counted its square root twice*/

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
