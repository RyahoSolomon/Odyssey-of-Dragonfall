#include "player_state_nodes.h"

PlayerMeleeAttackState::PlayerMeleeAttackState()
{
	timer.set_wait_time(0.7f);
	timer.set_one_shot(true);
	timer.set_on_timeout([&]()
		{
			Player* player = (Player*)CharacterManager::instance()->get_player();
			player->set_melee_attacking(false);
		}
	);
}

void PlayerMeleeAttackState::on_enter()
{
	Player* player = (Player*)CharacterManager::instance()->get_player();
	player->get_hit_box()->set_enabled(true);
	player->set_melee_attacking(true);
	update_hit_box_position();
	player->on_melee_attack();
	player->set_animation("melee_attack");
	timer.restart();

	//TODO: 播放攻击音效
}

void PlayerMeleeAttackState::on_update(float delta)
{
	timer.on_update(delta);
	update_hit_box_position();

	Player* player = (Player*)CharacterManager::instance()->get_player();

	if(player->get_hp() <= 0)
	{
		player->switch_state("dead");
	}
	else if (!player->get_melee_attacking())
	{
		if (player->get_move_dir() != Character::MoveDirection::None)
		{
			player->switch_state("run");
		}
		else
		{
			player->switch_state("idle");
		}
	}
}

void PlayerMeleeAttackState::on_exit()
{
	Player* player = (Player*)CharacterManager::instance()->get_player();
	player->get_hit_box()->set_enabled(false);
	player->set_melee_attacking(false);
}

void PlayerMeleeAttackState::update_hit_box_position()
{
	// 近战攻击只需要攻击碰撞箱偏移向角色朝向即可, 与鼠标位置无关
	Player* player = (Player*)CharacterManager::instance()->get_player();
	Vector2d position = player->get_position();
	CollisionBox* hit_box = player->get_hit_box();
	const Vector2d& hit_box_size = hit_box->get_size();

	if (player->get_facing_left())
	{
		hit_box->set_position({ position.x - hit_box_size.x / 2 , position.y});
	}
	else
	{
		hit_box->set_position({ position.x + hit_box_size.x / 2, position.y });
	}
}

PlayerDeadState::PlayerDeadState()
{
	
}

void PlayerDeadState::on_enter()
{
	CharacterManager::instance()->get_player()->set_animation("dead");
	// TODO: 播放死亡音效
}

void PlayerDeadState::on_update(float delta)
{
}

void PlayerDeadState::on_exit()
{
}

PlayerIdleState::PlayerIdleState()
{
}

void PlayerIdleState::on_enter()
{
	Player* player = (Player*)CharacterManager::instance()->get_player();
	player->set_animation("idle");
}

void PlayerIdleState::on_update(float delta)
{
	Player*player = (Player*)CharacterManager::instance()->get_player();
	if(player->get_hp() <= 0)
	{
		player->switch_state("dead");
	}
	else if (player->ready_to_melee_attack())
	{
		player->switch_state("melee_attack");
	}
	else if (player->ready_to_ranged_attack())
	{
		player->switch_state("ranged_attack");
	}
	else if (player->get_move_dir() != Character::MoveDirection::None)
	{
		player->switch_state("run");
	}
}

void PlayerIdleState::on_exit()
{
}

PlayerRunState::PlayerRunState()
{
	
}

void PlayerRunState::on_enter()
{
	CharacterManager::instance()->get_player()->set_animation("run");

	// TODO: 玩家移动音效播放开始, 这里可以先试试效果怎么样
}

void PlayerRunState::on_update(float delta)
{
	Player* player = (Player*)CharacterManager::instance()->get_player();

	if (player->get_hp() <= 0)
	{
		player->switch_state("dead");
	}
	else if (player->ready_to_melee_attack())
	{
		player->switch_state("melee_attack");
	}
	else if (player->ready_to_ranged_attack())
	{
		player->switch_state("ranged_attack");
	}
	else if (player->get_move_dir() == Character::MoveDirection::None)
	{
		player->switch_state("idle");
	}
}

void PlayerRunState::on_exit()
{
	// TODO: 结束播放玩家移动音效
}

PlayerRangedAttackState::PlayerRangedAttackState()
{
	timer.set_wait_time(0.7f);
	timer.set_one_shot(true);
	timer.set_on_timeout([&]()
		{
			Player* player = (Player*)CharacterManager::instance()->get_player();
			player->set_ranged_attacking(false);
		}
	);
}

void PlayerRangedAttackState::on_enter()
{
	Player* player = (Player*)CharacterManager::instance()->get_player();
	player->set_ranged_attacking(true);
	player->on_ranged_attack();
	player->set_animation("ranged_attack");
	timer.restart();

	//TODO: 播放攻击音效
}

void PlayerRangedAttackState::on_update(float delta)
{
	timer.on_update(delta);

	Player* player = (Player*)CharacterManager::instance()->get_player();
	if(player->get_hp() <= 0)
	{
		player->switch_state("dead");
	}
	else if (!player->get_ranged_attacking())
	{
		if (player->get_move_dir() != Character::MoveDirection::None)
		{
			player->switch_state("run");
		}
		else
		{
			player->switch_state("idle");
		}
	}
}

void PlayerRangedAttackState::on_exit()
{
	Player* player = (Player*)CharacterManager::instance()->get_player();
	player->set_ranged_attacking(false);
}
