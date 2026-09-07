#include "skill.h"

bool Skill::is_precondiction_completed(SkillList* skill_list)
{
	for (SkillID precodition_skill_id : precondition_skills)
	{
		if (! skill_list->get_skill_level(precodition_skill_id))
		{
			return false;
		}
	}
	return true;
}

Skill::Skill()
{
	// 仅用作 STL 初始化, 自己不许用
	id = SkillID::BITBullet;
	max_stack_count = 1;
	is_available = [](SkillList* skill_list) { return true; };
	cost = 1;
	stacked_count = 0;
	icon = ResourcesManager::instance()->find_image("skill_icon_general");
}

Skill::Skill(SkillID id, int max_stack_count, std::function<bool(SkillList* skill_list)> is_available, int cost, std::wstring name, int stacked_count) :
	id(id), max_stack_count(max_stack_count), is_available(is_available), cost(cost), name(name), stacked_count(stacked_count)
{
	icon = ResourcesManager::instance()->find_image("skill_icon_general");
}

void Skill::add_precondition_skill(SkillID precondition_skill)
{
	precondition_skills.push_back(precondition_skill);
}

bool Skill::get_is_available(SkillList* skill_list)
{
	if (!is_precondiction_completed(skill_list)) return false;
	if (skill_list->get_skill_level(id) >= max_stack_count) return false;
	return is_available(skill_list);
}

int Skill::get_level() const
{
	return stacked_count;
}

int Skill::get_max_stack_count() const
{
	return max_stack_count;
}

int Skill::stack(int value)
{
	stacked_count = min(stacked_count + value, max_stack_count);
	return stacked_count;
}

int Skill::get_cost() const
{
	return cost;
}

SkillID Skill::get_id() const
{
	return id;
}

void Skill::add_lore(std::wstring l)
{
	lore.push_back(l);
}

void Skill::set_icon(IMAGE* icon)
{
	this->icon = icon;
}

IMAGE* Skill::get_icon()
{
	return icon;
}

std::wstring Skill::get_name() const
{
	return name;
}

std::vector<std::wstring>* Skill::get_lores()
{
	return &lore;
}

SkillList::SkillList()
{	
	// 最大生命值提升
	skills[SkillID::MaxHealthBoost] = (Skill(SkillID::MaxHealthBoost, 114514, [](SkillList* skill_list)
		{
			return true;
		}, 5, L"体魄增强"));
	skills[SkillID::MaxHealthBoost].add_lore(L"最大生命值提升 20");

	// 最大法力值提升
	skills[SkillID::MaxMagicBoost] = (Skill(SkillID::MaxMagicBoost, 114514, [](SkillList* skill_list)
		{
			return true;
		}, 4, L"法力增强"));
	skills[SkillID::MaxMagicBoost].add_lore(L"最大法力值提升 20");

	// 法力恢复速度提升
	skills[SkillID::MagicRegenerationBoost] = (Skill(SkillID::MagicRegenerationBoost, 114514, [](SkillList* skill_list)
		{
			return true;
		}, 8, L"快速法术恢复"));
	skills[SkillID::MagicRegenerationBoost].add_lore(L"每秒法力恢复值提升 1");

	// 移动速度提升
	skills[SkillID::MoveSpeedBoost] = (Skill(SkillID::MoveSpeedBoost, 114514, [](SkillList* skill_list)
		{
			return true;
		}, 6, L"移动速度提升"));
	skills[SkillID::MoveSpeedBoost].add_lore(L"移动速度提升 16");

	// 远程攻击附带毒伤
	skills[SkillID::PoisonBullet] = (Skill(SkillID::PoisonBullet, 1, [](SkillList* skill_list)
		{
			if ((bool(skill_list->get_skill_level(SkillID::FireBullet)) +
				bool(skill_list->get_skill_level(SkillID::IceBullet)) +
				bool(skill_list->get_skill_level(SkillID::WeaknessBullet))) >= 2) return false;
			return true;
		}, 12, L"毒药飞弹"));
	skills[SkillID::PoisonBullet].add_lore(L"奥术飞弹附带一层毒");
	skills[SkillID::PoisonBullet].add_lore(L"奥术飞弹法力消耗增加 5");
	skills[SkillID::PoisonBullet].set_icon(ResourcesManager::instance()->find_image("skill_icon_poison"));

	// 远程攻击附带火伤
	skills[SkillID::FireBullet] = (Skill(SkillID::FireBullet, 1, [](SkillList* skill_list)
		{
			if ((bool(skill_list->get_skill_level(SkillID::PoisonBullet)) +
				bool(skill_list->get_skill_level(SkillID::IceBullet)) +
				bool(skill_list->get_skill_level(SkillID::WeaknessBullet))) >= 2) return false;
			return true;
		}, 12, L"烈焰飞弹"));
	skills[SkillID::FireBullet].add_lore(L"奥术飞弹附带火焰伤害");
	skills[SkillID::FireBullet].add_lore(L"奥术飞弹法力消耗增加 3");
	skills[SkillID::FireBullet].set_icon(ResourcesManager::instance()->find_image("skill_icon_fire"));

	// 远程攻击附带冰冻
	skills[SkillID::IceBullet] = (Skill(SkillID::IceBullet, 1, [](SkillList* skill_list)
		{
			if ((bool(skill_list->get_skill_level(SkillID::PoisonBullet)) +
				bool(skill_list->get_skill_level(SkillID::FireBullet)) +
				bool(skill_list->get_skill_level(SkillID::WeaknessBullet))) >= 2) return false;
			return true;
		}, 8, L"寒冰飞弹"));
	skills[SkillID::IceBullet].add_lore(L"奥术飞弹附带 50 层冰冻");
	skills[SkillID::IceBullet].add_lore(L"奥术飞弹法力消耗增加 2");
	skills[SkillID::IceBullet].set_icon(ResourcesManager::instance()->find_image("skill_icon_ice"));

	// 远程攻击附带虚弱
	skills[SkillID::WeaknessBullet] = (Skill(SkillID::WeaknessBullet, 1, [](SkillList* skill_list)
		{
			if ((bool(skill_list->get_skill_level(SkillID::PoisonBullet)) +
				bool(skill_list->get_skill_level(SkillID::FireBullet)) +
				bool(skill_list->get_skill_level(SkillID::IceBullet))) >= 2) return false;
			return true;
		}, 8, L"恶咒飞弹"));
	skills[SkillID::WeaknessBullet].add_lore(L"奥术飞弹附带 1 层诅咒");
	skills[SkillID::WeaknessBullet].add_lore(L"奥术飞弹法力消耗增加 2");
	skills[SkillID::WeaknessBullet].set_icon(ResourcesManager::instance()->find_image("skill_icon_weakness"));

	// 子弹速度提升
	skills[SkillID::BulletSpeedBoost] = (Skill(SkillID::BulletSpeedBoost, 114514, [](SkillList* skill_list)
		{
			return true;
		}, 8, L"飞弹速度提升"));
	skills[SkillID::BulletSpeedBoost].add_lore(L"奥术飞弹移动速度增加 40");

	// 远程攻击基础值提升
	skills[SkillID::RangedAttackBoost] = (Skill(SkillID::RangedAttackBoost, 114514, [](SkillList* skill_list)
		{
			return true;
		}, 8, L"奥术强化"));
	skills[SkillID::RangedAttackBoost].add_lore(L"奥术飞弹基础伤害增加 2");
	
	// 上毒层数增加
	skills[SkillID::FastPoison] = (Skill(SkillID::FastPoison, 114514, [](SkillList* skill_list)
		{
			return true;
		}, 15, L"强效毒药"));
	skills[SkillID::FastPoison].add_precondition_skill(SkillID::PoisonBullet);
	skills[SkillID::FastPoison].add_lore(L"奥术飞弹附带额外 1 层毒");
	skills[SkillID::FastPoison].add_lore(L"奥术飞弹法力消耗增加 3");
	skills[SkillID::FastPoison].set_icon(ResourcesManager::instance()->find_image("skill_icon_poison"));

	// 火属性伤害更高
	skills[SkillID::StrongFire] = (Skill(SkillID::StrongFire, 114514, [](SkillList* skill_list)
		{
			return true;
		}, 15, L"火焰增强"));
	skills[SkillID::StrongFire].add_precondition_skill(SkillID::FireBullet);
	skills[SkillID::StrongFire].add_lore(L"单次火焰伤害增加 1");
	skills[SkillID::StrongFire].add_lore(L"奥术飞弹法力消耗增加 2");
	skills[SkillID::StrongFire].set_icon(ResourcesManager::instance()->find_image("skill_icon_fire"));

	// 冰属性减速效果更强
	skills[SkillID::StrongIce] = (Skill(SkillID::StrongIce, 114514, [](SkillList* skill_list)
		{
			return true;
		}, 12, L"强效冰冻"));
	skills[SkillID::StrongIce].add_precondition_skill(SkillID::IceBullet);
	skills[SkillID::StrongIce].add_lore(L"奥术飞弹附带额外 25 层冰冻");
	skills[SkillID::StrongIce].add_lore(L"奥术飞弹法力消耗增加 1");
	skills[SkillID::StrongIce].set_icon(ResourcesManager::instance()->find_image("skill_icon_ice"));

	// 虚弱属性降低伤害效果更强
	skills[SkillID::StrongWeakness] = (Skill(SkillID::StrongWeakness, 114514, [](SkillList* skill_list)
		{
			return true;
		}, 12, L"强力恶咒"));
	skills[SkillID::StrongWeakness].add_precondition_skill(SkillID::StrongWeakness);
	skills[SkillID::StrongWeakness].add_lore(L"奥术飞弹附带额外 1 层恶咒");
	skills[SkillID::StrongWeakness].add_lore(L"奥术飞弹法力消耗增加 1");
	skills[SkillID::StrongWeakness].set_icon(ResourcesManager::instance()->find_image("skill_icon_weakness"));

	// 着火的敌人受到双倍毒伤害
	skills[SkillID::PoisonBurst] = (Skill(SkillID::PoisonBurst, 1, [](SkillList* skill_list)
		{
			return true;
		}, 18, L"毒素激发"));
	skills[SkillID::PoisonBurst].add_precondition_skill(SkillID::PoisonBullet);
	skills[SkillID::PoisonBurst].add_precondition_skill(SkillID::FireBullet);
	skills[SkillID::PoisonBurst].add_precondition_skill(SkillID::StrongWeakness);
	skills[SkillID::PoisonBurst].add_lore(L"着火的敌人受到双倍毒伤害");
	skills[SkillID::PoisonBurst].set_icon(ResourcesManager::instance()->find_image("skill_icon_hybrid"));

	// 火属性不会再移除冰效果, 且只要冰效果存在, 火效果的计时器就不会更新
	skills[SkillID::EternelFrostFire] = (Skill(SkillID::EternelFrostFire, 1, [](SkillList* skill_list)
		{
			return true;
		}, 15, L"永冻之火"));
	skills[SkillID::EternelFrostFire].add_precondition_skill(SkillID::IceBullet);
	skills[SkillID::EternelFrostFire].add_precondition_skill(SkillID::FireBullet);
	skills[SkillID::EternelFrostFire].add_lore(L"冰冻与火焰不再相互抵消");
	skills[SkillID::EternelFrostFire].add_lore(L"冰冻的敌人身上的火焰不再消退");
	skills[SkillID::EternelFrostFire].set_icon(ResourcesManager::instance()->find_image("skill_icon_hybrid"));

	// 子弹命中后会获得力量效果, 增强自己的攻击力
	skills[SkillID::EncouragingFire] = (Skill(SkillID::EncouragingFire, 1, [](SkillList* skill_list)
		{
			return true;
		}, 15, L"振奋之火"));
	skills[SkillID::EncouragingFire].add_precondition_skill(SkillID::WeaknessBullet);
	skills[SkillID::EncouragingFire].add_precondition_skill(SkillID::FireBullet);
	skills[SkillID::EncouragingFire].add_lore(L"奥术飞弹命中后提升 30% 的攻击力 10s");
	skills[SkillID::EncouragingFire].set_icon(ResourcesManager::instance()->find_image("skill_icon_hybrid"));

	// 长效毒药, 毒效果施加给冰属性的敌人后持续时间时间会加倍
	skills[SkillID::LongTermlPoison] = (Skill(SkillID::LongTermlPoison, 1, [](SkillList* skill_list)
		{
			return true;
		}, 15, L"长效毒药"));
	skills[SkillID::LongTermlPoison].add_precondition_skill(SkillID::PoisonBullet);
	skills[SkillID::LongTermlPoison].add_precondition_skill(SkillID::IceBullet);
	skills[SkillID::LongTermlPoison].add_lore(L"对冰冻的敌人施加的毒持续时长翻倍");
	skills[SkillID::LongTermlPoison].set_icon(ResourcesManager::instance()->find_image("skill_icon_hybrid"));

	// 多功能毒药, 毒药效果同时会降低敌人的攻击移动速度, 即冰的效果
	skills[SkillID::MultiFunctionPoison] = (Skill(SkillID::MultiFunctionPoison, 1, [](SkillList* skill_list)
		{
			return true;
		}, 15, L"全效毒药"));
	skills[SkillID::MultiFunctionPoison].add_precondition_skill(SkillID::WeaknessBullet);
	skills[SkillID::MultiFunctionPoison].add_precondition_skill(SkillID::PoisonBullet);
	skills[SkillID::MultiFunctionPoison].add_lore(L"对被诅咒的敌人施加的毒效果会同时降低其速度");
	skills[SkillID::MultiFunctionPoison].set_icon(ResourcesManager::instance()->find_image("skill_icon_hybrid"));

	// 脆变: 同时拥有冰效果和虚弱效果的敌人, 受到的所有伤害提升 50%;
	skills[SkillID::Embrittlement] = (Skill(SkillID::Embrittlement, 1, [](SkillList* skill_list)
		{
			return true;
		}, 15, L"脆变"));
	skills[SkillID::Embrittlement].add_precondition_skill(SkillID::WeaknessBullet);
	skills[SkillID::Embrittlement].add_precondition_skill(SkillID::IceBullet);
	skills[SkillID::Embrittlement].add_lore(L"同时被诅咒和冰冻的敌人受到的伤害增加 30%");
	skills[SkillID::Embrittlement].set_icon(ResourcesManager::instance()->find_image("skill_icon_hybrid"));

	// 子弹的图标替换为 BIT 的校徽
	skills[SkillID::BITBullet] = (Skill(SkillID::BITBullet, 1, [](SkillList* skill_list)
		{
			return true;
		}, 10, L"神秘子弹"));
	skills[SkillID::BITBullet].add_lore(L"???");
	skills[SkillID::BITBullet].set_icon(ResourcesManager::instance()->find_image("skill_icon_bit"));

	// 所有游戏场景替换为文萃楼平面地图
	skills[SkillID::WenCuiBackground] = (Skill(SkillID::WenCuiBackground, 1, [](SkillList* skill_list)
		{
			return true;
		}, 10, L"神秘场景"));
	skills[SkillID::WenCuiBackground].add_lore(L"???");
	skills[SkillID::WenCuiBackground].set_icon(ResourcesManager::instance()->find_image("skill_icon_bit"));

	// 扇形发射 3 个子弹
	skills[SkillID::SectorBulletsI] = (Skill(SkillID::SectorBulletsI, 1, [](SkillList* skill_list)
		{
			return true;
		}, 12, L"扇形飞弹I"));
	skills[SkillID::SectorBulletsI].add_lore(L"扇形发射 3 发奥术飞弹");
	skills[SkillID::SectorBulletsI].add_lore(L"奥术飞弹法力消耗增加 3");

	// 扇形发射 5 个子弹
	skills[SkillID::SectorBulletsII] = (Skill(SkillID::SectorBulletsII, 1, [](SkillList* skill_list)
		{
			return true;
		}, 15, L"扇形飞弹II"));
	skills[SkillID::SectorBulletsII].add_precondition_skill(SkillID::SectorBulletsI);
	skills[SkillID::SectorBulletsII].add_lore(L"扇形发射 5 发奥术飞弹");
	skills[SkillID::SectorBulletsII].add_lore(L"奥术飞弹法力消耗增加 2");

	// 扇形发射 7 个子弹
	skills[SkillID::SectorBulletsIII] = (Skill(SkillID::SectorBulletsIII, 1, [](SkillList* skill_list)
		{
			return true;
		}, 18, L"扇形飞弹III"));
	skills[SkillID::SectorBulletsIII].add_precondition_skill(SkillID::SectorBulletsII);
	skills[SkillID::SectorBulletsIII].add_lore(L"扇形发射 7 发奥术飞弹");
	skills[SkillID::SectorBulletsIII].add_lore(L"奥术飞弹法力消耗增加 2");

	// 发射 3 个子弹排成一排
	skills[SkillID::ParallelBulletsI] = (Skill(SkillID::ParallelBulletsI, 1, [](SkillList* skill_list)
		{
			return true;
		}, 12, L"飞弹阵列I"));
	skills[SkillID::ParallelBulletsI].add_lore(L"并排发射 3 发奥术飞弹");
	skills[SkillID::ParallelBulletsI].add_lore(L"奥术飞弹法力消耗增加 3");

	// 发射 5 个子弹排成一排
	skills[SkillID::ParallelBulletsII] = (Skill(SkillID::ParallelBulletsII, 1, [](SkillList* skill_list)
		{
			return true;
		}, 16, L"飞弹阵列II"));
	skills[SkillID::ParallelBulletsII].add_precondition_skill(SkillID::ParallelBulletsI);
	skills[SkillID::ParallelBulletsII].add_lore(L"并排发射 5 发奥术飞弹");
	skills[SkillID::ParallelBulletsII].add_lore(L"奥术飞弹法力消耗增加 2");

	// 发射 7 个子弹排成一排
	skills[SkillID::ParallelBulletsIII] = (Skill(SkillID::ParallelBulletsIII, 1, [](SkillList* skill_list)
		{
			return true;
		}, 20, L"飞弹阵列III"));
	skills[SkillID::ParallelBulletsIII].add_precondition_skill(SkillID::ParallelBulletsII);
	skills[SkillID::ParallelBulletsIII].add_lore(L"并排发射 7 发奥术飞弹");
	skills[SkillID::ParallelBulletsIII].add_lore(L"奥术飞弹法力消耗增加 2");

	skills[SkillID::MagicCostReduce] = (Skill(SkillID::MagicCostReduce, 3, [](SkillList* skill_list)
		{
			return true;
		}, 10, L"魔法节流"));
	skills[SkillID::MagicCostReduce].add_lore(L"降低 20% 的魔法消耗");
	skills[SkillID::MagicCostReduce].add_lore(L"最多叠加 3 次");
}

SkillList::~SkillList()
{
}

int SkillList::get_skill_level(SkillID id)
{
	auto it = skills_owned.find(id);
	if (it == skills_owned.end())
	{
		return 0;
	}
	return it->second.get_level();
}

std::vector<Skill> SkillList::get_available_skills(int count)
{
	std::mt19937 g(std::random_device{}());
	std::vector<Skill> result;
	for (auto it = skills.begin(); it != skills.end(); ++it)
	{
		if (it->second.get_is_available(this))
		{
			result.push_back(it->second);
		}
	}
	std::shuffle(result.begin(), result.end(), g);
	return result;
}

void SkillList::add_skill(SkillID id)
{
	if (get_skill_level(id) == 0)
	{
		skills_owned[id] = find_skill(id);
	}
	skills_owned[id].stack(1);
}

Skill& SkillList::find_skill(SkillID id)
{
	return skills[id];
}

void SkillList::reset()
{
	skills_owned.clear();
}
