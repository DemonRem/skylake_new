#ifndef __RANDOM_H__
#define __RANDOM_H__

void				srandom(unsigned long seed);
unsigned long		random();
float				frandom(float flLow, float flHigh);
long				random_range(long from, long to);

#endif