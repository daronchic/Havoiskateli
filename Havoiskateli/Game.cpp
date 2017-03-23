#include "stdafx.h"
#include "Game.h"

#include <chrono>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

Game::Game()
{
	m_window.create(sf::VideoMode(globalData::screenWidth, globalData::screenHeight), "Havoiskateli", sf::Style::Fullscreen);
	load();
	init();
	gameLoop();
}


Game::~Game()
{
}

void Game::load() 
{
	this->_level = new Level("city_day/debug_level", Vector2(0, 0));
	this->_player = Player("player_1", 640 / 2, 480 / 2, 100, 3);
	this->_hud = HUD(globalData::screenWidth - 180, globalData::screenHeight - 55);
	this->_hud.load();
}

void Game::init() 
{
	m_window.setFramerateLimit(60);
	m_playerView = sf::View(sf::FloatRect(_player.getPosition().x, _player.getPosition().y, globalData::screenWidth, globalData::screenHeight));
	m_hudView = sf::View(sf::FloatRect(0, 0, globalData::screenWidth, globalData::screenHeight));
	m_window.setView(m_playerView);
	_player.setPosition(globalData::screenWidth / 2, globalData::screenHeight / 2);
	_player.stopHorizontalMoving();
	_player.stopVerticalMoving();
	_hud.initialize(_player.getLifes());
}

void Game::gameLoop() 
{
	while (m_window.isOpen())
	{
		auto timePoint1(chrono::high_resolution_clock::now());

		this->input();
		this->update();
		this->draw();

		auto timePoint2(chrono::high_resolution_clock::now());
		auto elapsedTime(timePoint2 - timePoint1);
		FrameTime ft{ chrono::duration_cast<chrono::duration<float, milli> >(elapsedTime).count() };

		m_lastft = ft;

		auto ftSeconds(ft / 1000.f);
		auto fps(1.f / ftSeconds);
		//std::cout << fps << endl;

	}
}

void Game::input() 
{
	sf::Event event;
	Vector2 speed;
	while (m_window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			m_window.close();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			m_window.close();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
					_player.moveLeft(true);

		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
				_player.moveRight(true);
		}
		else {
			_player.stopHorizontalMoving();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
				_player.moveUp(true);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
				_player.moveDown(true);
		}
		else {
			_player.stopVerticalMoving();
		}
		if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space)
		{
			_hud.changeState();
		}
	}
}

void Game::update() 
{
	m_currentSlice += m_lastft;

	for (; m_currentSlice >= -ftSlice; m_currentSlice -= ftSlice)
	{
		//Update game logic
		std::vector<Rectangle> others;
		if ((others = this->_level->checkTileCollision(this->_player.getCollisonBox())).size() > 0) {
			this->_player.handleTileCollisons(others);
		}
		_player.update(m_currentSlice);
		viewX = _player.getPosition().x;
		viewY = _player.getPosition().y;
		if (m_playerView.getCenter().x + globalData::screenWidth / 2 >= globalData::levelWidth && _player.getPosition().x > m_playerView.getCenter().x) {
			viewX = globalData::levelWidth - globalData::screenWidth / 2;
		}
		if (m_playerView.getCenter().x - globalData::screenWidth / 2 <= 0 && _player.getPosition().x < m_playerView.getCenter().x) {
			viewX = globalData::screenWidth / 2;
		}
		if (m_playerView.getCenter().y - globalData::screenHeight / 2 <= 0 && _player.getPosition().y < m_playerView.getCenter().y) {
			viewY = globalData::screenHeight / 2;
		}
		if (m_playerView.getCenter().y + globalData::screenHeight / 2 >= globalData::levelHeight && _player.getPosition().y > m_playerView.getCenter().y) {
			viewY = globalData::levelHeight - globalData::screenHeight / 2;
		}
		m_playerView.setCenter(viewX, viewY);
		m_window.setView(m_playerView);
		_level->update(m_currentSlice);
		_hud.update(m_currentSlice);
	}
}

void Game::draw() 
{
	m_window.clear(sf::Color::Cyan);
	_level->draw(m_window);
	m_window.draw(_player);
	m_window.setView(m_hudView);
	_hud.draw(m_window);
	m_window.display();
}