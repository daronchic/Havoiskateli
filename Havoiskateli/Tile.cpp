#include "stdafx.h"
#include "Tile.h"


Tile::Tile()
{
}

Tile::Tile(sf::Image* tileset, Vector2 size, Vector2 tilesetPosition, Vector2 position) :
	m_tileset(tileset),
	m_size(size),
	m_tilesetPosition(tilesetPosition),
	m_position(position)
{
	sf::Texture* texture = new sf::Texture();
	texture->loadFromImage(*m_tileset, sf::IntRect(tilesetPosition.x, tilesetPosition.y, size.x, size.y));
	m_sprite.setTexture(*texture);
	m_sprite.setPosition(position.x, position.y);
}

Tile::~Tile()
{
}

void Tile::update(int elapsedTime)
{

}

void Tile::draw(sf::RenderTexture &window)
{
	window.draw(m_sprite);
}