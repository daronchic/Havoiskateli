#include "stdafx.h"
#include "MainmenuState.h"
#include "Globals.h"


MainmenuState::MainmenuState() : State()
{
}

MainmenuState::MainmenuState(sf::RenderWindow &window) : State(window)
{
}


MainmenuState::~MainmenuState()
{
}

void MainmenuState::load()
{
	m_fontHolder.load(Fonts::titleFont, "content/fonts/zerovelo.ttf");
	m_fontHolder.load(Fonts::menuFont, "content/fonts/8bitlimr.ttf");
	m_background.emplace_back(MSprite("content/images/main_menu/background_1.png", 0, 0, 1366, 768, 0, 0));
	m_background.emplace_back(MSprite("content/images/main_menu/background_2.png", 0, 0, 1366, 768, 0, 0));
	m_background.emplace_back(MSprite("content/images/main_menu/background_3.png", 0, 0, 1366, 768, 0, 0));
	m_background.emplace_back(MSprite("content/images/main_menu/background_4.png", 0, 0, 1366, 768, 0, 0));
}

void MainmenuState::init()
{
	m_title.setCharacterSize(50);
	m_title.setString("HAVOISKATELI");
	m_title.setFont(m_fontHolder.get(Fonts::titleFont));
	m_title.setFillColor(sf::Color(255, 251, 75));
	m_title.setPosition(globalData::screenWidth / 2 - m_title.getGlobalBounds().width / 2, 50);

	m_buttons.emplace_back(sf::Text("New Game", m_fontHolder.get(Fonts::menuFont), 50));
	m_buttons.emplace_back(sf::Text("Options", m_fontHolder.get(Fonts::menuFont), 50));
	m_buttons.emplace_back(sf::Text("Exit", m_fontHolder.get(Fonts::menuFont), 50));
	for (int i = 0; i < m_buttons.size(); i++) {
		m_buttons.at(i).setPosition(globalData::screenWidth / 2 - m_buttons.at(i).getGlobalBounds().width / 2, globalData::screenHeight / 2 + i * 64);
		m_buttons.at(i).setFillColor(sf::Color(129, 99, 150));
	}
}

void MainmenuState::handleInput(sf::Event & event)
{
}

void MainmenuState::update(float elapsed)
{
	m_timer += sf::seconds(1);
	if (m_timer >= sf::seconds(10000)) {
		m_currentBackground = rand() % 4;
		m_timer = sf::seconds(0);
	}
}

void MainmenuState::draw()
{
	m_window->draw(m_background.at(m_currentBackground));
	m_window->draw(m_title);
	for each (auto text in m_buttons)
	{
		m_window->draw(text);
	}
}
