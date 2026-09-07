#ifndef _SCENE_GAMEWIN_H_
#define _SCENE_GAMEWIN_H_

#include "game_scene.h"
#include "character_manager.h"
#include "scene_manager.h"

class SceneGamewin : public GameScene
{
public:
	void on_enter() override;
	void on_update(float delta) override;
	void on_exit() override;
	void on_render() override;
	void on_input(ExMessage msg) override;

	SceneGamewin();
	~SceneGamewin() = default;
protected:

	IMAGE* img_background = nullptr;
};
#endif // !_SCENE_GAMEWIN_H_
