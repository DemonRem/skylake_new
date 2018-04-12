#ifndef MATH_STRUCTS_H
#define MATH_STRUCTS_H

#include "../Base/typeDefs.h"

struct Vector2 {
	float x;
	float y;
};

struct Vector3 {
	float x;
	float y;
	float z;
};

struct Vector4 {
	float x;
	float y;
	float z;
	float w;
};

struct PlayerPosition {
	Vector3 positon;
	INT16 heading;
};

#endif