#ifndef _ENEMY_STATE_NODES_H_
#define _ENEMY_STATE_NODES_H_

#include "enemy.h"

class RangedEnemyIdleState : public EnemyStateNode
{
public:
	RangedEnemyIdleState(Enemy* owner);
	~RangedEnemyIdleState() = default;

	void on_enter() override;
	void on_update(float delta) override;
	void on_exit() override;

protected:
	Timer timer;
};

class RangedEnemyWanderState : public EnemyStateNode
{
public:
	RangedEnemyWanderState(Enemy* owner);
	~RangedEnemyWanderState() = default;

	void on_enter() override;
	void on_update(float delta) override;
	void on_exit() override;

protected:
	Timer timer;
};

class RangedEnemyAttackState : public EnemyStateNode
{
public:
	RangedEnemyAttackState(Enemy* owner);
	~RangedEnemyAttackState() = default;

	void on_enter() override;
	void on_update(float delta) override;
	void on_exit() override;

protected:
	Timer timer;
};

class RangedEnemyDeadState : public EnemyStateNode
{
public:
	RangedEnemyDeadState(Enemy* owner);
	~RangedEnemyDeadState() = default;

	void on_enter() override;
	void on_update(float delta) override;
	void on_exit() override;

protected:
	Timer timer;
};

#endif // !_ENEMY_STATE_NODES_H_
