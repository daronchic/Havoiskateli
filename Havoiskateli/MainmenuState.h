#pragma once
#include "Globals.h"
#include "State.hpp"
#include "MSprite.h"
#include "AudioManager.h"

class MainmenuState :
	public State
{
public:
	MainmenuState();
	MainmenuState(sf::RenderWindow &window);
	~MainmenuState();

	StateCode complete();
	void load();
	void init();
	void handleInput(sf::Event &event);
	void update(float elapsed);
	void draw();
private:
	std::vector<sf::Text> m_buttons;
	int m_switched{ 0 };
	sf::Text m_title;
	std::vector<MSprite> m_background;
	int m_currentBackground{ 0 };
	sf::Time m_timer;
	MSprite m_back;
	sf::RectangleShape m_buttonsBack;
};

