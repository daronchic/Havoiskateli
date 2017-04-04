#include "stdafx.h"
#include "Player.h"

namespace player_constants{
	const float WALK_SPEED = 0.02f;
	const int SLEEP_TIME = 5000;
}


Player::Player()
{
}

Player::Player(sf::Image image, float x, float y, float satiety, int lifes) :
	AnimatedSprite(image, 0, 0, 32, 32, x, y, 1000),
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

void Player::handleTileCollisons(std::vector<Rectangle>& others)
{
	for each (auto other in others)
	{
		sides::Side collisionSide = MSprite::getCollisionSide(other);
		if (collisionSide != sides::NONE) {
			switch (collisionSide) {
			case sides::TOP:
				this->setPosition(this->getPosition().x, other.getBottom() + 1);
				this->m_dy = 0;
				break;

			case sides::BOTTOM:
				this->setPosition(this->getPosition().x, other.getTop() - m_boundingBox.getHeight() - 1);
				this->m_dy = 0;
				break;
			case sides::LEFT:
				this->setPosition(other.getRight() + 1, this->getPosition().y);
				this->m_dx = 0;
				break;
			case sides::RIGHT:
				this->setPosition(other.getLeft() - m_boundingBox.getWidth() - 1, this->getPosition().y);
				this->m_dx = 0;
				break;
			}
		}
	}
}

int Player::getLifes()
{
	return m_lifes;
}

void Player::moveRight(bool walking)
{
	if(walking) this->m_dx = player_constants::WALK_SPEED;
	m_state = WALK;
	m_facing = RIGHT;
	m_sleepTime = 0;
	m_isMoving = true;
}

void Player::moveLeft(bool walking)
{
	if (walking) this->m_dx = -player_constants::WALK_SPEED;
	m_state = WALK;
	m_facing = LEFT;
	m_sleepTime = 0;
	m_isMoving = true;
}

void Player::moveUp(bool walking)
{
	if (walking) this->m_dy = -player_constants::WALK_SPEED;
	m_state = WALK;
	m_facing = UP;
	m_sleepTime = 0;
	m_isMoving = true;
}

void Player::moveDown(bool walking)
{
	if (walking) this->m_dy = player_constants::WALK_SPEED;
	m_state = WALK;
	m_facing = DOWN;
	m_sleepTime = 0;
	m_isMoving = true;
}

void Player::stopHorizontalMoving()
{
	m_dx = 0.0f;
}

void Player::stopVerticalMoving()
{
	m_dy = 0.0f;
}

void Player::stopMoving()
{
	this->m_isMoving = false;
}

void Player::animationDone(std::string currentAnimation) {}

void Player::update(float elapsedTime)
{
	MSprite::update(elapsedTime);
	AnimatedSprite::update(elapsedTime);
	this->move(this->m_dx * elapsedTime, this->m_dy * elapsedTime);
	if (!m_isMoving) {
		m_state = STAY;
		this->m_sleepTime++;
	}
	if (m_isMoving) {
		m_state = WALK;
	}
	if (m_sleepTime > player_constants::SLEEP_TIME) {
		m_state = SLEEP;
	}
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

Player::~Player()
{
}
