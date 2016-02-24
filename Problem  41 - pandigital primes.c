/*
 * Euler problem 41: Pandigital Primes
 *
 * A pandigital number is an n digit number which uses the digits 1,...,n each exactly once.
 * What is the largest n-digit pandigital prime that exists?
 *
 * Output:
 *
 * 2016-02-24 13:13:49 - CPU time used: 0 hrs 02 mins 19.711 secs
 *                         to build the sieve of primes up to 1000000000 containing 50847534 primes
 * 2016-02-24 13:14:08 - CPU time used: 0 hrs 02 mins 39.088 secs
 *                         there are 538 pandigital primes, and the largest is: 7652413
 */


#include "eulersubs.h"

int ispandigital(int n);

int main(void)
   {
   char msg[200];
   int start_tics, i, j, sq, max=0, count=0, primecnt=0, maxprime=1000000000;
   char *sieve;

   start_tics = clock();

   /* Construct a sieve of Eratosthenes; our limit is a billion, since no     */
   /* pandigital number could have more than nine digits                      */

   sieve = calloc(maxprime+1,          /* allocate space for the sieve        */
               sizeof(char));
   if (sieve == NULL)
       err_exit("error: cannot allocate space for sieve[]!", 1);

   sieve[0] = 0;                       /* 0 and 1 are not primes              */
   sieve[1] = 0;

   for (i=2; i<=maxprime; i++)         /* fill the rest of the sieve          */
      sieve[i] = 1;                    /*  with ones                          */

   sq = sqrt(maxprime);
   for (i=0; i<=sq; i++)               /* for each run of the loop, the first */
      {                                /*  value of i with sieve[i] != 0      */
      if (sieve[i] != 0)               /*   is the next prime number          */
         for (j=i*i; j<=maxprime; j+=i)/*     so strike out all multiples     */
            sieve[j] = 0;              /*      of that prime starting with    */
      }                                /*       its square (lower multiples   */
                                       /*        were taken care of earlier)  */
   for (i=0; i<=maxprime; i++)         /* count the primes we found           */
      if (sieve[i] != 0)
         primecnt++;

   sprintf(msg, "to build the sieve of primes up to %d containing %d primes",
         maxprime, primecnt);
   logcputime(start_tics, msg);

   for (i=1; i<maxprime; i++)          /* now search the primes for           */
      {                                /*  pandigital numbers                 */
      if ( (sieve[i] != 0) && (ispandigital(i)) )
         {
         count++;
         max = i;                      /* the latest found will be the max    */
         }
      }
   sprintf(msg, "there are %d pandigital primes, and the largest is: %d", count, max);
   logcputime(start_tics, msg);
   exit(0);
   }

/* Test a number to see if it is pandigital, which means has n digits and
 * uses the digits 1,...,n each exactly once. As a result, it can use no
 * other digits.
 *
 * Return values:
 *
 * 1 if the input is pandigital in base 10
 * 0 otherwise
 */
int ispandigital(int n)
   {
   int  i, dig, digs[10], max=0;

   for (i=0; i<10; i++)          /* init the count array to all 0 */
      digs[i] = 0;

   while(n>0)
      {
      dig = n%10;                /* peel off each digit in turn   */
      digs[dig]++;               /*  count another time that one  */
      if (dig > max)             /*   was used, keeping track of  */
         max = dig;              /*    the largest digit found    */
      if (dig == 0)              /* if zero appears, the number   */
         return(0);              /*  is not pandigital            */
      n /= 10;
      }

   for (i=1; i<=max; i++)        /* if any digit was not used     */
      if (digs[i] != 1)          /*  exactly once, the number is  */
         return(0);              /*   not pandigital              */

   return(1);                    /* else it is                    */
   }

