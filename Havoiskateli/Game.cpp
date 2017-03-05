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
	this->_player = Player("player_1", 640 / 2, 480 / 2, 100, 3);
	this->_level = Level("city_day/debug_level", Vector2(0, 0));
}

void Game::init() 
{
	m_window.setFramerateLimit(60);
	m_levelTexture.create(1250, 1250); 
	m_levelSprite.setTexture(m_levelTexture.getTexture());
	/*m_levelSprite.setScale(static_cast<float> (m_window.getSize().x) / m_levelTexture.getSize().x,
		static_cast<float> (m_window.getSize().y) / m_levelTexture.getSize().y); //Resize*/
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
	std::cout << m_levelSprite.getPosition().x;
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
			if (m_levelSprite.getPosition().x > -32) {
				m_dx = 0.0f;
			}
			else {
				m_dx = 0.01f;
			}
			_player.moveLeft();

		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			_player.moveRight();
			if (m_levelSprite.getPosition().x + m_levelSprite.getTexture()->getSize().x < 790) {
				m_dx = 0.0f;
			}
			else {
				m_dx = -0.01f;
			}
		}
		else {
			_player.stopMovingRL();
			m_dx = 0;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			_player.moveUp();
			if (m_levelSprite.getPosition().y > -32) {
				m_dy = 0.0f;
			}
			else {
				m_dy = 0.01f;
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			_player.moveDown();
			if (m_levelSprite.getPosition().y + m_levelSprite.getTexture()->getSize().y < 590) {
				m_dy = 0.0f;
			}
			else {
				m_dy = -0.01f;
			}
		}
		else {
			_player.stopMovingUD();
			m_dy = 0;
		}
	}
}

void Game::update() 
{
	m_currentSlice += m_lastft;
	for (; m_currentSlice >= -ftSlice; m_currentSlice -= ftSlice)
	{
		//Update game logic
		m_levelSprite.move(m_dx * m_currentSlice, m_dy * m_currentSlice);
		_player.update(m_currentSlice);
	}
}

void Game::draw() 
{
	m_window.clear(sf::Color::Cyan);
	_level.draw(m_levelTexture);
	m_window.draw(m_levelSprite);
	m_window.draw(_player);
	m_levelTexture.display();
	m_window.display();
}