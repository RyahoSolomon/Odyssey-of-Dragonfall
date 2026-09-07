#include "scene_manager.h"

SceneManager* SceneManager::scene_manager = nullptr;

void SceneManager::on_render()
{
	current_scene->on_render();
}

void SceneManager::on_input(ExMessage msg)
{
	current_scene->on_input(msg);
}

void SceneManager::switch_to(const std::string& id)
{
	StateMachine::switch_to(id);
	current_scene = dynamic_cast<GameScene*>(current_state);
}

void SceneManager::set_entry(const std::string& id)
{
	StateMachine::set_entry(id);
	current_scene = dynamic_cast<GameScene*>(current_state);
}

SceneManager* SceneManager::instance()
{
	if (scene_manager == nullptr)
	{
		scene_manager = new SceneManager();
	}
	return scene_manager;
}