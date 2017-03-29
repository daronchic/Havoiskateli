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
	m_stateStack = StateStack(m_window);
	m_stateStack.pushState(new GameState(m_window));
	load();
	init();
	gameLoop();
}


Game::~Game()
{
}

void Game::load() 
{
	m_stateStack.peekState()->load();
}

void Game::init() 
{
	m_window.setFramerateLimit(60);
	m_stateStack.peekState()->init();
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
		m_stateStack.peekState()->handleInput(event);
	}
}

void Game::update() 
{
	m_currentSlice += m_lastft;

	for (; m_currentSlice >= -ftSlice; m_currentSlice -= ftSlice)
	{
		m_stateStack.peekState()->update(m_currentSlice);
	}
}

void Game::draw() 
{
	m_window.clear(sf::Color::Cyan);
	m_stateStack.peekState()->draw();
	m_window.display();
}