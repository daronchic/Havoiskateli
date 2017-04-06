#include "stdafx.h"
#include "StartingState.h"
#include "ResourceManager.h"
#include "Globals.h"

StartingState::StartingState() : State()
{
}

StartingState::StartingState(sf::RenderWindow &window) : State(window)
{
}


StartingState::~StartingState()
{
	for each (auto stands in m_playerStands)
	{
		delete stands;
	}
	for each (auto players in m_players)
	{
		delete players;
	}
	m_players.clear();
	m_playerStands.clear();
}

StateCode StartingState::complete()
{
	return m_stateCode;
}

void StartingState::load()
{
	m_bigStand = MSprite(*ResourceManager::getInstance()->getImage(Images::menu_StartingWindow), 0, 0, 407, 111, 0, 0);
	for (int i = 0; i < 6; i++) {
		m_playerStands.emplace_back(new AnimatedObject(*ResourceManager::getInstance()->getImage(Images::menu_stand), 0, 0));
	}
	m_players.emplace_back(new Player(*ResourceManager::getInstance()->getImage(Images::player_1), 0, 0, 0, 0));
	m_players.emplace_back(new Player(*ResourceManager::getInstance()->getImage(Images::player_2), 0, 0, 0, 0));
	m_players.emplace_back(new Player(*ResourceManager::getInstance()->getImage(Images::player_3), 0, 0, 0, 0));
	m_players.emplace_back(new Player(*ResourceManager::getInstance()->getImage(Images::player_4), 0, 0, 0, 0));
	m_players.emplace_back(new Player(*ResourceManager::getInstance()->getImage(Images::player_1), 0, 0, 0, 0));
	m_players.emplace_back(new Player(*ResourceManager::getInstance()->getImage(Images::player_2), 0, 0, 0, 0));

}

void StartingState::init()
{
	m_switchedY = m_window->getSize().y / 4 - 47;
	m_bigStand.setPosition(m_window->getSize().x / 2 - m_bigStand.getLocalBounds().width / 2, m_window->getSize().y / 4);
	for (int i = 0; i < 6; i++) {
		m_playerStands[i]->setPosition(m_window->getSize().x / 2 - 3 * 55 + i * 55, m_window->getSize().y / 4);
	}
	for (int i = 0; i < 6; i++) {
		m_players[i]->setPosition(m_window->getSize().x / 2 - 3 * 55 + i * 55, m_window->getSize().y / 4 - 15);
	}
	m_descriptionRect = sf::RectangleShape(sf::Vector2f(m_window->getSize().x / 2, m_window->getSize().y / 2));
	m_descriptionRect.setPosition(m_window->getSize().x / 2-m_descriptionRect.getSize().x / 2, m_window->getSize().y / 2);
	m_descriptionRect.setFillColor(sf::Color(128, 109, 176, 217));
}

void StartingState::handleInput(sf::Event & event)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		m_stateCode = StateCode::MENU;
	}
	if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Left) {
		m_switched--;
	}
	else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Right) {
		m_switched++;
	}
}

void StartingState::update(float elapsed)
{
	if (m_switched > 5)
		m_switched = 0;
	else if (m_switched < 0)
		m_switched = 5;
	for (int i = 0; i < m_playerStands.size(); i++)
	{
		if (i == m_switched) {
			m_playerStands[i]->changeState(true);
			if (m_players[i]->getPosition().y > m_switchedY) {
				m_players[i]->moveUp(true);
			}
			else {
				m_players[i]->stopVerticalMoving();
			}
		}
		else {
			m_playerStands[i]->changeState(false);
			if (m_players[i]->getPosition().y < m_switchedY + 32) {
				m_players[i]->moveDown(true);
			}
			else {
				m_players[i]->stopVerticalMoving();
			}
		}
		m_playerStands[i]->update(elapsed);
		m_players[i]->update(elapsed);
	}
}

void StartingState::draw()
{
	m_window->clear(sf::Color(86, 86, 124));
	m_window->draw(m_bigStand);
	for each (auto stands in m_playerStands)
	{
		m_window->draw(*stands);
	}
	for each (auto players in m_players)
	{
		m_window->draw(*players);
	}
	m_window->draw(m_descriptionRect);
}
