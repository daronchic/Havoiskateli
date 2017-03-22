#pragma once

#include "Globals.h"
#include "MSprite.h"


class HUD
{
public:
	HUD();
	HUD(int x, int y);
	void load();
	void initialize();
	void update(int elapsedTime);
	void draw(sf::RenderWindow &window);

	void changeState();
private: 
	void open(int elapsedTime);
	void close(int elapsedTime);
	bool m_opened;
	MSprite m_panel;
	MSprite m_playerData;
	MSprite m_inventoryBlock;
	MSprite m_additionalBlock;
	MSprite m_life;
	std::vector<MSprite> m_additionalBox;
	float m_x, m_y;
	Vector2 CLOSED_POSITION;
	Vector2 OPENED_POSITION;

};

