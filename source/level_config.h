#ifndef _LEVEL_CONFIG_H_
#define _LEVEL_CONFIG_H_

#define ENEMY_SPAWN_AREA_WIDTH 144

#include <vector>
#include "resources_manager.h"
#include "util.h"
#include "enemy_types.h"
#include "enemy_boss.h"

class EnemyGroup
{
private:
	std::vector<EnemyType> enemies;

public:
	std::vector<EnemyType> get_enemies() const;

	void add_enemy(EnemyType enemy);
};

class Amplifier
{
	// 属性放大器
public:
	Amplifier(float rate_health, float rate_attack, float rate_cd, float rate_move_speed, float rate_bullet_speed);
	~Amplifier();

	int amplify_health(int original_health) const;
	int amplify_attack(int original_attack) const;
	float amplify_cd(float original_cd) const;
	int amplify_move_speed(int original_move_speed) const;
	int amplify_bullet_speed(int original_bullet_speed) const;

protected:
	float health_amplify_rate = 1.0;
	float attack_amplify_rate = 1.0;
	float cd_amplify_rate = 1.0;
	float move_speed_amplify_rate = 1.0;
	float bullet_speed_amplify_rate = 1.0;
};

class LevelConfig
{
protected:

	std::vector<EnemyGroup> enemy_pool;
	std::vector<int> nums_enemy_group; // 每波敌人的组数; 这样要求每关不同的敌人组之间的强度尽量相同
	Amplifier amplifier;
	IMAGE* background = nullptr;
	std::vector<int> duration_waves;
	int exp;
	
	std::vector<std::string> bgm;

	EnemyType boss = EnemyType::None;

public:
	std::vector<int> get_timer_waves() const;
	std::vector<Enemy*> summon_enemy(int wave) const;
	Enemy* create_boss();

	LevelConfig(Amplifier amplifier, int exp);
	~LevelConfig();

	IMAGE* get_background() const;
	void set_background(IMAGE* img);
	void add_enemy_group(EnemyGroup enemy_group);
	void add_wave(int num_enemy_group, int duration_wave);
	int get_exp() const;

	void set_boss(EnemyType type);
	EnemyType get_boss() const;

	void add_bgm(std::string name);
	std::vector<std::string> get_bgm() const;
};

#endif // !_LEVEL_CONFIG_H_
