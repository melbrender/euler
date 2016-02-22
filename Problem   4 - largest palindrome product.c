/*
 * Euler problem 4: Find the largest palindromic product of two three digit numbers
 *
 * Output:
 *
 * 2016-02-20 14:52:33 - CPU time used: 0 hrs 00 mins 00.330 secs
 *                         Maximal result: 913 x 993 = 906609
 */


#include "eulersubs.h"

int ispalind(int n);

int main(void)
   {
   char msg[200];
   int i,j, start_tics, savei, savej, max=0;

   start_tics = clock();

   for (i=100; i<=999; i++)
      {
      for (j=100; j<999; j++)
         if (ispalind(i*j) == 1)
            if (i*j > max)
               {
               max = i*j;
               savei = i;
               savej = j;
               }
      }

   sprintf(msg, "Maximal result: %d x %d = %d\n", savei, savej, savei*savej);
   logcputime(start_tics, msg);
   exit(0);
   }

/* Test a number to see if it is a palindrome.
 *
 * Form the reverse-reading integer by repeatedly shearing off the lowest
 * order digit and forming a new number with these digits added on the left.
 * If the new number equals the old number, it was a palindrome.
 *
 * Return values:
 *
 * 1 if the input is a palindrome in base 10
 * 0 otherwise
 */
int ispalind(int n)
   {
   int nn, sum=0, lodig;

   nn = n;                    /* save original value        */
   while (nn > 0)
      {
      lodig = nn%10;          /* isolate low digit          */
      sum = 10*sum+lodig;     /* build new integer with     */
      nn /= 10;               /*  these digits in           */
      }                       /*   reverse order            */

   if (n == sum)              /* if the result is the       */
      return(1);              /*  same, it's a palindrome   */
   else
      return(0);              /* else it's not              */
   }


