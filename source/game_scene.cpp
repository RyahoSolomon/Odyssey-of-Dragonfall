#include "game_scene.h"

void GameScene::on_update(float delta)
{
	MusicManager::instance()->on_update(delta);
}
