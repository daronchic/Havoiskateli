#include "stdafx.h"
#include "Game.h"

#include <chrono>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

Game::Game()
{
	m_window.create(sf::VideoMode(1280, 1024), "Havoiskateli");
	load();
	init();
	gameLoop();
}


Game::~Game()
{
}

void Game::load() 
{
	this->_player = Player("player_4", 640 / 2, 480 / 2, 100, 3);
	this->_level = Level("city_day/debug_level2", Vector2(0, 0));
}

void Game::init() 
{
	m_window.setFramerateLimit(60);
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
			_player.moveLeft();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			_player.moveRight();
		}
		else {
			_player.stopMovingRL();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			_player.moveUp();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			_player.moveDown();
		}
		else {
			_player.stopMovingUD();
		}
	}
}

void Game::update() 
{
	m_currentSlice += m_lastft;
	for (; m_currentSlice >= -ftSlice; m_currentSlice -= ftSlice)
	{
		//Update game logic
		
		_player.update(m_currentSlice);
	}
}

void Game::draw() 
{
	m_window.clear(sf::Color::Blue);
	_level.draw(m_window);
	m_window.draw(_player);
	m_window.display();
}