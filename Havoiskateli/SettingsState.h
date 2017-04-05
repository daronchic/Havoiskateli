#pragma once
#include "State.hpp"
#include "Globals.h"
#include "MSprite.h"
#include "ResourceIdentifiers.hpp"
#include "ResourceHolder.hpp"

#include <TGUI\TGUI.hpp>

class SettingsState :
	public State
{
public:
	SettingsState();
	SettingsState(sf::RenderWindow &window);
	~SettingsState();

	StateCode complete();
	void load();
	void init();
	void handleInput(sf::Event &event);
	void update(float elapsed);
	void draw();
	void saveSettings();
private:
	void createGui();

	sf::Text m_title;
	std::vector<MSprite> m_background;
	int m_currentBackground{ 0 };
	sf::Time m_timer;
	sf::RectangleShape m_settingsBack;
	ImagesHolder m_imagesHolder;
	FontHolder m_fontHolder;
	SoundHolder m_soundHolder;
	MusicHolder m_musicHolder;
	tgui::Gui m_gui;
};
