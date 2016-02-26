/*
 * Euler problem 4: Find the largest palindromic product of two three digit numbers
 *
 * Output:
 *
 * 2016-02-26 18:16:55 - CPU time used: 0 hrs 00 mins 00.150 secs
 *                         Maximal result: 993 x 913 = 906609
 */


#include "eulersubs.h"

int main(void)
   {
   char msg[200];
   int i,j, start_tics, savei, savej, max=0;

   start_tics = clock();

   for (i=999; i>99; i--)           /* loop backwards on i                 */
      {
      for (j=999; j>99; j--)        /*  and on j                           */
         {
         if (ispalind(i*j, 10) == 1)
            if (i*j > max)          /* so that we can save time            */
               {                    /*  by moving on to the next j         */
               max = i*j;           /*   once we have a new max with a     */
               savei = i;           /*    given i since we'll never do     */
               savej = j;           /*     better with the same i and a    */
               break;               /*      lower j (thanks Kate!)         */
               }
         }
      }

   sprintf(msg, "Maximal result: %d x %d = %d\n", savei, savej, savei*savej);
   logcputime(start_tics, msg);
   exit(0);
   }

