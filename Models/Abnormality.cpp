#include "Abnormality.h"

Abnormality::Abnormality()
{
	memset(this, 0, sizeof(Abnormality*));

	bySkillCategory[0] = -1;
	bySkillCategory[1] = -1;
	bySkillCategory[2] = -1;
}

Abnormality::~Abnormality() {
	UINT32 count = GetEffectCount();
	for (UINT32 i = 0; i < count; i++)
	{
		delete effects[i];
		effects[i] = nullptr;
	}
}
