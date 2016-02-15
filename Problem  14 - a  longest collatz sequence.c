/*
 * Problem 14: Longest Collatz Sequence
 *
 * It is conjectured that if one starts with any integer and repeatedly takes half if even or
 * triple plus one if odd, eventually one will end up with the value 1.
 *
 * Which starting number, under one million, produces the longest chain?
 *
 * This one is a straightforward approach, calculating the length of each chain and tracking
 * the maximum length.
 *
 * Output:
 *
 * 2016-02-14 15:33:35 - CPU time used: 0 hrs 00 mins 01.542 secs
 *                         Longest chain was 524 in length starting with 837799
 */

#include "eulersubs.h"

unsigned int next_coll(unsigned int n);

int main(void)
   {
   unsigned int count, i, j, max, maxval, start_tics, limit=1000000;
   char msg[200];

   start_tics = clock();
   max=0;                     /* init max length found   */
   for (i=2; i<limit; i++)
      {
     count = 0;
      j = i;
      while (j != 1)
         {
         j = next_coll(j);    /* turn the crank          */
         count ++;            /* count an iteration      */
         }
      if (count > max)
         {
         max = count;        /* save the new max length  */
         maxval = i;         /*  and the value that led  */
         }                   /*  to it                   */
      }

   sprintf(msg, "Longest chain was %d in length starting with %d\n", max, maxval);
   logcputime(start_tics, msg);
   exit(0);
   }

/*
 * Find the next value in a Collatz sequence
 */

unsigned int next_coll(unsigned int n)
   {
   if (n%2 == 0)
      return(n/2);
   else
     return(3*n+1);
   }
