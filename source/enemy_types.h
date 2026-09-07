#ifndef _ENEMY_TYPES_H_
#define _ENEMY_TYPES_H_

#include "enemy_state_nodes.h"
#include "character_manager.h"

class Jinn : public Enemy
{
protected:

public:
	Jinn(int max_health, int attack, float attack_cd, int move_speed, int bullet_speed);
	~Jinn();

	void on_attack() override;
};

class LesserVampire : public Enemy
{
protected:
	
public:
	LesserVampire(int max_health, int attack, float attack_cd, int move_speed, int bullet_speed);
	~LesserVampire();

	void on_attack() override;
};

class ElderVampire : public Enemy
{
protected:

public:
	ElderVampire(int max_health, int attack, float attack_cd, int move_speed, int bullet_speed);
	~ElderVampire();

	void on_attack() override;
};

class ElderOfShadow : public Enemy
{
protected:

public:
	ElderOfShadow(int max_health, int attack, float attack_cd, int move_speed, int bullet_speed);
	~ElderOfShadow();

	void on_attack() override;
};

#endif // !_ENEMY_TYPES_H_
