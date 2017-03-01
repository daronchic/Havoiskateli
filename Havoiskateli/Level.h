#pragma once

#include "Globals.h"
#include <string>
#include <SFML\Graphics.hpp>

class Level
{
public:
	Level();
	Level(std::string mapName, Vector2 spawnPoint);
	~Level();

	void update(float elapsedTime);
	void draw(sf::RenderWindow& window);

private:
	std::string m_mapName;
	Vector2 m_spawnPoint;
	Vector2 m_size;

	void loadMap(std::string mapName);
};

