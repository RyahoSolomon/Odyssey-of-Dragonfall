#include "character_manager.h"

CharacterManager* CharacterManager::manager = nullptr;

CharacterManager* CharacterManager::instance()
{
	if (!manager)
	{
		manager = new CharacterManager();
	}

	return manager;
}

void CharacterManager::on_input(const ExMessage& msg)
{
	player->on_input(msg);
}

void CharacterManager::on_update(float delta)
{
	player->on_update(delta);
	for (Enemy* enemy : enemies)
	{
		if (!enemy->get_is_dead())
		{
			enemy->on_update(delta);
		}
	}
}

void CharacterManager::on_render()
{
	//std::cout << "start render enemy" << std::endl;
	//std::cout << "start render player" << std::endl;
	player->on_render();
	for (Enemy* enemy : enemies)
	{
		if (!enemy->get_is_dead())
		{
			enemy->on_render();
		}
	}
}

void CharacterManager::on_debug_render()
{
	player->on_debug_render();
	for (Enemy* enemy : enemies)
	{
		if (!enemy->get_is_dead())
		{
			enemy->on_debug_render();
		}
	}
}

void CharacterManager::init_characters()
{
	if (player)
	{
		std::cout << "警告: 先前角色未被销毁\n";
	}
	player = new Player();
}

void CharacterManager::delete_characters()
{
	if (player)
	{
		delete player;
		player = nullptr;
	}
	for (Enemy* enemy : enemies)
	{
		delete enemy;
	}
	enemies.clear();
}

void CharacterManager::add_enemy(Enemy* enemy)
{
	enemies.push_back(enemy);
}

bool CharacterManager::is_all_enemy_dead() const
{
	for (Enemy* enemy : enemies)
	{
		if (!enemy->get_is_dead()) return false;
	}
	return true;
}

void CharacterManager::reset()
{
	delete_characters();
	player_skills->reset();
	exp = 0;
}

CharacterBaseProperty* CharacterManager::get_character_base_property(EnemyType type)
{
	return character_properties[type];
}

int CharacterManager::get_exp() const
{
	return exp;
}

void CharacterManager::add_exp(int value)
{
	exp += value;
}

bool CharacterManager::consume_exp(int value)
{
	// 消耗经验; 如果经验不足返回 false, 否则返回 true
	if (exp < value)
	{
		return false;
	}
	exp -= value;
	return true;
}

std::vector<Skill> CharacterManager::get_player_available_skills(int count)
{
	return player_skills->get_available_skills(count);
}

bool CharacterManager::add_skill(SkillID id)
{
	if (exp < player_skills->find_skill(id).get_cost())
	{
		return false;
	}
	exp -= player_skills->find_skill(id).get_cost();
	player_skills->add_skill(id);
	return true;
}

int CharacterManager::get_skill_level(SkillID id)
{
	return player_skills->get_skill_level(id);
}

CharacterManager::CharacterManager()
{
	player_skills = global_player_skills;
	// (int attack, int health, float attack_cd, int move_speed, int bullet_speed)
	character_properties[EnemyType::Jinn] = new CharacterBaseProperty(5, 10, 8.0f, 100, 100);
	character_properties[EnemyType::LesserVampire] = new CharacterBaseProperty(10, 10, 5.0f, 180, 160);
	character_properties[EnemyType::ElderVampire] = new CharacterBaseProperty(12, 10, 5.0f, 200, 175);
	character_properties[EnemyType::ElderOfShadow] = new CharacterBaseProperty(12, 10, 7.0f, 240, 175);
	character_properties[EnemyType::Dragon] = new CharacterBaseProperty(20, 1000, 10.0f, 0, 450);
}

CharacterManager::~CharacterManager()
{
	if (player)
	{
		delete player;
		player = nullptr;
	}
	for (Enemy* enemy : enemies)
	{
		delete enemy;
	}
	enemies.clear();

	for (auto& pair : character_properties)
	{
		delete pair.second;
	}
	character_properties.clear();
}