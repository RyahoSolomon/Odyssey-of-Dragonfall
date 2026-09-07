#include "enemy.h"

EnemyStateNode::EnemyStateNode(Enemy* owner) : owner(owner)
{
}

float Enemy::get_max_idle_time()
{
	return max_idle_time;
}

float Enemy::get_max_wander_time()
{
	return max_wander_time;
}

bool Enemy::get_is_attack_ready()
{
	return is_attack_ready;
}

float Enemy::get_attack_duration()
{
	return attack_duration;
}

float Enemy::get_dead_duration()
{
	return dead_duration;
}

void Enemy::set_is_dead(bool flag)
{
	is_dead = flag;
}

bool Enemy::get_is_dead() const
{
	return is_dead;
}

void Enemy::on_update(float delta)
{
	timer_attack_cd.on_update(ice_scale(delta));
	Character::on_update(delta);
	//std::cout << "Enemy@" << this << " state_machine@" << &state_machine << std::endl;
}

void Enemy::on_attack()
{
	timer_attack_cd.restart();
	is_attack_ready = false;
}

Enemy::Enemy()
{
	type = UnitType::Enemy;
}

void Boss::on_update(float delta)
{
	if (effect_poison > max_poison) effect_poison = max_poison;
	Enemy::on_update(delta);
}

Boss::Boss(int max_position) : max_poison(max_poison)
{
}
