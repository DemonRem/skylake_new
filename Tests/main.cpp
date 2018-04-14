#include <iostream>
#include <atomic>

#include "../Base/typeDefs.h"

#include "SimpleStackTest.h"
#include "DBOTest.h"
#include "RandomTest.h" 
#include "StatsTest.h" 

#include "../Base/Utils.h"

#include <chrono>


void ReadWriteTest() {
	
	UINT8 data[15];

	w_64(data, 23);

	print_packet_hex(data, 15);

	INT64 a = r_64(data);

	printf("%d\n", a);
	return;
}

int main()
{
	auto start = std::chrono::steady_clock::now();

	/*DBOTest();*/
	//RandomTest();
	//StatsTest();
	ReadWriteTest();
	
	auto end = std::chrono::steady_clock::now();
	auto diff = end - start;
	std::cout << "DURATION [MS]: " << std::chrono::duration <double, std::micro>(diff).count() << "\n";
	system("pause");
	return 0;
}