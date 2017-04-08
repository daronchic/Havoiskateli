#include "stdafx.h"
#include "MainmenuState.h"
#include "Globals.h"
#include "ResourceManager.h"


MainmenuState::MainmenuState() : State()
{
}

MainmenuState::MainmenuState(sf::RenderWindow &window) : State(window)
{
}


MainmenuState::~MainmenuState()
{
}

StateCode MainmenuState::complete()
{
	return m_stateCode;
}

void MainmenuState::load()
{
	m_background.emplace_back(MSprite("content/images/main_menu/background_1.png", 0, 0, 1366, 768, 0, 0));
	m_background.emplace_back(MSprite("content/images/main_menu/background_2.png", 0, 0, 1366, 768, 0, 0));
	m_background.emplace_back(MSprite("content/images/main_menu/background_3.png", 0, 0, 1366, 768, 0, 0));
	m_background.emplace_back(MSprite("content/images/main_menu/background_4.png", 0, 0, 1366, 768, 0, 0));
}

void MainmenuState::init()
{
	//m_audioManager.playMusic(Musics::menu);
	AudioManager::instance()->changeVolume(GameConfig::instance()->getMusicVolume());

	m_title.setCharacterSize(50);
	m_title.setString("HAVOISKATELI");
	m_title.setFont(*ResourceManager::getInstance()->getFont(Fonts::titleFont));
	m_title.setFillColor(sf::Color(255, 251, 75));
	m_title.setPosition(m_window->getSize().x / 2 - m_title.getGlobalBounds().width / 2, 50);

	m_buttons.emplace_back(sf::Text("New Game", *ResourceManager::getInstance()->getFont(Fonts::menuFont), 50));
	m_buttons.emplace_back(sf::Text("Options", *ResourceManager::getInstance()->getFont(Fonts::menuFont), 50));
	m_buttons.emplace_back(sf::Text("Exit", *ResourceManager::getInstance()->getFont(Fonts::menuFont), 50));
	for (int i = 0; i < m_buttons.size(); i++) {
		m_buttons.at(i).setPosition(m_window->getSize().x / 2 - m_buttons.at(i).getGlobalBounds().width / 2, m_window->getSize().y / 2 + i * 64);
		m_buttons.at(i).setFillColor(sf::Color(79, 65, 116));
	}
	m_buttonsBack.setSize(sf::Vector2f(210, 200));
	m_buttonsBack.setFillColor(sf::Color(128, 109, 176, 217));
	m_buttonsBack.setPosition(m_buttons.front().getPosition());
}

void MainmenuState::handleInput(sf::Event & event)
{
	if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Up) {
		m_switched--;
	}
	else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Down) {
		m_switched++;
	}
	if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Return) {
		if (m_switched == 0) {
			m_stateCode = StateCode::NEW_GAME;
		}
		if (m_switched == 1) {
			m_stateCode = StateCode::OPTIONS;
		}
		if (m_switched == 2) {
			m_stateCode = StateCode::EXIT;
		}
	}
}

void MainmenuState::update(float elapsed)
{
	AudioManager::instance()->playMusic(Musics::menu);
	m_timer += sf::seconds(1);
	if (m_timer >= sf::seconds(10000)) {
		m_currentBackground = rand() % 4;
		m_timer = sf::seconds(0);
	}
	if (m_switched > 2)
		m_switched = 0;
	else if (m_switched < 0)
		m_switched = 2;
	for(int i = 0; i < m_buttons.size(); i++)
	{
		if (i == m_switched) {
			m_buttons[i].setFillColor(sf::Color(187, 160, 255));
		}
		else {
			m_buttons[i].setFillColor(sf::Color(79, 65, 116));
		}
	}
	m_buttons.at(m_switched).setFillColor(sf::Color(187, 160, 255));
}

void MainmenuState::draw()
{
	m_window->draw(m_background.at(m_currentBackground));
	m_window->draw(m_title);
	m_window->draw(m_buttonsBack);
	for each (auto text in m_buttons)
	{
		m_window->draw(text);
	}
}
