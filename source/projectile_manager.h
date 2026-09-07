#ifndef _PROJECTILE_MANAGER_H_
#define _PROJECTILE_MANAGER_H_

#include "state_machine.h"
#include "bullet.h"
#include <vector>

// TODO: 突然有个赤石的想法, 可以做个技能让子弹的图标都变为北理的校徽

class ProjectileManager
{
public:
	ProjectileManager() = default;
	~ProjectileManager() = default;

	void destory_bullet(Bullet* bullet);
	void destory_all_bullets();
	void destory_invalid_bullets();
	void on_update(float delta);
	void on_render();
	void add_bullet(Bullet* bullet);

	static ProjectileManager* instance();

private:
	std::vector<Bullet*> bullets;
	static ProjectileManager* projectile_manager;
};

#endif