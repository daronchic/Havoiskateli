#pragma once

#include "ResourceIdentifiers.hpp"
#include "ResourceHolder.hpp"

class ResourceManager
{
	static ResourceManager* getInstance();

	sf::Font getFont(Fonts::ID id);
	sf::Image getImage(Images::ID id);
	sf::Sound *getSound(Sounds::ID id);
	sf::Music *getMusic(Musics::ID id);
private:
	static ResourceManager *m_instance;
	void loadData();

	FontHolder m_fontHolder;
	ImagesHolder m_imageHolder;
	SoundHolder m_soundHolder;
	MusicHolder m_musicHolder;
};

