#pragma once

#include <SFML\Graphics.hpp>

class State
{
public:
	State() {}
	State(sf::RenderWindow &window) : m_window(&window) {}
	virtual void load() = 0;
	virtual void init() = 0;
	virtual void handleInput(sf::Event &event) = 0;
	virtual void update(float elapsed) = 0;
	virtual void draw() = 0;
protected:
	sf::RenderWindow *m_window;
};