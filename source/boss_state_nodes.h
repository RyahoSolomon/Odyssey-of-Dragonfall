#ifndef _BOSS_STATE_NODES_H_
#define _BOSS_STATE_NODES_H_

#include "enemy_boss.h"

class DragonIdleState : public EnemyStateNode
{
public:
	DragonIdleState(Enemy* owner);
	~DragonIdleState() = default;

	void on_enter() override;
	void on_update(float delta) override;
	void on_exit() override;

protected:
	Timer timer;
};

class DragonNormalAttackState : public EnemyStateNode
{
public:
	DragonNormalAttackState(Enemy* owner);
	~DragonNormalAttackState() = default;

	void on_enter() override;
	void on_update(float delta) override;
	void on_exit() override;

protected:
	Timer timer;
};

class DragonFireArrayState : public EnemyStateNode
{
public:
	DragonFireArrayState(Enemy* owner);
	~DragonFireArrayState() = default;

	void on_enter() override;
	void on_update(float delta) override;
	void on_exit() override;

protected:
	Timer timer;
};

class DragonDeadState : public EnemyStateNode
{
public:
	DragonDeadState(Enemy* owner);
	~DragonDeadState() = default;

	void on_enter() override;
	void on_update(float delta) override;
	void on_exit() override;

protected:
	Timer timer;
};

#endif // !_BOSS_STATE_NODES_H_
