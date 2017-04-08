#pragma once
#include "SettingsParser.hpp"
#include "Globals.h"
#include "GameConfig.h"

class GameConfig
{
public:
	static GameConfig *instance();
	Vector2 getScreenSize();
	bool getScreenMode();
	bool getVerticalSync();
	float getMusicVolume();
	float getSoundVolume();

	void setScreenSize(const Vector2 &size);
	void setScreenMode(bool mode);
	void setVerticalSync(bool value);
	void setMusicVolume(int value);
	void setSoundVolume(int value);

private:
	static GameConfig *m_instance;
	SettingsParser m_parser;
};
