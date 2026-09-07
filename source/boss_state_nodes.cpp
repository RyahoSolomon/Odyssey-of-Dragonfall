#include "boss_state_nodes.h"

DragonIdleState::DragonIdleState(Enemy* owner) : EnemyStateNode(owner)
{
	timer.set_one_shot(true);
	timer.set_wait_time(range_random(0, owner->get_max_idle_time() * 100) / 100.0);
	timer.set_on_timeout([owner = this->owner]()
		{
			if (owner->get_is_attack_ready())
			{
				int attack_method_index = range_random(0, 1);
				switch(attack_method_index)
				{
				case 0:
					owner->switch_state("normal_attack");
					break;
				case 1:
					owner->switch_state("fire_array");
					break;
				}
			}
			else
			{
				owner->switch_state("idle");
			}
		});
}

void DragonIdleState::on_enter()
{
	owner->set_animation("idle");
	timer.set_wait_time(range_random(0, owner->get_max_idle_time() * 100) / 100.0);
	timer.restart();
}

void DragonIdleState::on_update(float delta)
{
	timer.on_update(delta);
	if (owner->get_hp() <= 0)
	{
		owner->switch_state("dead");
	}
}

void DragonIdleState::on_exit()
{
}

DragonNormalAttackState::DragonNormalAttackState(Enemy* owner) : EnemyStateNode(owner)
{
	timer.set_one_shot(true);
	timer.set_wait_time(owner->get_attack_duration());
	timer.set_on_timeout([owner = this->owner]()
		{
			if (owner->get_hp() > 0)
			{
				owner->on_attack();
			}
			owner->switch_state("idle");
		});
}

void DragonNormalAttackState::on_enter()
{
	timer.restart();
	owner->set_animation("attack");
}

void DragonNormalAttackState::on_update(float delta)
{
	timer.on_update(delta);
	if (owner->get_hp() <= 0)
	{
		owner->switch_state("dead");
	}
}

void DragonNormalAttackState::on_exit()
{
}

DragonDeadState::DragonDeadState(Enemy* owner) : EnemyStateNode(owner)
{
	timer.set_one_shot(true);
	timer.set_wait_time(owner->get_dead_duration());
	timer.set_on_timeout([owner = this->owner]()
		{
			owner->set_is_dead(true);
		});
}

void DragonDeadState::on_enter()
{
	timer.restart();
	owner->get_hurt_box()->set_enabled(false);
	owner->set_animation("dead");
}

void DragonDeadState::on_update(float delta)
{
	timer.on_update(delta);
}

void DragonDeadState::on_exit()
{
}

DragonFireArrayState::DragonFireArrayState(Enemy* owner) : EnemyStateNode(owner)
{
	timer.set_one_shot(true);
	timer.set_wait_time(owner->get_attack_duration());
	timer.set_on_timeout([owner = (Dragon*)this->owner]()
		{
			if (owner->get_hp() > 0)
			{
				owner->fire_array();
			}
			owner->switch_state("idle");
		});
}

void DragonFireArrayState::on_enter()
{
	timer.restart();
	owner->set_animation("attack");
}

void DragonFireArrayState::on_update(float delta)
{
	timer.on_update(delta);
	if (owner->get_hp() <= 0)
	{
		owner->switch_state("dead");
	}
}

void DragonFireArrayState::on_exit()
{
}
