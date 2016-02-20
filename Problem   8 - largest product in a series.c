/* Problem 8 – Largest product in a series
 *
 * Find the thirteen adjacent digits in the 1000-digit number that have the greatest product.
 * What is the value of this product?
 *
 * Working on a 32 bit machine, I had to handle the carries myself. I call the carry location
 * billions, but it's actually 100,000,000 since I might need to carry up to 9 in the high
 * place and my product wouldn't be able to hold 9 billion.
 *
 * I put the digits in a file and read them into the program at run time.
 *
 * Output:
 *
 * 2016-02-20 15:23:26 - We read 20 lines and 1000 digits
 * 2016-02-20 15:23:26 - CPU time used: 0 hrs 00 mins 00.000 secs
 *                         Max was: 23514624000 at index 197
 */


#include "eulersubs.h"

int main(int argc, char **argv)
   {
   int digits[1000];                               /* digits read from file      */
   int digitcnt=0, linecnt=0, start_tics;
   int i, j, maxidx;
   unsigned int bilmax=0, max=0, product, bilproduct;
   char line[1000], *cp;                           /* read-in area               */
   char msg[200];                                  /* output message space       */
   FILE *fp=NULL;
   char filename[]="C:\\Documents and Settings\\Mel\\My Documents\\cworkspace\\euler\\src\\thousand_digits.txt";

   start_tics = clock();

   fp = fopen(filename, "r");                      /* open input file            */
   if (fp == NULL)
      {
      perror("Error opening file");
      exit(0);
      }

   while (1)
      {
      cp = fgets(line, 200, fp);                   /* read a line                */
      if (cp == NULL)                              /* if EOF just end the loop   */
         break;
      linecnt++;

      for (i=0; i<strlen(line); i++)
         {
         if (line[i] != '\n')                      /* skip out on the linefeed     */
            digits[digitcnt++] = line[i] - '0';    /* move the character into array*/
         }
      }

   sprintf(msg, "We read %d lines and %d digits", linecnt, digitcnt);
   lognote(msg);

   for (i=0; i<987; i++)                           /* for each 13 digit sequence   */
      {
      product = 1;
      bilproduct = 0;
      for (j=0; j<13; j++)
         {
         product *= digits[i+j];
         bilproduct *= digits[i+j];
         if (product >= 100000000)
            {
            bilproduct += (product/100000000);
            product %= 100000000;
            }
         }
      if (   ( bilproduct > bilmax)
          || (  (bilproduct == bilmax) && (product > max) ) )
         {
         bilmax = bilproduct;
         max = product;
         maxidx = i;
         }
      }
   sprintf (msg, "Max was: %d%08d at index %d\n", bilmax, max, maxidx);
   logcputime(start_tics, msg);
   exit(0);
   }
