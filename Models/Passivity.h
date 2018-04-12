#ifndef PASSIVITYTEMEPLATE_H
#define PASSIVITYTEMEPLATE_H

#include "../Base/typeDefs.h"
#include "../Base/Enums/PlayerEnum.h"
#include "../Base/Enums/NpcEnums.h"
#include "../Base/Enums/PassivityEnums.h"

#define PASSIVITY_CONDITION_CATEGORY_MAX 8

struct Passivity {
	UID id;

	float	value;
	float	probability;
	float	conditionValue;

	UINT32 type;
	UINT32 tickInterval;
	UINT32 kind;
	UINT32 method;
	UINT32 condition;
	UINT32 prevPassivityId;
	UINT32 abnormalityKind;
	UINT32 abnormalityCategory;
	UINT32 passivityChangeId;
	UINT32 passivityChangeTime;
	UINT32 mySkillCategory;

	EMobSize mobSize;
	EPassivityFlags flags;

	UINT16 conditionCategoriesCount;
	UINT32 conditionCategories[PASSIVITY_CONDITION_CATEGORY_MAX];

	const inline BOOL HasFlag(const EPassivityFlags flag) const noexcept {
		return flags & flag;
	}
	const inline BOOL HasFlags(const FLAG flag) const noexcept {
		return flags & flag;
	}
};

#endif