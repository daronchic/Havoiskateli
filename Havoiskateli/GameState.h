#pragma once
#include "State.hpp"
#include "Player.h"
#include "Level.h"
#include "HUD.h"

class Player;
class Level;
class HUD;

class GameState :
	public State
{
public:
	GameState();
	GameState(sf::RenderWindow &window);
	~GameState();

	StateCode complete();
	void load();
	void init();
	void handleInput(sf::Event &event);
	void update(float elapsed);
	void draw();
private:
	Player m_player;
	Level* m_level;
	HUD m_hud;
	sf::View m_playerView;
	sf::View m_hudView;
	sf::Text m_speed;
	sf::Font font;
	float m_viewX, m_viewY, m_viewSpeedX, m_viewSpeedY;
};

