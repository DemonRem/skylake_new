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
	
	SendStream s(0);

	s.WriteString("ASDASD");

	print_packet((UINT8*)s.buff.buf, s.buff.len);
	print_packet_hex((UINT8*)s.buff.buf, s.buff.len);
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