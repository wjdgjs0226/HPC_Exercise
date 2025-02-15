#include <iostream>
#include "insert.h"
#include "insertionsort.h"

int main()
{
    int num = 10;
    float* randarray = new float[num];
    for (int i=0; i<num; ++i)
    {
        randarray[i] = float(rand()%1000);
        std::cout << randarray[i] << std::endl;
    }
    std::cout << "" << std::endl;
    insertionsort(randarray,num);
    
    for (int i=0; i<num; ++i)
    {
        std::cout << randarray[i] << std::endl;
    }

    delete[] randarray;
    return 0;
}