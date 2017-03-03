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
	texture->loadFromImage(*m_tileset, sf::IntRect(m_tilesetPosition.x, m_tilesetPosition.y, m_size.x, m_size.y));
	m_sprite.setTexture(*texture);
	m_sprite.setPosition(m_position.x, m_position.y);
}

Tile::~Tile()
{
}

void Tile::update(int elapsedTime)
{

}

void Tile::draw(sf::RenderWindow &window)
{
	window.draw(m_sprite);
}