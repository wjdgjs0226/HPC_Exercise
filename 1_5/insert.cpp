#include "insert.h"

void insert(float (&a)[], int p, float x)
{
    if (p == 0)
    {
    }
    else
    {
        if (x >= a[p])
        {
            a[p+1] = x;
        }
        else
        {
            for (int i = 0; i <p; ++i)
            {
                if(x <= a[i])
                {
                    for(int n = p+1; n > i; --n)
                    {
                        a[n] = a[n-1];
                    }
                    a[i] = x;
                    break;
                }
                else
                {
                    
                }
            }
        }
    }
}