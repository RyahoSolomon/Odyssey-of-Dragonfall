#include "level_config.h"

std::vector<EnemyType> EnemyGroup::get_enemies() const
{
    return enemies;
}

void EnemyGroup::add_enemy(EnemyType enemy)
{
    enemies.push_back(enemy);
}

Amplifier::Amplifier(float rate_health, float rate_attack, float rate_cd, float rate_move_speed, float rate_bullet_speed) : 
    health_amplify_rate(rate_health), attack_amplify_rate(rate_attack), cd_amplify_rate(rate_cd), move_speed_amplify_rate(rate_move_speed), bullet_speed_amplify_rate(rate_bullet_speed)
{
}

Amplifier::~Amplifier()
{
}

int Amplifier::amplify_health(int original_health) const
{
    return original_health * health_amplify_rate;
}

int Amplifier::amplify_attack(int original_attack) const
{
    return original_attack * attack_amplify_rate;
}

float Amplifier::amplify_cd(float original_cd) const
{
    return original_cd * cd_amplify_rate;
}

int Amplifier::amplify_move_speed(int original_move_speed) const
{
    return original_move_speed * move_speed_amplify_rate;
}

int Amplifier::amplify_bullet_speed(int original_bullet_speed) const
{
    return original_bullet_speed * bullet_speed_amplify_rate;
}

std::vector<int> LevelConfig::get_timer_waves() const
{
    return duration_waves;
}

std::vector<Enemy*> LevelConfig::summon_enemy(int wave) const
{
    std::vector<Enemy*> result;

    // TODO: 后续可以把 property 的 key 改为 EnemyType, 便于映射

    for (int i = 0; i < nums_enemy_group[wave]; i++)
    {
        int index = range_random(0, enemy_pool.size() - 1);
        std::vector<EnemyType> enemy_group = enemy_pool[index].get_enemies();
        CharacterBaseProperty* property = nullptr;
        for (EnemyType enemy_type : enemy_group)
        {
            Enemy* enemy = nullptr;
            Vector2d enemy_spawn_position = { double(range_random(1280, 1280 + ENEMY_SPAWN_AREA_WIDTH)), double(range_random(0, 720)) };
            property = CharacterManager::instance()->get_character_base_property(enemy_type);
            switch (enemy_type)
            {
            case EnemyType::Jinn:
                enemy = new Jinn(
                    amplifier.amplify_health(property->health),
                    amplifier.amplify_attack(property->attack),
                    amplifier.amplify_cd(property->attack_cd),
                    amplifier.amplify_move_speed(property->move_speed),
                    amplifier.amplify_bullet_speed(property->bullet_speed)
                    );
                break;
            case EnemyType::LesserVampire:
                enemy = new LesserVampire(
                    amplifier.amplify_health(property->health),
                    amplifier.amplify_attack(property->attack),
                    amplifier.amplify_cd(property->attack_cd),
                    amplifier.amplify_move_speed(property->move_speed),
                    amplifier.amplify_bullet_speed(property->bullet_speed)
                );
                break;
            case EnemyType::ElderVampire:
                enemy = new ElderVampire(
                    amplifier.amplify_health(property->health),
                    amplifier.amplify_attack(property->attack),
                    amplifier.amplify_cd(property->attack_cd),
                    amplifier.amplify_move_speed(property->move_speed),
                    amplifier.amplify_bullet_speed(property->bullet_speed)
                );
                break;
            case EnemyType::ElderOfShadow:
                enemy = new ElderOfShadow(
                    amplifier.amplify_health(property->health),
                    amplifier.amplify_attack(property->attack),
                    amplifier.amplify_cd(property->attack_cd),
                    amplifier.amplify_move_speed(property->move_speed),
                    amplifier.amplify_bullet_speed(property->bullet_speed)
                );
                break;
            default:
                enemy = new Jinn(
                    amplifier.amplify_health(property->health),
                    amplifier.amplify_attack(property->attack),
                    amplifier.amplify_cd(property->attack_cd),
                    amplifier.amplify_move_speed(property->move_speed),
                    amplifier.amplify_bullet_speed(property->bullet_speed)
                );
                break;
            }
            enemy->set_position(enemy_spawn_position);
            result.push_back(enemy);
        }
    }
    return result;
}

Enemy* LevelConfig::create_boss()
{
    Enemy* enemy = nullptr;
    EnemyType type = boss;
    Vector2d position = { 0, 0 };
    CharacterBaseProperty* property = CharacterManager::instance()->get_character_base_property(boss);
    if (type == EnemyType::Dragon)
    {
        enemy = new Dragon(
            amplifier.amplify_health(property->health),
            amplifier.amplify_attack(property->attack),
            amplifier.amplify_cd(property->attack_cd),
            amplifier.amplify_move_speed(property->move_speed),
            amplifier.amplify_bullet_speed(property->bullet_speed)
        );
        position.x = getwidth() - enemy->get_hurt_box()->get_size().x / 2;
        position.y = enemy->get_hurt_box()->get_size().y / 2;
    }
    enemy->set_position(position);
    return enemy;
}

LevelConfig::LevelConfig(Amplifier amplifier, int exp) : amplifier(amplifier), exp(exp)
{
}

LevelConfig::~LevelConfig()
{
}

IMAGE* LevelConfig::get_background() const
{
    return background;
}

void LevelConfig::set_background(IMAGE* img)
{
    background = img;
}

void LevelConfig::add_enemy_group(EnemyGroup enemy_group)
{
    enemy_pool.push_back(enemy_group);
}

void LevelConfig::add_wave(int num_enemy_group, int duration_wave)
{
    nums_enemy_group.push_back(num_enemy_group);
    duration_waves.push_back(duration_wave);
}

int LevelConfig::get_exp() const
{
    return exp;
}

void LevelConfig::set_boss(EnemyType type)
{
    boss = type;
}

EnemyType LevelConfig::get_boss() const
{
    return boss;
}

void LevelConfig::add_bgm(std::string name)
{
    bgm.push_back(name);
}

std::vector<std::string> LevelConfig::get_bgm() const
{
    return bgm;
}
