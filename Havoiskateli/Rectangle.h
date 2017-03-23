#pragma once

#include "Globals.h"

class Rectangle
{
public:
	Rectangle();
	Rectangle(int x, int y, int width, int height);
	const Vector2 getCenter() const;
	const int getLeft() const;
	const int getRight() const;
	const int getTop() const;
	const int getBottom() const;

	const int getWidth() const;
	const int getHeight() const;

	const int getSide(sides::Side side) const;
	const bool colledesWith(const Rectangle &other) const;

	const bool isValidRectangle() const;

	void setPosition(int x, int y);

private:
	int m_x, m_y, m_width, m_height;
};

