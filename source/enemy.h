#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "character.h"

enum class EnemyType
{
	None,
	Jinn,
	LesserVampire,
	ElderVampire,
	ElderOfShadow,
	Dragon
};

class Enemy : public Character
{
protected:
	Timer timer_attack_cd;
	bool is_attack_ready = false;
	float max_idle_time;
	float max_wander_time;
	float attack_duration;
	float dead_duration;
	int bullet_speed;

	bool is_dead = false;


public:
	float get_max_idle_time();
	float get_max_wander_time();
	bool get_is_attack_ready();
	float get_attack_duration();
	float get_dead_duration();

	void set_is_dead(bool flag);
	bool get_is_dead() const;
	
	void on_update(float delta) override;

	virtual void on_attack();

	Enemy();
};

class Boss : public Enemy
{
	// BOSS 主要是给那些可叠层的 buff 加了一个上限, 以防被太快打死
public:
	void on_update(float delta) override;
	Boss(int max_position);

protected:
	int max_poison;
};

class EnemyStateNode : public StateNode
{
protected:
	Enemy* owner = nullptr;

public:
	EnemyStateNode(Enemy* owner);
};

#endif