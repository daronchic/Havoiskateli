#pragma once
#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"
#include "State.hpp"
#include "MSprite.h"

class MainmenuState :
	public State
{
public:
	MainmenuState();
	MainmenuState(sf::RenderWindow &window);
	~MainmenuState();

	void load();
	void init();
	void handleInput(sf::Event &event);
	void update(float elapsed);
	void draw();
private:
	sf::Font m_menuFont;
	sf::Font m_buttonFont;
	std::vector<sf::Text> m_buttons;
	sf::Text m_title;
	std::vector<MSprite> m_background;
	int m_currentBackground{ 0 };
	sf::Time m_timer;
	MSprite m_back;
	ImagesHolder m_imagesHolder;
	FontHolder m_fontHolder;
	SoundHolder m_soundHolder;
	MusicHolder m_musicHolder;
};

