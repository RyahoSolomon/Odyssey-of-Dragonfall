#ifndef _ENEMY_BOSS_H_
#define _ENEMY_BOSS_H_

#include "enemy_state_nodes.h"
#include "character_manager.h"
#include "boss_state_nodes.h"

class DragonIdleState;
class DragonNormalAttackState;
class DragonDeadState;

class Dragon : public Boss
{
public:
	Dragon(int max_health, int attack, float attack_cd, int move_speed, int bullet_speed);
	~Dragon();

	void on_attack() override;
	void fire_array();
};

#endif // !_ENEMY_BOSS_H_
