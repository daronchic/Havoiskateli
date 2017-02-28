#pragma once
#include "SFML/Graphics.hpp"

#include <iostream>

class MSprite :
	public sf::Sprite
{
public: 
	MSprite();
	MSprite(const std::string &filename, int sourceX, int sourceY, int width, int height, int posX, int posY);
protected:
	sf::Image m_image;

private:
	sf::Texture* m_texture;
};

