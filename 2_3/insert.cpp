#include "insert.h"

void insert(float a[], int p, float x, bool order)
{
    if (order) {
        // Move items up array until the right place is reached
        while (p > 0 && x > a[p-1]) {
            a[p] = a[p-1];
            p--;
        }
    }
    else {
        // Move items up array until the right place is reached
        while (p > 0 && x < a[p-1]) {
            a[p] = a[p-1];
            p--;
        }
    }
    // Put 'val' in the right place
    a[p] = x;
}