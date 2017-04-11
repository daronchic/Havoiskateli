#include "stdafx.h"
#include "GameState.h"
#include "Rectangle.h"
#include "Globals.h"
#include "ResourceManager.h"
#include "AudioManager.h"

#include <sstream>



GameState::GameState() : State()
{
}


GameState::GameState(sf::RenderWindow &window) : State(window)
{
}

GameState::~GameState()
{
}

StateCode GameState::complete()
{
	return m_stateCode;
}

void GameState::load()
{
	font.loadFromFile("content/fonts/8bitlimr.ttf");

	this->m_level = new Level("city_day/debug_level", Vector2(0, 0));
	this->m_player = Player(*ResourceManager::getInstance()->getImage(Images::player_2), 640 / 2, 480 / 2, 100, 3);
	this->m_hud = HUD(m_window->getSize().x - 180, m_window->getSize().y - 55);
	this->m_hud.load();
}

void GameState::init()
{
	m_playerView = sf::View(sf::FloatRect(m_player.getPosition().x, m_player.getPosition().y, m_window->getSize().x, m_window->getSize().y));
	m_hudView = sf::View(sf::FloatRect(0, 0, m_window->getSize().x, m_window->getSize().y));
	m_window->setView(m_playerView);
	m_player.setPosition(m_window->getSize().x / 2, m_window->getSize().y / 2);
	m_player.stopHorizontalMoving();
	m_player.stopVerticalMoving();
	m_viewX = m_player.getPosition().x;
	m_viewY = m_player.getPosition().y;
	m_hud.initialize(m_player.getLifes());

	m_speed.setPosition(100, 100);
	m_speed.setFont(font);

	AudioManager::instance()->playMusic(Musics::city);
}

void GameState::handleInput(sf::Event &event)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		m_window->close();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		m_player.moveLeft(true);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		m_player.moveRight(true);
	}
	else {
		m_player.stopHorizontalMoving();
		m_viewSpeedX = 0;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		m_player.moveUp(true);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		m_player.moveDown(true);
	}
	else {
		m_player.stopVerticalMoving();
		m_viewSpeedY = 0;
	}
	if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space)
	{
		m_hud.changeState();
	}

}

void GameState::update(float elapsed)
{
	std::vector<Rectangle> others;
	if ((others = this->m_level->checkTileCollision(this->m_player.getCollisonBox())).size() > 0) {
		this->m_player.handleTileCollisons(others);
	}
	std::stringstream ss;
	ss << "HorizontalSpeed: " << m_viewSpeedX << "\n" << "VerticalSpeed: " << m_viewSpeedY << "\n" <<
		"ViewCX = " << m_playerView.getCenter().x << "\n" << "ViewCY = " << m_playerView.getCenter().y;
	m_speed.setString(ss.str());

	m_player.update(elapsed);
	if(m_viewX != m_player.getPosition().x)
		m_viewSpeedX += 0.00002f * elapsed;
	else 
		if (m_viewSpeedX > 0.0f) m_viewSpeedX -= 0.00002f * elapsed;
	if (m_viewX < m_player.getPosition().x) {
		m_viewX += m_viewSpeedX;
	}
	if (m_viewX > m_player.getPosition().x) {
		m_viewX -= m_viewSpeedX;
	}

	if (m_viewY != m_player.getPosition().y)
		m_viewSpeedY += 0.00002f * elapsed;
	else
		if (m_viewSpeedY > 0.0f) m_viewSpeedY -= 0.00002f * elapsed;
	if (m_viewY < m_player.getPosition().y) {
		m_viewY += m_viewSpeedY;
	}
	if (m_viewY > m_player.getPosition().y) {
		m_viewY -= m_viewSpeedY;
	}

	if (m_playerView.getCenter().x + m_window->getSize().x / 2 >= globalData::levelWidth && m_player.getPosition().x > m_playerView.getCenter().x) {
		m_viewX = globalData::levelWidth - m_window->getSize().x / 2;
		m_viewSpeedX = 0;
	}
	if (m_playerView.getCenter().x - m_window->getSize().x / 2 <= 0 && m_player.getPosition().x < m_playerView.getCenter().x) {
		m_viewX = m_window->getSize().x / 2;
		m_viewSpeedX = 0;
	}
	if (m_playerView.getCenter().y - m_window->getSize().y / 2 <= 0 && m_player.getPosition().y < m_playerView.getCenter().y) {
		m_viewY = m_window->getSize().y / 2;
		m_viewSpeedY = 0;
	}
	if (m_playerView.getCenter().y + m_window->getSize().y / 2 >= globalData::levelHeight && m_player.getPosition().y > m_playerView.getCenter().y) {
		m_viewY = globalData::levelHeight - m_window->getSize().y / 2;
		m_viewSpeedY = 0;
	}
	m_playerView.setCenter(m_viewX, m_viewY);
	m_window->setView(m_playerView);
	m_level->update(elapsed);
	m_hud.update(elapsed);
}

void GameState::draw()
{
	m_level->draw(*m_window);
	m_window->draw(m_player);
	m_window->setView(m_hudView);
	m_hud.draw(*m_window);
	//m_window->draw(m_speed);
}
