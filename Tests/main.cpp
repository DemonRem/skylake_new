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

#include "../DataLayer/ItemsDBO.h"
#include "../Models/Item.h"
#include "../Models/Passivity.h"

#include <chrono>


void ReadWriteTest() {
	MemoryStream m = MemoryStream(18);

	m.WriteUInt16(2);
	m.WriteUInt16(10);

	print_packet(m._raw, m._size);
	print_packet_hex(m._raw, m._size);
	return;
}

INT32 ItemsTests() {
	MemoryStream m = MemoryStream();
	Item i;
	Passivity p;
	p.index = 321;
	p.id = 123;

	i.stackCount = 1;

	i.crystals[0] = 1;
	i.crystals[1] = 2;
	i.crystals[2] = 3;
	i.crystals[3] = 4;

	i.binderDBId = 44;
	i.crafterDBId = 55;
	i.itemLevel = 2;
	i.flags = 575;
	i.masterworkRate = 24.556f;
	i.passivities[0] = &p;

	SerializeItem(&i, &m);
	print_packet_hex(m._raw, m._size);
	Item j;
	m._pos = 0;
	INT32 result = DeserializeItem(&j, &m);

	return result;
}

int main()
{
	auto start = std::chrono::steady_clock::now();

	/*DBOTest();*/
	//RandomTest();
	//StatsTest();
	//ReadWriteTest();
	INT32 result = ItemsTests();
	if (result) {
		printf("Test FAILED!! result = %d\n", result);
	}
	else {
		printf("Test SUCCESSS\n");
	}

	auto end = std::chrono::steady_clock::now();
	auto diff = end - start;
	std::cout << "DURATION [MS]: " << std::chrono::duration <double, std::micro>(diff).count() << "\n";
	system("pause");
	return 0;
}