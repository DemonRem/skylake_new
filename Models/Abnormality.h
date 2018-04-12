#ifndef ABNORMALITYTEMPLATE_H
#define ABNORMALITYTEMPLATE_H

#include <vector>
#include "../Base/typeDefs.h"
#include "../Base/Enums/AbnormalityEnums.h" 

#define ABNORMALITY_MAX_EFFECTS 10
#define ABNORMALITY_MAX_SKILL_CATEGORY 3

struct AbnormalityEffect {
	AbnormalityEffectType	type;				//max 336
	UINT16					tickInterval;		//max 299
	UINT32					method;				//max 9160005
	float					value;

	//BOOL					isEnemyCheck;       //only 3 (2 results)
	//INT32	overlayEffectId;
	//INT32	attackEffectId;
	//INT32	damageEffectId;
	//INT32	appearEffectId;
	//INT32	dissappearEffectId;
};

struct Abnormality {
	UID					id;
	UINT64				time;

	AbnormalityFlags	flags;
	UINT16				kind;
	UINT16				level;
	UINT16				property;
	UINT16				priority;

	INT64				bySkillCategory[ABNORMALITY_MAX_SKILL_CATEGORY];
	AbnormalityEffect*	effects[ABNORMALITY_MAX_EFFECTS];

	//std::string
	//	toolTip,
	//	name;

	const inline BOOL HasFlags(UINT16 flag) const noexcept {
		return flags & flag;
	}
	const inline BOOL HasFlag(AbnormalityFlags flag) const noexcept {
		return flags & flag;
	}
	const inline UINT32 GetEffectCount() const noexcept {
		register UINT32 count;

		for (UINT32 i = 0; i < ABNORMALITY_MAX_EFFECTS; i++) {
			if (effects[i]) {
				count++;
			}
		}

		return count;
	}
	const inline UINT32 GetSkyllCategoryCount() const noexcept {
		register UINT32 count;

		for (UINT32 i = 0; i < ABNORMALITY_MAX_SKILL_CATEGORY; i++) {
			if (bySkillCategory[i] >= 0) {
				count++;
			}
		}

		return count;
	}

	Abnormality();
	~Abnormality();
};

#endif
