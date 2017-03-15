#include "stdafx.h"
#include "Rectangle.h"


Rectangle::Rectangle()
{
}


Rectangle::Rectangle(int x, int y, int width, int height) :
	m_x(x),
	m_y(y),
	m_width(width),
	m_height(height)
{

}

const Vector2 Rectangle::getCenter() const {
	return Vector2(m_x + m_width / 2, m_y + m_height / 2);
}

const int Rectangle::getLeft() const
{
	return m_x;
}

const int Rectangle::getRight() const
{
	return m_x + m_width;
}

const int Rectangle::getTop() const
{
	return m_y;
}

const int Rectangle::getBottom() const
{
	return m_y + m_height;
}

const int Rectangle::getWidth() const
{
	return m_width;
}

const int Rectangle::getHeight() const
{
	return m_height;
}

const int Rectangle::getSide(sides::Side side) const
{
	return 
		side == sides::LEFT ? getLeft() :
		side == sides::RIGHT ? getRight() :
		side == sides::TOP ? getTop() :
		side == sides::BOTTOM ? getBottom() :
		sides::NONE;
}

const bool Rectangle::colledesWith(const Rectangle & other) const
{
	return 
		getRight() >= other.getLeft() &&
		getLeft() <= other.getRight() &&
		getTop() <= other.getBottom() &&
		getBottom() >= other.getTop();
}

const bool Rectangle::isValidRectangle() const
{
	return (m_x >= 0 && m_y >= 0 && m_width >= 0 && m_height >= 0);
}

