#include "stdafx.h"
#include "AudioManager.h"
#include "ResourceManager.h"


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
	m_currentMusic.openFromFile("content/music/main_theme.ogg");

	m_currentMusic.setVolume(m_musicVolume);
}

void AudioManager::playMusic(Musics::ID id, bool once) 
{
	if (m_currentMusic.getStatus() != sf::Music::Playing)
		m_currentMusic.play();
	if (!once) {
		//repeat
	}
}
void AudioManager::playSound(Sounds::ID id, bool once) {}
void AudioManager::changeVolume(float volume)
{
	m_musicVolume = volume;
	m_currentMusic.setVolume(m_musicVolume);
}
