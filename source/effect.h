#ifndef _EFFECT_H_
#define _EFFECT_H_

#include <vector>
#include <algorithm>

/*
* 毒: 持续 10s, 每秒根据毒的层数造成伤害, 中毒层数增加也会刷新持续时间
* 火: 持续 3s, 每 0.5 秒造成一次固定伤害, 只刷新不叠层
* 冰: 每层使得移动速度降低 1% (准确的说是 移动速度 / (1 + 0.01 * 冰层数), 层数增加刷新
* 咒: 每层使得伤害降低 10% (准确地说是攻击伤害 / (1 + 0.1 * 咒), 所有咒效果独立计算持续时长, 有效咒数为所有咒效果的叠加
* 
* 不过, 这里需要单独实现为 Effect 类的目前只有咒
* 
* Strength: 力量, 每层增加 10% 的伤害, 这个 10% 与上面的咒位于不同乘区
*/

extern const float default_fire_duration;
extern const float default_poison_duration;
extern const float default_ice_duration;
extern const float default_fire_damage_frequency;
extern const float default_poison_damage_frequency;
extern const int default_fire_damage_amount;

enum class EffectType
{
	// 虚弱, 降低伤害, 其实就是上面的咒, 一个字的话和其他效果能对齐字长
	Weakness,
	Fire,
	Ice,
	Poison,
	Strength
};

class Effect
{
	// 这个类主要是用来储存各来源独立而非叠加的状态效果的
public:

private:
	int level = 0;
	float duration = 0;
	float passed_time = 0;
    EffectType type;

public:
	Effect(EffectType type, int level, float duration);
	void update(float delta);
	bool is_expired() const;
	int get_level() const;
    EffectType get_type() const;
};

class EffectList
{
private:
    std::vector<Effect> effects;

public:
	enum EffectCalcMode
	{
		Max, // 取最大值
		Sum  // 取总和
	};
    void on_update(float delta);
    void add_effect(const Effect& effect);
    int get_effect_value(EffectType type, EffectCalcMode mode) const;
    void remove_effects(EffectType type);
	void clear();
};

#endif // !_EFFECT_H_
