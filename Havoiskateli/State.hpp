#pragma once

#include "GameConfig.h"
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include "ResourceIdentifiers.hpp"
#include "Globals.h"

class State
{
public:
	State() {}
	State(sf::RenderWindow &window) : m_window(&window) {}
	virtual StateCode complete() = 0;
	virtual void load() = 0;
	virtual void init() = 0;
	virtual void handleInput(sf::Event &event) = 0;
	virtual void update(float elapsed) = 0;
	virtual void draw() = 0;
protected:
	sf::RenderWindow *m_window;
	StateCode m_stateCode{ StateCode::NONE };
};