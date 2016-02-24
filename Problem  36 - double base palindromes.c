/*
 * Euler problem 36: Double Base Palindromes
 *
 * Find the sum of all numbers, less than one million, which are palindromic in base 10 and base 2.
 *
 * Output:
 *
 * 2016-02-23 18:53:21 - CPU time used: 0 hrs 00 mins 00.200 secs
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

/* Test a number to see if it is a palindrome in a given base.
 *
 * Form the reverse-reading integer by repeatedly shearing off the lowest
 * order digit and forming a new number with these digits appended on the right.
 * If the new number equals the old number, it was a palindrome.
 *
 * Return values:
 *
 * 1 if the input is a palindrome in base 10
 * 0 otherwise
 */
int ispalind(int n, int base)
   {
   int  i, j, idx=0, digs[100];

   while(n>0)
      {
      digs[idx++] = n%base;         /* shear off each digit into an  */
      n /= base;                    /*  array, starting with the     */
      }                             /*   lowest order                */

   j = idx/2;
   for (i=0; i<j; i++)              /* compare each digit            */
      {                             /*  with it's counterpart in     */
      if (digs[i] != digs[idx-1-i]) /*   the other direction         */
         return(0);                 /* if any pair doesn't match     */
      }                             /*  we're done                   */

   return(1);                       /* if they all matched,          */
                                    /* it's a palindrome             */
   }

