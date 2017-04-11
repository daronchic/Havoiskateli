#include "stdafx.h"
#include "AudioManager.h"
#include "ResourceManager.h"

#include <iostream>

AudioManager *AudioManager::m_instance = nullptr;

AudioManager * AudioManager::instance()
{
	if (!m_instance) {
		m_instance = new AudioManager;
		m_instance->loadMusic();
	}
	return m_instance;
}

void AudioManager::loadMusic()
{
	m_audioPath[Musics::menu] = "content/music/main_theme.ogg";
	m_audioPath[Musics::city] = "content/music/city_theme.ogg";

	m_currentMusic.setVolume(m_musicVolume);
	m_sound.setVolume(m_soundVolume);
}

void AudioManager::playMusic(Musics::ID id, bool once) 
{
	stopMusic();
	if (!m_currentMusic.openFromFile(m_audioPath[id])) {
		std::cout << "Error while loading audio file!" << std::endl;
	}
	m_currentMusic.setLoop(!once);
	m_currentMusic.play();
}

void AudioManager::stopMusic()
{
	if (m_currentMusic.getStatus() == sf::Music::Playing) {
		m_currentMusic.stop();
	}
}

void AudioManager::playSound(Sounds::ID id, bool once) 
{
	m_sound.setBuffer(*ResourceManager::getInstance()->getSound(id));
	m_sound.setLoop(!once);
	m_sound.play();
}
void AudioManager::changeVolume(float music_volume, float sound_volume)
{
	if (music_volume > 0) {
		m_musicVolume = music_volume;
		m_currentMusic.setVolume(m_musicVolume);
	}
	if (sound_volume > 0) {
		m_soundVolume = sound_volume;
		m_sound.setVolume(m_soundVolume);
	}

}
