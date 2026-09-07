#include "scene_homepage.h"

SceneHomepage::SceneHomepage()
{
	img_background = ResourcesManager::instance()->find_image("background_homepage");
	rect_dst = 
	{
		 (getwidth() - img_background->getwidth()) / 2,
		 (getheight() - img_background->getheight()) / 2,
		 img_background->getwidth(),
		 img_background->getheight()
	};
}

void SceneHomepage::on_enter()
{
	CharacterManager::instance()->reset();
	std::vector<std::string> bgm = { R"(assets\music\[homepage]tale_of_the_tongues.mp3)" };
	MusicManager::instance()->set_playlist(bgm);
}

void SceneHomepage::on_update(float delta)
{
	GameScene::on_update(delta);
}

void SceneHomepage::on_exit()
{
}

void SceneHomepage::on_render()
{
	GameScene::on_render();
}

void SceneHomepage::on_input(ExMessage msg)
{
	if (msg.message == WM_KEYDOWN)
	{
		GameFlow::instance()->next_after_selection();
		SceneManager::instance()->switch_to("level");
	};
}
