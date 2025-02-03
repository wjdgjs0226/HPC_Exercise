#include <iostream>
#include "insert.h"
#include "insertionsort.h"

int main()
{
    int num = 100;
    float randarray[num];
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
    return 0;
}