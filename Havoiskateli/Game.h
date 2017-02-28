#pragma once

#include <SFML\Graphics.hpp>
#include "MSprite.h"
#include "Player.h"

using FrameTime = float;

enum State {
	MENU,
	GAME,
	PAUSE
};
class Game
{
	constexpr static float ftStep{ 1.f }, ftSlice{ 1.f };
public:
	Game();
	~Game();
	void load();
	void init();
	void input();
	void gameLoop();
	void update();
	void draw();

private:
	sf::RenderWindow m_window;
	FrameTime m_lastft{ 0.f }, m_currentSlice{ 0.f };
	Player _player;

};

