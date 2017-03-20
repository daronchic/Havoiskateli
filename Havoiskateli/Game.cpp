#include "stdafx.h"
#include "Game.h"

#include <chrono>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

Game::Game()
{
	m_window.create(sf::VideoMode(800, 600), "Havoiskateli");
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
}

void Game::init() 
{
	m_window.setFramerateLimit(60);
	m_playerView = sf::View(sf::FloatRect(_player.getPosition().x, _player.getPosition().y, 800, 600));
	m_window.setView(m_playerView);
	sf::Joystick::Identification id = sf::Joystick::getIdentification(0);
	std::cout << "\nVendor ID: " << id.vendorId << "\nProduct ID: " << id.productId << std::endl;
	sf::String controller("Joystick Use: " + id.name);
	_player.setPosition(400, 300);
	_player.stopMovingRL();
	_player.stopMovingUD();
	if (sf::Joystick::isConnected(0)) {
		// check how many buttons joystick number 0 has
		unsigned int buttonCount = sf::Joystick::getButtonCount(0);

		// check if joystick number 0 has a Z axis
		bool hasZ = sf::Joystick::hasAxis(0, sf::Joystick::Z);

		std::cout << "Button count: " << buttonCount << std::endl;
		std::cout << "Has a z-axis: " << hasZ << std::endl;
	}
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
			_player.stopMovingRL();
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
			_player.stopMovingUD();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			std::cout << (int)_level->m_collisionRectangles[0].getLeft() << " " << (int)_level->m_collisionRectangles[0].getTop() << std::endl;
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
		if (m_playerView.getCenter().x + 400 >= 1500 && _player.getPosition().x > m_playerView.getCenter().x) {
			viewX = 1500 - 400;
		}
		if (m_playerView.getCenter().x - 400 <= 0 && _player.getPosition().x < m_playerView.getCenter().x) {
			viewX = 400;
		}
		if (m_playerView.getCenter().y - 300 <= 0 && _player.getPosition().y < m_playerView.getCenter().y) {
			viewY = 300;
		}
		if (m_playerView.getCenter().y + 300 >= 1500 && _player.getPosition().y > m_playerView.getCenter().y) {
			viewY = 1500 - 300;
		}
		m_playerView.setCenter(viewX, viewY);
		m_window.setView(m_playerView);
		_level->update(m_currentSlice);
	}
}

void Game::draw() 
{
	m_window.clear(sf::Color::Cyan);
	_level->draw(m_window);
	//m_window.draw(m_levelSprite);
	m_window.draw(_player);
	//m_levelTexture.display();
	m_window.display();
}