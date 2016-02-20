/*
 * Problem 18: Largest Path Sum I
 *
 * Output:
 *
 * 2016-02-11 15:44:28 - CPU time used: 0 hrs 00 mins 00.000 secs
 *        Max path total is: 1074
 */

#include "eulersubs.h"

int main(int argc, char **argv)
   {
   int values[15][15] =
        {75,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
         95, 64,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
         17, 47, 82,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
         18, 35, 87, 10,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
         20,  4, 82, 47, 65,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
         19,  1, 23, 75,  3, 34,  0,  0,  0,  0,  0,  0,  0,  0,  0,
         88,  2, 77, 73,  7, 63, 67,  0,  0,  0,  0,  0,  0,  0,  0,
         99, 65,  4, 28,  6, 16, 70, 92,  0,  0,  0,  0,  0,  0,  0,
         41, 41, 26, 56, 83, 40, 80, 70, 33,  0,  0,  0,  0,  0,  0,
         41, 48, 72, 33, 47, 32, 37, 16, 94, 29,  0,  0,  0,  0,  0,
         53, 71, 44, 65, 25, 43, 91, 52, 97, 51, 14,  0,  0,  0,  0,
         70, 11, 33, 28, 77, 73, 17, 78, 39, 68, 17, 57,  0,  0,  0,
         91, 71, 52, 38, 17, 14, 91, 43, 58, 50, 27, 29, 48,  0,  0,
         63, 66,  4, 68, 89, 53, 67, 30, 73, 16, 69, 87, 40, 31,  0,
         04, 62, 98, 27, 23,  9, 70, 98, 73, 93, 38, 53, 60,  4, 23};

   int i,j, start_tics;
   char msg[200];

   start_tics = clock();

   /* Loop through the array from bottom up; add to each item the larger of the two below */
   /* In effect we collapse the optimal path, pushing up the best choice row by row until */
   /* the top item has the optimal sum.                                                   */

   for (i=13; i>=0; i--)
      {
     for (j=0; j<=i; j++)
        {
        if (values[i+1][j] > values[i+1][j+1])
          values[i][j] += values[i+1][j];
        else
           values[i][j] += values[i+1][j+1];
        }
      }
   sprintf(msg, "Max path total is: %d\n", values[0][0]);
   logcputime(start_tics, msg);
   exit(0);
   }

