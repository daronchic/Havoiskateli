#include "stdafx.h"
#include "AnimatedObject.h"

AnimatedObject::AnimatedObject()
{
}

AnimatedObject::AnimatedObject(sf::Image image, float x, float y) :
	AnimatedSprite(image, 0, 0, 32, 32, x, y, 1000)
{
	setupAnimations();
	playAnimation("stay");
}

void AnimatedObject::setupAnimations()
{
	addAnimation(2, 0, 0, "stay", 32, 32, Vector2(0, 0));
	addAnimation(20, 32, 0, "move", 32, 32, Vector2(0, 0));
}

void AnimatedObject::animationDone(std::string currentAnimation) {}

void AnimatedObject::changeState(bool state)
{
	m_isMoving = state;
}

void AnimatedObject::update(float elapsedTime)
{
	MSprite::update(elapsedTime);
	AnimatedSprite::update(elapsedTime);

	if (!m_isMoving) {
		playAnimation("stay");
	}
	else {
		playAnimation("move");
	}
}

AnimatedObject::~AnimatedObject()
{
}
