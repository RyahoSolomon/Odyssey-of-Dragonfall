#include "scene_level.h"

void SceneLevel::on_enter()
{
	CharacterManager::instance()->init_characters();
	Player* player = (Player*)CharacterManager::instance()->get_player();

	current_wave = 0;
	level_config = GameFlow::instance()->get_current_level_config();
	img_background = level_config->get_background();
	if (CharacterManager::instance()->get_skill_level(SkillID::WenCuiBackground)) img_background = ResourcesManager::instance()->find_image("scene_wencui");
	std::vector<int> duration_waves = level_config->get_timer_waves();
	for (int i = 0; i < duration_waves.size(); i++)
	{
		Timer timer;
		timer.set_one_shot(true);
		timer.set_wait_time(duration_waves[i]);
		timer.set_on_timeout([cw = &current_wave, lc = level_config]()
			{
				std::vector<Enemy*> enemies_wave = lc->summon_enemy(*cw);
				for (Enemy* enemy_wave : enemies_wave)
				{
					CharacterManager::instance()->add_enemy(enemy_wave);
				}
				(*cw)++;
			});
		timer_waves.push_back(timer);
	}

	if (level_config->get_boss() == EnemyType::None)
	{
		is_boss_defeated = true;
	}
	else
	{
		is_boss_defeated = false;
	}

	if (bgm != level_config->get_bgm())
	{
		bgm = level_config->get_bgm();
		MusicManager::instance()->set_playlist(bgm);
	}
}

void SceneLevel::on_update(float delta)
{
	CharacterManager::instance()->on_update(delta);
	if (CharacterManager::instance()->get_player()->get_hp() > 0)
	{
		CollisionManager::instance()->process_collide();
		ProjectileManager::instance()->on_update(delta);
	}

	if (current_wave < timer_waves.size())
	{
		timer_waves[current_wave].on_update(delta);
	}
	else if (CharacterManager::instance()->is_all_enemy_dead())
	{
		if (is_boss_defeated)
		{
			SceneTransition transition = GameFlow::instance()->next_after_level();
			if (transition.next_scene == SceneType::SkillSelect)
			{
				CharacterManager::instance()->add_exp(level_config->get_exp());
				SceneManager::instance()->switch_to("skill_select");
			}
			else if (transition.has_request && transition.next_scene == SceneType::GameWin)
			{
				SceneManager::instance()->switch_to("gamewin");
			}
		}
		else
		{
			is_boss_defeated = true;
			Enemy* boss = level_config->create_boss();
			CharacterManager::instance()->add_enemy(boss);
			bgm = bgm_boss;
			MusicManager::instance()->set_playlist(bgm);
		}
	}
	GameScene::on_update(delta);
}

void SceneLevel::on_exit()
{
	current_wave = 0;
	timer_waves.clear();

	CharacterManager::instance()->delete_characters();
	ProjectileManager::instance()->destory_all_bullets();
}

void SceneLevel::on_render()
{
	GameScene::on_render();
	CharacterManager::instance()->on_render();
	if (is_on_debug) CharacterManager::instance()->on_debug_render();
	ProjectileManager::instance()->on_render();
	if (is_on_debug) CollisionManager::instance()->on_debug_render();
	Rect rect_ui = Rect(0, getheight() - img_ui_bar->getheight(), getwidth(), img_ui_bar->getheight());

	putimage_ex(img_ui_bar, &rect_ui);

	int player_hp = CharacterManager::instance()->get_player()->get_hp();
	int player_max_hp = CharacterManager::instance()->get_player()->get_max_hp();
	float hp_ratio = player_max_hp > 1 ? (float)player_hp / player_max_hp : 0.0f;
	rect_ui = Rect(4, 4, HEALTH_BAR_WIDTH + 12, HEALTH_BAR_HEIGHT + 12);
	int x1 = 4 + 6, y1 = 4 + 6, x2 = 4 + 6 + HEALTH_BAR_WIDTH, y2 = 4 + 6 + HEALTH_BAR_HEIGHT;
	putimage_ex(
		ResourcesManager::instance()->find_image("amount_bar"),
		&rect_ui
	);

	setfillcolor(RGB(120, 125, 123));
	solidrectangle(x1, y1, x2, y2);

	int current_healthbar_width = (int)((HEALTH_BAR_WIDTH - 2) * hp_ratio);
	int r, g, b = 0;
	if (hp_ratio > 0.5)
	{
		r = 0, g = 216, b = 0;
	}
	else
	{
		r = min(432 - 864 * hp_ratio, 216), g = 432 * hp_ratio, b = 0;
	}
	setfillcolor(RGB(r, g, b));
	solidrectangle(
		x1,
		y1,
		x1 + current_healthbar_width,
		y2
	);
	
	std::wstringstream ss;
	ss << player_hp << "/" << player_max_hp;
	std::wstring ss_str = ss.str();
	render_text(
		Rect(x1 + 1, y1 + 1, x2 - x1 + 1, y2 - y1 + 1),
		ss_str.c_str(),
		16,
		BLACK
	);
	render_text(
		Rect(x1, y1, x2 - x1, y2 - y1),
		ss_str.c_str(),
		16,
		WHITE
	);

	rect_ui = Rect(4, 4 + 6 + HEALTH_BAR_HEIGHT + 6 + 12, HEALTH_BAR_WIDTH + 12, HEALTH_BAR_HEIGHT + 12);
	x1 = 4 + 6, y1 = 4 + 6 + HEALTH_BAR_HEIGHT + 6 + 12 + 6, x2 = 4 + 6 + HEALTH_BAR_WIDTH, y2 = 4 + 6 + HEALTH_BAR_HEIGHT + 6 + 12 + 6 + HEALTH_BAR_HEIGHT;
	int player_mp = dynamic_cast<Player*>(CharacterManager::instance()->get_player())->get_mp();
	int player_max_mp = dynamic_cast<Player*>(CharacterManager::instance()->get_player())->get_max_mp();
	float mp_ratio = player_max_mp > 1 ? (float)player_mp / player_max_mp : 0.0f;
	int current_magicbar_width = (int)((HEALTH_BAR_WIDTH - 2) * mp_ratio);
	putimage_ex(
		ResourcesManager::instance()->find_image("amount_bar"),
		&rect_ui
	);
	setfillcolor(RGB(120, 125, 123));
	solidrectangle(x1, y1, x2, y2);
	setfillcolor(RGB(46, 169, 223));
	solidrectangle(
		x1,
		y1,
		x1 + current_magicbar_width,
		y2
	);

	ss.str(L"");
	ss.clear();
	ss << player_mp << "/" << player_max_mp;
	ss_str = ss.str();
	render_text(
		Rect(x1 + 1, y1 + 1, x2 - x1, y2 - y1),
		ss_str.c_str(),
		16,
		BLACK
	);
	render_text(
		Rect(x1, y1, x2 - x1, y2 - y1),
		ss_str.c_str(),
		16,
		WHITE
	);

	if (player_hp <= 0)
	{
		putimage_ex(ResourcesManager::instance()->find_image("death_mask"),
			0, 0, getwidth(), getheight()
		);
	}

	rect_ui = Rect(1280 - 236, getheight() - img_ui_bar->getheight() + (img_ui_bar->getheight() - img_wave_bar->getheight()) / 2, img_wave_bar->getwidth(), img_wave_bar->getheight());
	putimage_ex(img_wave_bar, &rect_ui);

	ss.str(L"");
	ss.clear();
	ss << L"��һ������ʱ: ";
	ss_str = ss.str();
	x1 = 1280 - 480, x2 = 1280 - 320, y1 = getheight() - img_ui_bar->getheight(), y2 = getheight();
	render_text(
		Rect(x1, y1, x2 - x1 , y2 - y1),
		ss_str.c_str(),
		24, 
		BLACK
	);
	ss.str(L"");
	ss.clear();
	if (current_wave < timer_waves.size())
	{
		ss << int(timer_waves[current_wave].get_remaining_time());
	}
	else
	{
		ss << L"-";
	}
	ss_str = ss.str();
	x1 = 1280 - 320, x2 = 1280 - 236, y1 = getheight() - img_ui_bar->getheight(), y2 = getheight();
	render_text(
		Rect(x1, y1, x2 - x1, y2 - y1),
		ss_str.c_str(),
		24,
		BLACK
	);

	ss.str(L"");
	ss.clear();
	ss << L"����: ";
	ss_str = ss.str();
	x1 = 1280 - 600, x2 = 1280 - 540, y1 = getheight() - img_ui_bar->getheight(), y2 = getheight();
	render_text(
		Rect(x1, y1, x2 - x1, y2 - y1),
		ss_str.c_str(),
		24,
		BLACK
	);
	ss.str(L"");
	ss.clear();
	ss << current_wave << L"/" << timer_waves.size();
	ss_str = ss.str();
	x1 = 1280 - 540, x2 = 1280 - 480, y1 = getheight() - img_ui_bar->getheight(), y2 = getheight();
	render_text(
		Rect(x1, y1, x2 - x1, y2 - y1),
		ss_str.c_str(),
		24,
		BLACK
	);

	int wave_bar_width = 1.0 * current_wave / timer_waves.size() * (img_wave_bar->getwidth() - 2 * 6);
	if (current_wave < timer_waves.size())
	{
		wave_bar_width += timer_waves[current_wave].get_current_time() / timer_waves[current_wave].get_wait_time() * (img_wave_bar->getwidth() - 2 * 6) / timer_waves.size();
	}
	x1 = 1280 - 236 + 6, x2 = x1 + wave_bar_width, y1 = getheight() - img_ui_bar->getheight() + (img_ui_bar->getheight() - img_wave_bar->getheight()) / 2 + 6, y2 = y1 + img_wave_bar->getheight() - 13;
	setfillcolor(GREEN);
	solidrectangle(x1, y1, x2, y2);
}

void SceneLevel::on_input(ExMessage msg)
{
	CharacterManager::instance()->get_player()->on_input(msg);
	if (CharacterManager::instance()->get_player()->get_hp() <= 0)
	{
		if (msg.message == WM_KEYDOWN) SceneManager::instance()->switch_to("homepage");
	}
}

void SceneLevel::switch_to_death_scene()
{
	SceneManager::instance()->switch_to("homepage");
}

SceneLevel::SceneLevel()
{
	rect_dst =
	{
		 0,
		 0,
		 getwidth(),
		 getheight()
	};

	img_ui_bar = ResourcesManager::instance()->find_image("ui_bar");
	img_wave_bar = ResourcesManager::instance()->find_image("wave_bar");

	bgm_boss = { R"(assets\music\[boss]same_old_story.mp3)" };
}
