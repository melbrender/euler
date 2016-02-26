/*
 * Euler problem 36: Double Base Palindromes
 *
 * Find the sum of all numbers, less than one million, which are palindromic in base 10 and base 2.
 *
 * Output:
 *
 * 2016-02-26 18:19:52 - CPU time used: 0 hrs 00 mins 00.180 secs
 *                         there were 20 bipalindromes, adding to 872187
 */


#include "eulersubs.h"

int ispalind(int n, int base);

int main(void)
   {
   char msg[200];
   int i, start_tics, sum=0, count=0, limit=1000000;

   start_tics = clock();

   for (i=0; i<limit; i++)          /* run through the integers      */
      {
      if (   ispalind(i, 10)        /* if an integer is a palindrome */
          && ispalind(i, 2) )       /*  in both bases                */
         {
         count++;                   /* count it                      */
         sum += i;                  /*  and add it                   */
         }
      }

   sprintf(msg, "there were %d bipalindromes, adding to %d", count, sum);
   logcputime(start_tics, msg);
   exit(0);
   }


