/*
 * Euler problem 6: Find the difference between the sum of the squares of the first one hundred
 * natural numbers and the square of the sum.
 *
 * 2016-02-20 14:52:33 - CPU time used: 0 hrs 00 mins 00.330 secs
 *                         Maximal result: 913 x 993 = 906609
 * Output:
 *
 * 2016-02-20 15:07:15 - CPU time used: 0 hrs 00 mins 00.000 secs
 *                         Result is: 25164150
 */


#include "eulersubs.h"

int main(void)
   {
   char msg[200];
   int i,sum=0, start_tics, result;

   start_tics = clock();               /* record start time                   */

   for (i=1; i<=100; i++)
      {
      sum += i*i;                      /* add up the first hundred squares    */
      }
   result = 5050*5050 - sum;           /* subtract the square of the sum      */
                                       /* [since this is Project Euler I      */
                                       /*  calculate the sum!]                */

   sprintf(msg, "Result is: %d", result);
   logcputime(start_tics, msg);
   exit(0);
   }
