#ifndef SKILL_ENUM_T_H
#define SKILL_ENUM_T_H

#include "../TypeDefs.h"

enum EAdjustTargetingPos :UINT32 {
	EAdjustTargetingPos_notUse = 1,
	EAdjustTargetingPos_toTarget = 2,
	EAdjustTargetingPos_toTargetWithGeo = 3,
	EAdjustTargetingPos_normal = 4,
};

enum ESkillMethod :UINT32 {
	ESkillMethod_normal = 1,
	ESkillMethod_lockOn = 2,
	ESkillMethod_useCollected = 3,
	ESkillMethod_real_forward = 4,
	ESkillMethod_spiritAttack = 5,
	ESkillMethod_spiritFollow = 6,
	ESkillMethod_rangelockon = 7,
	ESkillMethod_spiritUseSkill = 8,
	ESkillMethod_spiritStandBy = 9,
	ESkillMethod_collect = 10,
};

enum EPpushTarget :UINT32 {
	EPpushTarget_pass = 1,
	EPpushTarget_stop = 2,
	EPpushTarget_push = 3,
	EPpushTarget_pushall = 4,
};

enum EReactionPending :UINT32 {
	EReactionPending_normal = 1,
	EReactionPending_allTimeLine = 2,
	EReactionPending_immediateCancel = 3,
};

enum ESkillPending :UINT32 {
	ESkillPending_normal = 1,
	ESkillPending_immediateCancel = 2,
	ESkillPending_allTimeLine = 3,
	ESkillPending_rearCancelOnly = 4,
	ESkillPending_disable = 5,
	ESkillPending_rearCancel = 6,
	ESkillPending_hotkeyrearCancelOnly = 7,
	ESkillPending_immediawateCancel = 8,
};

enum ESkill :UINT32 {
	ESkill_instance = 1,
	ESkill_movingSkill = 2,
	ESkill_normal = 3,
	ESkill_movingCharge = 4,
	ESkill_projectile = 5,
	ESkill_evade = 6,
	ESkill_combo_instance = 7,
	ESkill_notimeline = 8,
	ESkill_stand = 9,
	ESkill_combo = 10,
	ESkill_switch = 11,
	ESkill_change = 12,
	ESkill_shootingmovingskill = 13,
	ESkill_userslug = 14,
	ESkill_dash = 15,
	ESkill_connect = 16,
	ESkill_catchBack = 17,
	ESkill_defence = 18,
	ESkill_transform = 19,
	ESkill_charm = 20,
	ESkill_firewood = 21,
	ESkill_summon = 22,
	ESkill_Gamble = 23,
	ESkill_rebirth = 24,
	ESkill_notimeline_revivenow = 25,
	ESkill_commander_scan = 26,
	ESkill_commander_normal = 27,
	ESkill_custom = 28,
	ESkill_eventseed = 29,
	ESkill_mount = 30,
	ESkill_drain = 31,
	ESkill_drain_back = 32,
	ESkill_shortTel = 33,
	ESkill_pressHit = 34,
	ESkill_bulldozer = 35,
	ESkill_capture = 36,
	ESkill_stone = 37,
	ESkill_positionswap = 38,
	ESkill_counter = 39,
	ESkill_inversecapture = 40,
	ESkill_chaseEffect = 41,
	ESkill_aiWork = 42,
	ESkill_Projectile = 43,
	ESkill_catchThrow = 44,
};

enum ETargetingAreaTeleport :UINT32 {
	ETargetingAreaTeleport_area_teleport_SER_POS = 1,
	ETargetingAreaTeleport_area_teleport_MYSELF_VILLAGE = 2,
	ETargetingAreaTeleport_area_teleport_RESERVED_POS = 3,
	ETargetingAreaTeleport_area_teleport_PARTY = 4,
	ETargetingAreaTeleport_area_teleport_FLOATINGCASTLE_POS = 5,
	ETargetingAreaTeleport_area_teleport_TELEPORTWARD_POS = 6,
	ETargetingAreaTeleport_area_teleport_GUILD = 7,
	ETargetingAreaTeleport_area_teleport_BONFIRE = 8,
};

enum ETargetingAreaType :UINT32 {
	ETargetingAreaType_targeting_area_enemyOrPvp = 1,
	ETargetingAreaType_targeting_area_me = 2,
	ETargetingAreaType_targeting_area_enemy = 3,
	ETargetingAreaType_targeting_area_pvp = 4,
	ETargetingAreaType_targeting_area_no = 5,
	ETargetingAreaType_targeting_area_second_hit = 6,
	ETargetingAreaType_targeting_area_none = 7,
	ETargetingAreaType_targeting_area_exceptAll = 8,
	ETargetingAreaType_targeting_area_ally = 9,
	ETargetingAreaType_targeting_area_allPcExceptMe = 10,
	ETargetingAreaType_targeting_area_party = 11,
	ETargetingAreaType_targeting_area_all = 12,
	ETargetingAreaType_targeting_area_allIncludeVillager = 13,
	ETargetingAreaType_targeting_area_raid = 14,
	ETargetingAreaType_targeting_area_allyOnDeath = 15,
	ETargetingAreaType_targeting_area_allyExceptMe = 16,
	ETargetingAreaType_targeting_area_allyVillager = 17,
	ETargetingAreaType_targeting_area_noneUnion = 18,
	ETargetingAreaType_targeting_area_allPCExceptMe = 19,
	ETargetingAreaType_targeting_area_raidExceptMe = 20,
	ETargetingAreaType_targeting_area_partyExceptMe = 21,
	ETargetingAreaType_targeting_area_allExceptMe = 22,
	ETargetingAreaType_targeting_area_Me = 23,
	ETargetingAreaType_targeting_area_allPcIgnoreSpirit = 24,
	ETargetingAreaType_targeting_area_enermy = 25,
	ETargetingAreaType_targeting_area_allPCIgnoreSpirit = 26,
	ETargetingAreaType_targeting_area_ignoreSpirit = 27,
	ETargetingAreaType_targeting_area_Pvp = 28,
};

enum ETargetingType :UINT32 {
	ETargetingType_targeting_none = 1,
	ETargetingType_targeting_second_hit = 2,
	ETargetingType_targeting_aggro = 3,
	ETargetingType_targeting_real_forward = 4,
	ETargetingType_targeting_real_ccw = 5,
	ETargetingType_targeting_condition_hit = 6,
	ETargetingType_targeting_real_cw = 7,
	ETargetingType_targeting_super_armor_reflect = 8,
	ETargetingType_targeting_defence = 9,
	ETargetingType_targeting_unreal_forward = 10,
	ETargetingType_targeting_real_backward = 11,
};

enum EWeaponStatus :UINT32 {
	EWeaponStatus_weapon_status_out = 1,
	EWeaponStatus_weapon_status_in = 2,
};

enum EAttackType :UINT16
{
	EAttackType_DAMAGE = 1,
	EAttackType_HEAL = 2,
	EAttackType_MANA_REGEN = 3
};

enum EVisualEffect : UINT16
{

};

enum ESkillAnimationFlags :UINT32 {
	ESkillAnimationFlags_RootMotion = 1 << 0,
	ESkillAnimationFlags_RootRotate = 1 << 1
};

enum ESkillActionStageFlags : UINT16 {
	ESkillActionStageFlags_Movable = 1 << 0,
	ESkillActionStageFlags_ChangeDirToTarget = 1 << 1,
	ESkillActionStageFlags_PAdjustAnimToTarget = 1 << 2
};

enum ESkillArgsFlags : UINT16 {
	ESkillArgsFlags_Unk1 = 1 << 0,
	ESkillArgsFlags_Unk2 = 1 << 1,
	ESkillArgsFlags_Unk3 = 1 << 2,
	ESkillArgsFlags_IsInstance = 1 << 3,
	ESkillArgsFlags_IsInstanceCombo = 1 << 4
};

enum ESkillFlags : UINT16 {
	ESkillFlags_AutoUse = 1 << 0,
	ESkillFlags_NeedWeapon = 1 << 1,
	ESkillFlags_ChangeDirToChanter = 1 << 2,
	ESkillFlags_KeepMovingCharge = 1 << 3,
	ESkillFlags_KeptMovingCharge = 1 << 4,
	ESkillFlags_UseSkillWhileReaction = 1 << 5,
};

#endif
