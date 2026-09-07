#ifndef _CHARACTER_MANAGER_H_
#define _CHARACTER_MANAGER_H_

#include <vector>
#include "character.h"
#include "player.h"
#include "enemy.h"
#include "skill.h"

extern SkillList* global_player_skills;

class CharacterManager
{
public:
	static CharacterManager* instance();

	Character* get_player()
	{
		return player;
	}

	void on_input(const ExMessage& msg);
	void on_update(float delta);
	void on_render();
	void on_debug_render();

	void init_characters();
	void delete_characters();
	void add_enemy(Enemy* enemy);

	bool is_all_enemy_dead() const;
	void reset();

	CharacterBaseProperty* get_character_base_property(EnemyType type);
	
	int get_exp() const;
	void add_exp(int value);
	bool consume_exp(int value);

	std::vector<Skill> get_player_available_skills(int count);
	bool add_skill(SkillID id);
	int get_skill_level(SkillID id);

protected:
	static CharacterManager* manager;

	Character* player = nullptr;
	Character* boss = nullptr;
	std::vector<Enemy*> enemies;

	std::unordered_map<EnemyType, CharacterBaseProperty*> character_properties;

	SkillList* player_skills;

	int exp = 0;

private:
	CharacterManager();
	~CharacterManager();
};

#endif