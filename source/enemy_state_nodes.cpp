#include "enemy_state_nodes.h"

// 由于怪物是生成在屏幕的右边的, 因此如果检测到位置在屏幕外就一直往左走, 这样可以模拟出怪物入场的效果
RangedEnemyIdleState::RangedEnemyIdleState(Enemy* owner) : EnemyStateNode(owner)
{
	timer.set_one_shot(true);
	timer.set_wait_time(range_random(0, owner->get_max_idle_time() * 100) / 100.0);
	timer.set_on_timeout([owner = this->owner]()
		{
			if (owner->get_position().x >= getwidth() || !owner->get_is_attack_ready())
			{
				owner->switch_state("wander");
			}
			else
			{
				owner->switch_state("attack");
			}
		});
}

void RangedEnemyIdleState::on_enter()
{
	owner->set_animation("idle");
	timer.set_wait_time(range_random(0, owner->get_max_idle_time() * 100) / 100.0);
	timer.restart();
}

void RangedEnemyIdleState::on_update(float delta)
{
	timer.on_update(delta);
	if (owner->get_hp() <= 0)
	{
		owner->switch_state("dead");
	}
}

void RangedEnemyIdleState::on_exit()
{
}

RangedEnemyWanderState::RangedEnemyWanderState(Enemy* owner) : EnemyStateNode(owner)
{
	timer.set_one_shot(true);
	timer.set_wait_time(range_random(0, owner->get_max_wander_time() * 100) / 100.0);
	timer.set_on_timeout([owner=this->owner]()
		{
			if (owner->get_position().x >= getwidth())
			{
				owner->switch_state("wander");
			}
			else if (owner->get_is_attack_ready())
			{
				owner->switch_state("attack");
			}
			else
			{
				owner->switch_state("idle");
			}
		});
}

void RangedEnemyWanderState::on_enter()
{
	timer.set_wait_time(range_random(0, owner->get_max_wander_time() * 100) / 100.0);
	timer.restart();

	owner->set_animation("wander");
	Character::MoveDirection move_direction = static_cast<Character::MoveDirection>(range_random(0, 7));
	if (owner->get_position().x >= getwidth())
	{
		move_direction = Character::MoveDirection::Left;
	}
	switch (move_direction)
	{
	case Character::MoveDirection::Left:
		owner->set_velocity(-owner->get_move_speed(), 0);
		break;
	case Character::MoveDirection::LeftDown:
		owner->set_velocity(-owner->get_move_speed() / SQUARE_ROOT_2, owner->get_move_speed() / SQUARE_ROOT_2);
		break;
	case Character::MoveDirection::Down:
		owner->set_velocity(0, owner->get_move_speed());
		break;
	case Character::MoveDirection::RightDown:
		owner->set_velocity(owner->get_move_speed() / SQUARE_ROOT_2, owner->get_move_speed() / SQUARE_ROOT_2);
		break;
	case Character::MoveDirection::Right:
		owner->set_velocity(owner->get_move_speed(), 0);
		break;
	case Character::MoveDirection::RightUp:
		owner->set_velocity(owner->get_move_speed() / SQUARE_ROOT_2, -owner->get_move_speed() / SQUARE_ROOT_2);
		break;
	case Character::MoveDirection::Up:
		owner->set_velocity(0, -owner->get_move_speed());
		break;
	case Character::MoveDirection::LeftUp:
		owner->set_velocity(-owner->get_move_speed() / SQUARE_ROOT_2, -owner->get_move_speed() / SQUARE_ROOT_2);
		break;
	}
	//std::cout << "移动方向: " << int(move_direction) << "\n";
}

void RangedEnemyWanderState::on_update(float delta)
{
	timer.on_update(delta);
	if (owner->get_hp() <= 0)
	{
		owner->switch_state("dead");
	}
}

void RangedEnemyWanderState::on_exit()
{
	owner->set_velocity(0, 0);
}

RangedEnemyAttackState::RangedEnemyAttackState(Enemy* owner) : EnemyStateNode(owner)
{
	timer.set_one_shot(true);
	timer.set_wait_time(owner->get_attack_duration());
	timer.set_on_timeout([owner = this->owner]()
		{
			if (owner->get_hp() > 0)
			{
				owner->on_attack();
			}
			if (owner->get_position().x >= getwidth() || range_random(0, 1))
			{
				owner->switch_state("wander");
			}
			else
			{
				owner->switch_state("idle");
			}
		});
}

void RangedEnemyAttackState::on_enter()
{
	timer.restart();
	owner->set_animation("attack");
}

void RangedEnemyAttackState::on_update(float delta)
{
	timer.on_update(delta);
	if (owner->get_hp() <= 0)
	{
		owner->switch_state("dead");
	}
}

void RangedEnemyAttackState::on_exit()
{
}

RangedEnemyDeadState::RangedEnemyDeadState(Enemy* owner) : EnemyStateNode(owner)
{
	timer.set_one_shot(true);
	timer.set_wait_time(owner->get_dead_duration());
	timer.set_on_timeout([owner = this->owner]()
		{
			owner->set_is_dead(true);
		});
}

void RangedEnemyDeadState::on_enter()
{
	timer.restart();
	owner->get_hurt_box()->set_enabled(false);
	owner->set_animation("dead");
}

void RangedEnemyDeadState::on_update(float delta)
{
	timer.on_update(delta);
}

void RangedEnemyDeadState::on_exit()
{
}


