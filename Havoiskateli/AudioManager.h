#pragma once

#include <SFML\Audio.hpp>
#include <vector>
#include <map>

#include "ResourceIdentifiers.hpp"


class AudioManager
{
public:
	static AudioManager *instance();
	void loadMusic();
	void playMusic(Musics::ID id, bool once = false);
	void playSound(Sounds::ID id, bool once = false);
	void changeVolume(float volume);

private:
	static AudioManager *m_instance;
	float m_musicVolume, m_soundVolume;
	sf::Music m_currentMusic;
	sf::SoundBuffer m_buffer;
};

