#include "stdafx.h"
#include "HUD.h"


HUD::HUD()
{
}

HUD::HUD(int x, int y) :
	m_x(x),
	m_y(y),
	m_opened(false)
{
	CLOSED_POSITION = Vector2(m_x, m_y);
}

void HUD::load()
{
	m_panel = MSprite("content/images/HUD/HUD_Panel.png", 0, 0, 280, 180, m_x, m_y);
	m_playerData = MSprite("content/images/HUD/HUD_playerData.png", 0, 0, 160, 40, m_x, m_y);
	m_inventoryBlock = MSprite("content/images/HUD/HUD_inventory.png", 0, 0, 40, 40, m_x, m_y);
	m_additionalBlock = MSprite("content/images/HUD/HUD_additionalBoxes.png", 0, 0, 40, 40, m_x, m_y);
	m_life = MSprite("content/images/HUD/HUD_life.png", 0, 0, 14, 14, m_x, m_y);
}

void HUD::initialize(int lifes)
{
	OPENED_POSITION = Vector2(CLOSED_POSITION.x - 102, CLOSED_POSITION.y - 125);
	m_panel.setPosition(m_x, m_y);
	m_playerData.setPosition(m_x + 18, m_y + 15);
	m_additionalBox.push_back(MSprite(m_additionalBlock));
	m_additionalBox.push_back(MSprite(m_additionalBlock));
	m_additionalBox.push_back(MSprite(m_additionalBlock));
	m_lifes = lifes;
	for (int i = 0; i < lifes; i++) {
		m_lifeBox.push_back(MSprite(m_life));
	}
	m_satiety = 1.0f;
}

void HUD::update(int elapsedTime)
{
	m_panel.setPosition(m_x, m_y);
	m_playerData.setPosition(m_x + 18, m_y + 15);
	for (int i = 0; i < 3; i++) {
		m_additionalBox.at(i).setPosition(m_x + 210, m_y + 15 + i * 50);
	}
	for (int i = 0; i < m_lifes; i++) {
		m_lifeBox.at(i).setPosition(m_x + 60 + i * 16, m_y + 20);
	}
	if (m_opened) {
		open(elapsedTime);
	}
	else {
		close(elapsedTime);
	}
}

void HUD::draw(sf::RenderWindow & window)
{
	window.draw(m_panel);
	window.draw(m_playerData);
	for (int i = 0; i < 3; i++) {
		window.draw(m_additionalBox.at(i));
	}
	for (int i = 0; i < m_lifes; i++) {
		window.draw(m_lifeBox.at(i));
	}
}

void HUD::changeState()
{
	std::cout << "Boop " << m_opened << std::endl;
	m_opened = !m_opened;
}

void HUD::open(int elapsedTime)
{
	if (m_x > OPENED_POSITION.x) {
		m_x -= 0.05f * elapsedTime;
	}
	if (m_y > OPENED_POSITION.y) {
		m_y -= 0.05f * elapsedTime;
	}
}

void HUD::close(int elapsedTime)
{
	if (m_x < CLOSED_POSITION.x) {
		m_x += 0.05f * elapsedTime;
	}
	if (m_y < CLOSED_POSITION.y) {
		m_y += 0.05f * elapsedTime;
	}
}
