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
	m_levelTexture.create(1600, 1600); 
	m_levelSprite.setTexture(m_levelTexture.getTexture());
	m_levelWidth = m_levelSprite.getTexture()->getSize().x;
	m_levelHeight = m_levelSprite.getTexture()->getSize().y;
	/*m_levelSprite.setScale(static_cast<float> (m_window.getSize().x) / m_levelTexture.getSize().x,
		static_cast<float> (m_window.getSize().y) / m_levelTexture.getSize().y); //Resize*/

	sf::Joystick::Identification id = sf::Joystick::getIdentification(0);
	std::cout << "\nVendor ID: " << id.vendorId << "\nProduct ID: " << id.productId << std::endl;
	sf::String controller("Joystick Use: " + id.name);

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
			if (m_levelSprite.getPosition().x > -32.0f) {
				m_dx = 0.0f;
				_player.moveLeft(true);
			}
			else {
				m_dx = 0.02f;
				_player.moveLeft(false);
			}
			

		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{

			if (m_levelSprite.getPosition().x + m_levelSprite.getTexture()->getSize().x < 800) {
				m_dx = 0.0f;
				_player.moveRight(true);
			}
			else {
				m_dx = -0.02f;
				_player.moveRight(false);
			}
		}
		else {
			_player.stopMovingRL();
			m_dx = 0;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{

			if (m_levelSprite.getPosition().y > -32.0f) {
				m_dy = 0.0f;
				_player.moveUp(true);
			}
			else {
				m_dy = 0.02f;
				_player.moveUp(false);
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{

			if (m_levelSprite.getPosition().y + m_levelSprite.getTexture()->getSize().y <= 568.f) {
				m_dy = 0.0f;
				_player.moveDown(true);
			}
			else {
				m_dy = -0.02f;
				_player.moveDown(false);
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
		if ((m_levelSprite.getPosition().x + m_levelSprite.getTexture()->getSize().x) < 800) {

			m_levelSprite.setPosition((800 - m_levelWidth), m_levelSprite.getPosition().y);
		}
		if ((m_levelSprite.getPosition().y + m_levelSprite.getTexture()->getSize().y) < 600) {
			m_levelSprite.setPosition(m_levelSprite.getPosition().x, 600 - m_levelHeight);
		}
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