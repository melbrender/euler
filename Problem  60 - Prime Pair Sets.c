/*
 * Problem 60: Prime Pair Sets
 *
 * The primes 3, 7, 109, and 673, are quite remarkable. By taking any two primes and concatenating
 * them in any order the result will always be prime. For example, taking 7 and 109, both 7109 and
 * 1097 are prime. The sum of these four primes, 792, represents the lowest sum for a set of four
 * primes with this property.
 *
 * Find the lowest sum for a set of five primes for which any two primes concatenate to produce
 * another prime.
 *
 * We consider all primes with four or fewer digits, excluding 2 since it can't be part of any
 * solution. Since the highest four-digit prime is 9997, wigh index is 1228 in the table of primes,
 * we use primes[1] through primes[1228] as possible candidates.
 *
 * To avoid repeatedly checking the same primes for concatenability, we loop though all pairs of
 * primes and build a relationship array which has 1 for every pair of concatenable primes, and 0
 * for all other pairs. We then do a five-way loop to search for a solution.
 *
 * Output:
 *
 * 2016-02-19 16:02:00 - CPU time used: 0 hrs 00 mins 17.735 secs
 *                         to build the list of primes up to 100000000 containing 5761455 primes
 * 2016-02-19 16:02:00 - Found 18176 mutually concatenable prime pairs under limit 10000
 * 2016-02-19 16:02:00 - CPU time used: 0 hrs 00 mins 17.895 secs
 *                         found a set: 8389 6733 5701 5197 13 with sum: 26033
 */

#include "eulersubs.h"

   extern int *primes;
   int are_concatenable(int a, int b);

int main()
   {
   int i, j, k, l, m, limit=100000000, limit2=1228;
   int start_tics, count=0;
   char msg[200];
   char concrel[1240][1240];                 /* concatenable relation table: entry at   */
                                             /* [i][j] and [j][i] is 1 if primes[i] and */
                                             /* primes[j] are concatenable; 0 otherwise */

   /* First, build a suitably large list of primes  */

   start_tics = clock();
   buildprimes(limit);                       /* construct list of primes               */

   /* Second, build relation table for all concatenable pairs of primes under 10000    */

   for(i=0; i<=limit2; i++)                  /* initialize the relation table          */
      for(j=0; j<1240; j++)                  /*  to all zeros                          */
         concrel[i][j] = 0;

   for(i=1; i<=limit2; i++)                  /* now go through the table. For each     */
      {                                      /*  pair of indices, set the value to 1   */
      for(j=1; j<i; j++)                     /*   at both [i][j] and [j][i] since      */
         {                                   /*    the relation is symmetric           */
         if (are_concatenable(primes[i], primes[j]) == 1)
            {
            concrel[i][j] = 1;
            concrel[j][i] = 1;
            count++;
            }
         }
      }

   sprintf(msg, "Found %d mutually concatenable prime pairs under limit %d", count, 10000);
   lognote(msg);

   /* Third, scan the relation table looking for sets of 5 mutually concatenable primes.  */
   /* we are looking for values of 5 indices i, j, k, l, and m such that the five primes  */
   /* primes[i], primes[j], primes[k], primes[l], and primes[m] are all concatenable.     */

   for(i=1; i<=limit2; i++)
      {
      for(j=1; j<i; j++)
         {
         if (concrel[i][j] == 0)
            continue;                     /* skip to next j if hopeless for this j  */
         for(k=1; k<j; k++)
            {
            if (concrel[i][k] == 0)
               continue;                  /* skip to next k if hopeless for this k */
            if (concrel[j][k] == 0)
               continue;                  /* ditto                                 */
            for(l=1; l<k; l++)
               {
               if (concrel[i][l] == 0)
                  continue;               /* skip to next l if hopeless for this l */
               if (concrel[j][l] == 0)
                  continue;               /* ditto                                  */
               if (concrel[k][l] == 0)
                  continue;               /* ditto                                  */
               for(m=1; m<l; m++)
                  {
                  if (    (concrel[i][m] == 1)
                       && (concrel[j][m] == 1)
                       && (concrel[k][m] == 1)
                       && (concrel[l][m] == 1) )
                     {
                     sprintf(msg, "found a set: %d %d %d %d %d with sum: %d",
                        primes[i], primes[j], primes[k], primes[l], primes[m],
                        primes[i]+primes[j]+primes[k]+primes[l]+primes[m]);
                     logcputime(start_tics, msg);
                     exit(0);
                     }
                  }
               }
            }
         }
      }

   sprintf(msg, "no set of 5 mutually concatenable primes found below 10000");
   logcputime(start_tics, msg);
   exit(0);
   }

/* are_concatenable(int a, int b)
 *
 * Determine if two primes can be concatenated in either order and return a new prime
 *
 * parameters:
 *
 * a and b        primes
 *
 * Return values
 *
 * 1 if ab and ba are both primes
 * 0 otherwise
 */

int are_concatenable(int a, int b)
   {
   int shifta, shiftb, val;

   shifta = 1;             /* for each one figure how many     */
   val = a;                /*  decimal digits it has           */
   while (val > 0)         /*   so we can shift appropriately  */
      {                    /*    when we concatenate           */
      shifta *= 10;
      val /= 10;
      }

   shiftb = 1;             /* for each one figure how many     */
   val = b;                /*  decimal digits it has           */
   while (val > 0)         /*   so we can shift appropriately  */
      {                    /*    when we concatenate           */
      shiftb *= 10;
      val /= 10;
      }

   if (isprime(a+shifta*b) == 0)
      return(0);           /* if ba is not prime, return zero  */

   if (isprime(b+shiftb*a) == 0)
      return(0);           /* if ab is not prime, return zero  */

   return(1);              /* else return one                  */
   }

