#include "stdafx.h"
#include "Level.h"
#include "tinyxml2.h"


Level::Level()
{
}

Level::Level(std::string mapName, Vector2 spawnPoint) :
	m_mapName(mapName),
	m_spawnPoint(spawnPoint),
	m_size(Vector2(0,0))
{
	this->loadMap(mapName);
}


Level::~Level()
{
}

void Level::loadMap(std::string mapName)
{

}

void Level::update(float elapsedTime)
{

}

void Level::draw(sf::RenderWindow &window)
{

}
