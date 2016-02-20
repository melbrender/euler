/*
 * Problem 21: Amicable Numbers
 *
 *   Find the sum of all amicable pairs where each is less than 10,000
 *
 * An amicable pair of primes are p and q where the sum of the proper
 * divisors of p is q, and the sum of the proper divisors of q is p.
 *
 * Method: build a table by directly counting numbers of divisors.
 *
 * Output:
 *
 * 6 is a perfect number
 * 28 is a perfect number
 * Amicable number found: 220 paired with 284
 * Amicable number found: 284 paired with 220
 * 496 is a perfect number
 * Amicable number found: 1184 paired with 1210
 * Amicable number found: 1210 paired with 1184
 * Amicable number found: 2620 paired with 2924
 * Amicable number found: 2924 paired with 2620
 * Amicable number found: 5020 paired with 5564
 * Amicable number found: 5564 paired with 5020
 * Amicable number found: 6232 paired with 6368
 * Amicable number found: 6368 paired with 6232
 * 8128 is a perfect number
 * 2016-02-13 14:57:17 - CPU time used: 0 hrs 00 mins 00.010 secs
 *                         to find 10 amicable numbers with sum 31626
 */

#include "eulersubs.h"
#define LIMIT 10000

int main()
   {
   int start_tics;
   unsigned int i, k, sum=0, sq, count=0;
   char msg[100];
   int sumdivs[LIMIT];                         /* proper divisor sum for each i   */

   start_tics = clock();                       /* get start cpu time              */

   sumdivs[0] = 0;
   sumdivs[1] = 0;

   /*
    * work out the table of the sum of proper divisors for each integer
    */

   for (i=2; i<LIMIT; i++)
      {
      sq = sqrt(i);                             /* look for divisors up to the       */
      sum = 1;                                  /*  square root; count the divisor 1 */
      for (k=2; k<=sq; k++)                     /*  start with 2 so we avoid         */
         {                                      /*   counting i itself               */
         if (i%k == 0)
            {
            sum += k;
            sum += i/k;
            }
         }

      if (sq*sq == i)                           /* if it is a perfect square         */
         sum -= sq;                             /*  don't count the sqrt twice       */
      sumdivs[i] = sum;                         /*   save the sum                    */
      }

   /*
    * Search the table for amicable pairs
    */

   sum = 0;
   for (i=2; i<LIMIT; i++)
      {
      if (sumdivs[i] >= LIMIT)                /* ignore if number of divisors     */
         continue;                            /*  is too big                      */
      if (sumdivs[sumdivs[i]] == i)           /* if amicable                      */
         {
         if (i != sumdivs[i])                 /* if two distinct numbers          */
            {
            sprintf(msg, "Amicable number found: %d paired with %d", i, sumdivs[i]);
            lognote(msg);
            sum += i;
            count++;
            }
         else
            {
            sprintf(msg, "Perfect number found: %d", i);
            lognote(msg);
            }
         }
      }

   sprintf(msg, "to find %d amicable numbers with sum %d\n", count, sum);
   logcputime(start_tics, msg);               /* report elapsed time              */
   exit(0);
   }
