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
			if (_level->canMove(LEFT))
			{
				if (_player.getPosition().x < 400)
				{
					_player.stopMovingRL();
					_level->moveLeft();
					_player.moveLeft(false);
				}
				else {
					_level->stopHorizontalMoving();
					_player.moveLeft(true);
				}
			}
			else {
				_level->stopHorizontalMoving();
				_player.moveLeft(true);
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			if (_level->canMove(RIGHT))
			{
				if (_player.getPosition().x > 400)
				{
					_player.stopMovingRL();
					_level->moveRight();
					_player.moveRight(false);
				}
				else {
					_level->stopHorizontalMoving();
					_player.moveRight(true);
				}
			}
			else {
				_level->stopHorizontalMoving();
				_player.moveRight(true);
			}
		}
		else {
			_player.stopMovingRL();
			_level->stopHorizontalMoving();
			_player.stopMoving();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			if (_level->canMove(UP))
			{
				if (_player.getPosition().y < 300)
				{
					_player.stopMovingUD();
					_level->moveUp();
					_player.moveUp(false);
				}
				else {
					_level->stopVerticalMoving();
					_player.moveUp(true);
				}
			}
			else {
				_level->stopVerticalMoving();
				_player.moveUp(true);
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			if (_level->canMove(DOWN))
			{
				if (_player.getPosition().y > 350)
				{
					_player.stopMovingUD();
					_level->moveDown();
					_player.moveDown(false);
				}
				else {
					_level->stopVerticalMoving();
					_player.moveDown(true);
				}
			}
			else {
				_level->stopVerticalMoving();
				_player.moveDown(true);
			}
		}
		else {
			_player.stopMovingUD();
			_level->stopVerticalMoving();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			std::cout << (int)_level->m_collisionRectangles[0].getLeft() << " " << (int)_level->m_collisionRectangles[0].getTop() << std::endl;
			//_player.stopMovingRL();
			//_player.stopMovingUD();
			//_player.setPosition(400, 300);
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