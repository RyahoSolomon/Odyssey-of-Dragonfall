#include "character.h"
#include "collision_manager.h"

Character::Character()
{
	// hurt box 由 Character 负责销毁; hit box 由与其绑定的 bullet 负责销毁! 千万注意!
	// 仅远程的角色不创建 hitbox, 只有能近战的角色创建 hitbox 并和 MeleeBullet 绑定
	hurt_box = CollisionManager::instance()->create_collision_box();

	timer_invulnerable_status.set_wait_time(1.0f);
	timer_invulnerable_status.set_one_shot(true);
	timer_invulnerable_status.set_on_timeout([&]()
		{
			is_invulnerable = false;
		});
	timer_invulnerable_blink.set_wait_time(0.075f);
	timer_invulnerable_blink.set_one_shot(false);
	timer_invulnerable_blink.set_on_timeout([&]()
		{
			is_blink_invisible = !is_blink_invisible;
		});

	hurt_box->set_on_collide([dst = this](CollisionBox* src_collision_box)
		{
			src_collision_box->get_owner()->on_hit(dst);
		});
}

Character::~Character()
{
	CollisionManager::instance()->destroy_collision_box(hurt_box);
}

void Character::decrease_hp()
{
	if (is_invulnerable)
	{
		return;
		//std::cout << "is_invulnerable" << std::endl;
	}
	hp -= 1;
	if (hp > 0)
	{
		make_invulnerable();
	}
	on_hurt();
}

void Character::on_input(const ExMessage& msg) {}

void Character::on_update(float delta)
{
	state_machine.on_update(delta);

	if (hp <= 0)
	{
		velocity.x = 0;
		velocity.y = 0;
	}

	// 角色移动及限位
	position += velocity * ice_scale(delta);

	if (position.x <= 0)
	{
		position.x = 0;
	}

	// 这里由于 enemy 是生成在屏幕外的, 所以如果只要角色是在往左走, 限位就不会生效
	if (position.x >= getwidth())
	{
		if (velocity.x <= 0 && velocity.y == 0) {}
		else
		{
			position.x = (float)getwidth();
		}
	}

	if (position.y < 0)
	{
		position.y = 0;
	}

	if (position.y > getheight() - ResourcesManager::instance()->find_image("ui_bar")->getheight())
	{
		position.y = (float)(getheight() - ResourcesManager::instance()->find_image("ui_bar")->getheight());
	}

	hurt_box->set_position(get_logic_center());

	timer_invulnerable_status.on_update(delta);

	if (is_invulnerable)
	{
		timer_invulnerable_blink.on_update(delta);
	}

	if (!current_animation)
	{
		return;
	}

	Animation& animation = (is_facing_left ? current_animation->left : current_animation->right);
	animation.update(delta);
	animation.set_position(position);

	Unit::on_update(delta);
}

void Character::on_render()
{
	if (!current_animation || (is_invulnerable && is_blink_invisible))
	{
		return;
	}

	(is_facing_left ? current_animation->left : current_animation->right).on_render();
}

void Character::on_hurt() {};

void Character::switch_state(const std::string& id)
{
	//std::cout << "角色状态切换: " << id << "\n";
	state_machine.switch_to(id);
}

void Character::set_animation(const std::string& id)
{
	current_animation = &animation_pool[id];

	current_animation->left.reset();
	current_animation->right.reset();
}

void Character::set_move_speed(float speed) 
{ 
	move_speed = speed; 
}

float Character::get_move_speed() const
{
	return move_speed;
}

CharacterBaseProperty::CharacterBaseProperty(int attack, int health, float attack_cd, int move_speed, int bullet_speed) :
	attack(attack), health(health), attack_cd(attack_cd), move_speed(move_speed), bullet_speed(bullet_speed)
{
}
