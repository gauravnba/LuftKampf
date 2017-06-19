#include <stdlib.h>
#include <time.h>
#include "baseTypes.h"
#include "randomnumbergenerator.h"

void seedRandomNumberGenerator()
{
	srand((unsigned)time(NULL));
}

float32_t getRangedRandom(float32_t min, float32_t max)
{
    int32_t r = rand();

    float32_t r1 = (float32_t)r/(float32_t)RAND_MAX;

    r1 *= (max-min);

    r1 += min;

    return r1;
}
int32_t getRangedRandom(int32_t min, int32_t max)
{
    int32_t r = rand();

    float32_t r2 = (float32_t)r/(float32_t)RAND_MAX;

    r2 *= ((float32_t)max-(float32_t)min);
	int32_t r1 = (int32_t) r2;

    r1 += min;

    return r1;

}