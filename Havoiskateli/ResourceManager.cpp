#include "stdafx.h"
#include "ResourceManager.h"
#include "SFML\Graphics.hpp"
#include "SFML\Audio\Music.hpp"
#include "SFML\Audio.hpp"

ResourceManager *ResourceManager::m_instance = nullptr;

ResourceManager * ResourceManager::getInstance()
{
	if (m_instance == nullptr) {
		m_instance = new ResourceManager();
	}
	return m_instance;
}

sf::Font ResourceManager::getFont(Fonts::ID id)
{
	return m_fontHolder.get(id);
}

sf::Image ResourceManager::getImage(Images::ID id)
{
	return m_imageHolder.get(id);
}

sf::Sound *ResourceManager::getSound(Sounds::ID id)
{
	return &m_soundHolder.get(id);
}

sf::Music *ResourceManager::getMusic(Musics::ID id)
{
	return &m_musicHolder.get(id);
}

void ResourceManager::loadData()
{
}
