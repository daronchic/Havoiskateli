#include "stdafx.h"
#include "MSprite.h"

MSprite::MSprite()
{}

MSprite::MSprite(const std::string &filename, int sourceX, int sourceY, int width, int height, int posX, int posY)
{
	m_texture = new sf::Texture();
	m_image.loadFromFile(filename);
	if (!m_texture->loadFromFile(filename, sf::IntRect(sourceX, sourceY, width, height)))
	{
		std::cout << "Can't load texture!";
	}
	else {
		this->setTexture(*m_texture);
		this->setPosition(posX, posY);
	}
}
