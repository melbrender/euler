/*
 * Problem 14: Longest Collatz Sequence
 *
 * It is conjectured that if one starts with any integer and repeatedly takes half if even or
 * triple plus one if odd, eventually one will end up with the value 1.
 *
 * Which starting number, under one million, produces the longest chain?
 *
 * This version runs faster because we keep checking if we're intersecting a chain we've
 * already followed to the end. To do this we create an array and in each slot store the
 * length of the collatz chain starting from there.
 *
 * Output:
 *
 * 2016-02-14 15:53:58 - CPU time used: 0 hrs 00 mins 00.120 secs
 *                         Longest chain was 525 in length starting with 837799
 */

#include "eulersubs.h"

unsigned int next_coll(unsigned int n);

int main(void)
   {
   unsigned int count, i, j, max, maxval, start_tics, limit=1000000;
   char msg[200];
   int *lengths;

   start_tics = clock();
   max=0;                              /* init max length found      */

   lengths = calloc(limit, sizeof(int));
   if (lengths == NULL)
      err_exit("Cannot allocate space for length[]", 2);
   lengths[1] = 0;

   for (i=2; i<limit; i++)
      {
      count = 0;
      j = i;
      while (j != 1)
         {
         j = next_coll(j);             /* turn the crank             */
         count++;                      /* count an iteration         */
         if (   (j < limit)            /* if we reach a chain of     */
             && (lengths[j] != 0) )    /*  known length              */
            {
            count += lengths[j];       /*   then we know how much    */
            break;                     /*    further till the end    */
            }
         }
      lengths[i] = count;              /* save the count for this i  */

      if (count > max)
         {
         max = count;                  /* save the new max length    */
         maxval = i;                   /*  and the value that led    */
         }                             /*  to it                     */
      }

   sprintf(msg, "Longest chain was %d in length starting with %d\n", max, maxval);
   logcputime(start_tics, msg);
   exit(0);
   }

unsigned int next_coll(unsigned int n)
   {

   if (n%2 == 0)
      return(n/2);
   else
     return(3*n+1);
   }
