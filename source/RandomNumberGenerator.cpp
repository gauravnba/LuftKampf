#include <stdlib.h>
#include "baseTypes.h"
#include "randomnumbergenerator.h"

float32_t getRangedRandom(float32_t min, float32_t max)
{
    int r = rand();

    float32_t r1 = (float32_t)r/(float32_t)RAND_MAX;

    r1 *= (max-min);

    r1 += min;

    return r1;
}
int getRangedRandom(int min, int max)
{
    int r = rand();

    float32_t r2 = (float32_t)r/(float32_t)RAND_MAX;

    r2 *= ((float32_t)max-(float32_t)min);
	int r1 = (int) r2;

    r1 += min;

    return r1;

}