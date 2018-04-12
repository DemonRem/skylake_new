#include "StatsTest.h"

#include "../Models/Stats.h"

PlayerStats ps, pr;

UINT32 StatsTest()
{
	ps.attack = 10;
	ps.defense  = 20;
	ps.damageAggro = 12.45f;
	ps.balance_factor = 44;

	ExchangeStats(&ps, &pr);


	return 0;
}
