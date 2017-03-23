#pragma once

#include "MSprite.h"

#include <SFML/Graphics.hpp>

class Tile
{
public:
	Tile();
	Tile(sf::Image* tileset, Vector2 size, Vector2 tilesetPosition, Vector2 position);
	~Tile();
	void update(int elapsedTime);
	void draw(sf::RenderTexture &window);

private:
	sf::Image* m_tileset;
	MSprite m_sprite;
	Vector2 m_size;
	Vector2 m_tilesetPosition;
	Vector2 m_position;
};

