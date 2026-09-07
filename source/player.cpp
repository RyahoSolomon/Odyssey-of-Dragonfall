#include "player.h"
#include "player_state_nodes.h"

void Player::update_attack_dir(int x, int y)
{
	attack_dir.x = x;
	attack_dir.y = y;
}

Player::Player()
{
	type = UnitType::Player;

	max_hp = basic_max_hp + CharacterManager::instance()->get_skill_level(SkillID::MaxHealthBoost) * MaxHealthBoostPerLevel;
	hp = max_hp;
	max_mp = basic_max_mp + CharacterManager::instance()->get_skill_level(SkillID::MaxMagicBoost) * MaxMagicBoostPerLevel;
	mp = max_mp;
	ranged_attack_power = basic_ranged_attack + CharacterManager::instance()->get_skill_level(SkillID::RangedAttackBoost) * RangedAttackBoostPerLevel;
	bullet_speed = basic_bullet_speed + CharacterManager::instance()->get_skill_level(SkillID::BulletSpeedBoost) * BulletSpeedBoostPerLevel;
	move_speed = basic_move_speed + CharacterManager::instance()->get_skill_level(SkillID::MoveSpeedBoost) * MoveSpeedBoostPerLevel;
	magic_regeneration_per_second = basic_magic_regeneration_per_second + CharacterManager::instance()->get_skill_level(SkillID::MagicRegenerationBoost) * MagicRegenerationBoostPerLevel;
	attack_power = basic_melee_attck;

	ranged_attack_magic_cost = basic_ranged_attack_magic_cost;
	if (CharacterManager::instance()->get_skill_level(SkillID::PoisonBullet)) ranged_attack_magic_cost += 5;
	if (CharacterManager::instance()->get_skill_level(SkillID::FireBullet)) ranged_attack_magic_cost += 3;
	if (CharacterManager::instance()->get_skill_level(SkillID::IceBullet)) ranged_attack_magic_cost += 2;
	if (CharacterManager::instance()->get_skill_level(SkillID::WeaknessBullet)) ranged_attack_magic_cost += 2;
	ranged_attack_magic_cost += CharacterManager::instance()->get_skill_level(SkillID::FastPoison) * 3;
	ranged_attack_magic_cost += CharacterManager::instance()->get_skill_level(SkillID::StrongFire) * 2;
	ranged_attack_magic_cost += CharacterManager::instance()->get_skill_level(SkillID::StrongIce) * 1;
	ranged_attack_magic_cost += CharacterManager::instance()->get_skill_level(SkillID::StrongWeakness) * 1;
	if (CharacterManager::instance()->get_skill_level(SkillID::SectorBulletsI)) ranged_attack_magic_cost += 3;
	if (CharacterManager::instance()->get_skill_level(SkillID::SectorBulletsII)) ranged_attack_magic_cost += 2;
	if (CharacterManager::instance()->get_skill_level(SkillID::SectorBulletsIII)) ranged_attack_magic_cost += 2;
	if (CharacterManager::instance()->get_skill_level(SkillID::ParallelBulletsI)) ranged_attack_magic_cost += 3;
	if (CharacterManager::instance()->get_skill_level(SkillID::ParallelBulletsII)) ranged_attack_magic_cost += 2;
	if (CharacterManager::instance()->get_skill_level(SkillID::ParallelBulletsIII)) ranged_attack_magic_cost += 2;

	ranged_attack_magic_cost *= 1.0 - 0.2 * CharacterManager::instance()->get_skill_level(SkillID::MagicCostReduce);
	//remaining_duration_fire = 50;

	timer_mp_recovery.set_one_shot(false);
	timer_mp_recovery.set_wait_time(1.0f);
	timer_mp_recovery.set_on_timeout([&]()
		{
			mp = min(mp + magic_regeneration_per_second, max_mp);
		});
	timer_mp_recovery.restart();

	is_facing_left = false;
	
	position = { 0, getheight() / 2.0 };

	hit_box = CollisionManager::instance()->create_collision_box();
	hit_box->set_size({ 64, 96 });
	hurt_box->set_size({ 24, 40 });

	hit_box->set_layer_src(CollisionLayer::None);
	hit_box->set_layer_dst(CollisionLayer::Enemy);

	hurt_box->set_layer_src(CollisionLayer::Player);
	hurt_box->set_layer_dst(CollisionLayer::None);

	hit_box->set_enabled(false);
	MeleeBullet* melee_bullet = new MeleeBullet(this, {0, 0}, attack_power);
	melee_bullet->set_collision_box(hit_box);
	hit_box->set_owner(melee_bullet);
	ProjectileManager::instance()->add_bullet(melee_bullet);

	timer_melee_attack_cd.set_wait_time(cd_melee_attack);
	timer_melee_attack_cd.set_one_shot(true);
	timer_melee_attack_cd.set_on_timeout([&]()
		{
			is_melee_attack_ready = true;
		});
	timer_ranged_attack_cd.set_wait_time(cd_ranged_attack);
	timer_ranged_attack_cd.set_one_shot(true);
	timer_ranged_attack_cd.set_on_timeout([&]()
		{
			is_ranged_attack_ready = true;
		});


	AnimationGroup& animation_idle = animation_pool["idle"];
	Animation& animation_idle_left = animation_idle.left;
	animation_idle_left.set_interval(0.1f); // 100ms per frame
	animation_idle_left.set_loop(true);
	animation_idle_left.set_anchor_mode(Animation::AnchorMode::Centered);
	animation_idle_left.add_frame(ResourcesManager::instance()->find_image("mage_idle"), 9);

	Animation& animation_idle_right = animation_idle.right;
	animation_idle_right.set_interval(0.1f); // 100ms per frame
	animation_idle_right.set_loop(true);
	animation_idle_right.set_anchor_mode(Animation::AnchorMode::Centered);
	animation_idle_right.add_frame(ResourcesManager::instance()->find_image("mage_idle"), 9);

	AnimationGroup& animation_run = animation_pool["run"];
	Animation& animation_run_left = animation_run.left;
	animation_run_left.set_interval(0.1f); // 100ms per frame
	animation_run_left.set_loop(true);
	animation_run_left.set_anchor_mode(Animation::AnchorMode::Centered);
	animation_run_left.add_frame(ResourcesManager::instance()->find_image("mage_run_left"), 8);

	Animation& animation_run_right = animation_run.right;
	animation_run_right.set_interval(0.1f); // 100ms per frame
	animation_run_right.set_loop(true);
	animation_run_right.set_anchor_mode(Animation::AnchorMode::Centered);
	animation_run_right.add_frame(ResourcesManager::instance()->find_image("mage_run_right"), 8);

	AnimationGroup& animation_melee_attack = animation_pool["melee_attack"];
	Animation& animation_melee_attack_left = animation_melee_attack.left;
	animation_melee_attack_left.set_interval(0.1f); // 100ms per frame
	animation_melee_attack_left.set_loop(false);
	animation_melee_attack_left.set_anchor_mode(Animation::AnchorMode::Centered);
	animation_melee_attack_left.add_frame(ResourcesManager::instance()->find_image("mage_melee_attack_left"), 7);

	Animation& animation_melee_attack_right = animation_melee_attack.right;
	animation_melee_attack_right.set_interval(0.1f); // 100ms per frame
	animation_melee_attack_right.set_loop(false);
	animation_melee_attack_right.set_anchor_mode(Animation::AnchorMode::Centered);
	animation_melee_attack_right.add_frame(ResourcesManager::instance()->find_image("mage_melee_attack_right"), 7);

	AnimationGroup& animation_ranged_attack = animation_pool["ranged_attack"];
	Animation& animation_ranged_attack_left = animation_ranged_attack.left;
	animation_ranged_attack_left.set_interval(0.1f); // 100ms per frame
	animation_ranged_attack_left.set_loop(false);
	animation_ranged_attack_left.set_anchor_mode(Animation::AnchorMode::Centered);
	animation_ranged_attack_left.add_frame(ResourcesManager::instance()->find_image("mage_attack_left"), 7);
	
	Animation& animation_ranged_attack_right = animation_ranged_attack.right;
	animation_ranged_attack_right.set_interval(0.1f); // 100ms per frame
	animation_ranged_attack_right.set_loop(false);
	animation_ranged_attack_right.set_anchor_mode(Animation::AnchorMode::Centered);
	animation_ranged_attack_right.add_frame(ResourcesManager::instance()->find_image("mage_attack_right"), 7);

	AnimationGroup& animation_run_ranged_attack = animation_pool["run_ranged_attack"];
	Animation& animation_run_ranged_attack_left = animation_run_ranged_attack.left;
	animation_run_ranged_attack_left.set_interval(0.1f); // 100ms per frame
	animation_run_ranged_attack_left.set_loop(false);
	animation_run_ranged_attack_left.set_anchor_mode(Animation::AnchorMode::Centered);
	animation_run_ranged_attack_left.add_frame(ResourcesManager::instance()->find_image("mage_run_attack_left"), 8);

	Animation& animation_run_ranged_attack_right = animation_run_ranged_attack.right;
	animation_run_ranged_attack_right.set_interval(0.1f); // 100ms per frame
	animation_run_ranged_attack_right.set_loop(false);
	animation_run_ranged_attack_right.set_anchor_mode(Animation::AnchorMode::Centered);
	animation_run_ranged_attack_right.add_frame(ResourcesManager::instance()->find_image("mage_run_attack_right"), 8);

	AnimationGroup& animation_dead = animation_pool["dead"];
	Animation& animation_dead_left = animation_dead.left;
	animation_dead_left.set_interval(0.1f);
	animation_dead_left.set_loop(false);
	animation_dead_left.set_anchor_mode(Animation::AnchorMode::Centered);
	animation_dead_left.add_frame(ResourcesManager::instance()->find_image("mage_dead_left"), 10);

	Animation& animation_dead_right = animation_dead.right;
	animation_dead_right.set_interval(0.1f);
	animation_dead_right.set_loop(false);
	animation_dead_right.set_anchor_mode(Animation::AnchorMode::Centered);
	animation_dead_right.add_frame(ResourcesManager::instance()->find_image("mage_dead_right"), 10);

	state_machine.register_state("idle", new PlayerIdleState());
	state_machine.register_state("run", new PlayerRunState());
	state_machine.register_state("melee_attack", new PlayerMeleeAttackState());
	state_machine.register_state("ranged_attack", new PlayerRangedAttackState());
	state_machine.register_state("dead", new PlayerDeadState());

	state_machine.set_entry("idle");
}

Player::~Player()
{
}

void Player::on_update(float delta)
{
	if (hp > 0)
	{
		if (is_melee_attacking || is_ranged_attacking)
		{
			velocity.x = 0;
			velocity.y = 0;
		}
		else
		{
			switch (get_move_dir())
			{
			case MoveDirection::Left:
				velocity.x = -move_speed;
				velocity.y = 0;
				break;
			case MoveDirection::Right:
				velocity.x = move_speed;
				velocity.y = 0;
				break;
			case MoveDirection::Up:
				velocity.x = 0;
				velocity.y = -move_speed;
				break;
			case MoveDirection::Down:
				velocity.x = 0;
				velocity.y = move_speed;
				break;
			case MoveDirection::LeftUp:
				velocity.x = -move_speed / SQUARE_ROOT_2;
				velocity.y = -move_speed / SQUARE_ROOT_2;
				break;
			case MoveDirection::LeftDown:
				velocity.x = -move_speed / SQUARE_ROOT_2;
				velocity.y = move_speed / SQUARE_ROOT_2;
				break;
			case MoveDirection::RightUp:
				velocity.x = move_speed / SQUARE_ROOT_2;
				velocity.y = -move_speed / SQUARE_ROOT_2;
				break;
			case MoveDirection::RightDown:
				velocity.x = move_speed / SQUARE_ROOT_2;
				velocity.y = move_speed / SQUARE_ROOT_2;
				break;
			case MoveDirection::None:
				velocity.x = 0;
				velocity.y = 0;
				break;
			}
		}
		timer_melee_attack_cd.on_update(delta);
		timer_ranged_attack_cd.on_update(delta);
		timer_mp_recovery.on_update(delta);

		if (get_move_axis_x() != 0 && !(is_melee_attacking || is_ranged_attacking))
		{
			is_facing_left = get_move_axis_x() < 0;
		}
	}

	Character::on_update(delta);
}

void Player::on_input(const ExMessage& msg)
{
	if(hp <= 0)
	{
		return;
	}

	switch (msg.message)
	{
		case WM_KEYDOWN:
			switch (msg.vkcode)
			{
			case 0x41: // A
			case VK_LEFT:
				is_left_key_down = true;
				break;
			case 0x44: // D
			case VK_RIGHT:
				is_right_key_down = true;
				break;
			case 0x57: // W
			case VK_UP:
				is_up_key_down = true;
				break;
			case 0x53: // S
			case VK_DOWN:
				is_down_key_down = true;
				break;
			}
			break;

		case WM_KEYUP:
			switch (msg.vkcode)
			{
			case 0x41: // A
			case VK_LEFT:
				is_left_key_down = false;
				break;
			case 0x44: // D
			case VK_RIGHT:
				is_right_key_down = false;
				break;
			case 0x57: // W
			case VK_UP:
				is_up_key_down = false;
				break;
			case 0x53: // S
			case VK_DOWN:
				is_down_key_down = false;
				break;
			}
			break;
		case WM_LBUTTONDOWN:
			is_melee_attack_key_down = true;
			break;
		case WM_LBUTTONUP:
			is_melee_attack_key_down = false;
			break;
		case WM_RBUTTONDOWN:
			is_ranged_attack_key_down = true;
			update_attack_dir(msg.x, msg.y);
			break;
		case WM_RBUTTONUP:
			is_ranged_attack_key_down = false;
			break;
	}
}

void Player::set_melee_attacking(bool flag)
{
	is_melee_attacking = flag;
}

void Player::set_ranged_attacking(bool flag)
{
	is_ranged_attacking = flag;
}

bool Player::get_melee_attacking() const
{
	return is_melee_attacking;
}

bool Player::get_ranged_attacking() const
{
	return is_ranged_attacking;
}

bool Player::ready_to_melee_attack() const
{
	return !(is_melee_attacking || is_ranged_attacking) && is_melee_attack_ready && is_melee_attack_key_down;
}

bool Player::ready_to_ranged_attack() const
{
	return !(is_ranged_attacking || is_melee_attacking) && is_ranged_attack_ready && is_ranged_attack_key_down;
}

bool Player::get_facing_left() const
{
	return is_facing_left;
}

void Player::on_melee_attack()
{
	timer_melee_attack_cd.restart();
	is_melee_attack_ready = false;
}

void Player::on_ranged_attack()
{
	if (consume_magic(ranged_attack_magic_cost) == -1) return;

	std::vector<PlayerBullet*> bullets;

	Vector2d base_dir = (attack_dir - position).normalize();

	bullets.push_back(new PlayerBullet(
		this,
		base_dir * bullet_speed,
		position,
		attack_scale(ranged_attack_power)
	));

	int sector_level =
		CharacterManager::instance()->get_skill_level(SkillID::SectorBulletsIII) ? 3 :
		CharacterManager::instance()->get_skill_level(SkillID::SectorBulletsII) ? 2 :
		CharacterManager::instance()->get_skill_level(SkillID::SectorBulletsI) ? 1 : 0;

	if (sector_level > 0)
	{
		int extra = sector_level * 2; 
		float total_angle = 60.0f;    

		for (int i = 0; i < extra; ++i)
		{
			float t = (i + 1.0f) / (extra + 1.0f);
			float angle = (t - 0.5f) * total_angle; 

			Vector2d dir = Vector2d(
				base_dir.x * cos(angle * PI / 180.0) - base_dir.y * sin(angle * PI / 180.0),
				base_dir.x * sin(angle * PI / 180.0) + base_dir.y * cos(angle * PI / 180.0)
			).normalize();

			bullets.push_back(new PlayerBullet(
				this,
				dir * bullet_speed,
				position,
				attack_scale(ranged_attack_power)
			));
		}
	}

	int parallel_level =
		CharacterManager::instance()->get_skill_level(SkillID::ParallelBulletsIII) ? 3 :
		CharacterManager::instance()->get_skill_level(SkillID::ParallelBulletsII) ? 2 :
		CharacterManager::instance()->get_skill_level(SkillID::ParallelBulletsI) ? 1 : 0;

	if (parallel_level > 0)
	{
		int extra = parallel_level * 2; 
		float spacing = 100.0f;

		Vector2d perp = Vector2d(-base_dir.y, base_dir.x);

		for (int i = 0; i < extra; ++i)
		{
			float t = (i + 1.0f) / (extra + 1.0f);
			float offset = (t - 0.5f) * spacing * extra;

			Vector2d spawn_pos = position + perp * offset;

			bullets.push_back(new PlayerBullet(
				this,
				base_dir * bullet_speed,
				spawn_pos,
				attack_scale(ranged_attack_power)
			));
		}
	}

	for (auto* bullet : bullets)
	{
		bullet->set_animation(
			CharacterManager::instance()->get_skill_level(SkillID::BITBullet)
			? "bullet_bit"
			: "bullet_player",
			1
		);

		int level = 0;
		float duration = 0;

		if (CharacterManager::instance()->get_skill_level(SkillID::PoisonBullet))
		{
			level = 1 + CharacterManager::instance()->get_skill_level(SkillID::FastPoison);
			duration = default_poison_duration;
			bullet->set_poison(level, duration);
		}

		if (CharacterManager::instance()->get_skill_level(SkillID::FireBullet))
		{
			level = 1 + CharacterManager::instance()->get_skill_level(SkillID::StrongFire);
			duration = default_fire_duration;
			bullet->set_fire(level, duration);
		}

		if (CharacterManager::instance()->get_skill_level(SkillID::IceBullet))
		{
			level = 50 + CharacterManager::instance()->get_skill_level(SkillID::StrongIce) * 25;
			duration = default_ice_duration;
			bullet->set_ice(level, duration);
		}

		if (CharacterManager::instance()->get_skill_level(SkillID::WeaknessBullet))
		{
			level = 1 + CharacterManager::instance()->get_skill_level(SkillID::StrongWeakness);
			duration = 15;
			bullet->set_weakness(level, duration);
		}

		ProjectileManager::instance()->add_bullet(bullet);
	}
}

int Player::get_move_axis_x() const
{
	return is_right_key_down - is_left_key_down;
}

int Player::get_move_axis_y() const
{
	return is_down_key_down - is_up_key_down;
}

Character::MoveDirection Player::get_move_dir() const
{
	if (get_move_axis_x() == 0 && get_move_axis_y() == 0)
	{
		return MoveDirection::None;
	}
	else if (get_move_axis_x() < 0 && get_move_axis_y() == 0)
	{
		return MoveDirection::Left;
	}
	else if (get_move_axis_x() > 0 && get_move_axis_y() == 0)
	{
		return MoveDirection::Right;
	}
	else if (get_move_axis_x() == 0 && get_move_axis_y() < 0)
	{
		return MoveDirection::Up;
	}
	else if (get_move_axis_x() == 0 && get_move_axis_y() > 0)
	{
		return MoveDirection::Down;
	}
	else if (get_move_axis_x() < 0 && get_move_axis_y() < 0)
	{
		return MoveDirection::LeftUp;
	}
	else if (get_move_axis_x() < 0 && get_move_axis_y() > 0)
	{
		return MoveDirection::LeftDown;
	}
	else if (get_move_axis_x() > 0 && get_move_axis_y() < 0)
	{
		return MoveDirection::RightUp;
	}
	else if (get_move_axis_x() > 0 && get_move_axis_y() > 0)
	{
		return MoveDirection::RightDown;
	}
	return MoveDirection::None;
}

Vector2d Player::get_attack_dir() const
{
	return attack_dir;
}

int Player::get_mp() const
{
	return mp;
}

int Player::get_max_mp() const
{
	return max_mp;
}

int Player::consume_magic(int value)
{
	// 参数为需要消耗的原始魔法值
	// 后续可能加技能降低魔耗, 以及魔耗相关的技能, 返回实际消耗值, 若返回 -1 则表示魔法不够
	int magic_consumed = value;
	if (magic_consumed > mp)
	{
		return -1;
	}
	mp -= magic_consumed;
	return magic_consumed;
}
