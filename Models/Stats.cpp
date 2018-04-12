#include "Stats.h"

#include <intrin.h>

BOOL ExchangeStats(GeneralPlayerStats * src, GeneralPlayerStats * dest)
{
	LONG *blocks = (LONG *)src;
	LONG *destBlocks = (LONG *)dest;
	LONG blocksCount = sizeof(GeneralPlayerStats) / sizeof(LONG);

	for (LONG i = 0; i < blocksCount; i++)
	{
		LONG oldVal = _InterlockedExchange(&destBlocks[i], blocks[i]);
	}

	return 0;
}

BOOL ExchangeStats(PlayerStats * src, PlayerStats * dest)
{
	LONG *blocks = (LONG *)src;
	LONG *destBlocks = (LONG *)dest;
	LONG blocksCount = sizeof(PlayerStats) / sizeof(LONG);

	for (LONG i = 0; i < blocksCount; i++)
	{
		LONG oldVal = _InterlockedExchange(&destBlocks[i], blocks[i]);
	}

	return 0;
}
