#pragma once

#include <stack>
#include <SFML\Graphics.hpp>

class State;

class StateStack {
public:
	StateStack();
	StateStack(sf::RenderWindow &window);
	void pushState(State *state);
	void popState();
	void changeState(State *state);
	State* peekState();
private:
	std::stack<State*> m_states;
	sf::RenderWindow *m_window;
};