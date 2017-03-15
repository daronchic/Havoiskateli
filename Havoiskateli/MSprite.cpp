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

	m_boundingBox = Rectangle(this->getPosition().x, this->getPosition().y, width, height);
}

void MSprite::update(int elapsedTime)
{
	m_boundingBox = Rectangle(this->getPosition().x, this->getPosition().y, this->getTexture()->getSize.x, this->getTexture()->getSize.y);
}

const Rectangle MSprite::getCollisonBox() const
{
	return m_boundingBox;
}

const sides::Side MSprite::getCollisionSide(const Rectangle & other) const
{
	int amtLeft, amtRight, amrUp, amtDown;

	return sides::Side();
}
