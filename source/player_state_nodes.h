#ifndef _PLAYER_STATE_NODES_H_
#define _PLAYER_STATE_NODES_H_

#include "timer.h"
#include "character_manager.h"
#include "state_node.h"

class PlayerIdleState : public StateNode
{
public:
	PlayerIdleState();
	~PlayerIdleState() = default;

	void on_enter() override;
	void on_update(float delta) override;
	void on_exit() override;
};

class PlayerRunState : public StateNode
{
public:
	PlayerRunState();
	~PlayerRunState() = default;

	void on_enter() override;
	void on_update(float delta) override;
	void on_exit() override;
};

class PlayerMeleeAttackState : public StateNode
{
public:
	PlayerMeleeAttackState();
	~PlayerMeleeAttackState() = default;

	void on_enter() override;
	void on_update(float delta) override;
	void on_exit() override;

private:
	void update_hit_box_position();

protected:
	Timer timer;
};

class PlayerRangedAttackState : public StateNode
{
public:
	PlayerRangedAttackState();
	~PlayerRangedAttackState() = default;
	void on_enter() override;
	void on_update(float delta) override;
	void on_exit() override;

protected:
	Timer timer;
};

class PlayerDeadState : public StateNode
{
public:
	PlayerDeadState();
	~PlayerDeadState() = default;
	void on_enter() override;
	void on_update(float delta) override;
	void on_exit() override;
};

#endif