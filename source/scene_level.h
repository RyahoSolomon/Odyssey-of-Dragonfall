#ifndef _SCENE_LEVEL_H_
#define _SCENE_LEVEL_H_

#define HEALTH_BAR_WIDTH 256
#define HEALTH_BAR_HEIGHT 20

#include <sstream>

#include "game_scene.h"
#include "character_manager.h"
#include "scene_manager.h"
#include "enemy_types.h"

extern bool is_on_debug;

class SceneLevel : public GameScene
{
public:
	void on_enter() override;
	void on_update(float delta) override;
	void on_exit() override;
	void on_render() override;
	void on_input(ExMessage msg) override;

	void switch_to_death_scene();

	SceneLevel();
	~SceneLevel() = default;

	IMAGE* img_ui_bar = nullptr;
	IMAGE* img_wave_bar = nullptr;

	int current_wave = 0;
	std::vector<Timer> timer_waves;

protected:
	LevelConfig* level_config = nullptr;

	bool is_boss_defeated = true;
	bool is_player_dead = false;

	std::vector<std::string> bgm;
	std::vector<std::string> bgm_boss;
};

#endif // !_SCENE_LEVEL_H_
