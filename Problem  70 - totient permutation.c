/*
 * Problem 70: Totient Permutation
 *
 * Euler's Totient function, phi(n) [sometimes called the phi function], is used to determine the
 * number of positive numbers less than or equal to n which are relatively prime to n. For example,
 * as 1, 2, 4, 5, 7, and 8, are all less than nine and relatively prime to nine, phi(9)=6. The number
 * 1 is considered to be relatively prime to every positive number, so phi(1)=1.
 *
 * Interestingly, phi(87109)=79180, and it can be seen that 87109 is a permutation of 79180.
 *
 * Find the value of n, 1 < n < 10,000,000 for which phi(n) is a permutation of n and the ratio
 * n/phi(n) produces a minimum.
 *
 * Output:
 *
 * 2016-02-20 14:40:04 - There were 2068 integers for which the phi function had the same digits permuted
 * 2016-02-20 14:40:04 - CPU time used: 0 hrs 00 mins 08.141 secs
 *                         Minimum ratio was 1.000709 with integer 8319823 and tots 8313928
 */

#include "eulersubs.h"

int phi_prime_power(int p, int k);

int main()
   {
   int i, j, k, e, p, sq, mini, limit=10000000;
   int start_tics, count=0, *tots, *lowprimes;
   double num, den, ratio, min=1000000.0;
   char msg[200];

   /*
    * First, build a list of the values of the totient function. We use the same
    * trick we stole from Robert Gerbicz that we used to build the number of divisors
    * of each integer.
    */

   start_tics = clock();                     /* record the start time               */
   sq = sqrt(limit);
   lowprimes = calloc(sq+1, sizeof(int));    /* allocate space for the small list   */
   if (lowprimes == NULL)
      err_exit("error: cannot allocate space for lowprimes[]!", 2);

   tots = calloc(limit+1, sizeof(int));      /* allocate space for tots[]           */
   if (tots == NULL)
      err_exit("error: cannot allocate space for tots[]!", 2);

   /* Build lowprimes[] and tots[] simultaneously                                   */

   for(i=2; i<=sq; i++)                      /* initialize lowprimes to 0 for 0,1   */
      lowprimes[i]=1;                        /*  and 1 for everything after         */
                                             /* tots is already all 0's             */
   for(i=2; i<=sq; i++)
      {                                      /* at each run of the loop the         */
      if(lowprimes[i])                       /*  first slot containing a one        */
         {                                   /*   will be the next prime.           */
         for(j=i*i; j<=sq; j+=i)             /* zero out non-primes by striking     */
            lowprimes[j]=0;                  /*  out all higher multiples           */
         for(j=i*2; j<=limit; j+=i)          /* leave highest prime dividing        */
            tots[j]=i;                       /*  each integer in tots               */
         }
      }

   /*
    * Manipulate tots so that for each integer index it contains the value of
    * phi(index). This is done recursively, with values for the lower indices helping
    * to calculate the values for the higher ones.
    */

   tots[1] = 1;                               /* initialize tots[1]                  */
   for(i=2; i<=limit; i++)
      {
      if(tots[i]==0)                         /* take care of the primes:            */
         tots[i] = i-1;                      /*  for a prime p, phi(p) = p-1        */

      else
         {                                   /* for the composites, take the        */
         p=tots[i];                          /*  largest prime divisor, and count   */
         k=i;                                /*    the times it is a factor         */
         e=0;
         while(k%p==0)
            {
            k/=p;                            /* if i is p to a power times k        */
            e++;                             /*  where k is relatively prime to p   */
            }
         tots[i]=tots[k]*phi_prime_power(p,e);
                                             /* so we get tots[i] recursively       */
         }                                   /*  using the multiplicative property  */
      }                                      /*   since k < i and k and p are       */
                                             /*    relatively prime                 */

   free(lowprimes);                          /* discard the junior list             */

   for (i=2; i<limit; i++)                   /* search for integers where phi(n)    */
                                             /* consists of digits of n permuted    */
      {
      if (arepermuted(2, i, tots[i]) == 1)   /* if they are permutations            */
         {                                   /*  we've got a canditate so           */
         count++;                            /*   check the ratio of i/phi(i)       */
         num = i;
         den = tots[i];
         ratio= num/den;
         if (ratio < min)
            {
            min = ratio;
            mini = i;
            }
         }
      }
   sprintf(msg, "There were %d integers for which the phi function had the same digits permuted", count);
   lognote(msg);
   sprintf(msg, "Minimum ratio was %f with integer %d and tots %d", min, mini, tots[mini]);
   logcputime(start_tics, msg);
   exit(0);
   }

/* phi_prime_power(int p, int k)
 *
 *              k
 * Determine phi(p )
 *
 * parameters:
 *
 * p prime
 * k power
 *
 * Return values
 *
 *  k     k-1         k-1
 * p  -  p        or p   (p - 1)
 */

int phi_prime_power(int p, int k)
   {
   int val;

   val = 1;
   while (k>1)
      {
      val *= p;
      k--;
      }
   return(val*(p-1));
   }

