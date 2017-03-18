#pragma once
#include "SFML/Graphics.hpp"
#include "Rectangle.h"
#include "Globals.h"

#include <iostream>

class MSprite :
	public sf::Sprite
{
public: 
	MSprite();
	MSprite(const std::string &filename, int sourceX, int sourceY, int width, int height, int posX, int posY);
	void update(int elapsedTime);
	const Rectangle getCollisonBox() const;
	const sides::Side getCollisionSide(const Rectangle &other) const;
protected:
	sf::Image m_image;
	Rectangle m_boundingBox;
private:
	sf::Texture* m_texture;

};

