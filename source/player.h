#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "character.h"

class Player : public Character
{
protected:
	Timer timer_melee_attack_cd;
	Timer timer_ranged_attack_cd;
	Timer timer_mp_recovery;

	// TODO: 后续根据自身状态在每个游戏刻动态计算 cd
	float cd_melee_attack = 1.0f;
	float cd_ranged_attack = 1.0f;

	bool is_left_key_down = false;
	bool is_right_key_down = false;
	bool is_up_key_down = false;
	bool is_down_key_down = false;
	bool is_melee_attack_key_down = false;
	bool is_ranged_attack_key_down = false;

	bool is_melee_attacking = false;
	bool is_ranged_attacking = false;

	// 指示远程攻击 cd 是否转好
	bool is_ranged_attack_ready = true;
	// 指示近战攻击 cd 是否转好
	bool is_melee_attack_ready = true;

	void update_attack_dir(int x, int y);
	Vector2d attack_dir = { 0, 0 };

	int mp;
	int max_mp;

	int basic_max_hp = 100;
	int basic_max_mp = 100;
	int basic_ranged_attack = 5;
	int basic_melee_attck = 4;
	float basic_move_speed = 144;
	float basic_bullet_speed = 256;
	int basic_magic_regeneration_per_second = 1;
	int basic_ranged_attack_magic_cost = 5;

	float bullet_speed;
	int ranged_attack_power;
	int magic_regeneration_per_second = 1;
	int ranged_attack_magic_cost;

public:
	Player();
	~Player();

	void on_update(float delta) override;
	void on_input(const ExMessage& msg) override;

	void set_melee_attacking(bool flag);
	void set_ranged_attacking(bool flag);
	bool get_melee_attacking() const;
	bool get_ranged_attacking() const;
	bool ready_to_melee_attack() const;
	bool ready_to_ranged_attack() const;
	bool get_facing_left() const;

	void on_melee_attack();
	void on_ranged_attack();

	int get_move_axis_x() const;
	int get_move_axis_y() const;
	MoveDirection get_move_dir() const;
	Vector2d get_attack_dir() const;

	int get_mp() const;
	int get_max_mp() const;

	int consume_magic(int value);
};

#endif // !_PLAYER_H_
