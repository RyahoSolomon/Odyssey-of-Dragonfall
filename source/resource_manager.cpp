#include "resources_manager.h"
#include <iostream>
using namespace std;

ResourcesManager* ResourcesManager::manager = nullptr;

ResourcesManager* ResourcesManager::instance()
{
	if (!manager)
	{
		manager = new ResourcesManager();
	}
	return manager;
}

ResourcesManager::ResourcesManager() = default;

ResourcesManager::~ResourcesManager() = default;

struct ImageResInfo
{
	std::string id;
	LPCTSTR path;
};

struct AtlasResInfo
{
	std::string id;
	LPCTSTR path;
	int num_frame = 0;
};

static const std::vector<ImageResInfo> image_info_list =
{
	{"mage_run_right", _T(R"(assets\mage\run_right.png)")},
	{"mage_run_attack_right", _T(R"(assets\mage\run_attack_right.png)")},
	{"mage_melee_attack_right", _T(R"(assets\mage\melee_attack_right.png)")},
	{"mage_attack_right", _T(R"(assets\mage\attack_right.png)")},
	{"mage_idle", _T(R"(assets\mage\idle.png)")},
	{"mage_dead_right", _T(R"(assets\mage\dead.png)")},

	{"jinn_idle_right", _T(R"(assets\enemies\jinn\idle_right.png)")},
	{"jinn_attack_right", _T(R"(assets\enemies\jinn\attack_right.png)")},
	{"jinn_dead_right", _T(R"(assets\enemies\jinn\dead_right.png)")},
	{"vampire1_idle_right", _T(R"(assets\enemies\vampire1\idle_right.png)")},
	{"vampire1_attack_right", _T(R"(assets\enemies\vampire1\attack_right.png)")},
	{"vampire1_wander_right", _T(R"(assets\enemies\vampire1\wander_right.png)")},
	{"vampire1_dead_right", _T(R"(assets\enemies\vampire1\dead_right.png)")},
	{"vampire2_idle_right", _T(R"(assets\enemies\vampire2\idle_right.png)")},
	{"vampire2_attack_right", _T(R"(assets\enemies\vampire2\attack_right.png)")},
	{"vampire2_wander_right", _T(R"(assets\enemies\vampire2\wander_right.png)")},
	{"vampire2_dead_right", _T(R"(assets\enemies\vampire2\dead_right.png)")},
	{"vampire3_idle_right", _T(R"(assets\enemies\vampire3\idle_right.png)")},
	{"vampire3_attack_right", _T(R"(assets\enemies\vampire3\attack_right.png)")},
	{"vampire3_wander_right", _T(R"(assets\enemies\vampire3\wander_right.png)")},
	{"vampire3_dead_right", _T(R"(assets\enemies\vampire3\dead_right.png)")},

	{"dragon_idle", _T(R"(assets\enemies\dragon\idle.png)")},

	{"bullet_bit", _T(R"(assets\bullets\bit.png)")},
	{"bullet_blood", _T(R"(assets\bullets\blood.png)")},
	{"bullet_wind", _T(R"(assets\bullets\wind.png)")},
	{"bullet_spark", _T(R"(assets\bullets\spark.png)")},
	{"bullet_player", _T(R"(assets\bullets\player.png)")},
	{"bullet_dragonfire", _T(R"(assets\bullets\dragon_fire.png)")},

	{"ui_bar", _T(R"(assets\ui\bar.png)")},
	{"ui_skillselect_bar", _T(R"(assets\ui\bar2.png)")},
	{"amount_bar", _T(R"(assets\ui\amount_bar.png)")},
	{"wave_bar", _T(R"(assets\ui\wave_bar.png)")},
	{"skill_select_button", _T(R"(assets\ui\skill_select_button.png)")},
	{"skill_select_button_hover", _T(R"(assets\ui\skill_select_button_hover.png)")},
	{"skill_select_button_unable", _T(R"(assets\ui\skill_select_button_unable.png)")},
	{"skill_select_bar", _T(R"(assets\ui\bar2.png)")},
	{"icon_frame", _T(R"(assets\ui\icon_frame.png)")},
	{"button_refresh", _T(R"(assets\ui\button_refresh.png)")},
	{"button_refresh_hover", _T(R"(assets\ui\button_refresh_hover.png)")},
	{"button_refresh_unable", _T(R"(assets\ui\button_refresh_unable.png)")},
	{"button_next_level", _T(R"(assets\ui\button_next_level.png)")},
	{"button_next_level_hover", _T(R"(assets\ui\button_next_level_hover.png)")},

	{"skill_icon_general", _T(R"(assets\ui\skill_icon_general.png)")},
	{"skill_icon_poison", _T(R"(assets\ui\skill_icon_poison.png)")},
	{"skill_icon_fire", _T(R"(assets\ui\skill_icon_fire.png)")},
	{"skill_icon_ice", _T(R"(assets\ui\skill_icon_ice.png)")},
	{"skill_icon_weakness", _T(R"(assets\ui\skill_icon_weakness.png)")},
	{"skill_icon_hybrid", _T(R"(assets\ui\skill_icon_hybrid.png)")},
	{"skill_icon_bit", _T(R"(assets\ui\skill_icon_bit.png)")},

	{"scene_grassland", _T(R"(assets\scene\flower_grassland.png)")},
	{"scene_desert", _T(R"(assets\scene\endless_desert.png)")},
	{"scene_badland", _T(R"(assets\scene\barren_badland.png)")},
	{"scene_death", _T(R"(assets\scene\death_realm.png)")},
	{"scene_snowfield", _T(R"(assets\scene\final_snowfield.png)")},
	{"scene_wencui", _T(R"(assets\scene\wencui.png)")},
	{"background_gamewin", _T(R"(assets\scene\game_win.png)")},
	{"background_homepage", _T(R"(assets\scene\cover.png)")},

	{"death_mask", _T(R"(assets\mage\death_mask.png)")},
	{"exp48", _T(R"(assets\ui\exp.png)")},
};

static const std::vector<AtlasResInfo> atlas_info_list =
{
	/*{ "mage_idle", _T(R"(assets\mage\idle\%d.png)"), 9},
	{ "mage_run_right", _T(R"(assets\mage\run_right\%d.png)"), 8},
	{ "mage_run_attack_right", _T(R"(assets\mage\run_attack_right\%d.png)"), 8},
	{ "mage_melee_attack_right", _T(R"(assets\mage\melee_attack_right\%d.png)"), 7},
	{ "mage_attack_right", _T(R"(assets\mage\attack_right\%d.png)"), 7},*/
};

static inline bool check_image_valid(IMAGE* image)
{
	return GetImageBuffer(image);
}

void ResourcesManager::load()
{
	for (const auto& info : image_info_list)
	{
		IMAGE* image = new IMAGE();
		loadimage(image, info.path);

		if (!check_image_valid(image))
		{
			throw info.path;
		}
		image_pool[info.id] = image;
	}

	for (const auto& info : atlas_info_list)
	{
		Atlas* atlas = new Atlas();
		atlas->load(info.path, info.num_frame);
		for (int i = 0; i < atlas->get_size(); i++)
		{
			IMAGE* image = atlas->get_image(i);
			if (!check_image_valid(image))
			{
				throw info.path;
			}
			atlas_pool[info.id] = atlas;
		}
	}

	/*flip_atlas("mage_attack_right", "player_attack_left");
	flip_atlas("mage_run_attack_right", "mage_run_attack_left");
	flip_atlas("mage_melee_attack_right", "mage_melee_attack_left");
	flip_atlas("mage_run_right", "mage_run_left");*/
	flip_image("mage_attack_right", "mage_attack_left", 7);
	flip_image("mage_run_attack_right", "mage_run_attack_left", 8);
	flip_image("mage_melee_attack_right", "mage_melee_attack_left", 7);
	flip_image("mage_run_right", "mage_run_left", 8);
	flip_image("mage_dead_right", "mage_dead_left", 10);

	flip_image("jinn_idle_right", "jinn_idle_left", 5);
	flip_image("jinn_attack_right", "jinn_attack_left", 4);
	flip_image("jinn_dead_right", "jinn_dead_left", 6);
	flip_image("vampire1_idle_right", "vampire1_idle_left", 4);
	flip_image("vampire1_attack_right", "vampire1_attack_left", 12);
	flip_image("vampire1_wander_right", "vampire1_wander_left", 6);
	flip_image("vampire1_dead_right", "vampire1_dead_left", 11);
	flip_image("vampire2_idle_right", "vampire2_idle_left", 4);
	flip_image("vampire2_attack_right", "vampire2_attack_left", 12);
	flip_image("vampire2_wander_right", "vampire2_wander_left", 6);
	flip_image("vampire2_dead_right", "vampire2_dead_left", 11);
	flip_image("vampire3_idle_right", "vampire3_idle_left", 4);
	flip_image("vampire3_attack_right", "vampire3_attack_left", 12);
	flip_image("vampire3_wander_right", "vampire3_wander_left", 6);
	flip_image("vampire3_dead_right", "vampire3_dead_left", 11);
	AddFontResourceEx(_T("resources/IPix.ttf"), FR_PRIVATE, 0);
}


Atlas* ResourcesManager::find_atlas(const std::string& id) const
{
	const auto& itor = atlas_pool.find(id);
	if (itor == atlas_pool.end())
	{
		return nullptr;
	}

	return itor->second;
}

IMAGE* ResourcesManager::find_image(const std::string& id) const
{
	const auto& itor = image_pool.find(id);
	if (itor == image_pool.end())
	{
		return nullptr;
	}
	return itor->second;
}

//void ResourcesManager::flip_image(IMAGE* src_image, IMAGE* dst_image, int num_h)
//{
//	int w = src_image->getwidth();
//	int h = src_image->getheight();
//	int w_frame = w / num_h;
//	Resize(dst_image, w, h);
//	DWORD* src_buffer = GetImageBuffer(src_image);
//	DWORD* dst_buffer = GetImageBuffer(dst_image);
//	for (int i = 0; i < num_h; i++)
//	{
//		int x_left = i * w_frame;
//		int x_right = (i + 1) * w_frame;
//		for (int y = 0; y < h; y++)
//		{
//			for (int x = x_left; x < x_right; x++)
//			{
//				int idx_src = y * w + x;
//				int idx_dst = y * w + x_right - (x - x_left);
//				dst_buffer[idx_dst] = src_buffer[idx_src];
//			}
//		}
//	}
//}

void ResourcesManager::flip_image(IMAGE* src_image, IMAGE* dst_image, int num_h)
{
	int w = src_image->getwidth();
	int h = src_image->getheight();
	if (w <= 0 || h <= 0 || num_h <= 0) return;

	// 平均帧宽和余数（最后一帧处理余下像素）
	int base_frame_w = w / num_h;
	int remainder = w % num_h;

	// 使用对象成员 Resize 更稳妥（如果库提供全局 Resize 可以保持，但成员调用更明确）
	dst_image->Resize(w, h);

	DWORD* src_buffer = GetImageBuffer(src_image);
	DWORD* dst_buffer = GetImageBuffer(dst_image);
	if (!src_buffer || !dst_buffer) return;

	int x_offset = 0;
	for (int i = 0; i < num_h; ++i)
	{
		int frame_w = base_frame_w + (i == num_h - 1 ? remainder : 0); // 最后一帧加上余数
		if (frame_w <= 0) break;

		int x_left = x_offset;
		// 按局部 x 处理，避免越界与 off-by-one
		for (int y = 0; y < h; ++y)
		{
			int row_base = y * w;
			for (int xl = 0; xl < frame_w; ++xl)
			{
				int src_x = x_left + xl;
				int dst_x = x_left + (frame_w - 1 - xl); // 镜像的局部位置
				// 额外保险检查（release 下可去掉以提速）
				if (src_x < 0 || src_x >= w || dst_x < 0 || dst_x >= w) continue;
				int idx_src = row_base + src_x;
				int idx_dst = row_base + dst_x;
				dst_buffer[idx_dst] = src_buffer[idx_src];
			}
		}

		x_offset += frame_w;
	}
}

void ResourcesManager::flip_image(const std::string& src_id, const std::string dst_id, int num_h)
{
	IMAGE* src_image = image_pool[src_id];
	IMAGE* dst_image = new IMAGE();

	flip_image(src_image, dst_image, num_h);

	image_pool[dst_id] = dst_image;
}

void ResourcesManager::flip_atlas(const std::string& src_id, const std::string dst_id)
{
	Atlas* src_atlas = atlas_pool[src_id];
	Atlas* dst_atlas = new Atlas();

	for (int i = 0; i < src_atlas->get_size(); i++)
	{
		IMAGE img_flipped;
		flip_image(src_atlas->get_image(i), &img_flipped);
		dst_atlas->add_image(img_flipped);
	}

	atlas_pool[dst_id] = dst_atlas;
}