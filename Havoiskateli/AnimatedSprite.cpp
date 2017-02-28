#include "stdafx.h"
#include "AnimatedSprite.h"
#include <SFML\Graphics.hpp>


AnimatedSprite::AnimatedSprite()
{
}

AnimatedSprite::AnimatedSprite(const std::string &filename, int sourceX, int sourceY, int width, int height,
	float posX, float posY, float timeToUpdate) :
	MSprite(filename, sourceX, sourceY, width, height, posX, posY),
	m_frameIndex(0),
	m_timeToUpdate(timeToUpdate),
	m_visible(false),
	m_currentAnimationOnce(false),
	m_currentAnimation("") {

}

AnimatedSprite::~AnimatedSprite()
{
}

void AnimatedSprite::addAnimation(int frames, int x, int y, std::string name, int width, int height, Vector2 offset)
{
	std::vector<sf::Texture*> rectangles;
	for (int i = 0; i < frames; i++)
	{
		sf::Texture* texture = new sf::Texture();
		texture->loadFromImage(this->m_image, sf::IntRect((x + i) * width, y, width, height));
		rectangles.push_back(texture);
	}
	this->m_animation.insert(std::pair<std::string, std::vector<sf::Texture*> >(name, rectangles));
	this->m_offsets.insert(std::pair<std::string, Vector2>(name, offset));
}

void AnimatedSprite::resetAnimations()
{
	this->m_animation.clear();
	this->m_offsets.clear();
}

void AnimatedSprite::playAnimation(const std::string &animation, bool once)
{
	this->m_currentAnimationOnce = once;
	if (this->m_currentAnimation != animation) {
		this->m_currentAnimation = animation;
		this->m_frameIndex = 0;
	}
}

void AnimatedSprite::setVisible(bool visible) 
{
	this->m_visible = visible;
}

void AnimatedSprite::stopAnimation()
{
	this->m_frameIndex = 0;
	this->animationDone(this->m_currentAnimation);
}

void AnimatedSprite::update(int elapsedTime)
{
	this->m_timeElapsed += elapsedTime;
	if (this->m_timeElapsed > this->m_timeToUpdate) {
		if (this->m_frameIndex < this->m_animation[this->m_currentAnimation].size() - 1) {
			this->setTexture(*this->m_animation[this->m_currentAnimation].at(this->m_frameIndex));
			this->m_frameIndex++;
			this->m_timeElapsed = 0;
		}
		else {
			if (this->m_currentAnimationOnce == true) {
				this->setVisible(false);
			}
			this->m_frameIndex = 0;
			this->animationDone(this->m_currentAnimation);
		}
	}
	
}

void AnimatedSprite::animationDone(std::string animation)
{
}

/*void AnimatedSprite::setupAnimation()
{
	addAnimation(9, 0, 0, "stay", 32, 32, Vector2(0, 0));
	addAnimation(6, 0, 32, "sleep", 32, 32, Vector2(0, 0));
}*/





