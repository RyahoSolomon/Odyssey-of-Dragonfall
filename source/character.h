#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#define SQUARE_ROOT_2 1.41

#include <string>
#include <graphics.h>
#include <unordered_map>

#include "Vector2d.h"
#include "animation.h"
#include "collision_box.h"
#include "state_machine.h"
#include "resources_manager.h"
#include "unit.h"
#include "bullet.h"
#include "util.h"
#include "projectile_manager.h"
#include "bullets.h"

struct CharacterBaseProperty
{
	int attack = 0;
	int health = 0;
	float attack_cd = 5.0f;
	int move_speed = 0;
	int bullet_speed = 100;

	CharacterBaseProperty(int attack, int health, float attack_cd, int move_speed, int bullet_speed);
};

class Character : public Unit
{
public:
	Character();
	~Character();

	enum class MoveDirection
	{
		None,
		Left,
		Right,
		Up,
		Down,
		LeftUp,
		LeftDown,
		RightUp,
		RightDown
	};

	void decrease_hp();

	Vector2d get_logic_center() const
	{
		return Vector2d(position.x, position.y - logic_height / 2);
	}

	CollisionBox* get_hit_box()
	{
		return hit_box;
	}

	CollisionBox* get_hurt_box()
	{
		return hurt_box;
	}

	void make_invulnerable()
	{
		is_invulnerable = true;
		timer_invulnerable_status.restart();
	}

	virtual void on_input(const ExMessage& msg);
	virtual void on_update(float delta);
	virtual void on_render();

	virtual void on_hurt();

	void switch_state(const std::string& id);
	void set_animation(const std::string& id);

	void set_move_speed(float speed);
	float get_move_speed() const;

	StateMachine state_machine;

protected:
	struct AnimationGroup
	{
		Animation left;
		Animation right;
	};

protected:

	// TODO: 移动速度也要根据 buff 动态计算
	float move_speed = 100;

protected:
	bool is_facing_left = true;
	bool is_invulnerable = false;
	Timer timer_invulnerable_blink;
	Timer timer_invulnerable_status;
	bool is_blink_invisible = false;
	// hurt box 由 Character 负责销毁; hit box 由与其绑定的 bullet 负责销毁! 千万注意!
	// 仅远程的角色不创建 hitbox, 只有能近战的角色创建 hitbox 并和 MeleeBullet 绑定
	CollisionBox* hit_box = nullptr;
	CollisionBox* hurt_box = nullptr;
	AnimationGroup* current_animation = nullptr;
	std::unordered_map<std::string, AnimationGroup> animation_pool;
};

#endif