#pragma once

#include "MSprite.h"

#include <iostream>
#include <map>
#include <vector>
#include <string>

class AnimatedSprite : public MSprite
{
public:
	AnimatedSprite();
	AnimatedSprite(const std::string &filename, int sourceX, int sourceY, int width, int height, 
		float posX, float posY, float timeToUpdate);
	void playAnimation(const std::string &animation, bool once = false);
	void update(int elapsedTime);

	~AnimatedSprite();

protected:
	double m_timeToUpdate;
	bool m_currentAnimationOnce;
	std::string m_currentAnimation;

	void addAnimation(int frames, int x, int y, std::string name, int width, int height, Vector2 offset);

	void resetAnimations();

	void stopAnimation();

	void setVisible(bool visible);

	virtual void animationDone(std::string currentAnimation) = 0;

	virtual void setupAnimations() = 0;

private:
	std::map<std::string, std::vector<sf::Texture*> > m_animation;
	std::map<std::string, Vector2> m_offsets;
	int m_frameIndex;
	double m_timeElapsed;
	bool m_visible;
};

