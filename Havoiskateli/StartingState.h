#pragma once
#include "State.hpp"
#include "Player.h"
#include "AnimatedObject.h"

struct PlayerData;

class StartingState :
	public State
{
public:
	StartingState();
	StartingState(sf::RenderWindow &window);
	~StartingState();

	StateCode complete();
	void load();
	void init();
	void handleInput(sf::Event &event);
	void update(float elapsed);
	void setPlayerData();
	void draw();
private:
	int m_switched{ 3 };
	std::vector<Player*> m_players;
	std::vector<AnimatedObject*> m_playerStands;
	std::vector<PlayerData> m_playerData;
	sf::RectangleShape m_descriptionRect;
	int m_switchedY;
	MSprite m_bigStand;

	sf::String m_descriptionString;
	sf::Text m_descriptionText;
};