#ifndef _GAME_SCENE_H_
#define _GAME_SCENE_H_

#include <graphics.h>
#include "state_node.h"
#include "resources_manager.h"
#include "gameflow.h"
#include "music_manager.h"

class GameScene : public StateNode
{
protected:
	IMAGE* img_background = nullptr;
	Rect rect_dst = { 0, 0, 0, 0 };
public:
	virtual void on_render() 
	{
		putimage_ex(img_background, &rect_dst);
	};
	virtual void on_input(ExMessage msg) {};
	void on_update(float delta) override;

	GameScene() = default;
	~GameScene() = default;
};

#endif