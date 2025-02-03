#include "insert.h"
#include "insertionsort.h"

void insertionsort(float (&a)[], int l)
{
    for (int i = 0; i < l; ++i)
    {
        insert(a,i-1,a[i]);
    }
}