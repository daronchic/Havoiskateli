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
	void stopMusic();
	void playSound(Sounds::ID id, bool once = false);
	void changeVolume(float music_volume = -1, float sound_volume = -1);

private:
	static AudioManager *m_instance;
	float m_musicVolume, m_soundVolume;
	sf::Music m_currentMusic;
	Musics::ID m_currentID{Musics::none};
	sf::Sound m_sound;
	std::map<Musics::ID, std::string> m_audioPath;
};

