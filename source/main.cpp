#include <iostream>
#include <chrono>
#include <thread>
#include <graphics.h>
#include <windows.h>

#include "util.h"
#include "resources_manager.h"
#include "collision_manager.h"
#include "character_manager.h"
#include "scene_manager.h"

#include "scene_homepage.h"
#include "scene_level.h"
#include "scene_skillselect.h"
#include "scene_gamewin.h"

const float default_fire_duration = 3;
const float default_poison_duration = 10;
const float default_ice_duration = 10;
const int default_fire_damage_amount = 1;

const float default_fire_damage_frequency = 0.5;
const float default_poison_damage_frequency = 1;

SkillList* global_player_skills = nullptr;

bool is_on_debug = true;

using namespace std;

static void draw_background()
{
	static IMAGE* img_background = ResourcesManager::instance()->find_image("background");
	static Rect rect_dst = {
		(getwidth() - img_background->getwidth()) / 2,
		(getheight() - img_background->getheight()) / 2,
		img_background->getwidth(),
		img_background->getheight()
	};
	putimage_ex(img_background, &rect_dst);
}

// 初始化 scene_manager
void init_scenes();

//int main()
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	std::srand(std::time(nullptr));
	HWND hwnd = initgraph(1280, 720, 0);
	std::wstring title = L"Odyssey of Dragonfall";
	SetWindowTextW(hwnd, title.c_str());

	try
	{
		ResourcesManager::instance()->load();
	}
	catch (const LPCTSTR id)
	{
		TCHAR err_msg[512];
		_stprintf_s(err_msg, _T("加载资源失败 %s"), id);
		MessageBox(hwnd, err_msg, _T("加载资源失败"), MB_OK | MB_ICONERROR);
		return -1;
	}

	//play_audio(_T("bgm"), true);

	const std::chrono::nanoseconds frame_duration(1000000000 / 144);
	std::chrono::steady_clock::time_point last_tick = std::chrono::steady_clock::now();

	ExMessage msg;
	bool is_quit = false;

	init_scenes();
	global_player_skills = new SkillList();

	BeginBatchDraw();

	while (!is_quit)
	{
		while (peekmessage(&msg))
		{
			if (msg.message == WM_KEYDOWN && msg.vkcode == VK_F1)
			{
				is_on_debug = !is_on_debug;
			}
			SceneManager::instance()->on_input(msg);
		}

		std::chrono::steady_clock::time_point frame_start = std::chrono::steady_clock::now();
		std::chrono::duration<float> delta = std::chrono::duration<float>(frame_start - last_tick);
		//std::cout << 3 << "\n";

		SceneManager::instance()->on_update(delta.count());
		//std::cout << "Collision processed update end" << std::endl;

		setbkcolor(RGB(0, 0, 0));
		cleardevice();
		//std::cout << 3.5 << "\n";

		//draw_background();
		SceneManager::instance()->on_render();
		//std::cout << "render processed update end" << std::endl;

		FlushBatchDraw();
		//std::cout << 4 << "\n";

		last_tick = frame_start;
		std::chrono::nanoseconds sleep_duration = frame_duration - (std::chrono::steady_clock::now() - frame_start);
		CharacterManager::instance()->get_player();
		if (sleep_duration > std::chrono::nanoseconds(0))
		{
			std::this_thread::sleep_for(sleep_duration);
		}
		//std::cout << "main loop one circle end" << std::endl;
		//std::cout << 5 << "\n";
	}
	EndBatchDraw();
	delete global_player_skills;
	return 0;
}

void init_scenes()
{
	SceneManager* scene_manager = SceneManager::instance();
	scene_manager->register_state("homepage", new SceneHomepage());
	scene_manager->register_state("level", new SceneLevel());
	scene_manager->register_state("skill_select", new SceneSkillSelect());
	scene_manager->register_state("gamewin", new SceneGamewin());
	scene_manager->set_entry("homepage");
}
