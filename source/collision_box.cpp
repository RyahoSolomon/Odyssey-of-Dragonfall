#include "collision_box.h"

void CollisionBox::set_enabled(bool flag)
{
	enabled = flag;
}

void CollisionBox::set_layer_src(CollisionLayer layer)
{
	layer_src = layer;
}

void CollisionBox::set_layer_dst(CollisionLayer layer)
{
	layer_dst = layer;
}

void CollisionBox::set_on_collide(std::function<void(CollisionBox* src_collision_box)> on_collide)
{
	this->on_collide = on_collide;
}

void CollisionBox::set_size(const Vector2d& size)
{
	this->size = size;
}

const Vector2d& CollisionBox::get_size() const
{
	return size;
}

void CollisionBox::set_position(const Vector2d& position)
{
	this->position = position;
}

void CollisionBox::set_owner(Bullet* owner)
{
	this->onwer = owner;
}

Bullet* CollisionBox::get_owner() const
{
	return onwer;
}
