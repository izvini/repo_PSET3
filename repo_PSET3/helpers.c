/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include <stdio.h>
#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    if (n > 0)
    {
        int f = 0;
        int l = n ;
        int m = (int)(f + l)/2;
    
        while(f <= l)
        {
            m = (int)(f + l)/2;
            if(values[m] == value)
            {
                return true;
            }
            else if(value < values[m])
            {
                l = m - 1;
            }
            else
            {
                f = m + 1;
            }
        }
    }
    return false;
}
/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    int z = n;
    for(int i = 0 ; i < n ; i++)
    {
        for(int j = 0  ; j < z ; j++)
        {
            if(values[i] > values[i + 1])
            {
                int t = values[i + 1];
                values[i + 1] = values[i];
                values[i] = t;
            }
           
        }
        z = z - 1;
    }
   return;
}