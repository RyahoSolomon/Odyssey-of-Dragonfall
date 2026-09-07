#include "projectile_manager.h"

ProjectileManager* ProjectileManager::projectile_manager = nullptr;

void ProjectileManager::destory_bullet(Bullet* bullet)
{
	bullets.erase(std::remove(bullets.begin(), bullets.end(), bullet), bullets.end());
	delete bullet;
}

void ProjectileManager::on_update(float delta)
{
	for (Bullet* bullet : bullets)
	{
		if (bullet->is_valid())
		{
			bullet->on_update(delta);
		}
	}
	destory_invalid_bullets();
}

void ProjectileManager::on_render()
{
	for (Bullet* bullet : bullets)
	{
		bullet->on_render();
	}
}

void ProjectileManager::add_bullet(Bullet* bullet)
{
	bullets.push_back(bullet);
}

void ProjectileManager::destory_all_bullets()
{
	for (Bullet* bullet : bullets)
	{
		delete bullet;
	}
	bullets.clear();
}

void ProjectileManager::destory_invalid_bullets()
{
	bullets.erase(
		std::remove_if(bullets.begin(), bullets.end(),
			[](Bullet* bullet) 
			{
				if (!bullet->is_valid()) 
				{
					delete bullet;
					return true;
				}
				return false;
			}),
		bullets.end());
}

ProjectileManager* ProjectileManager::instance()
{
	if (projectile_manager == nullptr)
	{
		projectile_manager = new ProjectileManager();
	}
	return projectile_manager;
}
