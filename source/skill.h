#ifndef _SKILL_H_
#define _SKILL_H_

// 技能与常数相关的在这里改
#define MaxHealthBoostPerLevel 20
#define MaxMagicBoostPerLevel 20
#define MagicRegenerationBoostPerLevel 1
#define MoveSpeedBoostPerLevel 16
#define BulletSpeedBoostPerLevel 40
#define EmbrittlementDamageBoostRate 0.5
#define RangedAttackBoostPerLevel 2

#include <vector>
#include <functional>
#include <unordered_map>
#include <string>
#include <graphics.h>
#include <random>
#include <algorithm>
#include <iostream>
#include "resources_manager.h"

enum class SkillID
{
	MaxHealthBoost,
	MaxMagicBoost,
	MagicRegenerationBoost,
	MoveSpeedBoost,
	PoisonBullet,
	FireBullet,
	IceBullet,
	WeaknessBullet,
	BulletSpeedBoost,
	RangedAttackBoost,
	FastPoison,
	StrongFire,
	StrongIce,
	StrongWeakness,
	PoisonBurst,
	EternelFrostFire,
	EncouragingFire,
	LongTermlPoison,
	MultiFunctionPoison,
	Embrittlement,
	BITBullet,
	WenCuiBackground,
	SectorBulletsI,
	SectorBulletsII,
	SectorBulletsIII,
	ParallelBulletsI,
	ParallelBulletsII,
	ParallelBulletsIII,
	MagicCostReduce,
	MagicDrain
};

class SkillList;

class Skill
{
protected:
	SkillID id;
	int max_stack_count;
	int stacked_count;
	std::vector<SkillID> precondition_skills;
	std::function<bool(SkillList* skill_list)> is_available;
	int cost = 0;

	std::wstring name = L"";
	std::vector<std::wstring> lore;

	IMAGE* icon = nullptr;

	bool is_precondiction_completed(SkillList* skill_list);

public:
	Skill();
	Skill(SkillID id, int max_stack_count, std::function<bool(SkillList* skill_list)> is_available, int cost, std::wstring name, int stacked_count = 0);
	void add_precondition_skill(SkillID precondition_skill);
	bool get_is_available(SkillList* skill_list);
	int get_level() const;
	int get_max_stack_count() const;
	int stack(int value);
	int get_cost() const;
	SkillID get_id() const;
	void add_lore(std::wstring l);

	void set_icon(IMAGE* icon);
	IMAGE* get_icon();

	std::wstring get_name() const;
	std::vector<std::wstring>* get_lores();
};

class SkillList
{
protected:
	std::unordered_map<SkillID, Skill> skills;
	std::unordered_map<SkillID, Skill> skills_owned;

public:
	SkillList();
	~SkillList();
	int get_skill_level(SkillID id);
	std::vector<Skill> get_available_skills(int count);
	void add_skill(SkillID id);

	Skill& find_skill(SkillID id);

	void reset();
};

#endif // !_SKILL_H_
