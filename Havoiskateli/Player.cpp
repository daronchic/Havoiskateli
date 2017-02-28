#include "stdafx.h"
#include "Player.h"


Player::Player()
{
}

Player::Player(std::string playerName, float x, float y, float satiety, int lifes) :
	AnimatedSprite("E:/Havoiskateli/images/player/" + playerName + ".png", 0, 0, 32, 32, x, y, 1000),
	m_satiety(satiety),
	m_lifes(lifes)
{
	setupAnimations();
	playAnimation("stay");
	m_state = STAY;
}

void Player::setupAnimations()
{
	addAnimation(9, 0, 0, "walk", 32, 32, Vector2(0, 0));
	addAnimation(6, 0, 32, "sleep", 32, 32, Vector2(0, 0));
	addAnimation(7, 0, 64, "stay", 32, 32, Vector2(0, 0));
}

void Player::moveRight()
{
}

void Player::moveUp()
{
}

void Player::moveDown()
{
}

void Player::stopMoving()
{
}

void Player::animationDone(std::string currentAnimation) {}

void Player::update(float elapsedTime)
{
	AnimatedSprite::update(elapsedTime);
	switch (m_state)
	{
	case STAY:
		playAnimation("stay");
		break;
	case WALK:
		playAnimation("walk");
		break;
	case SLEEP:
		playAnimation("sleep");
		break;
	default:
		break;
	}
}

void Player::moveLeft()
{
}

Player::~Player()
{
}
