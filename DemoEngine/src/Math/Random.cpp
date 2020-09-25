#include "Random.h"
#include <iostream>

float Random::randFloatInRange(int min, int max)
{
    return ((max - min) * ((float)rand() / RAND_MAX)) + min;
}

int Random::randIntInRange(int min, int max)
{
    return min + (std::rand() % (max - min + 1));
}

bool Random::randBool()
{
    return (1 + (std::rand() % (2 - 1 + 1))) % 2 == 0 ? true : false;
}
