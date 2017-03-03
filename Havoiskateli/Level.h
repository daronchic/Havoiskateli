#pragma once

#include "Globals.h"
#include "Tile.h"

#include <string>
#include <vector>

#include <SFML\Graphics.hpp>

struct Tileset;

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
	Vector2 m_tileSize;

	std::vector<Tile> m_tileList;
	std::vector<Tileset> m_tilesets;

	void loadMap(std::string mapName);
};

struct Tileset {
	sf::Image* Image;
	int FirstGid;
	Tileset() {
		this->FirstGid = -1;
	}

	Tileset(sf::Image* image, int firstGid) {
		this->Image = image;
		this->FirstGid = firstGid;
	}
};