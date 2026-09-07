#include "scene_gamewin.h"

void SceneGamewin::on_enter()
{
	CharacterManager::instance()->reset();
	GameFlow::instance()->reset();
	MusicManager::instance()->set_playlist({ R"(assets\music\[gamewin]catch_me.mp3)" });
}

void SceneGamewin::on_update(float delta)
{
	GameScene::on_update(delta);
}

void SceneGamewin::on_exit()
{
}

void SceneGamewin::on_render()
{
	Rect rect_ui = { 0, 0, getwidth(), getheight() };
	putimage_ex(img_background, &rect_ui);
}

void SceneGamewin::on_input(ExMessage msg)
{
	switch (msg.message)
	{
	case WM_KEYDOWN:
		SceneManager::instance()->switch_to("homepage");
		break;
	}
}

SceneGamewin::SceneGamewin()
{
	img_background = ResourcesManager::instance()->find_image("background_gamewin");
}
