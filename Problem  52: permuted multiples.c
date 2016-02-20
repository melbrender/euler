/*
 * Problem 52: Permuted Multiples
 *
 * It can be seen that the number, 125874, and its double, 251748, contain exactly the
 * same digits, but in a different order.
 *
 * Find the smallest positive integer, x, such that 2x, 3x, 4x, 5x, and 6x, contain the
 * same digits (as x).
 *
 * Output:
 *
 * 2016-02-20 12:11:33 - CPU time used: 0 hrs 00 mins 00.220 secs
 *                         Found a success: 142857  with multiples: 285714 428571 571428 714285 857142
 */

#include "eulersubs.h"


int main()
   {
   int i, start_tics, limit=1000000;
   char msg[200];

   start_tics = clock();                  /* record start time                   */

   for (i=1; i<limit; i++)
      {
      if (arepermuted(6, i, 2*i, 3*i, 4*i, 5*i, 6*i) == 1)
         {
         sprintf(msg, "Found a success: %d  with multiples: %d %d %d %d %d",
                    i, 2*i, 3*i, 4*i, 5*i, 6*i);
         logcputime(start_tics, msg);
         exit(0);
         }
      }

   sprintf(msg, "No success found for values up to %d", limit);
   logcputime(start_tics, msg);
   exit(0);
   }

