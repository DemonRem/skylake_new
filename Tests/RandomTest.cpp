#include "RandomTest.h"

#include <time.h>
#include <stdio.h>

#include "../Base/Random.h"

int RandomTest()
{
	srandom((unsigned long)time(0));

	for (size_t i = 0; i < 100; i++)
	{
		int a = random_range(0, 100);
		if (a == 0 || a == 100) {
			printf("[%d]", a);
		}
	}

	printf("\n\n");

	return true;
}
