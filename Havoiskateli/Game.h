#pragma once

#include <SFML\Graphics.hpp>
#include "StateStack.h"
#include "GameState.h"
#include "MSprite.h"
#include "Player.h"
#include "Level.h"
#include "HUD.h"


//Background movement 1#
//Draw background on sprite, move this sprite, draw player as usual

using FrameTime = float;

class Game
{
	constexpr static float ftStep{ 1.f }, ftSlice{ 1.f };
public:
	Game();
	~Game();
	void registerStates();
	void load();
	void init();
	void input();
	void gameLoop();
	void update();
	void draw();

private:
	sf::RenderWindow m_window;
	FrameTime m_lastft{ 0.f }, m_currentSlice{ 0.f };
	StateStack m_stateStack;
};

