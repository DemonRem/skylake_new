#include "RandomTest.h"

#include <time.h>
#include <stdio.h>

#include "../Base/Random.h"

int RandomTest()
{
	//srandom(time(0));

	for (size_t i = 0; i < 100; i++)
	{
		int a = random_range(0, 100);
		//printf("[%d]", a);
	}

	return true;
}
