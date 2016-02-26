/*
 * Common subroutines for the Project Euler problems
 */

#include "eulersubs.h"


/* Create lists of primes and of divisor counts
 *
 * We have two subroutines available here. One, buildprimes(), simply uses the
 * standard Sieve of Eratosthenes to compile prime/non-prime flags and then a
 * list of all primes up to a maximum desired value.
 *
 * The second, buildprimesdivs(), builds the same list of primes, flags, but also
 * builds an array containing the number of divisors of each integer up to the same
 * maximum. This is handy if the number of divisors will be needed, but takes more time.
 * This second algorithm is very fast for what it accomplishes. I first saw it in some
 * code due to Robert Gerbicz on the Euler threads.
 *
 * The two routines each use the same externals. Presumably only one routine will be
 * called in any program. Either one is a prerequisite for calling the isprime() function.
 */

int *divcnts=NULL;                  /* if buildprimes() is called, this will contain   */
                                    /*  2 for primes, 0 for composites                 */
                                    /* if buildprimesdivs is called, this will contain */
                                    /*  the number of divisors for each integer        */
int *primes=NULL;                   /* array of prime numbers                          */
int primecnt=0;                     /* number of primes in primes[]                    */
int maxval=0;                       /* highest value for which above tables are valid  */

/* Build Prime List: buildprimes()
 *
 * We build a sieve containing all integers not exceeding maxvalue. We initialize
 * it to zero for 0 and 1, and fill the rest of the array with 2's. We then zero
 * out the slots for each non-prime integer up to maxvalue.
 *
 * We next create a second external array, primes[], which lists the primes that
 * were found. Finally, we leave the count of primes found in a third external
 * location: primecnt.
 *
 * Callers can then either call isprime() to check if a given value is prime, or can
 * loop through the values in primes[] if they need to check properties of primes.
 *
 * Parameters:
 *
 * maxvalue    Maximum value of primes to be added to the array
 *
 * Outputs:
 *
 * primes[]    an external array containing all the primes up to maxvalue
 * primecnt    an external integer containing the count of primes in primes[]
 * divcnts[]   an external array with indices from 0 to maxvalue. It contains
 *                2 at each prime index and 0 everywhere else. It is suitable
 *                for use by the isprime() function.
 *
 * Return value:
 *
 * 1 if success
 *
 * if an error is encountered, we print an error note and exit
 */
int buildprimes(int maxprime)
   {
   int start_tics, i, j;
   char msg[200];

   start_tics = clock();               /* record CPU time now                 */
   if (primecnt != 0)                  /* if we've been here before           */
      {
      if (primes != NULL)              /* return memory for these arrays      */
         free(primes);
      if (divcnts != NULL)
         free(divcnts);
      primecnt=0;
      }

   divcnts = calloc(maxprime+1,        /* allocate space for the sieve        */
         sizeof(int));
   if (divcnts == NULL)
       err_exit("buildprimes() error: cannot allocate space for divcnts[]!", 1);
   maxval = maxprime;                  /* save highest value studied          */

   divcnts[0] = 0;                     /* 0 and 1 are not primes              */
   divcnts[1] = 0;

   for (i=2; i<=maxprime; i++)         /* fill the rest of the sieve          */
      divcnts[i] = 2;                  /*  with twos                          */

   for (i=0; i<=sqrt(maxprime); i++)   /* for each run of the loop, the first */
      {                                /*  value of i with divcnts[i] != 0    */
      if (divcnts[i] != 0)             /*   is the next prime number          */
         for (j=i*i; j<=maxprime; j+=i)/*     so strike out all multiples     */
            divcnts[j] = 0;            /*      of that prime starting with    */
      }                                /*       its square (lower multiples   */
                                       /*        were taken care of earlier)  */
   for (i=0; i<=maxprime; i++)         /*  count the primes we found          */
      if (divcnts[i] != 0)
         primecnt++;

   /*   Allocate space for the list of primes   */

   primes = calloc(primecnt, sizeof(int));
   if (primes == NULL)
      err_exit("buildprimes() error: cannot allocate space for primes[]!", 1);

   j = 0;                              /* initialize index into primes        */
   for (i=0; i<=maxprime; i++)         /* build array of primes               */
      if (divcnts[i] != 0)
         primes[j++] = i;

   sprintf(msg, "to build the list of primes up to %d containing %d primes",
         maxprime, primecnt);
   logcputime(start_tics, msg);

   return(1);
   }


/*  Build Primes and Divisor Count Lists: buildprimesdivs()
 *
 * We simultaneously build two lists: one of primes, and one of divisor counts.
 * The first list is only built up to the square root of the desired maximum
 * maximum prime; the second list goes the full distance.
 *
 * The second list is then used to build the full list of primes, since primes
 * are the numbers with exactly two divisors.
 *
 * Callers can then either call isprime() to check if a given value is prime, or
 * can loop through the values in primes[] if they need to check properties of primes.
 * They also have available in divcnts[] the number of divisors of every integer.
 *
 * Parameters:
 *
 * maxprime    Maximum value of primes to be added to the primes list
 *
 * Outputs:
 *
 * primes[]    an external array containing all the primes up to maxvalue
 * primecnt    an external integer containing the count of primes in primes[]
 * divcnts[]   an external array with indices from 0 to maxvalue. At each index
 *                from 1 to maxvalue it contains the number of divisors of that
 *                index. In particular, for primes it will contain 2.
 *
 * Return values:
 *
 * 1 if success
 *
 * if an error is encountered, we print an error note and then exit
 */
int buildprimesdivs(int maxprime)
   {
   int start_tics;
   char msg[200];
   int i, j, p, k, e, sq, *lowprimes;

   start_tics = clock();               /* record CPU time now                 */
   if (primecnt != 0)                  /* if we've been here before           */
      {
      if (primes != NULL)              /* return memory for these arrays      */
         free(primes);
      if (divcnts != NULL)
         free(divcnts);
      primecnt=0;
      }

   /* Phase One:
    *
    * We build two arrays:
    *
    * The first is lowprimes: this is a junior list of all primes up to the square
    * root of the maxvalue. We build it using the classic sieve of Eratosthenes.
    * Once the divcnts[] array is complete this will be discarded.
    *
    * The second is divcnts: this is a kind of reverse sieve of Eratosthenes; in this
    * phase it will contain:
    *
    *       zero for each prime
    *       the largest prime divisor for each composite
    *
    * The two lists are built together, each helping to build the other.
    */

   sq = sqrt(maxprime);
   lowprimes = calloc(sq+1,            /* allocate space for the small list   */
         sizeof(int));
   if (lowprimes == NULL)
      err_exit("buildprimesdivs() error: cannot allocate space for lowprimes[]!", 2);

   divcnts = calloc(maxprime+1,        /* allocate space for divcnts[]        */
         sizeof(int));
   if (divcnts == NULL)
      err_exit("buildprimesdivs() error: cannot allocate space for divcnts[]!", 2);
   maxval = maxprime;                  /* save highest value studied          */

   /* Build lowprimes[] and divcnts[] simultaneously                          */

   for(i=2; i<=sq; i++)                /* initialize lowprimes to 0 for 0,1   */
      lowprimes[i]=1;                  /*  and 1 for everything after         */
                                       /* divcnts is already all 0's          */
   for(i=2; i<=sq; i++)
      {                                /* At each run of the loop the         */
      if(lowprimes[i])                 /*  first slot containing a one        */
         {                             /*   will be the next prime.           */
         for(j=i*i; j<=sq; j+=i)       /* zero out non-primes by striking     */
            lowprimes[j]=0;            /*  out all higher multiples           */
         for(j=i*2; j<=maxprime; j+=i) /* leave highest prime dividing        */
            divcnts[j]=i;              /*  each integer in divcnts            */
         }
      }

   /* Phase two:
    *
    * Manipulate divcnts so that for each integer index it contains the number of
    * divisors of that integer. This is done recursively, with values for the lower
    * indices helping to calculate the values for the higher ones.
    */

   divcnts[1] = 1;                     /* initialize divcnts[1]               */
   for(i=2; i<=maxprime; i++)
      {
      if(divcnts[i]==0)                /* take care of the primes:            */
         {
         divcnts[i] = 2;               /*  they each have two divisors        */
         primecnt++;                   /*   count them as we go               */
         }
      else
         {                             /* for the composites, take the        */
         p=divcnts[i];                 /*  largest prime divisor, and count   */
         k=i;                          /*    the times it is a factor         */
         e=0;
         while(k%p==0)
            {
            k/=p;                      /* if i is p to a power times k        */
            e++;                       /*  where k is relatively prime to p   */
            }
         divcnts[i]=divcnts[k]*(e+1);  /* so we get divcnts[i] recursively    */
         }                             /*  using the multiplicative property  */
      }                                /*   since k < i and k and p are       */
                                       /*    relatively prime                 */
   /*
    * Phase 3:
    *
    * Discard the junior list of primes and build the full list of primes
    */

   free(lowprimes);                    /* discard the junior list             */

   primes = calloc(primecnt,           /* allocate space for the full list    */
         sizeof(int));
   if (primes == NULL)
      err_exit("buildprimesdivs() error: cannot allocate space for primes[]!", 2);

   j = 0;                              /* fill the primes[] table with        */
   for (i=0; i<=maxprime; i++)         /*  the primes we have found           */
      if (divcnts[i] == 2)
         primes[j++] = i;

   sprintf(msg, "to compile primes and divisor counts; found %d primes up to %d",
         primecnt, maxprime);
   logcputime(start_tics, msg);

   return(1);
   }

/* Check if a value is a prime: isprime()
 *
 * The caller should have already called either buildprimes() or buildprimesdivs
 * with the appropriate limit. We simply check the value in the divslist[] table, which
 * is 2 for primes and not 2 otherwise.
 *
 * Return value:
 *
 *   1 if the value is a prime
 *   0 if the value is not a prime
 *
 *   If we are called with a bad value for the parameter, we exit with an explanation.
 */
int isprime(int val)
   {
   char msg[200];

   if (val <= 0)
      {
      sprintf(msg, "isprime() called with inappropriate value: %d", val);
      err_exit(msg, 2);
      }
   if (val > maxval)
      {
      sprintf(msg, "isprime() error: called for %d but primes built only up to %d", val, maxval);
      err_exit(msg, 2);
      }

   if (divcnts[val] == 2)
      return(1);
   else
      return(0);
   }

/* Test a number to see if it is a palindrome in a given base
 *
 * Form the reverse-reading integer by repeatedly shearing off the lowest
 * order digit and forming a new number with these digits added on the right.
 * If the new number equals the old number, it was a palindrome.
 *
 * Return values:
 *
 * 1 if the input is a palindrome in base 10
 * 0 otherwise
 */
int ispalind(int n, int base)
   {
   int nn, sum=0, lodig;

   nn = n;                    /* save original value        */
   while (nn > 0)
      {
      lodig = nn%base;        /* isolate low digit          */
      sum = base*sum+lodig;   /* build new integer with     */
      nn /= base;             /*  these digits in           */
      }                       /*   reverse order            */

   if (n == sum)              /* if the result is the       */
      return(1);              /*  same, it's a palindrome   */
   else
      return(0);              /* else it's not              */
   }
/* Count combinations: comb()
 *
 * Calculate the number of combinations of m things taken n at a time.
 *
 * Parameters:
 *    m  number of objects
 *    n  number to be selected
 *
 * Return value:
 *
 *    the number of combinations
 *
 * If we experience an error, we display an error note and exit the program.
 */
unsigned int comb(unsigned int m, unsigned int n)
   {
   /* Calculate the number of combinations of m things taken n at a time
    *
    *                       m!            m(m-1)(m-2)...(m-n+1)
    * We use C(m, n)  =  --------    =    ---------------------
    *                    n! (m-n)!                  n!
    *
    * and the fact that
    *
    * for 0 <= n < = m we always have  C(m, n)    =  C(m, m-n)
    *
    * Return value: C(m, n)
    *
    * If called with a value too large, we exit with an error.
    */
#define MAXSIZE_COMB 120

   unsigned int i, j, nn, l, k, p, found, cnt, res=1;
   char msg[200];
   unsigned int nums[MAXSIZE_COMB];
   unsigned int dens[MAXSIZE_COMB];
   int primes[]={2,3,5,7,11,13,17,19,23,29,  /* should contain all primes  */
                 31,37,41,43,47,53,59,61,    /*  less than MAXSIZE_COMB    */
                 67,71,73,79,83,89,93,97,
                 101,103,107,109,113};

   nn = n;                        /* save a copy of n                     */

   if ( (n > m) || (m < 0) || (n < 0) )
      {
      sprintf(msg, "Error calling comb(m,n) with parameters: %d and %d", m, nn);
      err_exit(msg, 2);
      }

   if ( (m > MAXSIZE_COMB) || (n > MAXSIZE_COMB) )
      {
      sprintf(msg, "Error calling comb(m,n) with too large parameters: %d and %d", m, nn);
      err_exit(msg, 2);
      }

   if (n >= m/2)                  /* if n is more than half,               */
      n = m-n;                    /*  use the complement                   */

   if (m == 0)                    /* C(0, 0) = 1                           */
      res = 1;
   else if (m == 1)               /* C(1, 0) = C(1, 1) = 1                 */
      res = 1;
   else if (n == 0)               /* C(m, 0) is one                        */
      res = 1;
   else if (n == 1)               /* C(m, 1) is m                          */
      res = m;
   else
      {
      /*
       * We may now assume m and n are at least 2
       * Create list of the factors in Numerator and Denominator
       */

      cnt = n;                    /* number of factors is n                */

      for (i=0; i<cnt; i++)       /* set all the factors of numerator      */
         nums[i] = m-i;

      for (i=0; i<cnt; i++)       /* set all the factors of denominator    */
         dens[i] = i+1;

      /*
       * For each of the primes, cast off any duplicate factors
       */

      for (i=0; i<sizeof(primes)/sizeof(primes[0]); )
         {                        /* loop through our list of primes       */
         p=primes[i];
         found=0;

         for (j=0; j<cnt; j++)    /* for all factors in num and den        */
            {
            for (k=0; k<cnt; k++)
               {
               if ( (nums[j]%p == 0) && (dens[k]%p == 0) )
                  {
                  nums[j]/=p;     /* if we can reduce by that prime        */
                  dens[k]/=p;     /*   do so                               */
                  found = 1;
                  }
               }
            }
         if (found == 0)          /* if no more reductions by that prime   */
            i++;                  /*  advance to the next prime in list    */
         }

      for (i=0; i<cnt; i++)
         if (dens[i] != 1)        /* all denominator fctrs should now be 1 */
            {
            printf("\t\t\tError calculating comb with parameters %d and %d\n",
                          m, nn);
            for (l=0; l<cnt; l++)
               printf("\t\t\tNumerators: %d  ", nums[l]);
            printf("\n");
            for (l=0; l<cnt;l++)
               printf("\t\t\tDenominators: %d  ", dens[l]);
            err_exit("Error calculating comb with parameters %d and %d\n", 1);
            }

      for (i=0; i<cnt; i++)
         res *= nums[i];          /* gather all factors left               */
      }

   return(res);
   }

/* Determine if two or more integers involve the same digits permuted
 *
 * arepermuted() will check whether every one of the integers in its argument list
 * involve the same digits merely permuted. If so it will return 1. Otherwise it will
 * return 0.
 *
 * To be clear, we will return 1 only if each digit is used the same number of times in every
 * argument.
 *
 * Parameters:
 *
 * count    will specify how many integers to be checked appear in the argument list
 * val1,    integers to be
 * val2,     checked to see if they
 *  ...       involve the same digits permuted
 */
int arepermuted(int count, ...)
   {
   va_list ap;                               /* points to optional arguments in turn   */
   int i, j, n, tmp, val, digit;
   int vals[8];                              /* array of values to check               */
   short int *digsused[8][10];               /* two-dimensional array of digit counts  */

   va_start(ap, count);                      /* start the variable list going          */
   if (count > 8)
      err_exit("arepermuted() error: called with too many arguments", 2);
   if (count < 2)
      err_exit("arepermuted() error: called with too few arguments", 2);

   tmp = count;
   j = 0;
   while(tmp > 0)
      {
      vals[j++] = va_arg(ap, int);           /* fetch next parameter                   */
      tmp--;
      }
   va_end(ap);                               /* clean up                               */

   for (i=0; i<count; i++)
      for (n=0; n<10; n++)
         digsused[i][n] = 0;                 /* clear digits count fields              */

   for (i=0; i<count; i++)
      {
      val = vals[i];                         /* for each parameter                     */
      while (val > 0)                        /* and record the digits used             */
         {
         digit = val%10;
         digsused[i][digit]++;               /* count a digit used                     */
         val /= 10;                          /* shift to the right                     */
         }
      }

   for (i=1; i<count; i++)                   /* for all values past the first          */
      for (n=0; n<10; n++)                   /*  and each possible digit, if there     */
         {                                   /*   is a discrepancy from the first then */
         if (digsused[0][n] != digsused[i][n]) /*  our answer is no                    */
            return(0);
         }
   return(1);                                /* if we got here, our answer is yes      */
   }


/* Exit with an error note: err_exit()
 *
 * Display the caller's error note with a timestamp, and exit with
 * the caller's specified exit code.
 *
 */
void err_exit(char *msg, int code)
   {
   lognote(msg);
   exit(code);
   }

/* Report CPU time used: logcputime()
 *
 * The caller should snap the CPU time at the start of their process using clock().
 * When the process is complete the caller should supply us with the original value
 * of clock() and a message to be displayed.
 *
 * We will compute the CPU time used and display it along with the caller's message.
 * The output will require two lines and will terminate with the second linefeed.
 *
 * Format:
 *
 * YYYY-MM-DD hh:mm:ss - CPU time used: h hrs mm mins ss.ttt secs
 *                         'msg'
 *
 * Return value: 0 for success.
 */

int logcputime(int start_tics, char *msg)
   {
   int secs, thsecs, mins=0, hrs=0, tics, end_tics;
   char newmsg[250];

   end_tics = clock();              /* record CPU time now           */
   tics = end_tics - start_tics;    /* figure CPU time used          */

   thsecs = tics%CLOCKS_PER_SEC;    /* figure thousands of a sec     */
   secs = tics/CLOCKS_PER_SEC;      /* figure seconds                */

   if (secs > 59)                   /* if more than just seconds     */
      {
      mins = secs/60;               /* figure minutes                */
      secs %= 60;                   /*  and leftover seconds         */
      }

   if (mins > 59)                   /* if more than just minutes     */
      {
      hrs = mins/60;                /* figure hours                  */
      mins %= 60;                   /*  and lefover minutes          */
      }

   sprintf(newmsg, "CPU time used: %d hrs %02d mins %02d.%03d secs\n\t\t\t%s",
         hrs, mins, secs, thsecs, msg);

   lognote(newmsg);
   return(0);
   }

/* Print a timestamped log note: lognote()
 *
 * Display a the caller's note with a current timestamp, followed by a linefeed.
 *
 * Format:
 *
 * YYYY-MM-D hh:mm:ss - 'msg'
 *
 * Return value: 0 for success.
 */

int lognote(char *msg)
   {
   struct tm *tim;
   time_t curtim;

   curtim = time(NULL);
   tim = localtime(&curtim);
   printf("%d-%02d-%02d %02d:%02d:%02d - %s\n",
         1900+tim->tm_year,
         1+tim->tm_mon,
         tim->tm_mday,
         tim->tm_hour,
         tim->tm_min,
         tim->tm_sec,
         msg);
   fflush(stdout);
   return(0);
   }
