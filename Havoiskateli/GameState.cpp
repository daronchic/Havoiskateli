#include "stdafx.h"
#include "GameState.h"
#include "Rectangle.h"
#include "Globals.h"



GameState::GameState() : State()
{
}


GameState::GameState(sf::RenderWindow &window) : State(window)
{
}

GameState::~GameState()
{
}

void GameState::load()
{
	this->m_level = new Level("city_day/debug_level", Vector2(0, 0));
	this->m_player = Player("player_1", 640 / 2, 480 / 2, 100, 3);
	this->m_hud = HUD(globalData::screenWidth - 180, globalData::screenHeight - 55);
	this->m_hud.load();
}

void GameState::init()
{
	m_playerView = sf::View(sf::FloatRect(m_player.getPosition().x, m_player.getPosition().y, globalData::screenWidth, globalData::screenHeight));
	m_hudView = sf::View(sf::FloatRect(0, 0, globalData::screenWidth, globalData::screenHeight));
	m_window->setView(m_playerView);
	m_player.setPosition(globalData::screenWidth / 2, globalData::screenHeight / 2);
	m_player.stopHorizontalMoving();
	m_player.stopVerticalMoving();
	m_hud.initialize(m_player.getLifes());
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
	m_player.update(elapsed);
	m_viewX = m_player.getPosition().x;
	m_viewY = m_player.getPosition().y;
	if (m_playerView.getCenter().x + globalData::screenWidth / 2 >= globalData::levelWidth && m_player.getPosition().x > m_playerView.getCenter().x) {
		m_viewX = globalData::levelWidth - globalData::screenWidth / 2;
	}
	if (m_playerView.getCenter().x - globalData::screenWidth / 2 <= 0 && m_player.getPosition().x < m_playerView.getCenter().x) {
		m_viewX = globalData::screenWidth / 2;
	}
	if (m_playerView.getCenter().y - globalData::screenHeight / 2 <= 0 && m_player.getPosition().y < m_playerView.getCenter().y) {
		m_viewY = globalData::screenHeight / 2;
	}
	if (m_playerView.getCenter().y + globalData::screenHeight / 2 >= globalData::levelHeight && m_player.getPosition().y > m_playerView.getCenter().y) {
		m_viewY = globalData::levelHeight - globalData::screenHeight / 2;
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
}
