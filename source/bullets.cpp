#include "bullets.h"

PlayerBullet::PlayerBullet(Unit* owner, Vector2d velocity, Vector2d pos, int damage) : LinearBullet(owner, velocity, pos, damage)
{
	default_animation.set_interval(1.0f);
	default_animation.set_loop(true);
	default_animation.set_anchor_mode(Animation::AnchorMode::Centered);
	current_animation = &default_animation;

	collision_box = CollisionManager::instance()->create_collision_box();
	collision_box->set_size({ 24, 24 });
	collision_box->set_layer_dst(CollisionLayer::Enemy);
	collision_box->set_layer_src(CollisionLayer::None);
	collision_box->set_enabled(true);
	collision_box->set_owner(this);
}

PlayerBullet::~PlayerBullet()
{
}

void PlayerBullet::on_update(float delta)
{
	LinearBullet::on_update(delta);
}

void PlayerBullet::set_animation(std::string sprite_id, int h)
{
	default_animation.add_frame(ResourcesManager::instance()->find_image(sprite_id), h);
}

void PlayerBullet::set_poison(int level, float duration)
{
	poison = level;
	poison_duration = duration;
}

void PlayerBullet::set_fire(int level, float duration)
{
	fire = level;
	fire_duration = duration;
}

void PlayerBullet::set_ice(int level, float duration)
{
	ice = level;
	ice_duration = duration;
}

void PlayerBullet::set_weakness(int level, float duration)
{
	weakness = level;
	weakness_duration = duration;
}

int PlayerBullet::on_hit(Unit* target)
{
	if (global_player_skills->get_skill_level(SkillID::EncouragingFire))
	{
		owner->apply_effect(EffectType::Strength, 3, 10.0f);
	}
	return LinearBullet::on_hit(target);
}

WindBullet::WindBullet(Unit* owner, Vector2d velocity, Vector2d pos, int damage) : LinearBullet(owner, velocity, pos, damage)
{
	default_animation.set_interval(1.0f);
	default_animation.set_loop(true);
	default_animation.set_anchor_mode(Animation::AnchorMode::Centered);
	default_animation.add_frame(ResourcesManager::instance()->find_image("bullet_wind"), 1);
	current_animation = &default_animation;

	collision_box = CollisionManager::instance()->create_collision_box();
	collision_box->set_size({ 16, 16 });
	collision_box->set_layer_dst(CollisionLayer::Player);
	collision_box->set_layer_src(CollisionLayer::None);
	collision_box->set_enabled(true);
	collision_box->set_owner(this);
}

WindBullet::~WindBullet()
{
}

void WindBullet::on_update(float delta)
{
	LinearBullet::on_update(delta);
}

int WindBullet::on_hit(Unit* target)
{
	return LinearBullet::on_hit(target);
}

BloodBullet::BloodBullet(Unit* owner, Vector2d velocity, Vector2d pos, int damage) : LinearBullet(owner, velocity, pos, damage)
{
	default_animation.set_interval(1.0f);
	default_animation.set_loop(true);
	default_animation.set_anchor_mode(Animation::AnchorMode::Centered);
	default_animation.add_frame(ResourcesManager::instance()->find_image("bullet_blood"), 1);
	current_animation = &default_animation;

	collision_box = CollisionManager::instance()->create_collision_box();
	collision_box->set_size({ 8, 8 });
	collision_box->set_layer_dst(CollisionLayer::Player);
	collision_box->set_layer_src(CollisionLayer::None);
	collision_box->set_enabled(true);
	collision_box->set_owner(this);
}

BloodBullet::~BloodBullet()
{
}

void BloodBullet::on_update(float delta)
{
	LinearBullet::on_update(delta);
}

int BloodBullet::on_hit(Unit* target)
{
	int d = target->apply_damage(damage_value);
	valid = false;
	owner->apply_healing(d * 0.5);
	return d;
}

DragonFire::DragonFire(Unit* owner, Vector2d velocity, Vector2d pos, int damage) : LinearBullet(owner, velocity, pos, damage)
{
	default_animation.set_interval(0.2f);
	default_animation.set_loop(true);
	default_animation.set_anchor_mode(Animation::AnchorMode::Centered);
	default_animation.add_frame(ResourcesManager::instance()->find_image("bullet_dragonfire"), 4);
	current_animation = &default_animation;

	collision_box = CollisionManager::instance()->create_collision_box();
	collision_box->set_size({ 24, 24 });
	collision_box->set_layer_dst(CollisionLayer::Player);
	collision_box->set_layer_src(CollisionLayer::None);
	collision_box->set_enabled(true);
	collision_box->set_owner(this);

	fire = 1;
	fire_duration = default_fire_duration;
}

DragonFire::~DragonFire()
{
}

void DragonFire::on_update(float delta)
{
	return LinearBullet::on_update(delta);
}

int DragonFire::on_hit(Unit* target)
{
	return LinearBullet::on_hit(target);
}