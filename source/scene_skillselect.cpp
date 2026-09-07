#include "scene_skillselect.h"
#include "scene_learn.h"

void SceneSkillSelect::on_enter()
{
	refresh();
}

void SceneSkillSelect::on_update(float delta)
{
	int exp_owned = CharacterManager::instance()->get_exp();
	for (int i = 0; i < skills_display.size(); ++i)
	{
		if (is_available[i] && exp_owned < skills_display[i].get_cost())
		{
			is_available[i] = false;
		}
	}
	GameScene::on_update(delta);
}

void SceneSkillSelect::on_exit()
{
}

void SceneSkillSelect::on_render()
{
	int i = 0;
	Rect rect_ui;
	for (; i < 12; i++)
	{
		int index_column = i % 4;
		int index_row = i / 4;
		rect_ui = Rect(index_column * 320, index_row * 216, 320, 216);
		IMAGE* img_button_to_render = img_button_unable;
		if (is_available[i])
		{
			if (int(position_cursor.x / 320) == index_column && int(position_cursor.y / 216) == index_row)
			{
				img_button_to_render = img_button_hover;
			}
			else
			{
				img_button_to_render = img_button;
			}
		}
		putimage_ex(img_button_to_render, &rect_ui); 
		if (i < skills_display.size())
		{
			rect_ui = Rect(index_column * 320 + 8, index_row * 216 + 8, img_icon_frame->getwidth(), img_icon_frame->getheight());
			putimage_ex(img_icon_frame, &rect_ui);

			std::wstring skill_name_str = skills_display[i].get_name();

			int text_x = rect_ui.x + rect_ui.w + 8;
			int text_y = rect_ui.y;
			int text_w = 320 - 24 - img_icon_frame->getwidth();
			int text_h = 36;

			Rect text_rect(text_x, text_y, text_w, text_h);

			render_text(text_rect, skill_name_str.c_str(), 24, BLACK);

			std::vector<std::wstring>* lores = skills_display[i].get_lores();
			if (lores && !lores->empty()) {
				text_x = rect_ui.x;
				text_w = 320 - 16;
				text_y = rect_ui.y + 16 + img_icon_frame->getheight();
				text_h = 24;
				int lore_line_height = 32;
				for (size_t li = 0; li < lores->size(); ++li) {
					Rect lore_rect(text_x, text_y + li * lore_line_height, text_w, lore_line_height);
					render_text(lore_rect, (*lores)[li].c_str(), text_h, RGB(80, 80, 80));
				}
			}

			rect_ui.x += 6, rect_ui.y += 6, rect_ui.w = 64, rect_ui.h = 64;
			putimage_ex(skills_display[i].get_icon(), &rect_ui);

			rect_ui = Rect(
				index_column * 320 + 160,
				index_row * 216 + 48,
				36,
				36
			);
			putimage_ex(img_exp48, &rect_ui);

			int skill_cost = skills_display[i].get_cost();
			std::wstring cost_text = std::to_wstring(skill_cost);

			rect_ui = Rect(
				rect_ui.x + rect_ui.w + 4, 
				rect_ui.y,
				48, 
				rect_ui.h
			);

			render_text(rect_ui, cost_text.c_str(), 24, CharacterManager::instance()->get_exp() >= skill_cost ? BLACK : RED);

		}
	}

	rect_ui = Rect(0, getheight() - img_bar->getheight(), img_bar->getwidth(), img_bar->getheight());
	putimage_ex(img_bar, &rect_ui);

	rect_ui = Rect(
		(img_bar->getheight() - img_button_refresh->getheight()) / 2,
		getheight() - img_bar->getheight() + (img_bar->getheight() - img_button_refresh->getheight()) / 2,
		img_button_refresh->getwidth(),
		img_button_refresh->getheight()
	);
	bool is_on_hover = 
		position_cursor.x >= (img_bar->getheight() - (img_button_refresh->getheight()) / 2) && 
		position_cursor.x <= (img_button_refresh->getwidth() + img_bar->getheight() - (img_button_refresh->getheight()) / 2) &&
		position_cursor.y >= (getheight() - img_bar->getheight() + (img_bar->getheight() - img_button_refresh->getheight()) / 2) &&
		position_cursor.y <= (img_button_refresh->getheight() + getheight() - img_bar->getheight() + (img_bar->getheight() - img_button_refresh->getheight()) / 2);
	
	if (CharacterManager::instance()->get_exp() < 1) putimage_ex(img_button_refresh_unable, &rect_ui);
	else if (is_on_hover)putimage_ex(img_button_refresh_hover, &rect_ui);
	else putimage_ex(img_button_refresh, &rect_ui);


	rect_ui = Rect(
		getwidth() - (img_bar->getheight() - img_button_refresh->getheight()) / 2 - img_button_refresh->getwidth(),
		getheight() - img_bar->getheight() + (img_bar->getheight() - img_button_refresh->getheight()) / 2,
		img_button_refresh->getwidth(),
		img_button_refresh->getheight()
	);

	is_on_hover =
		position_cursor.x >= (getwidth() - (img_bar->getheight() + img_button_refresh->getwidth() - (img_button_refresh->getheight()) / 2)) &&
		position_cursor.x <= (img_button_refresh->getwidth() + getwidth() - (img_bar->getheight() + img_button_refresh->getwidth() - (img_button_refresh->getheight()) / 2)) &&
		position_cursor.y >= (getheight() - img_bar->getheight() + (img_bar->getheight() - img_button_refresh->getheight()) / 2) &&
		position_cursor.y <= (img_button_refresh->getheight() + getheight() - img_bar->getheight() + (img_bar->getheight() - img_button_refresh->getheight()) / 2);
	if (is_on_hover)putimage_ex(img_button_next_level_hover, &rect_ui);
	else putimage_ex(img_button_next_level, &rect_ui);

	rect_ui = Rect(
		576,
		getheight() - img_bar->getheight() + (img_bar->getheight() - img_exp48->getheight()) / 2,
		img_exp48->getwidth(),
		img_exp48->getheight()
	);
	putimage_ex(img_exp48, &rect_ui);

	rect_ui = Rect(
		640,
		getheight() - img_bar->getheight(),
		144,
		img_bar->getheight()
	);
	std::wstring wstr_exp = std::to_wstring(CharacterManager::instance()->get_exp());
	render_text(rect_ui, wstr_exp.c_str(), 32);
}

void SceneSkillSelect::on_input(ExMessage msg)
{
	switch (msg.message)
	{
	case WM_MOUSEMOVE:
		position_cursor = { double(msg.x), double(msg.y) };
		break;

	case WM_LBUTTONDOWN:
		if (position_cursor.x >= 0 && position_cursor.x < getwidth() && position_cursor.y >= 0 && position_cursor.y < 648)
		{
			int index_column = int(msg.x / 320);
			int index_row = int(msg.y / 216);
			int index = index_row * 4 + index_column;
			if (is_available[index])
			{
				CharacterManager::instance()->add_skill(skills_display[index].get_id());
				is_available[index] = false;
			}
			break;
		}

		// �����Ǽ���Ƿ���ˢ�°�ť��
		bool is_on_hover =
			position_cursor.x >= (img_bar->getheight() - (img_button_refresh->getheight()) / 2) &&
			position_cursor.x <= (img_button_refresh->getwidth() + img_bar->getheight() - (img_button_refresh->getheight()) / 2) &&
			position_cursor.y >= (getheight() - img_bar->getheight() + (img_bar->getheight() - img_button_refresh->getheight()) / 2) &&
			position_cursor.y <= (img_button_refresh->getheight() + getheight() - img_bar->getheight() + (img_bar->getheight() - img_button_refresh->getheight()) / 2);

		if (is_on_hover)
		{
			if (CharacterManager::instance()->consume_exp(1)) refresh();
			break;
		}

		is_on_hover =
			position_cursor.x >= (getwidth() - (img_bar->getheight() + img_button_refresh->getwidth() - (img_button_refresh->getheight()) / 2)) &&
			position_cursor.x <= (img_button_refresh->getwidth() + getwidth() - (img_bar->getheight() + img_button_refresh->getwidth() - (img_button_refresh->getheight()) / 2)) &&
			position_cursor.y >= (getheight() - img_bar->getheight() + (img_bar->getheight() - img_button_refresh->getheight()) / 2) &&
			position_cursor.y <= (img_button_refresh->getheight() + getheight() - img_bar->getheight() + (img_bar->getheight() - img_button_refresh->getheight()) / 2);
		
		if (is_on_hover)
		{
			SceneTransition transistion = GameFlow::instance()->next_after_selection();
			if (transistion.has_request && transistion.next_scene == SceneType::Level)  SceneManager::instance()->switch_to("level");
			break;
		}
		break;
	}
}

SceneSkillSelect::SceneSkillSelect()
{
	img_button = ResourcesManager::instance()->find_image("skill_select_button");
	img_button_hover = ResourcesManager::instance()->find_image("skill_select_button_hover");
	img_button_unable = ResourcesManager::instance()->find_image("skill_select_button_unable");
	img_icon_frame = ResourcesManager::instance()->find_image("icon_frame");
	img_bar = ResourcesManager::instance()->find_image("ui_skillselect_bar");

	img_button_refresh = ResourcesManager::instance()->find_image("button_refresh");
	img_button_refresh_hover = ResourcesManager::instance()->find_image("button_refresh_hover");
	img_button_refresh_unable = ResourcesManager::instance()->find_image("button_refresh_unable");
	img_button_next_level = ResourcesManager::instance()->find_image("button_next_level");
	img_button_next_level_hover = ResourcesManager::instance()->find_image("button_next_level_hover");

	img_exp48 = ResourcesManager::instance()->find_image("exp48");
}

void SceneSkillSelect::refresh()
{
	int exp = CharacterManager::instance()->get_exp();
	std::cout << exp << "\n";
	skills_display = CharacterManager::instance()->get_player_available_skills(12);
	int i = 0; 
	for (; i < skills_display.size(); i++)
	{
		if (exp < skills_display[i].get_cost())
		{
			is_available[i] = false;
		}
		else is_available[i] = true;
	}
	for (; i < 12; ++i)
	{
		is_available[i] = false;
;	}
	std::cout << "\n";
}
