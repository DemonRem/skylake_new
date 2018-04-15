#include <iostream>
#include <atomic>

#include "../Base/typeDefs.h"

#include "../Base/win32.h"
#include "../Base/MemoryStreams.h"
#include "SimpleStackTest.h"
#include "DBOTest.h"
#include "RandomTest.h" 
#include "StatsTest.h" 

#include "../Base/Utils.h"

#include <chrono>


void ReadWriteTest() {
	
	MemoryStream m = MemoryStream(18);

	m.WriteUInt16(2);
	m.WriteUInt16(10);

	print_packet(m._raw, m._size);
	print_packet_hex(m._raw, m._size);
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