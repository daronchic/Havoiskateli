#include "stdafx.h"
#include "StartingState.h"
#include "ResourceManager.h"
#include "AudioManager.h"
#include "Globals.h"

#include <fstream>

struct PlayerData {
	std::string playerName;
	int lifes, inventory;
	sf::String description;

	PlayerData() {}
	PlayerData(int lifes, int inventory, const sf::String &description) :
		lifes(lifes), inventory(inventory), description(description) {}
	void setPlayerName(const std::string &name)
	{
		playerName = name;
	}
};

static inline std::string convertToString(int value);

StartingState::StartingState() : State()
{
}

StartingState::StartingState(sf::RenderWindow &window) : State(window), m_gui(window)
{
}


StartingState::~StartingState()
{
	for each (auto stands in m_playerStands)
	{
		delete stands;
	}
	for each (auto players in m_players)
	{
		delete players;
	}
	m_players.clear();
	m_playerStands.clear();
	m_gui.removeAllWidgets();
}

StateCode StartingState::complete()
{
	if (m_stateCode != StateCode::NONE) {
		m_window->setMouseCursorVisible(false);
	}
	return m_stateCode;
}

void StartingState::saveProfile(const std::string & playerName, int playerNumber)
{
	std::fstream ifs;
	ifs.open("content/profiles/current_profile.prof", std::fstream::binary | std::fstream::out);

	if (ifs.is_open()) {
		ifs << playerName << '\n';
		ifs << playerNumber;
	}
}

void StartingState::load()
{
	m_bigStand = MSprite(*ResourceManager::getInstance()->getImage(Images::menu_StartingWindow), 0, 0, 407, 111, 0, 0);
	for (int i = 0; i < 6; i++) {
		m_playerStands.emplace_back(new AnimatedObject(*ResourceManager::getInstance()->getImage(Images::menu_stand), 0, 0));
	}
	m_players.emplace_back(new Player(*ResourceManager::getInstance()->getImage(Images::player_1), 0, 0, 0, 0));
	m_playerData.emplace_back(PlayerData(3, 3, L"description of orange yam yam. \nHe is as regular as his developer, \nvery weak, not really smart \nand very hungry, \nGood luck, dude xD"));
	m_players.emplace_back(new Player(*ResourceManager::getInstance()->getImage(Images::player_2), 0, 0, 0, 0));
	m_playerData.emplace_back(PlayerData(3, 4, L"description of dark yam yam. \nThis dude is really serious men, \nHe looks like night, like darkness! \nHis inventory is very spacious!"));
	m_players.emplace_back(new Player(*ResourceManager::getInstance()->getImage(Images::player_3), 0, 0, 0, 0));
	m_playerData.emplace_back(PlayerData(3, 3, L"description of green yam yam. \nDudes, this is your chance! \nAs you can see - he is green! \nLike grass or... green sky.. \nwhatever"));
	m_players.emplace_back(new Player(*ResourceManager::getInstance()->getImage(Images::player_4), 0, 0, 0, 0));
	m_playerData.emplace_back(PlayerData(3, 3, L"description of blue yam yam. \nIm not sure, but I think that guy \ncan swim or, actually he \ncould stay alive in water \nor else..."));
	m_players.emplace_back(new Player(*ResourceManager::getInstance()->getImage(Images::player_1), 0, 0, 0, 0));
	m_playerData.emplace_back(PlayerData(3, 3, L"description of ... yam yam?\n Who is this guy? I dont know, \nhe looks like regular, but \nhe just stole his sprite"));
	m_players.emplace_back(new Player(*ResourceManager::getInstance()->getImage(Images::player_2), 0, 0, 0, 0));
	m_playerData.emplace_back(PlayerData(6, 5, L"description of ... yam yam? \nit will be super kitten! \nReally! With pair of ears \nand, you know, as hungry \nas real cat!"));

}

void StartingState::init()
{
	m_window->setMouseCursorVisible(true);
	m_switchedY = m_window->getSize().y / 4 - 47;
	m_bigStand.setPosition(m_window->getSize().x / 2 - m_bigStand.getLocalBounds().width / 2, m_window->getSize().y / 4);
	for (int i = 0; i < 6; i++) {
		m_playerStands[i]->setPosition(m_window->getSize().x / 2 - 3 * 55 + i * 55, m_window->getSize().y / 4);
	}
	for (int i = 0; i < 6; i++) {
		m_players[i]->setPosition(m_window->getSize().x / 2 - 3 * 55 + i * 55, m_window->getSize().y / 4 - 15);
	}
	m_descriptionRect = sf::RectangleShape(sf::Vector2f(m_window->getSize().x / 2, m_window->getSize().y / 2));
	m_descriptionRect.setPosition(m_window->getSize().x / 2-m_descriptionRect.getSize().x / 2, m_window->getSize().y / 2);
	m_descriptionRect.setFillColor(sf::Color(128, 109, 176, 217));

	m_descriptionString = "Player name- %1\nHP- %2\nInventory capacity- %3 \n\nDescription- %4";
	m_descriptionText.setFont(*ResourceManager::getInstance()->getFont(Fonts::menuFont));
	m_descriptionText.setPosition(m_descriptionRect.getPosition().x + 10, m_descriptionRect.getPosition().y + 10);

	tgui::EditBox::Ptr nameBox = tgui::EditBox::create();
	//nameBox->setSize(100, 25);
	nameBox->setPosition(m_descriptionRect.getPosition().x + 100 + nameBox->getSize().x, m_descriptionRect.getPosition().y + nameBox->getSize().y / 2);
	nameBox->focus();
	m_gui.add(nameBox, "nameBox");
}

void StartingState::handleInput(sf::Event & event)
{
	m_gui.handleEvent(event);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		AudioManager::instance()->playSound(Sounds::button_pressed, true);
		m_stateCode = StateCode::MENU;
	}
	if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Return) {
		AudioManager::instance()->playSound(Sounds::player_switched, true);
		tgui::EditBox::Ptr nameBox = m_gui.get<tgui::EditBox>("nameBox");
		saveProfile(nameBox->getText(), m_switched);
		m_stateCode = StateCode::NEXT;
	}
	if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Left) {
		m_switched--;
		m_descriptionString = "Player name- %1\nHP- %2\nInventory capacity- %3 \n\nDescription- %4";
		AudioManager::instance()->playSound(Sounds::player_changed, true);
	}
	else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Right) {
		m_switched++;
		m_descriptionString = "Player name- %1\nHP- %2\nInventory capacity- %3 \n\nDescription- %4";
		AudioManager::instance()->playSound(Sounds::player_changed, true);
	}
}

void StartingState::update(float elapsed)
{
	if (m_switched > 5)
		m_switched = 0;
	else if (m_switched < 0)
		m_switched = 5;
	for (int i = 0; i < m_playerStands.size(); i++)
	{
		m_playerStands[i]->update(elapsed);
		m_players[i]->update(elapsed);
		setPlayerData();
		if (i == m_switched) {
			m_playerStands[i]->changeState(true);
			if (m_players[i]->getPosition().y > m_switchedY) {
				m_players[i]->moveUp(true);
			}
			else {
				m_players[i]->stopVerticalMoving();
			}
		}
		else {
			m_playerStands[i]->changeState(false);
			if (m_players[i]->getPosition().y < m_switchedY + 32) {
				m_players[i]->moveDown(true);
			}
			else {
				m_players[i]->stopVerticalMoving();
			}
		}
	}
}

void StartingState::draw()
{
	m_window->clear(sf::Color(86, 86, 124));
	m_window->draw(m_bigStand);
	for each (auto stands in m_playerStands)
	{
		m_window->draw(*stands);
	}
	for each (auto players in m_players)
	{
		m_window->draw(*players);
	}
	m_window->draw(m_descriptionRect);
	m_window->draw(m_descriptionText);
	m_gui.draw();
}

void StartingState::setPlayerData()
{
	m_descriptionString.replace("%1", m_playerData[m_switched].playerName);
	m_descriptionString.replace("%2", convertToString(m_playerData[m_switched].lifes));
	m_descriptionString.replace("%3", convertToString(m_playerData[m_switched].inventory));
	m_descriptionString.replace("%4", m_playerData[m_switched].description);
	m_descriptionText.setString(m_descriptionString);
}

static std::string convertToString(int value)
{
	std::stringstream strBuf;
	strBuf << value;
	return strBuf.str();
}
