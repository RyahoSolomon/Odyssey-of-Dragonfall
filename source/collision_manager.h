#ifndef _COLLISION_MANAGER_H_
#define _COLLISION_MANAGER_H_

#include <vector>
#include "collision_box.h"

class CollisionBox;

class CollisionManager
{
public:
	static CollisionManager* instance();

	CollisionBox* create_collision_box();
	void destroy_collision_box(CollisionBox* collision_box);

	void process_collide();
	void on_debug_render();

private:
	static CollisionManager* manager;

	std::vector<CollisionBox*> collision_box_list;

private:
	CollisionManager();
	~CollisionManager();
};

#endif