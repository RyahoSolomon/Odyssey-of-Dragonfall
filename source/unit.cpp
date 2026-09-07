#include "unit.h"

Unit::Unit()
{
	timer_fire.set_one_shot(false);
	timer_fire.set_wait_time(default_fire_damage_frequency);
	timer_fire.set_on_timeout([&]()
		{
			if (remaining_duration_fire > 0)
			{
				apply_damage(effect_fire);
			}
		});

	timer_poison.set_one_shot(false);
	timer_poison.set_wait_time(default_poison_damage_frequency);
	timer_poison.set_on_timeout([&]()
		{
			if (global_player_skills->get_skill_level(SkillID::PoisonBurst) && type != UnitType::Player && remaining_duration_fire > 0) apply_damage(effect_poison);
			apply_damage(effect_poison);
		});
}

void Unit::on_input(const ExMessage& msg)
{
}

void Unit::on_update(float delta)
{
	if (hp > 0)
	{
		timer_poison.on_update(delta);
		timer_fire.on_update(delta);

		if (remaining_duration_fire > 0)
		{
			if (global_player_skills->get_skill_level(SkillID::EternelFrostFire) && type != UnitType::Player && effect_ice)
			{
				// 敌人 + 永冻之火 + 有冰, 不更新火焰计时器
			}
			else
			{
				remaining_duration_fire -= delta;
				if (remaining_duration_fire <= 0)
				{
					effect_fire = 0;
					remaining_duration_fire = 0;
				}
			}
		}

		if (remaining_duration_poison > 0)
		{
			// 长效毒药技能
			if (global_player_skills->get_skill_level(SkillID::LongTermlPoison) && type != UnitType::Player && effect_ice)
			{
				remaining_duration_poison -= 0.5 * delta;
			}
			else
			{
				remaining_duration_poison -= delta;
			}

			if (remaining_duration_poison <= 0)
			{
				effect_poison = 0;
				remaining_duration_poison = 0;
			}
		}

		if (remaining_duration_ice > 0)
		{
			remaining_duration_ice -= delta;
			if (remaining_duration_ice <= 0)
			{
				effect_ice = 0;
				remaining_duration_ice = 0;
			}
		}
	}
}

void Unit::on_render()
{
}

void Unit::apply_effect(EffectType type, int level, float duration)
{
	switch (type)
	{
	case EffectType::Fire:
		// 等级较小的火焰效果无法更新时间, 即无法叠加
		if (level < effect_fire) break;
		if (remaining_duration_fire <= 0)
		{
			// 让火焰伤害/中毒伤害的计时器在被施加时刷新, 这样会更符合直觉
			timer_fire.restart();
		}
		effect_fire = level;
		remaining_duration_fire = duration ? duration : default_fire_duration;
		break;
	case EffectType::Ice:
		remaining_duration_ice = duration ? duration : default_ice_duration;
		if (level > effect_ice)
		{
			effect_ice = level;
		}
		break;
	case EffectType::Poison:
		if (remaining_duration_poison <= 0)
		{
			timer_poison.restart();
		}
		remaining_duration_poison = duration ? duration : default_poison_duration;
		effect_poison += level;
		break;
	case EffectType::Weakness:
		effects.add_effect(Effect(type, level, duration));
	}
}

int Unit::apply_damage(int amount)
{
	if (global_player_skills->get_skill_level(SkillID::Embrittlement) && type != UnitType::Player && effect_ice && effects.get_effect_value(EffectType::Weakness, EffectList::EffectCalcMode::Sum))
	{
		amount *= 1.3;
	}
	int damage = min(amount, hp);
	hp -= damage;
	return damage;
}

void Unit::apply_healing(int amount)
{
	hp = min(max_hp, hp + amount);
}

void Unit::on_debug_render()
{
	Rect debug_info_rect = Rect(position.x - 32, position.y - 12, 64, 24); 
	std::wstringstream ss;
	ss << hp << "/" << max_hp;
	std::wstring ss_str = ss.str();
	render_text(
		Rect(position.x - 31, position.y - 11, 64, 24),
		ss_str.c_str(),
		24,
		BLACK
	);
	render_text(
		Rect(position.x - 32, position.y - 12, 64, 24),
		ss_str.c_str(),
		24,
		RED
	);
}

int Unit::get_attack() const
{
	return attack_scale(attack_power);
}

float Unit::ice_scale(float original_value)
{
	double valid_rate = 1.0 + 0.01 * effect_ice;
	if (global_player_skills->get_skill_level(SkillID::MultiFunctionPoison) && type != UnitType::Player)
	{
		valid_rate = max(valid_rate, 0.2 * effect_poison);
	}
	return original_value / valid_rate;
}

int Unit::attack_scale(int original_value) const
{
	double amplify_rate = 1.0;
	amplify_rate /= 1.0 + 0.1 * effects.get_effect_value(EffectType::Weakness, EffectList::EffectCalcMode::Sum);
	amplify_rate *= 1.0 + 0.1 * effects.get_effect_value(EffectType::Strength, EffectList::EffectCalcMode::Max);
	return int(amplify_rate * original_value);
}

