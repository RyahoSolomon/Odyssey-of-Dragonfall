#ifndef _UNIT_H_
#define _UNIT_H_

#include <graphics.h>
#include <sstream>

#include "Vector2d.h"
#include "effect.h"
#include "timer.h"
#include "util.h"
#include "skill.h"

/*
* 毒: 持续 10s, 每秒根据毒的层数造成伤害, 中毒层数增加也会刷新持续时间
* 火: 持续 3s, 每 0.5 秒造成一次固定伤害, 只刷新不叠层
* 冰: 每层使得移动速度降低 1% (准确的说是 移动速度 / (1 + 0.01 * 冰层数), 层数增加刷新
* 咒: 每层使得伤害降低 10% (准确地说是攻击伤害 / (1 + 0.1 * 咒), 所有咒效果独立计算持续时长, 有效咒数为所有咒效果的叠加
*
* 为了让代码尽可能不重复引用, 在 Character 上面套了个 Unit, 专门用来实现状态效果层, 不过倒是未来也能在这个基础上实现 Object 等场景互动物体
*/

// 在 Unit/Character 层实现的技能效果, 一定要先判断对象是否为玩家! 

extern SkillList* global_player_skills;

enum class UnitType
{
	Enemy,
	Player,

};

class Unit
{
public:
	Unit();
	~Unit() = default;

protected:
	// 下面这些量是状态效果层数
	int effect_fire = 0;
	int effect_ice = 0;
	int effect_poison = 0;
	int effact_weakness_valid = 0;

	float remaining_duration_fire = 0;
	float remaining_duration_ice = 0;
	float remaining_duration_poison = 0;

	Timer timer_fire;
	Timer timer_poison;

	EffectList effects;

	int hp = 10;
	int max_hp = 10;
	Vector2d position;
	Vector2d velocity;
	float logic_height = 0;
	int attack_power = 0;

	UnitType type;
	
public:
	virtual void on_input(const ExMessage& msg);
	virtual void on_update(float delta);
	virtual void on_render();

	void apply_effect(EffectType type, int level = 0, float duration = 0);

	int apply_damage(int amount);
	void apply_healing(int amount);

	int get_hp() const
	{
		return hp;
	}

	int get_max_hp() const
	{
		return max_hp;
	}

	void set_position(const Vector2d& position)
	{
		this->position = position;
	}

	const Vector2d& get_position() const
	{
		return position;
	}

	void set_velocity(const Vector2d& velocity)
	{
		this->velocity = velocity;
	}

	void set_velocity(float x, float y)
	{
		velocity.x = x;
		velocity.y = y;
	}

	const Vector2d& get_velocity() const
	{
		return velocity;
	}

	void on_debug_render();
	int get_attack() const;

	float ice_scale(float original_value);
	int attack_scale(int original_value) const;
};

#endif