#ifndef TYPEDEFS_H
#define TYPEDEFS_H

typedef signed char         INT8, *PINT8;
typedef signed short        INT16, FLAG16, *PINT16;
typedef signed int          INT32, INT, BOOL, *PINT32;
typedef signed long			LONG;
typedef signed __int64      INT64, *PINT64;
typedef unsigned char       UINT8, *PUINT8;
typedef unsigned short      UINT16, *PUINT16;
typedef unsigned int        UINT32, UINT, *PUINT32;
typedef unsigned long		ULONG, FLAG;
typedef unsigned __int64    UINT64, *PUINT64;

#define INT8_MIN			(-127i8 - 1)
#define INT16_MIN			(-32767i16 - 1)
#define INT32_MIN			(-2147483647i32 - 1)
#define INT64_MIN			(-9223372036854775807i64 - 1)
#define INT8_MAX			127i8
#define INT16_MAX			32767i16
#define INT32_MAX			2147483647i32
#define INT64_MAX			9223372036854775807i64
#define UINT8_MAX			0xffui8
#define UINT16_MAX			0xffffui16
#define UINT32_MAX			0xffffffffui32
#define UINT64_MAX			0xffffffffffffffffui64

typedef union _UID {
	struct {
		UINT32 hi;
		UINT32 lo;
	};
	UINT64 id;

	inline const bool operator==(_UID& id) const noexcept {
		return this->id == id.id;
	}
	inline const bool operator==(UINT64& id) const noexcept {
		return this->id == id;
	}

} UID;
typedef struct {
	UID id;
	UINT32 index;
} ResourceIndex;


#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FORCEINLINE
#define FORCEINLINE __forceinline
#endif

#define u32for(count) for(UINT32 i = 0; i < count; ++i)
#define u64for(count) for(UINT64 i = 0; i < count; ++i)
#define u32fort(count, t) for(UINT32  i##t = 0; i##t < count; ++ i##t)
#define u64fort(count, t) for(UINT64  i##t = 0; i##t < count; ++ i##t)
#define xfort(type, count, t) for(n  i##t = 0; i##t < count; ++ i##t)

#endif

