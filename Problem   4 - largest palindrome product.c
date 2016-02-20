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

int ispalind(int n)
   {
   /* returns 1 if integer is palindromic in base 10
    * returns 0 otherwise
    */

   char s[100];
   int i, len;

   sprintf(s, "%d", n);             /* convert to string         */
   len = strlen(s);                 /* get length                */

   for (i=0; i<(len+1/2); i++)
      {
      if (s[i] != s[len-i-1])       /* if not palindrome         */
         return(0);                 /*  return right away        */
      }

   return(1);                       /* it is a palindrome        */
   }

