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
bool search(int value, int values[], int z)
{
    if (z > 0)
    {
        int f = 0;
        int l = z ;
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
