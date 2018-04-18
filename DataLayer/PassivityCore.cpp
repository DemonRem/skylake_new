#include "PassivityCore.h"

#include "../Models/ItemTemplate.h"
#include "../Models/EnchantData.h"
#include "../Models/Passivity.h"
#include "../Models/PassivityCategory.h"
#include "../Models/Item.h"
#include "../Models/DataStore.h"

#define DECREASE_BY_VALUE 1
#define INCREASE_BY_VALUE 2
#define INCREASE_BY_PERCENTAGE 3
#define DECREASE_BY_PERCENTAGE 4

INT32 PassivityRollItem(Item * item) {
	ItemTemplate * iTemplate = item->iTemplate;
	if (!iTemplate) {
		return 1;
	}
	const ItemTemplatePtrs * iPtrs = GetItemTemplateInventoryPtrs(iTemplate->index);
	if (!iPtrs) {
		return 2;
	}

	const Passivity * temp = nullptr;

	Passivity** ptr = item->ClearPassivities();
	if (iPtrs->passivityCategory) {
		temp = iPtrs->passivityCategory->GetRandom();
		if (!temp) {
			return 2;
		}

		*ptr = (Passivity*)temp;
		ptr++;
	}

	if (iPtrs->enchant && iPtrs->masterpieceEnchant) {
		if (item->HasFlag(EItemFlags_IsAwakened)) {
			for (UINT32 i = 0; i < iPtrs->masterpieceEnchant->effectsCount; i++) {
				temp = iPtrs->masterpieceEnchant->effects[i].passivitiesCategory->GetRandom();
				if (temp) {
					*ptr = (Passivity*)temp;
					ptr++;
				}
			}
		}
		else if (item->HasFlag(EItemFlags_IsMasterworked)) {
			for (UINT32 i = 0; i < iPtrs->masterpieceEnchant->effectsCount; i++) {
				if (iPtrs->masterpieceEnchant->effects[i].step <= 12) {
					temp = iPtrs->masterpieceEnchant->effects[i].passivitiesCategory->GetRandom();
					if (temp) {
						*ptr = (Passivity*)temp;
						ptr++;
					}
				}
			}
		}
		else {
			for (UINT32 i = 0; i < iPtrs->enchant->effectsCount; i++) {
				temp = iPtrs->enchant->effects[i].passivitiesCategory->GetRandom();
				if (temp) {
					*ptr = (Passivity*)temp;
					ptr++;
				}
			}
		}
	}

	/*if (i->isMasterworked) {
	for (size_t j = 0; j < i->item_t->masterpiecePassivities.size(); j++)
	i->passivities.push_back(i->item_t->masterpiecePassivities[j]);
	}
	else {
	for (size_t j = 0; j < i->item_t->passivities.size(); j++)
	i->passivities.push_back(i->item_t->passivities[j]);
	}*/

	return 0;
}

