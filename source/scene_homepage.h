#ifndef _SCENE_HOMEPAGE_H_
#define _SCENE_HOMEPAGE_H_

#include "game_scene.h"
#include "scene_manager.h"
#include "character_manager.h"

class SceneHomepage : public GameScene
{
public:
	void on_enter() override;
	void on_update(float delta) override;
	void on_exit() override;
	void on_render() override;
	void on_input(ExMessage msg) override;

	SceneHomepage();
	~SceneHomepage() = default;

private:
};

#endif // !_SCENE_HOMEPAGE_H_
