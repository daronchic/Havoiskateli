#pragma once

#include "ResourceIdentifiers.hpp"
#include "ResourceHolder.hpp"

class ResourceManager
{
public:
	static ResourceManager* getInstance();

	sf::Font* getFont(Fonts::ID id);
	sf::Image* getImage(Images::ID id);
	sf::Sound *getSound(Sounds::ID id);
	sf::Music *getMusic(Musics::ID id);
private:
	static ResourceManager *m_instance;
	void loadData();

	bool m_loaded{ false };
	FontHolder m_fontHolder;
	ImagesHolder m_imageHolder;
	SoundHolder m_soundHolder;
	MusicHolder m_musicHolder;
};

