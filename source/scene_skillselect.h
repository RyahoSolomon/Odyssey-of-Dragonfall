#ifndef _SCENE_SKILLSELECT_H_
#define _SCENE_SKILLSELECT_H_

#include "game_scene.h"
#include "character_manager.h"
#include "scene_manager.h"

class SceneSkillSelect : public GameScene
{
public:
	void on_enter() override;
	void on_update(float delta) override;
	void on_exit() override;
	void on_render() override;
	void on_input(ExMessage msg) override;

	SceneSkillSelect();
	~SceneSkillSelect() = default;
protected:
	Vector2d position_cursor;

	IMAGE* img_bar = nullptr;

	IMAGE* img_button = nullptr;
	IMAGE* img_button_hover = nullptr;
	IMAGE* img_button_unable = nullptr;

	IMAGE* img_icon_frame = nullptr;

	IMAGE* img_button_refresh = nullptr;
	IMAGE* img_button_refresh_hover = nullptr;
	IMAGE* img_button_refresh_unable = nullptr;
	IMAGE* img_button_next_level = nullptr;
	IMAGE* img_button_next_level_hover = nullptr;

	IMAGE* img_exp48 = nullptr;
	std::vector<Skill> skills_display;

	void refresh();

	bool is_available[12] = { false, false, false, false, false, false, false, false, false, false, false, false };
};

#endif // !_SCENE_SKILLSELECT_H_
