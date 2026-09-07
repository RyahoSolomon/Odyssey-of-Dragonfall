#include "bullet.h"

Bullet::Bullet(Unit* owner) : owner(owner)
{
}

Bullet::~Bullet()
{
	CollisionManager::instance()->destroy_collision_box(collision_box);
}

void Bullet::on_update(float delta)
{
	// 常数说明, 100 为最大超出屏幕的像素限制, 超出限制后子弹会被销毁, 懒得写成宏或者常量了
	if (position.x < 0 - 100 ||
		position.x > getwidth() + 100 ||
		position.y < 0 - 100 ||
		position.y > getheight() + 100)
	{
		valid = false;
	}

	current_animation->set_position(position);
	current_animation->update(delta);
	collision_box->set_position(position);
}

void Bullet::on_render()
{
	current_animation->on_render();
}

int Bullet::on_hit(Unit* target)
{
	if (poison) target->apply_effect(EffectType::Poison, poison, poison_duration);
	if (fire) target->apply_effect(EffectType::Fire, 1);
	if (ice) target->apply_effect(EffectType::Ice, ice, ice_duration);
	if (weakness) target->apply_effect(EffectType::Weakness, weakness, weakness_duration);
	return target->apply_damage(damage_value);
}

void Bullet::set_position(Vector2d position)
{
	this->position = position;
}

CollisionBox* Bullet::get_collision_box()
{
	return collision_box;
}

bool Bullet::is_valid() const
{
	return valid;
}

void Bullet::set_damage_value(int value)
{
	damage_value = value;
}

int Bullet::get_damage_value() const
{
	return damage_value;
}

LinearBullet::LinearBullet(Unit* owner, Vector2d velocity, Vector2d pos, int damage) : Bullet(owner), velocity(velocity)
{
	this->position = pos;
	this->damage_value = damage;
}

LinearBullet::~LinearBullet()
{
}

void LinearBullet::on_update(float delta)
{
	position += velocity * delta;
	Bullet::on_update(delta);
}

int LinearBullet::on_hit(Unit* target)
{
	valid = false;
	return Bullet::on_hit(target);
}

MeleeBullet::MeleeBullet(Unit* owner, Vector2d pos, int damage) :
	Bullet(owner)
{
	damage_value = damage;
	position.x = pos.x;
	position.y = pos.y;
	damage_type = DamageType::Melee;
}

void MeleeBullet::on_update(float delta)
{
	damage_value = owner->get_attack();
}

void MeleeBullet::on_render()
{
}

int MeleeBullet::on_hit(Unit* target)
{
	collision_box->set_enabled(false);
	return Bullet::on_hit(target);
}

void MeleeBullet::set_collision_box(CollisionBox* collison_box)
{
	this->collision_box = collison_box;
}
