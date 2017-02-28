#pragma once

#include "Globals.h"
#include "AnimatedSprite.h"

#include <string>

class Player : public AnimatedSprite
{
public:
	Player();
	Player(std::string playerName, float x, float y, float satiety, int lifes);
	~Player();

	void update(float elapsedTime);
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
	void stopMoving();
	virtual void animationDone(std::string currentAnimation);
	virtual void setupAnimations();

private:
	float m_satiety;
	int m_lifes;
	float m_dx, m_dy;
	Direction m_facing;
	PlayerState m_state;
};

