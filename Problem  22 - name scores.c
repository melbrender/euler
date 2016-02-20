/*
 * Problem 22: Name Scores
 *
 * Using names.txt, a 46K text file containing over five-thousand first names, begin by sorting it
 * into alphabetical order. Then working out the alphabetical value for each name, multiply this value
 * by its alphabetical position in the list to obtain a name score.
 *
 * For example, when the list is sorted into alphabetical order, COLIN, which is worth
 * 3 + 15 + 12 + 9 + 14 = 53, is the 938th name in the list. So, COLIN would obtain a score
 * of 938 × 53 = 49714.
 *
 * What is the total of all the name scores in the file?
 *
 * Output:
 *
 * 2016-02-20 16:15:19 - Characters read: 46447
 * 2016-02-20 16:15:19 - Found 5163 names
 * 2016-02-20 16:15:19 - CPU time used: 0 hrs 00 mins 00.440 secs
 *                         to find the total namescore of: 871198282
 */
#include "eulersubs.h"

int alphascore(char *name);

int main(int argc, char **argv)
   {
   int start_tics, i, j, namecnt, namescore, total=0;
   char *cp, *tmp,  msg[200], data[50000], *names[6000];
   FILE *fp=NULL;
   char filename[]="C:\\Documents and Settings\\Mel\\My Documents\\cworkspace\\euler\\src\\p022_names.txt";

   start_tics = clock();
   fp = fopen(filename, "r");
   if (fp == NULL)
      {
      perror("Error opening file");
      exit(0);
      }

   cp = fgets(data, 50000, fp);              /* read the only line                  */
   if (cp == NULL)
      {
      perror("Error reading file");
      exit(0);
      }

   sprintf(msg, "Characters read: %d", strlen(data));
   lognote(msg);

   /* Find pointers to the start of each name, and terminate each name in the data  */

   cp++;                                     /* advance past first quote            */
   namecnt = 0;
   names[namecnt++] = cp;

   while(1)
      {
      while (isalpha(*cp))                   /* advance through the next name       */
         cp++;
      *cp++ = 0;                             /* place terminator                    */
      if (*cp == 0)                          /* if we've reached the end of the     */
         break;                              /*  data, quit now                     */
      cp += 2;                               /* else advance past comma and next    */
      names[namecnt++] = cp;                 /*  quote; save pointer to next name   */
      }

   sprintf(msg, "Found %d names", namecnt);
   lognote(msg);

   for (i=0; i<namecnt-1; i++)               /* bubble sort is ok for small         */
      for (j=0; j<namecnt-i-1; j++)          /*  number of names                    */
         if (strcmp(names[j],names[j+1])>0)
            {
            tmp = names[j];
            names[j] = names[j+1];
            names[j+1] = tmp;
            }

   for (i=0; i<namecnt; i++)                 /* for each name                       */
      {                                      /*  figure the score                   */
      namescore = (i+1)*alphascore(names[i]);
      total += namescore;                    /* and accumulate the total            */
      }

   sprintf(msg, "to find the total namescore of: %d", total);
   logcputime(start_tics, msg);
   exit(0);
   }

/* Figure the alphabetic score of a name: alphascore()
 *
 * Return value: the sum of the letter values in the name where
 * A=1, B=2, etc.
 */
int alphascore(char *name)
   {
   int i, val=0;

   for (i=0; i<strlen(name); i++)
      val += name[i] - 'A' + 1;

   return(val);
   }

