/*
 * eulersubs.h
 *
 *  Header files and function declarations for the euler files.
 */

#include "stdio.h"
#include "errno.h"
#include "ctype.h"
#include "string.h"
#include "stdlib.h"
#include "time.h"
#include "math.h"
#include "stdarg.h"

#ifndef EULERSUBS_H_
#define EULERSUBS_H_


int buildprimes(int maxvalue);                        /* build list of primes for isprime() routine   */
int buildprimesdivs(int maxvalue);                    /* build primes list, divisor counts list       */
int isprime(int val);                                 /* tests primality; call one of above first     */
int ispalind(int n, int base);                        /* test if a number is a palindrome in a base   */
unsigned int comb(unsigned int m, unsigned int n);    /* calculates combinations(m,n)                 */
int arepermuted(int count, ...);                      /* determine if 2 or more integers have same    */
                                                      /*  digits but possibly permuted                */
void err_exit(char *msg, int code);                   /* display timestamp, a message, exit program   */
int logcputime(int start_tics, char *msg);            /* display timestamp, cpu time used, and a msg  */
int lognote(char *msg);                               /* display timestamp and a message              */


#endif /* EULERSUBS_H_ */
