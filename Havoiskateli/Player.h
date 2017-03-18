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
	void moveLeft(bool walking);
	void moveRight(bool walking);
	void moveUp(bool walking);
	void moveDown(bool walking);
	void stopMovingRL();
	void stopMovingUD();
	void stopMoving();
	virtual void animationDone(std::string currentAnimation);
	virtual void setupAnimations();
	void handleTileCollisons(std::vector<Rectangle> &others);
	
private:
	float m_satiety;
	float m_sleepTime{ 0 };
	int m_lifes;
	float m_dx, m_dy;
	bool m_isMoving{ false };
	Direction m_facing;
	PlayerState m_state;
};

