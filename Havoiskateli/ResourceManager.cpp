#include "stdafx.h"
#include "ResourceManager.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

ResourceManager *ResourceManager::m_instance = nullptr;

ResourceManager * ResourceManager::getInstance()
{
	if (!m_instance) {
		m_instance = new ResourceManager;
		m_instance->loadData();
	}
	return m_instance;
}

sf::Font *ResourceManager::getFont(Fonts::ID id)
{
	return &m_fontHolder.get(id);
}

sf::Image *ResourceManager::getImage(Images::ID id)
{
	return &m_imageHolder.get(id);
}

sf::Sound *ResourceManager::getSound(Sounds::ID id)
{
	return &m_soundHolder.get(id);
}

void ResourceManager::loadData()
{
	//Get fonts
	m_fontHolder.load(Fonts::titleFont, "content/fonts/zerovelo.ttf");
	m_fontHolder.load(Fonts::menuFont, "content/fonts/8bitlimr.ttf");

	//Get Images
	m_imageHolder.load(Images::player_1, "content/images/player/player_1.png");
	m_imageHolder.load(Images::player_2, "content/images/player/player_2.png");
	m_imageHolder.load(Images::player_3, "content/images/player/player_3.png");
	m_imageHolder.load(Images::player_4, "content/images/player/player_4.png");
	m_imageHolder.load(Images::menu_StartingWindow, "content/images/main_menu/startingMenu.png");
	m_imageHolder.load(Images::menu_stand, "content/images/main_menu/player_stand.png");

	//Get sounds

}
