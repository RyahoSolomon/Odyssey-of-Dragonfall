#ifndef _GAMEFLOW_H_
#define _GAMEFLOW_H_

#include <string>
#include "level_config.h"

enum class SceneType
{
    HomePage,
    Level,
    SkillSelect,
    GameWin,
    GameLose
};

std::string type_to_string(SceneType type);

struct SceneTransition
{
    bool has_request = false;
    SceneType next_scene = SceneType::HomePage;
    int level_index = 0;
};

class GameFlow
{
private:
    int current_level = 0;

    std::vector<LevelConfig> level_config;

public:
    // 每个关卡过后的
    SceneTransition next_after_level();
    // 下一关是关卡, 则调用这个
    SceneTransition next_after_selection();
    void reset();
    int get_level() const;

    static GameFlow* instance();
    static GameFlow* game_flow;

    GameFlow();

    LevelConfig* get_current_level_config();
};

#endif // !_GAMEFLOW_H_
