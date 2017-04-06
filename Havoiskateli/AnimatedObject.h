#pragma once
#include "AnimatedSprite.h"
class AnimatedObject :
	public AnimatedSprite
{
public:
	AnimatedObject();
	AnimatedObject(sf::Image image, float x, float y);
	~AnimatedObject();

	void update(float elapsedTime);
	void changeState(bool state);
	virtual void animationDone(std::string currentAnimation);
	virtual void setupAnimations();
private:
	bool m_isMoving{ false };
};

