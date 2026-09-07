#include "effect.h"

Effect::Effect(EffectType type, int level, float duration) : type(type), level(level), duration(duration) {}

void Effect::update(float delta)
{
	passed_time += delta;
}

EffectType Effect::get_type() const
{
	return type;
}

bool Effect::is_expired() const
{
	return passed_time >= duration;
}

int Effect::get_level()const
{
	return level;
}

void EffectList::on_update(float delta)
{
    for (auto& e : effects)
    {
        e.update(delta);
    }

    effects.erase(
        std::remove_if(effects.begin(), effects.end(),
            [](const Effect& e)
            {
                return e.is_expired();
            }),
        effects.end()
    );
}

void EffectList::add_effect(const Effect& effect)
{
    effects.push_back(effect);
}

int EffectList::get_effect_value(EffectType type, EffectCalcMode mode) const
{
    int result = 0;

    if (mode == EffectCalcMode::Max)
    {
        for (const auto& e : effects)
        {
            if (e.get_type() == type)
            {
                result = std::max(result, e.get_level());
            }
        }
    }

    else
    {
        for (const auto& e : effects)
        {
            if (e.get_type() == type)
            {
                result += e.get_level();
            }
        }
    }

    return result;
}

void EffectList::remove_effects(EffectType type)
{
    effects.erase(
        std::remove_if(effects.begin(), effects.end(),
            [type](const Effect& e)
            {
                return e.get_type() == type;
            }),
        effects.end()
    );
}

void EffectList::clear()
{
    effects.clear();
}
