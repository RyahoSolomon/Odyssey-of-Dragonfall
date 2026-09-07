#ifndef _BULLETS_H_
#define _BULETTS_H_

#include "resources_manager.h"
#include "bullet.h"

class PlayerBullet : public LinearBullet
{
public:
	PlayerBullet(Unit* owner, Vector2d velocity, Vector2d pos, int damage);
	~PlayerBullet();

	void on_update(float delta) override;
	int on_hit(Unit* target) override;

	void set_animation(std::string sprite_id, int h);

	void set_poison(int level, float duration);
	void set_fire(int level, float duration);
	void set_ice(int level, float duration);
	void set_weakness(int level, float duration);

protected:
	Animation default_animation;
};

class WindBullet : public LinearBullet
{
public:
	WindBullet(Unit* owner, Vector2d velocity, Vector2d pos, int damage);
	~WindBullet();

	void on_update(float delta) override;
	int on_hit(Unit* target) override;

protected:
	Animation default_animation;
};

class BloodBullet : public LinearBullet
{
public:
	BloodBullet(Unit* owner, Vector2d velocity, Vector2d pos, int damage);
	~BloodBullet();

	void on_update(float delta) override;
	int on_hit(Unit* target) override;

protected:
	Animation default_animation;
};

class DragonFire : public LinearBullet
{
public:
	DragonFire(Unit* owner, Vector2d velocity, Vector2d pos, int damage);
	~DragonFire();

	void on_update(float delta) override;
	int on_hit(Unit* target) override;

protected:
	Animation default_animation;
};

#endif // !_BULLETS_H_
