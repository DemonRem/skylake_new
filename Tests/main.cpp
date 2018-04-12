#include <iostream>
#include <atomic>

#include "../Base/typeDefs.h"

#include "SimpleStackTest.h"
#include "DBOTest.h"
#include "RandomTest.h" 
#include "StatsTest.h" 

#include <chrono>

int main()
{
	auto start = std::chrono::steady_clock::now();

	/*DBOTest();*/
	//RandomTest();
	//StatsTest();
	
	auto end = std::chrono::steady_clock::now();
	auto diff = end - start;
	std::cout << "DURATION [MS]: " << std::chrono::duration <double, std::micro>(diff).count() << "\n";
	system("pause");
	return 0;
}