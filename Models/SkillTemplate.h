#ifndef SKILLTEMPLATE_H
#define SKILLTEMPLATE_H

#include "../Base/typeDefs.h"
#include "../Base/Enums/SkillEnum.h"

#include "Models.h"

#define SKILL_ACTION_STAGES_MAX_ANIMATIONS 4
#define SKILL_MAX_ACTION_STAGES 8
#define SKILL_CHARGE_STAGES_MAX 8
#define SKILL_AREA_EFFECT_MAX_ABNORMALOTIES 4
#define SKILL_TARGETING_AREA_MAX 8
#define SKILL_PROJECTILE_DATA_MAX_TARGETINGS 8
#define SKILL_TARGETING_MAX 8
#define SKILL_ACTIONS_MAX 8

struct AbnormalityTemplate;

struct Cost {
	INT32 HP;
	INT32 MP;
};

struct Precondition
{
	Cost cost;
	INT32 coolTime;
	INT32 exclusiveAbnormality;
	INT32 modeChangeMethod;
	INT32 modeNo;
};

struct SkillAnimation {

	ESkillAnimationFlags flags;
	INT32	animDuration;
	INT32	moveDir;
	INT32	rotateYaw;

	float modeDistance[6];
	char *name;

	const BOOL HasFlag(const ESkillAnimationFlags flag) const noexcept {
		return flags & flag;
	}
};

struct SkillAnimSeq
{
	INT32	duration;
	INT32	blendInTime;
	INT32	animMotionId;

	float	animRate;
	float	loopingRate;
	float	rootMotionXYRate;
	float	rootMotionZRate;

	SkillAnimation	animation;
	SkillAnimation	movingAnimation;
	SkillAnimation	waitAnimation;
};

struct SkillActionStage {
	ESkillActionStageFlags flags;
	SkillAnimSeq animationList[SKILL_ACTION_STAGES_MAX_ANIMATIONS];

	INT32	sriptId;
	INT32	changeDirToTargetMax;
	INT32	pAnimControlType; //tocollect

	const BOOL HasFlag(const ESkillActionStageFlags flag) const noexcept {
		return flags & flag;
	}
};

struct SkillAction
{
	INT32	moveInvincibleStartTime;
	INT32	moveInvincivleEndTime;
	INT32	pendingStartTime;
	INT32	frontCancelEndTime;
	INT32	moveCancelStartTime;
	INT32	rearCancelStartTime;

	SkillActionStage stageList[SKILL_ACTION_STAGES_MAX_ANIMATIONS];

	//float
	//	cameraDuration,
	//	cameraStartTime,
	//	cameraWight;
	//
	//INT32 
	//	cameraType,
	//	cameraStartStageId,

};

struct SkillChargeStage
{
	float costHPRate;
	float costMPRate;
	float duration;
	INT32 shotSkillID;
};

struct SkillCharginStageList
{
	SkillChargeStage chargeStageList[SKILL_CHARGE_STAGES_MAX];
	float intervalCostHPRate;
	float intervalCostMPRate;
	INT32 costTotalHP;
	INT32 costTotalMP;

	BOOL movable;
};

struct SkillAttackTarget
{
	UID id;

	float x;
	float y;
	float z;
};

struct SkillArgs
{
	float	x;
	float	y;
	float	z;
	float	x2;
	float	y2;
	float	z2;

	UID targetId;

	INT16 heading;
	ESkillArgsFlags flags;

	SkillAttackTarget* targets;

	const BOOL HasFlag(const ESkillArgsFlags flag) const noexcept {
		return flags & flag;
	}
};

struct SkillAreaEffect {
	float attackMultiplier;

	INT32	hpDiff;
	INT32	mpDiff;

	const AbnormalityTemplate * abnormalitiesOnPvp[SKILL_AREA_EFFECT_MAX_ABNORMALOTIES];
	const AbnormalityTemplate * abnormalitiesOnCommon[SKILL_AREA_EFFECT_MAX_ABNORMALOTIES];
};

struct SkillTargetingArea
{
	float	crosshairRadius;
	float	crosshairRadius2;
	float	maxHeight;
	float	maxRadius;
	float	minHeight;
	float	minRadius;
	float	offsetAngle;
	float	offsetDistance;
	float	rangeAngle;
	float	rectionBasicRate;
	float	rectionMiniRate;
	float	rotateAngle;
	INT32	pierceDepth;
	INT32	maxCount;

	ETargetingAreaType type;
	SkillAreaEffect effect;

	INT32	dropItem;
};

struct SkillTargeting
{
	SkillTargetingArea areaList[SKILL_TARGETING_AREA_MAX];

	Cost			cost;

	ESkillMethod	method;
	ETargetingType	type;

	INT32			endTime;
	INT32			interval;
	INT32			startTime;
	INT32			time;
	INT32			until;

	INT32			id;

	//@TODO
	//std::vector<ProjectileSkill> projectileSkillList;
};

struct SkillProjectileData
{
	INT32 areaBoxSizeX;
	INT32 areaBoxSizeY;
	INT32 areaBoxSizeZ;
	INT32 lifeTime;

	SkillTargeting targetingList[SKILL_PROJECTILE_DATA_MAX_TARGETINGS];
};

struct AreaCircle
{
	float	radius;
	float	x;
	float	y;
	float	z;
};

struct SkillAttackResult
{
	BOOL critical;

	UID	attackerID;
	UID	targetID;

	INT32	hpDiff;
	INT32	angleDiff;
	INT32	damage;

	EAttackType type;
	EVisualEffect visualEffect;

	INT32 uid;
};

struct AnimationSet
{
	UINT32		animationsCount;
	SkillAnimation** animations;

	char *name;
};



struct SkillTemplateTargetingsAndActions {
	SkillTargeting targetingList[SKILL_TARGETING_MAX];
	SkillAction actions[SKILL_ACTIONS_MAX];
};

struct SkillTemplateAttackData {
	float	attackRangeMax;
	float	attackRange;
	float	totalAttack;
	float	timeRate;
	float	totalAtk;

	INT32	totalStk;
	INT32	totalStkPvP;
};

struct SkillTemplateBase {
	Precondition					precondition;
	SkillAnimation					animation;
	SkillCharginStageList			chargingStageList;
	SkillProjectileData				projectileData;
};

struct SkillTemplate {
	
	ESkill						type;
	ESkillFlags					flags;
	EPpushTarget				pushTarget;
	EAdjustTargetingPos			adjustTargetingPos;

	INT32	level;
	INT32	needSkill;
	INT32	nextSkill;
	INT32	templateId;
	INT32	parentId;
	INT32	baseId;
	INT32	id;

	/*char *	category;
	char *	name;*/

	const BOOL HasFlag(const ESkillFlags flag) const noexcept {
		return flags & flag;
	}
};

#endif 
