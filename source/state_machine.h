#ifndef _STATE_MACHINE_H_
#define _STATE_MACHINE_H_
#include <string>
#include <graphics.h>
#include <unordered_map>
#include <iostream>

#include "state_node.h"

class StateMachine
{
public:
	StateMachine();
	~StateMachine();
	virtual void on_update(float delta);

	virtual void set_entry(const std::string& id);
	virtual void switch_to(const std::string& id);
	virtual void register_state(const std::string& id, StateNode* statenode);

protected:
	bool need_init = true;
	StateNode* current_state = nullptr;
	std::unordered_map<std::string, StateNode*> state_pool;
};

#endif