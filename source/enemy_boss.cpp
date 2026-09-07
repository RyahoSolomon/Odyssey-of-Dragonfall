#include "enemy_boss.h"

Dragon::Dragon(int max_health, int attack, float attack_cd, int move_speed, int bullet_speed) : Boss(20)
{
	max_hp = max_health;
	hp = max_health;
	attack_power = attack;
	this->move_speed = move_speed;
	this->bullet_speed = bullet_speed;

	timer_attack_cd.set_one_shot(true);
	timer_attack_cd.set_wait_time(attack_cd);
	timer_attack_cd.set_on_timeout([&]()
		{
			is_attack_ready = true;
		});

	AnimationGroup& animation_idle = animation_pool["idle"];
	Animation& animation_idle_left = animation_idle.left;
	animation_idle_left.set_interval(0.25);
	animation_idle_left.set_anchor_mode(Animation::AnchorMode::Centered);
	animation_idle_left.set_loop(true);
	animation_idle_left.add_frame(ResourcesManager::instance()->find_image("dragon_idle"), 1);

	Animation& animation_idle_right = animation_idle.right;
	animation_idle_right.set_interval(0.25);
	animation_idle_right.set_anchor_mode(Animation::AnchorMode::Centered);
	animation_idle_right.set_loop(true);
	animation_idle_right.add_frame(ResourcesManager::instance()->find_image("dragon_idle"), 1);

	// 因为美术素材的原因, 精怪的移动和闲置动画是一样的
	AnimationGroup& animation_wander = animation_pool["wander"];
	Animation& animation_wander_left = animation_wander.left;
	animation_wander_left.set_interval(0.25);
	animation_wander_left.set_anchor_mode(Animation::AnchorMode::Centered);
	animation_wander_left.set_loop(true);
	animation_wander_left.add_frame(ResourcesManager::instance()->find_image("dragon_idle"), 1);

	Animation& animation_wander_right = animation_wander.right;
	animation_wander_right.set_interval(0.25);
	animation_wander_right.set_anchor_mode(Animation::AnchorMode::Centered);
	animation_wander_right.set_loop(true);
	animation_wander_right.add_frame(ResourcesManager::instance()->find_image("dragon_idle"), 1);

	AnimationGroup& animation_attack = animation_pool["attack"];
	Animation& animation_attack_left = animation_attack.left;
	animation_attack_left.set_interval(0.25);
	animation_attack_left.set_anchor_mode(Animation::AnchorMode::Centered);
	animation_attack_left.set_loop(false);
	animation_attack_left.add_frame(ResourcesManager::instance()->find_image("dragon_idle"), 1);

	Animation& animation_attack_right = animation_attack.right;
	animation_attack_right.set_interval(0.25);
	animation_attack_right.set_anchor_mode(Animation::AnchorMode::Centered);
	animation_attack_right.set_loop(false);
	animation_attack_right.add_frame(ResourcesManager::instance()->find_image("dragon_idle"), 1);

	AnimationGroup& animation_dead = animation_pool["dead"];
	Animation& animation_dead_left = animation_dead.left;
	animation_dead_left.set_interval(0.25);
	animation_dead_left.set_anchor_mode(Animation::AnchorMode::Centered);
	animation_dead_left.set_loop(false);
	animation_dead_left.add_frame(ResourcesManager::instance()->find_image("dragon_idle"), 1);

	Animation& animation_dead_right = animation_dead.right;
	animation_dead_right.set_interval(0.25);
	animation_dead_right.set_anchor_mode(Animation::AnchorMode::Centered);
	animation_dead_right.set_loop(false);
	animation_dead_right.add_frame(ResourcesManager::instance()->find_image("dragon_idle"), 1);

	attack_duration = 0.25 * 1;
	dead_duration = 0.25 * 1;

	max_idle_time = 3.0f;
	max_wander_time = 2.0f;

	hurt_box->set_enabled(true);
	hurt_box->set_size({ 512, 720 });
	hurt_box->set_layer_dst(CollisionLayer::None);
	hurt_box->set_layer_src(CollisionLayer::Enemy);

	state_machine.register_state("idle", new DragonIdleState(this));
	state_machine.register_state("normal_attack", new DragonNormalAttackState(this));
	state_machine.register_state("dead", new DragonDeadState(this));
	state_machine.register_state("fire_array", new DragonFireArrayState(this));
	state_machine.set_entry("idle");
}

Dragon::~Dragon()
{
}

void Dragon::on_attack()
{
	Vector2d dir = (CharacterManager::instance()->get_player()->get_position() - position).normalize();
	float angle_offset = 10.0f * 3.1415926f / 180.0f;

	auto rotate = [](const Vector2d& v, float rad) {
		float cos_r = std::cos(rad);
		float sin_r = std::sin(rad);
		return Vector2d(
			v.x * cos_r - v.y * sin_r,
			v.x * sin_r + v.y * cos_r
		);
		};

	Vector2d dirs[7] = {
		dir,
		rotate(dir, angle_offset),
		rotate(dir, -angle_offset),
		rotate(dir, 2 * angle_offset),
		rotate(dir, -2 * angle_offset),
		rotate(dir, 3 * angle_offset),
		rotate(dir, -3 * angle_offset)
	};

	for (int i = 0; i < 7; ++i) {
		Bullet* bullet = new DragonFire(
			this,
			dirs[i] * bullet_speed,
			position,
			attack_scale(attack_power)
		);
		ProjectileManager::instance()->add_bullet(bullet);
	}

	Enemy::on_attack();
}

void Dragon::fire_array()
{
	const int bullet_count = 10;

	float screen_width = float(getwidth());
	float screen_height = float(getwidth());

	float spacing = screen_height / (bullet_count + 1);

	Vector2d dir = Vector2d(-1.0f, 0.0f);

	for (int i = 1; i <= bullet_count; ++i)
	{
		Vector2d spawn_pos = Vector2d(
			screen_width, 
			spacing * i 
		);

		Bullet* bullet = new DragonFire(
			this,
			dir * bullet_speed,
			spawn_pos,
			attack_scale(attack_power)
		);

		ProjectileManager::instance()->add_bullet(bullet);
	}

	Enemy::on_attack();
}