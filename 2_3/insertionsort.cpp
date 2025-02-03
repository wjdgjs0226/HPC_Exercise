#include "insert.h"
#include "insertionsort.h"

void insertionsort(float a[], int l, bool order)
{
    for (int i = 0; i < l; ++i)
    {
        insert(a, i, a[i], order);
    }
}