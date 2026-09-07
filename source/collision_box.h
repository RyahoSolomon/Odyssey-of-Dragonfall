#ifndef _COLLISION_BOX_H_
#define _COLLISION_BOX_H_

#include <functional>

#include "Vector2d.h"
#include "collision_layer.h"
#include "bullet.h"

class CollisionManager;
class Bullet;

class CollisionBox
{
	friend class CollisionManager;

private:
	Vector2d size;
	Vector2d position;
	bool enabled = true;
	std::function<void(CollisionBox* src_collision_box)> on_collide;
	CollisionLayer layer_src = CollisionLayer::None;
	CollisionLayer layer_dst = CollisionLayer::None;

	Bullet* onwer = nullptr;

private:
	CollisionBox() = default;
	~CollisionBox() = default;

public:
	void set_enabled(bool flag);

	void set_layer_src(CollisionLayer layer);
	void set_layer_dst(CollisionLayer layer);
	void set_on_collide(std::function<void(CollisionBox* src_collision_box)> on_collide);
	void set_size(const Vector2d& size);

	const Vector2d& get_size() const;

	void set_position(const Vector2d& position);

	void set_owner(Bullet* owner);

	Bullet* get_owner() const;
};

#endif