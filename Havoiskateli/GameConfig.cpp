#include "stdafx.h"
#include "GameConfig.h"
#include <iostream>

GameConfig *GameConfig::m_instance = nullptr;

GameConfig * GameConfig::instance()
{
	if (!m_instance) {
		m_instance = new GameConfig;
		if (!m_instance->m_parser.loadFromFile("content/configuration/default.conf")) {
			std::cout << "Error reading file config!" << std::endl;
		}
	}
	return m_instance;
}

Vector2 GameConfig::getScreenSize()
{
	int width, height;
	m_parser.get("width", width);
	m_parser.get("height", height);
	return Vector2(width, height);
}

bool GameConfig::getScreenMode()
{
	bool mode;
	m_parser.get("fullscreen", mode);
	return mode;
}

bool GameConfig::getVerticalSync()
{
	bool vertSync;
	m_parser.get("verticalSync", vertSync);
	return vertSync;
}

float GameConfig::getMusicVolume()
{
	int volume;
	m_parser.get("music_volume", volume);
	return (float)volume;
}

float GameConfig::getSoundVolume()
{
	float volume;
	m_parser.get("sound_volume", volume);
	return volume;
}

void GameConfig::setScreenSize(const Vector2 & size)
{
	m_parser.set("width", size.x);
	m_parser.set("height", size.y);
	if (!m_parser.saveToFile()) {
		std::cout << "Error writing config file!" << std::endl;
	}
}

void GameConfig::setScreenMode(bool mode)
{
	m_parser.set("fullscreen", mode);
	if (!m_parser.saveToFile()) {
		std::cout << "Error writing config file!" << std::endl;
	}
}

void GameConfig::setVerticalSync(bool value)
{
	m_parser.set("verticalSync", value);
	if (!m_parser.saveToFile()) {
		std::cout << "Error writing config file!" << std::endl;
	}
}

void GameConfig::setMusicVolume(int value)
{
	m_parser.set("music_volume", value*10);
	if (!m_parser.saveToFile()) {
		std::cout << "Error writing config file!" << std::endl;
	}
}

void GameConfig::setSoundVolume(int value)
{
	m_parser.set("sound_volume", value*10);
	if (!m_parser.saveToFile()) {
		std::cout << "Error writing config file!" << std::endl;
	}
}
