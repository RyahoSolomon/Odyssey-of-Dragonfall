#include "gameflow.h"

GameFlow* GameFlow::game_flow = nullptr;

SceneTransition GameFlow::next_after_level()
{
    SceneTransition t;
    t.has_request = true;
    if (current_level == 10)
    {
        t.next_scene = SceneType::GameWin;
    }
    else
    {
        t.next_scene = SceneType::SkillSelect;
    }

    t.level_index = current_level;
    return t;
}

SceneTransition GameFlow::next_after_selection()
{
    current_level++;

    SceneTransition t;
    t.has_request = true;
    t.next_scene = SceneType::Level;
    t.level_index = current_level;
    return t;
}

int GameFlow::get_level() const 
{ 
    return current_level; 

}

void GameFlow::reset()
{
    current_level = 0;
}

GameFlow* GameFlow::instance()
{
    if (game_flow == nullptr)
    {
        game_flow = new GameFlow();
    }
    return game_flow;
}

GameFlow::GameFlow()
{
    // Amplifier(float rate_health, float rate_attack, float rate_cd, float rate_move_speed, float rate_bullet_speed
    // Level 1
    Amplifier amplifier(1.0, 1.0, 1.0, 1.0, 1.0);
    level_config.push_back(LevelConfig(amplifier, 24));
    level_config[level_config.size() - 1].set_background(ResourcesManager::instance()->find_image("scene_grassland"));

    EnemyGroup enemy_group;
    enemy_group.add_enemy(EnemyType::Jinn);
    enemy_group.add_enemy(EnemyType::Jinn);
    level_config[level_config.size() - 1].add_enemy_group(enemy_group);

    level_config[level_config.size() - 1].add_wave(1, 5);
    level_config[level_config.size() - 1].add_wave(1, 10);
    level_config[level_config.size() - 1].add_wave(2, 10);

    level_config[level_config.size() - 1].add_bgm(R"(assets\music\[scene_grassland]the_silver_sisters.mp3)");

    // Level 2
    amplifier = Amplifier(1.2, 1.0, 1.0, 1.0, 1.0);
    level_config.push_back(LevelConfig(amplifier, 24));
    level_config[level_config.size() - 1].set_background(ResourcesManager::instance()->find_image("scene_grassland"));

    enemy_group = EnemyGroup();
    enemy_group.add_enemy(EnemyType::Jinn);
    enemy_group.add_enemy(EnemyType::Jinn);
    level_config[level_config.size() - 1].add_enemy_group(enemy_group);
    enemy_group = EnemyGroup();
    enemy_group.add_enemy(EnemyType::LesserVampire);
    level_config[level_config.size() - 1].add_enemy_group(enemy_group);

    level_config[level_config.size() - 1].add_wave(1, 5);
    level_config[level_config.size() - 1].add_wave(2, 10);
    level_config[level_config.size() - 1].add_wave(2, 18);
    level_config[level_config.size() - 1].add_wave(3, 18);

    level_config[level_config.size() - 1].add_bgm(R"(assets\music\[scene_grassland]the_silver_sisters.mp3)");

    // Level 3
    amplifier = Amplifier(1.5, 1.0, 1.0, 1.0, 1.0);
    level_config.push_back(LevelConfig(amplifier, 28));
    level_config[level_config.size() - 1].set_background(ResourcesManager::instance()->find_image("scene_desert"));

    enemy_group = EnemyGroup();
    enemy_group.add_enemy(EnemyType::Jinn);
    enemy_group.add_enemy(EnemyType::Jinn);
    enemy_group.add_enemy(EnemyType::Jinn);
    level_config[level_config.size() - 1].add_enemy_group(enemy_group);
    enemy_group = EnemyGroup();
    enemy_group.add_enemy(EnemyType::Jinn);
    enemy_group.add_enemy(EnemyType::LesserVampire);
    level_config[level_config.size() - 1].add_enemy_group(enemy_group);

    level_config[level_config.size() - 1].add_wave(1, 5);
    level_config[level_config.size() - 1].add_wave(2, 10);
    level_config[level_config.size() - 1].add_wave(2, 15);
    level_config[level_config.size() - 1].add_wave(3, 18);
    level_config[level_config.size() - 1].add_wave(4, 20);

    level_config[level_config.size() - 1].add_bgm(R"(assets\music\[scene_desert]memories_of_dust.mp3)");

    // Level 4
    amplifier = Amplifier(1.5, 1.2, 1.0, 1.0, 1.0);
    level_config.push_back(LevelConfig(amplifier, 28));
    level_config[level_config.size() - 1].set_background(ResourcesManager::instance()->find_image("scene_desert"));

    enemy_group = EnemyGroup();
    enemy_group.add_enemy(EnemyType::Jinn);
    enemy_group.add_enemy(EnemyType::ElderVampire);
    level_config[level_config.size() - 1].add_enemy_group(enemy_group);
    enemy_group = EnemyGroup();
    enemy_group.add_enemy(EnemyType::Jinn);
    enemy_group.add_enemy(EnemyType::Jinn);
    enemy_group.add_enemy(EnemyType::LesserVampire);
    level_config[level_config.size() - 1].add_enemy_group(enemy_group);
    enemy_group = EnemyGroup();
    enemy_group.add_enemy(EnemyType::LesserVampire);
    enemy_group.add_enemy(EnemyType::LesserVampire);
    level_config[level_config.size() - 1].add_enemy_group(enemy_group);

    level_config[level_config.size() - 1].add_wave(1, 5);
    level_config[level_config.size() - 1].add_wave(2, 10);
    level_config[level_config.size() - 1].add_wave(2, 20);
    level_config[level_config.size() - 1].add_wave(3, 20);
    level_config[level_config.size() - 1].add_wave(4, 25);

    level_config[level_config.size() - 1].add_bgm(R"(assets\music\[scene_desert]memories_of_dust.mp3)");

    // Level 5
    amplifier = Amplifier(2.0, 1.2, 1.0, 1.0, 1.0);
    level_config.push_back(LevelConfig(amplifier, 32));
    level_config[level_config.size() - 1].set_background(ResourcesManager::instance()->find_image("scene_badland"));

    enemy_group = EnemyGroup();
    enemy_group.add_enemy(EnemyType::Jinn);
    enemy_group.add_enemy(EnemyType::Jinn);
    enemy_group.add_enemy(EnemyType::Jinn);
    enemy_group.add_enemy(EnemyType::Jinn);
    level_config[level_config.size() - 1].add_enemy_group(enemy_group);
    enemy_group = EnemyGroup();
    enemy_group.add_enemy(EnemyType::Jinn);
    enemy_group.add_enemy(EnemyType::Jinn);
    enemy_group.add_enemy(EnemyType::ElderVampire);
    level_config[level_config.size() - 1].add_enemy_group(enemy_group);
    enemy_group = EnemyGroup();
    enemy_group.add_enemy(EnemyType::LesserVampire);
    enemy_group.add_enemy(EnemyType::ElderVampire);
    level_config[level_config.size() - 1].add_enemy_group(enemy_group);

    level_config[level_config.size() - 1].add_wave(1, 5);
    level_config[level_config.size() - 1].add_wave(2, 10);
    level_config[level_config.size() - 1].add_wave(2, 20);
    level_config[level_config.size() - 1].add_wave(3, 20);
    level_config[level_config.size() - 1].add_wave(4, 25);
    level_config[level_config.size() - 1].add_wave(4, 32);

    level_config[level_config.size() - 1].add_bgm(R"(assets\music\[scene_badland]factured_shrines.mp3)");

    // Level 6
    amplifier = Amplifier(2.0, 1.2, 0.9, 1.0, 1.0);
    level_config.push_back(LevelConfig(amplifier, 32));
    level_config[level_config.size() - 1].set_background(ResourcesManager::instance()->find_image("scene_badland"));

    enemy_group = EnemyGroup();
    enemy_group.add_enemy(EnemyType::Jinn);
    enemy_group.add_enemy(EnemyType::Jinn);
    enemy_group.add_enemy(EnemyType::Jinn);
    enemy_group.add_enemy(EnemyType::Jinn);
    enemy_group.add_enemy(EnemyType::Jinn);
    level_config[level_config.size() - 1].add_enemy_group(enemy_group);
    enemy_group = EnemyGroup();
    enemy_group.add_enemy(EnemyType::Jinn);
    enemy_group.add_enemy(EnemyType::Jinn);
    enemy_group.add_enemy(EnemyType::ElderVampire);
    enemy_group.add_enemy(EnemyType::ElderVampire);
    level_config[level_config.size() - 1].add_enemy_group(enemy_group);
    enemy_group = EnemyGroup();
    enemy_group.add_enemy(EnemyType::Jinn);
    enemy_group.add_enemy(EnemyType::LesserVampire);
    enemy_group.add_enemy(EnemyType::ElderVampire);
    level_config[level_config.size() - 1].add_enemy_group(enemy_group);
    enemy_group = EnemyGroup();
    enemy_group.add_enemy(EnemyType::ElderVampire);
    enemy_group.add_enemy(EnemyType::ElderVampire);
    level_config[level_config.size() - 1].add_enemy_group(enemy_group);

    level_config[level_config.size() - 1].add_wave(1, 5);
    level_config[level_config.size() - 1].add_wave(2, 10);
    level_config[level_config.size() - 1].add_wave(2, 18);
    level_config[level_config.size() - 1].add_wave(3, 18);
    level_config[level_config.size() - 1].add_wave(4, 24);
    level_config[level_config.size() - 1].add_wave(4, 36);

    level_config[level_config.size() - 1].add_bgm(R"(assets\music\[scene_badland]factured_shrines.mp3)");

    // Level 7
    amplifier = Amplifier(2.5, 1.2, 0.85, 1.0, 1.0);
    level_config.push_back(LevelConfig(amplifier, 36));
    level_config[level_config.size() - 1].set_background(ResourcesManager::instance()->find_image("scene_death"));

    enemy_group = EnemyGroup();
    enemy_group.add_enemy(EnemyType::LesserVampire);
    enemy_group.add_enemy(EnemyType::LesserVampire);
    enemy_group.add_enemy(EnemyType::LesserVampire);
    level_config[level_config.size() - 1].add_enemy_group(enemy_group);
    enemy_group = EnemyGroup();
    enemy_group.add_enemy(EnemyType::ElderVampire);
    enemy_group.add_enemy(EnemyType::LesserVampire);
    enemy_group.add_enemy(EnemyType::LesserVampire);
    level_config[level_config.size() - 1].add_enemy_group(enemy_group);
    enemy_group = EnemyGroup();
    enemy_group.add_enemy(EnemyType::ElderVampire);
    enemy_group.add_enemy(EnemyType::ElderVampire);
    level_config[level_config.size() - 1].add_enemy_group(enemy_group);
    enemy_group = EnemyGroup();
    enemy_group.add_enemy(EnemyType::ElderOfShadow);
    level_config[level_config.size() - 1].add_enemy_group(enemy_group);

    level_config[level_config.size() - 1].add_wave(2, 5);
    level_config[level_config.size() - 1].add_wave(3, 16);
    level_config[level_config.size() - 1].add_wave(4, 23);
    level_config[level_config.size() - 1].add_wave(4, 27);
    level_config[level_config.size() - 1].add_wave(5, 36);

    level_config[level_config.size() - 1].add_bgm(R"(assets\music\[scene_death]a_closer_understanding_of_the_past.mp3)");

    // Level 8
    amplifier = Amplifier(2.5, 1.5, 0.80, 1.0, 1.0);
    level_config.push_back(LevelConfig(amplifier, 36));
    level_config[level_config.size() - 1].set_background(ResourcesManager::instance()->find_image("scene_death"));

    enemy_group = EnemyGroup();
    enemy_group.add_enemy(EnemyType::LesserVampire);
    enemy_group.add_enemy(EnemyType::LesserVampire);
    enemy_group.add_enemy(EnemyType::LesserVampire);
    enemy_group.add_enemy(EnemyType::LesserVampire);
    level_config[level_config.size() - 1].add_enemy_group(enemy_group);
    enemy_group = EnemyGroup();
    enemy_group.add_enemy(EnemyType::ElderVampire);
    enemy_group.add_enemy(EnemyType::ElderVampire);
    enemy_group.add_enemy(EnemyType::LesserVampire);
    level_config[level_config.size() - 1].add_enemy_group(enemy_group);
    enemy_group = EnemyGroup();
    enemy_group.add_enemy(EnemyType::ElderVampire);
    enemy_group.add_enemy(EnemyType::ElderVampire);
    enemy_group.add_enemy(EnemyType::LesserVampire);
    level_config[level_config.size() - 1].add_enemy_group(enemy_group);
    enemy_group = EnemyGroup();
    enemy_group.add_enemy(EnemyType::ElderOfShadow);
    enemy_group.add_enemy(EnemyType::LesserVampire);
    level_config[level_config.size() - 1].add_enemy_group(enemy_group);

    level_config[level_config.size() - 1].add_wave(3, 5);
    level_config[level_config.size() - 1].add_wave(3, 24);
    level_config[level_config.size() - 1].add_wave(4, 28);
    level_config[level_config.size() - 1].add_wave(4, 32);
    level_config[level_config.size() - 1].add_wave(5, 36);

    level_config[level_config.size() - 1].add_bgm(R"(assets\music\[scene_death]a_closer_understanding_of_the_past.mp3)");

    // Level 9
    amplifier = Amplifier(3.0, 1.5, 0.75, 1.0, 1.0);
    level_config.push_back(LevelConfig(amplifier, 45));
    level_config[level_config.size() - 1].set_background(ResourcesManager::instance()->find_image("scene_snowfield"));

    enemy_group = EnemyGroup();
    enemy_group.add_enemy(EnemyType::ElderVampire);
    enemy_group.add_enemy(EnemyType::ElderVampire);
    enemy_group.add_enemy(EnemyType::ElderVampire);
    level_config[level_config.size() - 1].add_enemy_group(enemy_group);
    enemy_group = EnemyGroup();
    enemy_group.add_enemy(EnemyType::LesserVampire);
    enemy_group.add_enemy(EnemyType::LesserVampire);
    enemy_group.add_enemy(EnemyType::LesserVampire);
    enemy_group.add_enemy(EnemyType::ElderVampire);
    enemy_group.add_enemy(EnemyType::ElderVampire);
    level_config[level_config.size() - 1].add_enemy_group(enemy_group);
    enemy_group = EnemyGroup();
    enemy_group.add_enemy(EnemyType::ElderOfShadow);
    enemy_group.add_enemy(EnemyType::ElderVampire);
    enemy_group.add_enemy(EnemyType::ElderVampire);
    level_config[level_config.size() - 1].add_enemy_group(enemy_group);

    level_config[level_config.size() - 1].add_wave(3, 5);
    level_config[level_config.size() - 1].add_wave(3, 20);
    level_config[level_config.size() - 1].add_wave(4, 24);
    level_config[level_config.size() - 1].add_wave(4, 30);
    level_config[level_config.size() - 1].add_wave(6, 30);

    level_config[level_config.size() - 1].add_bgm(R"(assets\music\[scene_snowfield]light_of_nibel.mp3)");

    // Level 10
    amplifier = Amplifier(5.0, 2.0, 0.75, 1.0, 1.0);
    level_config.push_back(LevelConfig(amplifier, 114));
    level_config[level_config.size() - 1].set_background(ResourcesManager::instance()->find_image("scene_snowfield"));

    enemy_group = EnemyGroup();
    enemy_group.add_enemy(EnemyType::ElderOfShadow);
    enemy_group.add_enemy(EnemyType::ElderVampire);
    enemy_group.add_enemy(EnemyType::ElderVampire);
    level_config[level_config.size() - 1].add_enemy_group(enemy_group);
    enemy_group = EnemyGroup();
    enemy_group.add_enemy(EnemyType::LesserVampire);
    enemy_group.add_enemy(EnemyType::LesserVampire);
    enemy_group.add_enemy(EnemyType::LesserVampire);
    enemy_group.add_enemy(EnemyType::ElderVampire);
    enemy_group.add_enemy(EnemyType::ElderVampire);
    enemy_group.add_enemy(EnemyType::ElderVampire);
    level_config[level_config.size() - 1].add_enemy_group(enemy_group);
    enemy_group = EnemyGroup();
    enemy_group.add_enemy(EnemyType::ElderOfShadow);
    enemy_group.add_enemy(EnemyType::LesserVampire);
    enemy_group.add_enemy(EnemyType::LesserVampire);
    enemy_group.add_enemy(EnemyType::LesserVampire);
    enemy_group.add_enemy(EnemyType::LesserVampire);
    level_config[level_config.size() - 1].add_enemy_group(enemy_group);

    level_config[level_config.size() - 1].add_wave(3, 5);
    level_config[level_config.size() - 1].add_wave(4, 25);
    level_config[level_config.size() - 1].add_wave(4, 25);
    level_config[level_config.size() - 1].add_wave(5, 32);
    level_config[level_config.size() - 1].add_wave(7, 36);

    level_config[level_config.size() - 1].add_bgm(R"(assets\music\[scene_snowfield]light_of_nibel.mp3)");

    level_config[level_config.size() - 1].set_boss(EnemyType::Dragon);
}

LevelConfig* GameFlow::get_current_level_config()
{
    return &level_config[current_level - 1];
}

std::string type_to_string(SceneType type)
{
    std::string str_type = "invalid";
    switch (type)
    {
    case SceneType::HomePage:
        str_type = "homepage";
        break;
    case SceneType::Level:
        str_type = "level";
        break;
    case SceneType::SkillSelect:
        str_type = "skill_select";
        break;
    case SceneType::GameWin:
        str_type = "game_win";
        break;
    case SceneType::GameLose:
        str_type = "game_lose";
        break;
    };
    return str_type;
};
