#include "helpers.h"

int get_rand(int min, int max)
{
    return min + rand() % (max - min + 1);
}