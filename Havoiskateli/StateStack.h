#pragma once

#include <stack>
#include <SFML\Graphics.hpp>

class State;

class StateStack {
public:
	StateStack();
	void pushState(State *state);
	void popState();
	void changeState(State *state);
	State* peekState();
private:
	std::stack<State*> m_states;
};