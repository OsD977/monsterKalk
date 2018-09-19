#include "funzioni.h"

int randomBetween(int min, int max){
    if (min>max)
        throw "minimo maggiore del massimo";
    srand(time(NULL));
    int ris = rand()%(max-min + 1) + min;
    return ris;
}


int checkBounds(int min, int max, int val){
    if (min>max)
        throw "minimo maggiore del massimo";
    if((val<=max)&&(val>=min))
        return val;
    if(val<min)
        return min;
    else
        return max;
}
