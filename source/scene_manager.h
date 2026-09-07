#ifndef _SCENE_MANAGER_H_
#define _SCENE_MANAGER_H_

#include "state_machine.h"
#include "gameflow.h"
#include "game_scene.h"

class SceneManager : public StateMachine
{
	// TODO, 如果后续测试这么写不行, 就复制 StateMachine 的代码过来, 把 StateNode 都改为 GameScene, 然后再把 input 和 render 方法加上
	GameScene* current_scene = nullptr;
public:
	void on_render();
	void on_input(ExMessage msg);
	void switch_to(const std::string& id) override;
	void set_entry(const std::string& id) override;

	static SceneManager* instance();
	static SceneManager* scene_manager;
};

#endif