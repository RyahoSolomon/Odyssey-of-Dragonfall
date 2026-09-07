#ifndef _BULLET_H_
#define _BULLET_H_

#define PI 3.1415926

#include "unit.h"
#include "animation.h"
#include "collision_manager.h"

enum class DamageType
{
	Ranged,
	Melee
};

// 基本子弹类, 不能直接用
class CollisionManager;
class CollisionBox;

class Bullet
{
public:
	Bullet(Unit* owner);
	~Bullet();

	virtual void on_update(float delta);
	virtual void on_render();
	virtual int on_hit(Unit* target);
	
	void set_position(Vector2d position);
	
	CollisionBox* get_collision_box();

	bool is_valid() const;

	void set_damage_value(int value);
	int get_damage_value() const;

	DamageType damage_type = DamageType::Ranged;

protected:
	Vector2d position;
	Animation* current_animation = nullptr;
	bool valid = true;

	int damage_value = 0;

	CollisionBox* collision_box = nullptr;

	Unit* owner = nullptr;

	int poison = 0;
	float poison_duration = 0;
	int fire = 0;
	float fire_duration = 0;
	int ice = 0;
	float ice_duration = 0;
	int weakness = 0;
	float weakness_duration = 0;
}; 

class LinearBullet : public Bullet
{
protected:
	Vector2d velocity;
	LinearBullet(Unit* owner, Vector2d velocity, Vector2d pos, int damage);
	~LinearBullet();
	void on_update(float delta) override;
	int on_hit(Unit* target) override;
};

class MeleeBullet : public Bullet
{
public:
	MeleeBullet(Unit* owner, Vector2d pos, int damage);

	void on_update(float delta) override;
	void on_render() override;
	int on_hit(Unit* target) override;
	void set_collision_box(CollisionBox* collison_box);
};

#endif